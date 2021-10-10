lst = [1,2,3,"str"]
print(lst)
print(lst[0])
print(lst[3])

s = "abcdefg"

if "a" in s:
    print("a in s")
else:
    print("error")

if "ac" in s:
    print("error")
else:
    print("ac not in s")

if 1 in lst:
    print("1 in lst")
else:
    print("error")

if "str" in lst:
    print("\"str\" in lst")
else:
    print("error")

if "A" not in s:
    print("a not in s")
else:
    print("error")

if 10 not in lst:
    print("10 not in lst")
else:
    print("error")

lst.append(123)
print(lst)

lst.append([1,2,3])
print(lst)