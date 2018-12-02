import collections
import itertools
import numpy as np

# Advent of Code Day 2
input_file = open("2-input.txt", "r")
input_data = input_file.read()
box_ids = input_data.split()

# Part A
nr3s = 0
nr2s = 0
for id_str in box_ids:
    d = {}
    c = collections.Counter(id_str)
    for char in c.most_common():
        occurences = char[1]
        if (occurences == 3):
            nr3s = nr3s + 1
            continue
        elif (occurences == 2):
            nr2s = nr2s + 1
            break
        else:
            break

# Part B
common_chars = ''
for str1, str2 in itertools.combinations(box_ids, 2):

    char_vec_1 = np.array(list(map(ord, list(str1))))
    char_vec_2 = np.array(list(map(ord, list(str2))))

    difference_vec = char_vec_1 - char_vec_2
    diffs = np.where(difference_vec != 0)

    if (len(diffs[0]) == 1):
        differingIndex = diffs[0][0]
        common_chars = str1[:differingIndex] + str1[differingIndex+1:]
        break

print('Common chars: {}'.format(common_chars))
