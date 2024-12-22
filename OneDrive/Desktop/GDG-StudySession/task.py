def sum_number(num):
    sum = 0
    for i in range(len(num)):
        sum += num[i]
    return sum

numbers = [1, 2, 3, 4, 5]
print("sum :", sum_number(numbers))