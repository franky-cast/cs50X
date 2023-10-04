-- Create table sql statements

CREATE TABLE purchases (
    id INTEGER,
    user_id INTEGER NOT NULL,
    stock_id INTEGER NOT NULL,
    purchase_date DATE NOT NULL,
    price NUMERIC NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (stock_id) REFERENCES stocks(id)
);

CREATE TABLE stocks (
    id INTEGER,
    stock_name TEXT NOT NULL,
    symbol TEXT NOT NULL,
    Primary Key (id)
);

-- Creating unique indeces
CREATE UNIQUE INDEX IDX_stocks_symbol ON stocks (symbol);
CREATE INDEX IDX_purchases_purchaseDate ON purchases (purchase_date);
CREATE INDEX IDX_purchases_price ON purchases (price);

-- Query that returns all stocks purchased by user
SELECT symbol FROM stocks WHERE id IN (
    SELECT stock_id FROM purchases WHERE user_id IN (
        SELECT id FROM users WHERE id = ?
    )
);

-- Query that returns amount of shares of a specifc stock owned by user
SELECT SUM(shares) FROM purchases
WHERE 
stock_id IN (SELECT id FROM stocks WHERE symbol = ?)
AND
user_id = ?;

-- Query that returns current price of stock in quesiton