## 编译
```
mkdir build
cd build
cmake ..
make
```

## 示例
```python
#test.py

def sum(a = 1):
    x = 0
    i = 0
    while i <= a:
        x = x + i
        i = i + 1

    return x

print(sum())
```

```shell
$ python3 -m py_compile test/test.py

$ build/ToyPythonVM build/ToyPythonVM test/__pycache__/test.cpython-38.pyc
5050
```

## 参考资料
- 《自己动手写Python虚拟机》
- Cpython Internals
- Cpython