import operator
import random

TEST_SHOULD_PASS_CHANCE = 0.50
TEST_NUM = 10
NUM_START = -20
NUM_END = 20


def is_number(str):
    try:
        int(str)
        return True
    except ValueError:
        return False


def generate():
    ops = ["+", "-", "*", "/"]
    tests = []
    tests.append("1 2 + 3 4 - 5 * +")  # тест-пример, рабочий
    tests.append("1 + 5 3 -")  # тест-пример, ошибка: не хватает операнда для оператора
    tests.append("1 2 + 3 4")  # тест-пример, ошибка: кол-во элементов в стеке > 1
    tests.append("1 2 * 0 /")  # тест-пример, ошибка: деление на 0
    for i in range(4, TEST_NUM):  # генерируем рандомные тесты
        test_str = []
        elements_count = random.randrange(3, 20)
        for j in range(elements_count):
            test_str.append(random.randrange(NUM_START, NUM_END))
        if (random.random() > TEST_SHOULD_PASS_CHANCE):  # если делаем валидный тест
            operator_count = elements_count - 1  # условие разрешимости задачи
            for k in range(operator_count):
                test_str.append(ops[random.randrange(0,3)])
        else:
            if(random.random() > 0.5): # 50/50
                operator_count = elements_count - 1
            else:
                operator_count = random.randrange(1, elements_count-1)
            for k in range(operator_count):
                test_str.insert(
                    random.randrange(2, len(test_str)),
                    ops[random.randrange(0,3)])
        tests.append(''.join(map('{} '.format, test_str)))
    return tests

def solve(dataset):
    ops = {
        "+": operator.add,
        "-": operator.sub,
        "*": operator.mul,
        "/": operator.truediv,
        # "**": operator.pow,
        # "//": operator.floordiv
    }
    stack = []
    inputs = list(map(str, dataset.split()))
    for _input in inputs:
        if (is_number(_input)):
            stack.append(int(_input))
        else:
            try:
                right_op = stack.pop()
            except:
                return "error"
            try:
                left_op = stack.pop()
            except:
                return "error"
            op_func = ops[_input]
            try:
                stack.append(op_func(left_op, right_op))
            except:
                return "error"
    if (len(stack) != 1):
        return "error"
    return str(stack[0])


def check(reply, clue):
    return str(reply) == str(clue)