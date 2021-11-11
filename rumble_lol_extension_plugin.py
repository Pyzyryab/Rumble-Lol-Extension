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

        # Instanciate a new RumbleLeague object
        ## This is a def constr, but exists in the C++ lib an overloaded constructor that receives the language id.
        # TODO This should means that the def constructor should set the language to the Rumble AI default
        self.rumble_league = rle.RumbleLeague(1) 

    def __str__(self) -> str:
        return self.name[ self.id_language - 1 ]

    def play(self, rumble, **kwargs) -> None:

        # Print it's memory address to ckeck if it's working correctly
        print(self.rumble_league)  ## TODO In the C++ lib, on the pybind module, change the __repr__ python behaviour

        query = kwargs['query']

        # if query.__contains__("extension league"): 
            # If true, the extension will take the full control of the Rumble skills, letting the user just interact with this extension.
            # This leads to potentially use a reduced syntax on the queries (the voice input) to control the client or perform some action 
            # through this plugin being less verbose to perform any action.
            # Example: Instead of 'Rumble league play', just will be necessary to voice input 'play'
        rumble.talk( "Entering on take control mode:" )
        control = True

        while control:
            # query = rumble.listen()
            query = input('Introduce una acción: \n')
            print(f'He escuchado desde dentro del LoL: {query}')
            
            if query == "desactivar":
                break
            elif query != "":
                result = self.rumble_league.play( query.lower() )
                print( f'resultado: {result}' )
                rumble.talk( result )
                print( '*************************\n' )
        # else:
        #    self.rumble_league.play(kwargs['query'])
