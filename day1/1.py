# Advent of Code Day 1

# Part A
input_file = open("1-input.txt", "r")
input_data = input_file.read()
nums = list(map(int, input_data.split()))
totalFreq = sum(nums)

print("Total frequency: {}".format(totalFreq))

# Part B
currFreq = 0
freqs = {}
while True:
    for num in nums:
        currFreq = currFreq + num
        if (str(currFreq) in freqs):
            print("Freq: {}".format(currFreq))
            quit()
        freqs[str(currFreq)] = currFreq
