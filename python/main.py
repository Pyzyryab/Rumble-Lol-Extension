import rle

# Instanciate a new RumbleLeague object
rle = rle.RumbleLeague()  ## This is def constr, but exists in C++ an overloaded constructor that receives the language

# Print it's memory address to ckeck if it's working correctly
print(rle)  ## TODO In the C++ lib, on the pybind module, change the __repr__ python behaviour

# For now, the unique method availiable it's the one shown below.
rle.league_client_action()