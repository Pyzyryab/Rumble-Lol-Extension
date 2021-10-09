import rle

# Instanciate a new RumbleLeague object
## This is def constr, but exists in C++ an overloaded constructor that receives the language
# TODO This should mean that the def constructor should set the language to the Rumble AI default
rle = rle.RumbleLeague()  


# Print it's memory address to ckeck if it's working correctly
print(rle)  ## TODO In the C++ lib, on the pybind module, change the __repr__ python behaviour

# For now, the unique method availiable it's the one shown below.
rle.league_client_action()