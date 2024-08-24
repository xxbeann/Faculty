def selection_sort(a):
    n = len(a)
    for i in range(n-1):
        least = i
        for j in range(i+1,n):
            if(a[j]<a[least]):
                least = j
        a[i], a[least] = a[least], a[i]
        printStep(a, i + 1)

def printStep(arr, val):
    print(" step %2d =", val,end = '')
    print(arr)

data =[5,3,8,4,9,1,6,2,7]
print("original: ",data)
selection_sort(data)
print("Selction = ", data)