from random import choice, randint
from string import ascii_uppercase

with open("test2.txt", "w") as f:
    for i in range(100000):
        f.write((''.join(choice(ascii_uppercase) for i in range(150))) + '\n')