def is_bissextile(y):
    return ( y % 4 == 0 and y % 100 != 0 ) or ( y % 400 == 0 )

def number_of_days(year, month):
    """Returns the number of days of the specified month"""
    if month in (1, 3, 5, 7, 8, 10, 12):
        return 31
    elif month == 2:
        return 29 if is_bissextile(year) else 28
    else:
        return 30

def nb_days_of_year(y):
    return 366 if is_bissextile(y) else 365

def nb_days_from_new_year(y, m, d):
        return sum([number_of_days(y, mm) for mm in range(1, m)]) + d

def days_between(y, m, d, Y, M, D):
    # y must be < or = Y
    return sum([nb_days_of_year(yy) for yy in range(y, Y)]) \
        - nb_days_from_new_year(y, m, d) \
        + nb_days_from_new_year(Y, M, D)

def weekday(y, m, d):
    days = days_between(1900,1,1,y,m,d)
    return (days+1) % 7

buffer = ['', '', '', '', '', '', '']
cursor_x = 0
cursor_y = 0

def print_txt(text, len):
    global buffer, cursor_x, cursor_y
    tmp = list(buffer[cursor_y])
    for i in range(len):
        tmp[cursor_x] = list(text)[i]
        cursor_x += 1
    buffer[cursor_y] = (''.join(tmp))

def print_ln():
    global buffer, cursor_x, cursor_y
    cursor_y += 1

def cal(y, m):
    global buffer, cursor_x, cursor_y
    print("A8152B - interph 0038")

    def print_cell(s):
        print('{0: >3}'.format(s), end='')

    print_txt(''.join([m, '/', y]))
    print_ln
    print_txt(' CN T2 T3 T4 T5 T6 T7')

    first_day_of_week = weekday(y, m, 1)
    nb_days = number_of_days(y, m)
    current_day = 1
    for y in range(6):
        for x in range(7):
            if (y == 0 and x < first_day_of_week) or current_day > nb_days:
                print_cell('')
            else:
                print_cell(current_day)
                current_day = current_day + 1
        print()

cal(2020,9)