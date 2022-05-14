from dataclasses import dataclass
from typing import Union

@dataclass
class RocketStatsEvent:
    """Class to represent an event from the RocketStats websocket"""
    name: str
    type: str
    data: Union[str, dict]
    states: dict

    def __str__(self):
        return f"RocketStatsEvent(name={self.name},\n"\
               f"                 type={self.type},\n"\
               f"                 states={self.states})\n"\
               f"data:\n{self.data}"
