#!/usr/bin/python3
import random
import string
MIN_TAG_LEN = 1
MAX_TAG_LEN = 4
MIN_TEXT_LEN = 0
MAX_TEXT_LEN = 100
TAGS = 20
AUTO_TESTS = 50

#funclion generates random string with or without <br> and <hr> tags
def rand_text_gen(min_len, max_len, with_br_or_hr):
    text=""
    if (with_br_or_hr):
        for i in range (random.randint(min_len, max_len)):
            text+=random.choice(string.ascii_uppercase + string.ascii_lowercase)
            if (random.randint(0,100)==10):
                text+="<br>"
            elif (random.randint(0,100)==90):
                text+="<hr>"
            if (random.randint(0, 20)==1):
                text+="\n"
    else:
        for i in range (random.randint(min_len, max_len)):
            text+=random.choice(string.ascii_uppercase + string.ascii_lowercase)
    return text

def generate():

    test_cases = []

    #first two hand-made tests (human-readable)
    test_cases.append("<html>\n\t<head>\n\t\t<title>HTML Document</title>\n\t</head>\n\t<body>\n\t\t<p><b>Этот текст будет полужирным,<br>\n\t\t<i>а этот — ещё и курсивным</i></b></p>\n\t</body>\n</html>")
    test_cases.append("<html>\n\t<head>\n\t\t<title>HTML Page</title>\n\t</head>\n\t<body>\n\t\t<p><b>Страница выглядит правильной,<br><i>но где-то тут мы потеряли закрывающий тег</b></p>\n\t</body>\n</html>")

    #auto tests
    for x in range (3, AUTO_TESTS):
        tags_list=[]
        for i in range (2, TAGS):
            tags_list.append('<'+rand_text_gen(MIN_TAG_LEN, MAX_TAG_LEN, 0)+'>')
        case=""
        for i in range (len(tags_list)):
            case+=tags_list[i]
            if random.randint(0, 30):
                case+='\n'
                if random.randint(0, 200):
                    case+='\t'
            case+=rand_text_gen(MIN_TEXT_LEN, MAX_TEXT_LEN, 1)
        tags_list.reverse()
        for i in range (len(tags_list)):
            case+=rand_text_gen(MIN_TEXT_LEN, MAX_TEXT_LEN, 1)
            if random.randint(0,1)==1:
                case+='</'
                case+=tags_list[i][1:]
        test_cases.append(str(case))

    return test_cases


def solve(dataset):
    string=dataset
    solution=""
    line_count=1
    tags_list=[]
    line=1
    flag=0
    tag=""
    stack=[]
    for i in range (len(dataset)):
        pair=[]
        if dataset[i]=='\n':
            line_count+=1
        if (flag==0) and (dataset[i])=='<':
            flag=1
        elif (flag==1) and (dataset[i]!='>'):
            tag+=dataset[i]

        else:
            flag=0
            if (tag!="") and (tag!="br") and (tag!="hr"):
                pair.append(tag)
                pair.append(line_count)
                tags_list.append(pair)
            tag=""
    for x in range (len(tags_list)):
        if (tags_list[x][0][0]!='/'):
            stack.append(tags_list[x])
        else:
            if stack[len(stack)-1][0]==tags_list[x][0][1:]:
                stack.pop()
            else:
                line=stack[len(stack)-1][1]
                break
    solution = "correct" if len(stack)==0 else "wrong {}".format(line)
    return (solution)

def check(reply, clue):
    return 1 if reply == clue else 0
