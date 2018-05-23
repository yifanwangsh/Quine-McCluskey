import copy;

input = [0, 1, 2, 3, 4, 5, 6, 7];
main_container = [];

def convertToBin(num):
    binArray = [];
    binList = list(bin(num));
    i = 1;
    while i <= len(binList):
        if binList[-i] == "b":
            j = i;
            while j < len(binList):
                binList[-j] = "0";
                j += 1;
            continue;
        i += 1;

    if len(binList) < 6:
        j = len(binList) + 1;
        while j <= 6:
            binList.insert(0, "0");
            j += 1;

    for k in range(len(binList)):
        if (binList[k] == "0"): binList[k] = "0";
        elif (binList[k] == "1"): binList[k] = "1";

    return flatten(binList);

def flatten(list):
    while (len(list) > 6):
        del list[0]
    return list;

def compare(l1, l2):
    flag = False;
    count = 0;

    for i in range(len(l1)):
        if (l1[i] == "-") & (l2[i] != "-"):
            return False;

    for i in range(len(l1)):
        if (l1[i] != l2[i]) & (l1[i] != "-"):
            count += 1;

    if count == 1:
        for i in range(len(l1)):
            if (l1[i] != l2[i]) & (l1[i] != "-"):
                tmp = l1[i];
                l1[i] = "-";
                flag = copy.copy(l1);
                l1[i] = tmp;
    return flag;

def combine(g):
    backup_container = copy.copy(g);
    flag_recursion = False;
    for m in backup_container:
        for n in backup_container:
            flag = compare(m, n)
            if flag:
                if m in g:
                    g.remove(m);
                if n in g:
                    g.remove(n);
                if flag not in g:
                    g.append(flag);
                flag_recursion = True;
    if flag_recursion: combine(g);
    return g;

for i in input:
    i_list = convertToBin(i);
    main_container.append(i_list);

Quine_McCluskey_list = combine(main_container);
