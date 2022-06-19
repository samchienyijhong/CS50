# TODO

from cs50 import get_float
from math import floor


def main():
    # Ask how many dollars the customer is owed
    dollars = get_dollars()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(dollars)
    dollars = dollars - quarters * 0.25
    dollars = float(round(dollars, 2))

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(dollars)
    dollars = dollars - dimes * 0.10
    dollars = float(round(dollars, 2))

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(dollars)
    dollars = dollars - nickels * 0.05
    dollars = float(round(dollars, 2))

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(dollars)
    dollars = dollars - pennies * 0.01
    dollars = float(round(dollars, 2))

    # Sum dollars
    dollars = int(quarters + dimes + nickels + pennies)

    # Print total amount of dollars to give the customer
    print(dollars)


def get_dollars():
    # TODO
    dollars = -1
    while dollars < 0:
        dollars = get_float("Change owed: ")

    # Truncate a decimal value
    dollars = floor(dollars * (10 ** 2)) / (10 ** 2)
    return dollars


def calculate_quarters(dollars):
    # TODO
    quarters = int(dollars / 0.25)
    return quarters


def calculate_dimes(dollars):
    # TODO
    dimes = int(dollars / 0.10)
    return dimes


def calculate_nickels(dollars):
    # TODO
    nickels = int(dollars / 0.05)
    return nickels


def calculate_pennies(dollars):
    # TODO
    pennies = int(dollars / 0.01)
    return pennies


if __name__ == "__main__":
    main()
