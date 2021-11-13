import os

'''
    1º -  Detects if the **rle** it's been running as a standalone or as an installed plugin of Rumble-AI.
    If the base path contains the Rumble-AI folder, it should be as plugin, else, as standalone.
    Also, if this script it's running as __main__, the base path should be a dir above this one, needing to 
    strip the /python_mod from the base path to set it to the root dir of the project.
'''
base_path = os.getcwd()
as_standalone = False

if base_path.endswith( 'python_mod' ):
    base_path = base_path[ : len( base_path ) - (len( 'python_mod' ) + 1) ]

if base_path.endswith( 'Rumble-AI' ):
    '''
        2º - If it's running as a plugin, we need to add to the path the intermediate folders from the Rumble-AI base path
        to the base path of the installation plugin
    '''
    base_path += '\\src\\plugins\\rumble_league_extension_plugin'
else:
    as_standalone = True

print( f'Base path: { base_path }' )

'''
    3º - Since Python 3.8, DLL's from installed libs should be manually pointed, mark it them as a safe-directory.
        3.1 - Let's gonna create a variable to track the folder
        3.2 - Add the folder to the DLL search path 
'''
dll_folder = base_path + '\\x64\\Release'
 # NEW - TODO PROVIDE AN INTERNAL FOLDER WITH THE OPENCV /bin folder and DLL's (like the x64\Release folder)
 # or find a way to provide a path to the installation directory (in this case, managed by vcpkg)
os.add_dll_directory("C:\\vcpkg\\installed\\x64-windows\\bin")

'''
    3º - Since Python 3.8, DLL's from installed libs should be manually pointed, mark it them as a safe-directory.
        3.1 - Let's gonna create a variable to track the folder
        3.2 - Add the folder to the DLL search path 
'''

os.chdir( base_path )
# activate_this_file = ".\\python_mod\\env\\Scripts\\activate_this.py"
# exec(compile(open(activate_this_file, "rb").read(), activate_this_file, 'exec'), dict(__file__=activate_this_file))


'''
    5º - chdir to the lib env, to let the C++ library have a correct environment
    to load all the necessary assets
'''

os.chdir('./python_mod')

if as_standalone:
    import rle

    rumble_league = rle.RumbleLeague(1, True, False)  

    # Print it's memory address to check if it's working correctly
    print(rumble_league)  ## TODO In the C++ lib, on the pybind module, change the __repr__ python behaviour
    control = True

    while control:
        # query = rumble.listen()
        query = input('Provide an action: \n')
            
        if query == "stop":
            break
        elif query != "":
            result = rumble_league.play( query.lower() )
            print( f'C++ output: {result}' )
            print( '*************************\n' )