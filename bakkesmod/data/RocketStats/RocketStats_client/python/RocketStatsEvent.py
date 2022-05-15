import json

from typing import Union
from dataclasses import dataclass


@dataclass
class RocketStatsEvent:
    """Class to represent an event from the RocketStats websocket"""
    name: str
    type: str
    data: Union[str, dict]
    states: dict
    title: str = 'RocketStatsEvent'

    def __str__(self):
        tdata = '\n    '.join(json.dumps(self.data, indent = 4).split('\n'))
        tstates = '\n    '.join(json.dumps(self.states, indent = 4).split('\n'))

        return (
            f'\n{self.title}(\n'\
            f'    name = {self.name},\n'\
            f'    type = {self.type},\n'\
            f'    data = {tdata},\n'\
            f'    states = {tstates}\n'\
            f')'
        )
