import operator
import sys


def is_number(str):
    try:
        int(str)
        return True
    except ValueError:
        return False


ops = {
    "+": operator.add,
    "-": operator.sub,
    "*": operator.mul,
    "/": operator.truediv,
    "**": operator.pow,
    "//": operator.floordiv
}
stack = []
inputs = list(map(str, input().split()))
for _input in inputs:
    if (is_number(_input)):
        stack.append(int(_input))
    else:
        try:
            right_op = stack.pop()
        except:
            print("error")
            sys.exit()
        try:
            left_op = stack.pop()
        except:
            print("error")
            sys.exit()
        op_func = ops[_input]
        try:
            stack.append(op_func(left_op, right_op))
        except:
            print("error")
            sys.exit()
if (len(stack) != 1):
    print("error")
    sys.exit()
print(stack[0])
