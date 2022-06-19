-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Locate the crime scene report with given information '2021/7/28'
SELECT *
  FROM crime_scene_reports
  WHERE street = 'Humphrey Street'
  AND year = 2021
  AND month = 7
  AND day = 28;

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- – each of their interview transcripts mentions the bakery.

-- Locate the interviews
SELECT *
  FROM interviews
  WHERE year = 2021
  AND month = 7
  AND day = 28
  AND transcript
  LIKE '%bakery%';

-- | 161 | Ruth    | 2021 | 7     | 28  |
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |

-- Locate the security footages
SELECT *
  FROM bakery_security_logs
  WHERE year = 2021
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute >= 15
  AND minute <= 25
  AND activity = 'exit';

-- Locate the people based on the security footages
SELECT people.id, people.name
  FROM people
  JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
  JOIN passengers ON passengers.passport_number = people.passport_number
  WHERE bakery_security_logs.year = 2021
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute >= 15
  AND bakery_security_logs.minute <= 25
  AND bakery_security_logs.activity = 'exit';

-- | 162 | Eugene  | 2021 | 7     | 28  |
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Locate the ATM transactions
SELECT *
  FROM atm_transactions
  WHERE year = 2021
  AND month = 7
  AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw';

-- Locate the people based on the ATM transactions
SELECT people.id, people.name
  FROM people
  JOIN bank_accounts
  ON people.id = bank_accounts.person_id
  JOIN atm_transactions
  ON atm_transactions.account_number = bank_accounts.account_number
  WHERE atm_transactions.year = 2021
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw';

-- | 163 | Raymond | 2021 | 7     | 28  |
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Locate the phone calls
SELECT *
  FROM phone_calls
  WHERE year = 2021
  AND month = 7
  AND day = 28
  AND duration < 60;

-- Locate the flight
SELECT *
  FROM flights
  JOIN airports ON airports.id = flights.origin_airport_id
  WHERE airports.city = 'Fiftyville'
  AND year = 2021
  AND month = 7
  AND day = 29
  ORDER BY hour, minute ASC LIMIT 1;
-- Flight ID: 36

SELECT city
  FROM airports
  WHERE id =
    (SELECT destination_airport_id
      FROM flights
      JOIN airports ON airports.id = flights.origin_airport_id
      WHERE airports.city = 'Fiftyville'
      AND year = 2021
      AND month = 7
      AND day = 29
      ORDER BY hour, minute ASC LIMIT 1);
-- Answer - Destination City: New York City

-- Locate the people based on the phone calls
SELECT people.id, people.name
  FROM people
  JOIN phone_calls
  ON phone_calls.caller = people.phone_number
  WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60

-- INTERSECT the above results
SELECT people.id, people.name
  FROM people
  JOIN bakery_security_logs
  ON bakery_security_logs.license_plate = people.license_plate
  JOIN passengers
  ON passengers.passport_number = people.passport_number
  JOIN flights
  ON flights.id = passengers.flight_id
  WHERE flights.id = 36
  AND bakery_security_logs.year = 2021
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute >= 15
  AND bakery_security_logs.minute <= 25
  AND bakery_security_logs.activity = 'exit'
INTERSECT
SELECT people.id, people.name
  FROM people
  JOIN bank_accounts
  ON people.id = bank_accounts.person_id
  JOIN atm_transactions
  ON atm_transactions.account_number = bank_accounts.account_number
  WHERE atm_transactions.year = 2021
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw'
INTERSECT
SELECT people.id, people.name
  FROM people
  JOIN phone_calls
  ON phone_calls.caller = people.phone_number
  WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60;
-- People ID: 686048
-- Answer - People name: Bruce

SELECT name
  FROM people
  WHERE phone_number =
    (SELECT receiver
      FROM phone_calls
      JOIN people
      ON people.phone_number = phone_calls.caller
      WHERE people.id = 686048
      AND phone_calls.year = 2021
      AND phone_calls.month = 7
      AND phone_calls.day = 28
      AND phone_calls.duration < 60);
-- Phone call receiver: (375) 555-8161
-- Answer - People name: Robin






