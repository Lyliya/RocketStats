import rel
import json
import websocket

from RocketStatsEvent import RocketStatsEvent


class RocketStatsSocket:
    _socket: websocket.WebSocket

    url = 'ws://localhost:8085'

    errors = 0b11
    is_connected = False

    # Whether to log events to the console or not
    debug = True

    def __init__(self):
        # create a websocket connection
        self._socket = websocket.WebSocketApp(
            self.url,
            on_open = self._on_open,
            on_message = self._on_message,
            on_error = self._on_error,
            on_close = self._on_close
        )

    def send(self, data: str):
        """Send data to the socket"""

        if self.is_connected:
            self._socket.send(data)

    def _on_open(self, ws):
        """Called when the socket is connected"""

        self.is_connected = True
        self.errors = 0b00
        if self.debug:
            print('Connected')

    def _on_message(self, ws, msg):
        """Called when a message is received from the socket"""

        # parse event as JSON
        try:
            data = json.loads(msg)
        except json.JSONDecodeError as e:
            self._on_error(e)
            return

        event = RocketStatsEvent(
            data['name'],
            data['type'],
            data['data'],
            data['states'],
            title = data['type']
        )

        if self.debug:
            print(event)

        if event.type == 'GameState':
            # Returns all stats
            self.on_game_state_event(event)

        elif event.type == 'StatEvent':
            # Returns stats (displayed in the middle)
            self.on_stat_event(event)

        elif event.type == 'TickerMessage':
            # Returns stats (displayed in the top right corner)
            self.on_ticker_message_event(event)

        elif event.type == 'Boost':
            # Returns current boost state (on / off)
            self.on_boost_event(event)

        elif event.type == 'Default':
            # ???
            self.on_default_event(event)

        else:
            if self.debug:
                print('Unknown event')

    def _on_close(self, ws, close_status_code, close_msg):
        """Called when the socket is closed"""

        if self.debug and not(self.errors & 0b01):
            print('Socket closed, try reconnect...')

        self.is_connected = False
        self.errors |= 0b01

    def _on_error(self, ws, error):
        """Called when an error occurs"""

        if self.debug and not(self.errors & 0b10):
            print('Socket error: {}'.format(error))

        self.errors |= 0b10

    def request_data(self):
        self.send('request')

    def on_game_state_event(self, event: RocketStatsEvent):
        # Do what you want here
        pass

    def on_stat_event(self, event: RocketStatsEvent):
        # Do what you want here
        pass

    def on_ticker_message_event(self, event: RocketStatsEvent):
        # Do what you want here
        pass

    def on_boost_event(self, event: RocketStatsEvent):
        # Do what you want here
        pass

    def on_default_event(self, event: RocketStatsEvent):
        # Do what you want here
        pass

    def mainloop(self):
        """Listen to socket events until the socket is closed"""
        self._socket.run_forever(dispatcher = rel)
        rel.signal(2, rel.abort)  # handle Keyboard Interrupt
        rel.dispatch()


if __name__ == '__main__':
    rs_socket = RocketStatsSocket()
    rs_socket.mainloop()
