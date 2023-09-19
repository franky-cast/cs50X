# TODO

def main():
    while True:
        try:
            height = int(input("Enter height: "))
            if height > 0:
                break
        except:
            continue

    mario(height)


def mario(height):
    for i in range(1, height + 1):
        spaces = height - i
        print(" " * spaces + "#" * i)


main()
