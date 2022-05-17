from json import JSONDecodeError
from time import sleep

from obswebsocket.exceptions import ConnectionFailure
from websocket import WebSocketTimeoutException, WebSocketConnectionClosedException, WebSocketAddressException

from BaseSocket import BaseSocket
from RocketStatsEvent import RocketStatsEvent
from config import Config


class SampleSocket(BaseSocket):
    """Sample websocket that implements BaseSocket"""
    def __init__(self):
        super().__init__(Config.url)

    def on_open(self):
        if Config.debug:
            print("Connected!")

    def on_close(self):
        if Config.debug:
            print("Disconnected!")

    def on_error(self, error):
        # RS websocket connection errors
        if isinstance(error, ValueError):
            # Invalid address
            print("Invalid address, make sure the url is a valid websocket url (url should start with ws://)")

        elif isinstance(error, WebSocketAddressException):
            # Address is valid but the host can't be resolved
            print("Unable to resolve url, check spelling of the host")

        elif isinstance(error, ConnectionRefusedError):
            # Address was valid but the connection can't be established
            print("Can't connect to websocket, check that RocketStats is running")

        # OBS websocket connection errors
        elif isinstance(error, ConnectionFailure):
            # Can't connect to OBS websocket
            print("Can't connect to OBS, check that OBS is up and running")

        # Runtime errors
        elif isinstance(error, WebSocketTimeoutException):
            print("Nothing to receive")

        elif isinstance(error, JSONDecodeError):
            print("Can't decode JSON payload, invalid response")

        elif isinstance(error, WebSocketConnectionClosedException):
            print("Remote connection was closed! Trying to reconnect...")
            self.close()

        elif isinstance(error, OSError):
            error_code = error.errno
            if error_code == 10054:
                print("")
            else:
                print(f"OSError:"
                      f"    Code: {error_code}"
                      f"    Message: {error.strerror}")

        else:
            print("Unhandled Error!")
            print(f"{type(error)}: {error}")

    def on_message(self, event: RocketStatsEvent):
        if event is None:
            return

        if Config.debug:
            print(event)

        # TODO: Handle events here
        if event.data == "Disconnected":
            self.close()
        elif Config.enable_obs:
            if event.type == "GameWon":
                self.display_obs_source("Win", "Rocket League", 3)
            elif event.type == "GameLost":
                self.display_obs_source("Loss", "Rocket League", 3)

    def mainloop(self):
        """Main event loop which dispatches messages and connection errors"""
        while True:
            if not self.is_rs_connected:
                if not self.reconnect():
                    # Quit mainloop if websocket can't be reconnected
                    return

            self.on_message(self.receive())

            sleep(1)

    def reconnect(self) -> bool:
        """Try to reconnect to RS websocket"""
        for to in Config.reconnect_timeouts:
            print(f"Trying to reconnect in {to} seconds...")
            sleep(to)
            rs_status, obs_status = self.connect()
            if not rs_status:
                # Can't connect to RS
                pass
            elif Config.enable_obs and not obs_status:
                # Can't connect to OBS
                pass
            else:
                # Connected!
                print("Succesfully reconnected!")
                return True
        else:
            print("Unable to reconnect to RocketStats. Exiting...")
            return False


if __name__ == '__main__':
    socket = SampleSocket()
    socket.connect()
    try:
        socket.mainloop()
    except KeyboardInterrupt:
        socket.close()
