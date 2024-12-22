def sum_number(num):
    sum = 0
    for i in range(len(num)):
        sum += num[i]
    return sum

def even_number():
    for i in range(0, 20, 2):
        if (i != 0):
            print(i, end='')

    print()

numbers = [1, 2, 3, 4, 5]
print("sum :", sum_number(numbers))
print("even_number :", end=' ')
even_number()
