import os

def set_dll_dir(dir: str):
    dll_dir = os.getcwd() # Get it after change it on the if path or else path
    os.add_dll_directory(dll_dir)
    os.chdir(initial_dir + dir) # Restab to the correct one to run the lib

# Since Python 3.8, DLL's from installed libs should be manually pointed, as a safe-directory check.
initial_dir = os.getcwd()
print(f'Current working directory: {initial_dir}')

if __name__ == '__main__':
    os.chdir('../x64/Release')
    set_dll_dir('')
else:
    # This is the real entry point for the C++ library, but notice how a Python environment exists in this folder.
    # In that environment it's where the C++ lib it's installed, so we need to activate that environment to being able to call the library.
    # In VS, it's activated when you run a file in the same directory (don't confuse what the environment does with where it's located, 
    # I am just talking about the VS feature that automatically activates the venv on every run).
    # So we need to tell to this script to activate that venv before reaches the 'import rle' line, to have access to the C++ lib.
    activate_this_file = ".\python\env\Scripts\\activate_this.py"
    # TODO Change to relative path
    exec(compile(open(activate_this_file, "rb").read(), activate_this_file, 'exec'), dict(__file__=activate_this_file))

    # The common case. This file it's being called by an external one.
    os.chdir('./x64/Release')
    set_dll_dir('/python')


import rle

# Instanciate a new RumbleLeague object
## This is def constr, but exists in C++ an overloaded constructor that receives the language
# TODO This should mean that the def constructor should set the language to the Rumble AI default
rle = rle.RumbleLeague(1)  

# Print it's memory address to ckeck if it's working correctly
print(rle)  ## TODO In the C++ lib, on the pybind module, change the __repr__ python behaviour

# For now, the unique method availiable it's the one shown below.
rle.play('Rumble, play')