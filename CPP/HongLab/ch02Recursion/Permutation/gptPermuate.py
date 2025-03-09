def permutations(base_list, pick_count):
    permutations_list = []
    
    def permute(current_list, remaining_count, picked_elements):
        if remaining_count == 0:
            permutations_list.append(picked_elements)
            return 
        for i, element in enumerate(current_list):
            permute(current_list[:i] + current_list[i+1:], remaining_count - 1, tuple(picked_elements)+ tuple([element]))

    permute(base_list, pick_count, tuple())
    return permutations_list

a = [1, 2, 3]
permutes = permutations(a, 2)
print(f"{permutes=}")
for permute in permutes:
    print(f"{permute=}")

permutes = permutations(a, 3)
for permute in permutes:
    print(f"{permute=}")