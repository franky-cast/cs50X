-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Starting information:
-- date of theft: July 28, 2021
-- place of theft: Humphrey Street


-- Query #1: Read the crime scene report
-- information obtained:
-- Theft took place at 10:15am Humphrey Street Bakery
-- Three witnesses interviewed - transcripts mention bakery
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND day = 28 AND month = 7 AND description LIKE "%heft%";


-- Query #2: Read the interview transcripts from the three witnesses
-- information obtained:
-- Ruth: Within 10 minutes of theft, thief got in car in bakery parking lot and left. Check cars that left parking lot in that time frame.
-- Eugene: "idk the thiefs name, but it was someone i recognized". Emma's bakery?? Thief at ATM on Leggett Street withdrawing money
-- Raymond: As thief was leaving bakery, they called someone for less than a minute and asked person on phone to purchase..
--          earliest flight available out of Fiftyville on the following day
SELECT * FROM interviews
WHERE year = 2021 AND transcript LIKE "%bakery%";


-- Query #3: returns name for person who withdrew money on Legget Street the day of the robbery, made a phone call for less than 60 seconds after the robbery
--           occurred, left the bakery parking lot within 10 minutes of the robbery, and was on the earliest flight departing Fiftyville the very next day

-- names of people who made withdrawals on Leggett Street the day of the robbery
SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street"
    )
)
INTERSECT
-- names of people who made a call for less than 60 seconds after the robbery
SELECT name FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)
INTERSECT
-- names of people who left bakery parking lot within 10 minutes of robbery
SELECT name FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND day = 28 AND month = 7 AND hour = 10 AND (minute >= 15 AND minute <= 30)
)
INTERSECT
-- names of people who were on the earliest flight out of sunnyville
SELECT name FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN (
            SELECT id FROM airports
            WHERE city = "Fiftyville"
        )
    ORDER BY hour ASC
    LIMIT 1
    )
);


-- Query #4: Quering the destination of the earliest flight departing Fiftyville on the 29 to find out what city the thief escaped to
SELECT city FROM airports
WHERE id IN (
    SELECT destination_airport_id FROM flights
    WHERE id = (
        SELECT id FROM flights
        WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN (
            SELECT id FROM airports
            WHERE city = "Fiftyville")
        ORDER BY hour ASC LIMIT 1
    )
);

-- Query #5:
-- names of people who received a call for less than 60 seconds after the robbery
SELECT name FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE caller = (SELECT phone_number FROM people WHERE name = "Bruce")
    AND
    (year = 2021 AND month = 7 AND day = 28 AND duration < 60)
);