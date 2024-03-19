# permutations
# class permutations():
#     pass
'''
n개 중에 pick_count만큼을 뽑는다. 
뽑아서 정렬 

[1,2,3]
3P1 => [(1), (2), (3)]
3P2 => [(1,2), (1,3), (2,1), (2,3), (3,1), (3,2)]
'''
def permutations(base_list, pick_count):
    permutations_list = []
    def permute(base_list, pick_count):
        print(f"{base_list=}, {pick_count=}")
        if (pick_count > 1):
            for index, element in enumerate(base_list):
                return tuple(element) + tuple(permute(base_list[:index] + base_list[index + 1:], pick_count - 1))
        return tuple(base_list[0])
    for index, element in enumerate(base_list):
        print(f"{element=}")
        permutations_list.append(tuple(element) + permute(base_list[:index] + base_list[index + 1:], pick_count - 1))
    # current_case.add
    # print(f"{base_list=}")
    # print(f"{pick_count=}")
    return permutations_list


a = [1,2,3,4,5,6,7]
permutes = permutations(a, 5)
for permute in permutes:
    print(f"{permute=}")