# TODO

from cs50 import get_int

height = int()

while height > 8 or height < 1:
    height = get_int("Height: ")

# Print out a double half-pyramid
for i in reversed(range(height)):
    print(" " * i + "#" * (height - i), end="  " + "#" * (height - i) + "\n")
