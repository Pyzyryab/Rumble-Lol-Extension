### Uncomment the line below to make this code available to run as a Rumble AI extension
#from src.core.skill import Skill

import os
initial_dir = os.getcwd()

from python import main

name: list[str] = ['Rumble League Extension', 'Rumble League Extension']
description: str = 'The extension for voice control, analitics and game tracking for Rumble-AI'
tags: dict = {
    'tags': {
        'english': [ 'league', 'extension' ],
        'spanish': [ 'league', 'extension']
    }
}


class RumbleLeagueExtension(Skill):
    """
        Linker with the C++ library that contains the whole logic of the RLE
    """
    def __init__(self, name: str, description: str, tags: dict, id_language: int):
        self.name: list[str] = name
        self.description: str = description
        self.tags: list[str] = tags
        self.id_language: int = id_language

    def __str__(self) -> str:
        return self.name[ self.id_language - 1 ]

    def play(self, rumble, **kwargs) -> None:
        return rumble.talk(
            self.text_to_voice()
        )
