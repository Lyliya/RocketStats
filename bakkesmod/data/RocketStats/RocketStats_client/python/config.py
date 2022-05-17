class Config:
    # RocketStats websocket URL
    url = "ws://localhost:8085/"
    # ws timeout
    timeout = 2

    # should try to connect to OBS
    enable_obs = False
    # OBS websocket config
    OBS_HOST = "localhost"
    OBS_PORT = 4444
    OBS_PWD = ""
    OBS = (OBS_HOST, OBS_PORT, OBS_PWD)

    # should debug event when received
    debug: bool = True
    # amount to sleep before retrying (if not connected after every timeout, program will exit)
    reconnect_timeouts = [5, 5, 10, 20] + [30]*3
