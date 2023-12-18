**Fork of the Storm**, a variant of the Gambit of Ord, is a card game introduced in "Critical Role." For fun, I decided to implement it in C!

# How to Play
Download and run `stormfork.exe`. Alternatively, you can compile it from the code, `source.c`.

![alt text](./demo.png?raw=true "Demo")

# Mechanics
- Round 1: The player and dealer pull one of 8 cards with replacement, keeping the result hidden.
- Round 2: The player and dealer pull one of 6 cards with replacement, revealing the result.
- Round 3: The player and dealer pull one of 4 cards with replacement, revealing the result.
- Final Round: The player and dealer reveal all results, pulling another one of four cards if there were any duplicates.
In "Critical Role," these pools are determined by d8s, d6s, and d4s, respectively.