from dataclasses import dataclass
from json import dumps as dump_json
from typing import Union


@dataclass
class RocketStatsEvent:
    """Class to represent an event from the RocketStats websocket"""
    name: str
    type: str
    data: Union[str, dict]
    states: dict

    def __str__(self):
        tdata = '\n           '.join(dump_json(self.data, indent=4).split('\n'))
        tstates = '\n             '.join(dump_json(self.states, indent=4).split('\n'))

        return (
            f'RocketStatsEvent(\n'
            f'    name = {self.name},\n'
            f'    type = {self.type},\n'
            f'    data = {tdata},\n'
            f'    states = {tstates}\n'
            f')'
        )
