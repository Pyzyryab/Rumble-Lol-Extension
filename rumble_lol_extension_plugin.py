from src.core.skill import Skill

name: list[str] = ['Rumble League Extension', 'Rumble League Extension']
description: str = 'The extension for voice control, analitics and game tracking for Rumble-AI'
tags: dict = {
    'tags': {
        'english': [ 'league', 'extension' ],
        'spanish': [ 'league', 'extension' ]
    }
}

# This file it's the real entry point from the program when it's runned as a Rumble-AI plugin


import os
from .python_mod import setup_rle
import rle


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
        # Instanciate a new RumbleLeague object
        ## This is def constr, but exists in C++ an overloaded constructor that receives the language
        # TODO This should mean that the def constructor should set the language to the Rumble AI default
        rumble_league = rle.RumbleLeague(1)  

        # Print it's memory address to ckeck if it's working correctly
        print(rumble_league)  ## TODO In the C++ lib, on the pybind module, change the __repr__ python behaviour

        # For now, the unique method availiable it's the one shown below.
        rumble_league.play(kwargs['query'])

