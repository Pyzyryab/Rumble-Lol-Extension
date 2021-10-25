import os

'''
    1º -  Detect if the **rle** it's been running as a standalone or as an installed plugin of Rumble-AI.
    If the base path contains the Rumble-AI folder, it should be as plugin, else, as standalone
'''
base_path = os.getcwd()
as_standalone = False

if base_path.__contains__( 'Rumble-AI' ):
    as_standalone = True
    '''
        2º - If it's running as a plugin, we need to add to the path the intermediate folders from the Rumble-AI base path
        to the base path of the installation plugin
    '''
    base_path += '\\src\\plugins\\rumble_league_extension_plugin'

print( f'Base path: { base_path }' )

'''
    3º - Since Python 3.8, DLL's from installed libs should be manually pointed, mark it them as a safe-directory.
        3.1 - Let's gonna create a variable to track the folder
        3.2 - Add the folder to the DLL search path 
'''
dll_folder = base_path + '\\x64\\Release'
os.add_dll_directory(dll_folder)

'''
    3º - Since Python 3.8, DLL's from installed libs should be manually pointed, mark it them as a safe-directory.
        3.1 - Let's gonna create a variable to track the folder
        3.2 - Add the folder to the DLL search path 
'''

os.chdir( base_path )
activate_this_file = ".\\python_mod\\env\\Scripts\\activate_this.py"
exec(compile(open(activate_this_file, "rb").read(), activate_this_file, 'exec'), dict(__file__=activate_this_file))


'''
    5º - chdir to the lib env, to let the C++ library have a correct environment
    to load all the necessary assets
'''

os.chdir('./python_mod')

import rle

rumble_league = rle.RumbleLeague(1)  

# Print it's memory address to ckeck if it's working correctly
print(rumble_league)  ## TODO In the C++ lib, on the pybind module, change the __repr__ python behaviour

# For now, the unique method availiable it's the one shown below.
rumble_league.play('Rumble, play')