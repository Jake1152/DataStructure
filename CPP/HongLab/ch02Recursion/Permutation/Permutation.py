from itertools import permutations


a = [1,2,3]
permutes = permutations(a, 2)
for permute in permutes:
    print(f"{permute=}")