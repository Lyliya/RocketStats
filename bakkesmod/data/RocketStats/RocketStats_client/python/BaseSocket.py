from abc import abstractmethod
from json import loads as load_json
from threading import Thread
from time import sleep
from typing import Optional, Tuple

from obswebsocket import obsws
from obswebsocket.exceptions import ConnectionFailure
from obswebsocket.requests import GetSceneItemProperties, SetSceneItemProperties
from websocket import WebSocket

from config import Config
from RocketStatsEvent import RocketStatsEvent


class BaseSocket:
    """Base class to implement RS and OBS websockets"""
    _url: str
    _ws: WebSocket
    _obsws: obsws = None

    @property
    def is_rs_connected(self) -> bool:
        """Return True if RocketStats websocket is connected"""
        return self._ws.connected

    @property
    def is_obs_connected(self) -> bool:
        """Return True if OBS websocket is connected"""
        return self._obsws is not None

    def __init__(self, url: str):
        self._url = url
        self._ws = WebSocket()

    @abstractmethod
    def on_open(self):
        """Called when a websocket connection is established"""
        pass

    @abstractmethod
    def on_close(self):
        """Called when a websocket connection is closed"""
        pass

    @abstractmethod
    def on_error(self, error: Exception):
        """Called when an error occurs"""
        pass

    @abstractmethod
    def on_message(self, event: RocketStatsEvent):
        """Called when the RS websocket received an event"""
        pass

    def connect(self, dispatch_error: bool = True) -> Optional[Tuple[bool, bool]]:
        """
        Return True if connection succeed, False otherwise, None if dispatch_error is True (error is raised)
        First boolean is for the RocketStats websocket
        Second boolean is for ths OBS websocket
        """
        # RS websocket
        try:
            self._ws.connect(self._url)
            self._ws.timeout = Config.timeout
        except Exception as e:
            if dispatch_error:
                self.on_error(e)
                return False, False
            else:
                raise e
        else:
            self.on_open()

        if not Config.enable_obs:
            return True, False

        # OBS websocket
        try:
            ws = obsws(*Config.OBS)
            ws.connect()
        except ConnectionFailure as e:
            if dispatch_error:
                self.on_error(e)
                return True, False
            else:
                raise e
        else:
            self._obsws = ws
            return True, True

    def close(self):
        """Close the opened websocket"""
        self._ws.close()
        self._ws = WebSocket()

        if Config.enable_obs and self.is_obs_connected:
            self._obsws.disconnect()

        self.on_close()

    def display_obs_source(self, source_name: str, scene_name: str = None, duration: int = None):
        """
        Make the source visible in your OBS scene

        Args:
        source_name: Name of the source to show
        scene_name: Name of the scene where to look for source (defaults to current one)
        duration: Hid the source after {timeout} seconds if specified
        """
        if not (Config.enable_obs and self.is_obs_connected):
            return

        def callback(src, scene, dur):
            # get source to display
            item = self._obsws.call(GetSceneItemProperties(src, scene_name=scene))

            # make it visible
            self._obsws.call(SetSceneItemProperties(item.datain, scene_name=scene, visible=True))

            if dur:
                sleep(dur)

                # hid it back again
                self._obsws.call(SetSceneItemProperties(item.datain, scene_name=scene, visible=False))

        Thread(target=callback, args=(source_name, scene_name, duration)).start()

    def send(self, data: str):
        """Send message to RS websocket"""
        if self.is_rs_connected:
            self._ws.send(data)

    def receive(self) -> Optional[RocketStatsEvent]:
        """Receive event from RS websocket"""
        if not self.is_rs_connected:
            return None

        try:
            raw_payload = self._ws.recv()
            json_payload = load_json(raw_payload)
        except Exception as e:
            self.on_error(e)
            return None

        return RocketStatsEvent(**json_payload)

    def send_then_receive(self, data: str) -> Optional[RocketStatsEvent]:
        """Send data and receive the response"""
        self.send(data)
        return self.receive()
