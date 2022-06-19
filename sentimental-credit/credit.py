# TODO

from cs50 import get_string
from re import match


def main():
    numbers = get_string("Number: ")
    if checksum(numbers):
        print(checklenth(numbers))
    else:
        print("INVALID")


def checksum(numbers):
    checksum = 0

    # Don't multiply for last digit
    is_multiply = False

    # Start with number's last digit
    for number in reversed(numbers):

        # Multiply every other digit by 2, starting with number’s second-to-last digit
        if is_multiply:
            number = int(number) * 2

            # And then add those products’ digits together.
            for i in range(len(str(number))):
                digit = int(str(number)[i])
                checksum += digit
            is_multiply = False

        # Add sum to sum of the digits that weren’t multiplied by 2.
        else:
            digit = int(number)
            checksum += digit
            is_multiply = True

    # If the total’s last digit is 0, the number is valid
    if str(checksum)[-1] == "0":
        return True
    return False


def checklenth(numbers):
    if match("^5[1-5]\d{14}$", numbers):
        return "MASTERCARD"
    elif match("^3[4|7]\d{13}$", numbers):
        return "AMEX"
    elif match("^4(\d{12}$|\d{15}$)", numbers):
        return "VISA"
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
    