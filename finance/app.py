import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import date

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # which stocks the user owns, numbers of shares owned, 
    # current price of each stock, total value of each holding
    portfolio = []

    # stocks the user owns
    sql = "SELECT symbol FROM stocks WHERE id IN (SELECT stock_id FROM purchases WHERE user_id IN (SELECT id FROM users WHERE id = ?))"
    stocks = db.execute(sql, session["user_id"])

    for stock in stocks:
        portfolio.append(stock)

    stocks_total_value = 0

    for stock in portfolio:
        symbol = stock["symbol"]
        print (symbol)

        # how many shares the user owns of this stock
        sql = "SELECT SUM(shares) FROM purchases WHERE stock_id IN (SELECT id FROM stocks WHERE symbol = ?) AND user_id = ?"
        shares = db.execute(sql, symbol, session["user_id"])[0]['SUM(shares)']

        # current price of stock
        price = lookup(symbol)["price"]
        total_holding = int(shares) * price

        # append all values to portfolio dictionary
        updated_stock = {
            "symbol": symbol,
            "shares": shares,
            "price": price,
            "total_value_holding": total_holding,
        }

        portfolio[portfolio.index(stock)] = updated_stock

        stocks_total_value += total_holding
    
    portfolio.append(stocks_total_value + db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"])

    print (portfolio)

    return render_template("index.html", portfolio=portfolio)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        # Ensure symbol input
        if not symbol:
            return apology("Must provide symbol", 403)

        # Ensure symbol exists
        look_up = lookup(symbol)
        if not look_up:
            return apology("Stock does not exist", 403)

        # Ensure number of share is positive
        shares = request.form.get("shares")
        if not shares:
            return apology("Enter amount of shares")
        
        shares = int(shares)
        
        if not shares >= 1:
            return apology("Must provide positive number of shares", 403)
        
        user_rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        user_cash = user_rows[0]["cash"]
        current_stock_price = look_up["price"]
        
        # Ensure user has enough cash to buy stock(s)
        if (current_stock_price * shares) > user_cash:
            return apology("Not enough funds", 403)

        else:
            # update users (cash)
            n = db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash - (current_stock_price * shares), session["user_id"])
        
            # update stocks table
            stocks_rows = db.execute("SELECT * FROM stocks where symbol = ?", symbol)
            if len(stocks_rows) == 0:
                stock_id = db.execute("INSERT INTO stocks (stock_name, symbol) VALUES(?, ?)", look_up["name"], symbol)
                
            else:
                stock_id = stocks_rows[0]["id"]

            try:
                # update purchases table
                db.execute("INSERT INTO purchases (user_id, stock_id, purchase_date, price, shares) VALUES(?, ?, ?, ?, ?)",
                        session["user_id"], stock_id, date.today(), current_stock_price, shares)
                
                return redirect("/")

            except:
                return apology("Internal Server Error at /buy")

    # User reached route via GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if request.form.get("symbol"):

            # call API here and feed parameters to render_tempalate
            data = lookup(request.form.get("symbol"))
            print(data)
            if data == None:
                return apology("Stock does not exist", 403)

            return render_template("quoted.html", data=data)

        # no user input
        else:
            return redirect("/quote")
        
    # User reached route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username was submitted
        username_entered = request.form.get("username")
        if not username_entered:
            return apology("must provide username", 403)

        # Ensure username does not already exist in DB
        if len(db.execute("SELECT * FROM users WHERE username = ?", username_entered)) != 0:
            return apology("username already exists", 403)

        # Ensure password was submitted
        password_entered = request.form.get("password")
        confirmation_entered = request.form.get("confirmation")
        if not password_entered:
            return apology("must provide password", 403)

        # Ensure passwords match
        if password_entered != confirmation_entered:
            return apology("password does not match with confirmation", 403)

        # Insert new user into users
        if db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username_entered, generate_password_hash(password_entered)):
            return redirect("/")
        
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    
    return apology("TODO")


if __name__ == "__main__":
    app.run(debug=True)
