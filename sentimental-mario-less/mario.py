# TODO

while True:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Invalid input")
    else:
        if (height > 0 and height != 9):
            break
        else:
            print("Invalid input")

# Print out a half-pyramid
for i in reversed(range(height)):
    print(" " * i + "#" * (height - i))
