global x

x = 1

def foo():
    global x
    x = 2

foo()
print(x)

