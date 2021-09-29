def wrap():
    def foo():
        print(1)
    return foo

func = wrap()
func()