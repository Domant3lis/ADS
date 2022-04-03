c_out = open("output.txt", "rb")
rand_in = open("random.txt", "rb")

good_list = []
nums = rand_in.read().rstrip().decode("utf-8").split()
for num in nums:
  good_list.insert(0, int(num))
  
good_list.sort()

stranger_list = []
nums = c_out.read(40076).rstrip().decode("utf-8").split("\n")[:-1]
for num in nums:
  stranger_list.insert(len(stranger_list), int(num))

# print(stranger_list)

ix = 0
while ix != 8192 - 1:
  assert good_list[ix] == stranger_list[ix]
  ix = ix + 1
  
print("Test passed")

