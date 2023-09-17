# Simulate a sports tournament
import csv
import sys
import random
import copy

# Number of simluations to run
N = 10000


# (command line args tell Python which team CSV file to use when running tournament simulation)
def main():
    if len(sys.argv) != 2:
        print("Incorrect amount of command-line arguments")
        sys.exit(1)

    # read team data from CSV file into memory, store team data in teams[]
    teams = []
    counts = {}
    filename = sys.argv[1]
    with open(filename) as fp:
        reader = csv.DictReader(fp)
        for row in reader:
            team_name = row["team"]
            team_rating = int(row["rating"])

            counts[team_name] = 0

            # append to list
            teams.append({"name": team_name, "rating": team_rating})

    # run N number of simualtions
    for i in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1

    # print estimated probability that each team wins the world cup
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

    sys.exit(0)


# accepts two teams as input and simulates a game between them
# if first team wins, function returns True - otherwise, returns False
# each team is a dict containing name / rating values
def simulate_game(team1, team2):
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


# accepts a list of teams and simulates a game between each pair of teams
# returns a list of all the teams that won the round
def simulate_round(teams):
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


# repeatedly simulates rounds until left with one team, then returns that one team
def simulate_tournament(teams):
    winners = copy.deepcopy(teams)
    while True:
        winners = simulate_round(winners)
        if len(winners) == 1:
            # print(winners)
            return winners[0]["name"]


if __name__ == "__main__":
    main()
