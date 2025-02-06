try:
    x = int(input("Enter the x: "))
    y = int(input("Enter the y: "))
except:
    print("You've input incorrect vars, int type expected")

height, weight = 100, 100
saveArr = [(x,y),(x,y)]

def rem_add(arr,x,y,back=False):
    if not back:    
        arr.remove(arr[0])
        arr.append((x,y))
    else:
        arr.remove(arr[1])
        arr.append((x,y))

def func1(arr):
    while True:
        var = input().strip(' ').split(',')

        var[0] = var[0].upper()

        if var[0] == "B":
            var.append(1)

        if var == ['']:
            break
        arr.append(var)
    
def func2(arr,directon:list, steps=1) -> str:
    global x, y
    if (((x+steps < weight) and (-weight<x-steps)) and ((y+steps < height) and (-height<y-steps))):
        if directon  == "R":
            [print(i,y) for i in range(x+1,x+steps+1)]
            x += steps
            rem_add(arr=arr,x=x,y=y)

        elif directon  == "L":
            [print(i,y) for i in range(x-1,x-steps-1,-1)]
            x = x -steps
            rem_add(arr=arr,x=x,y=y)

        elif directon  == "U":
            [print(x,i) for i in range(y+1,y+steps+1)]
            y += steps
            rem_add(arr=arr,x=x,y=y)

        elif directon  == "D":
            [print(x,i) for i in range(y-1,y-steps-1,-1)]
            y -= steps
            rem_add(arr=arr,x=x,y=y)

        elif directon == "B":
            if steps % 2 != 0:    
                if arr[0][0] == x:
                    if (y < arr[0][1]):
                        [print(x,i) for i in range(y+1,arr[0][1]+1)]
                    elif (y > arr[0][1]): 
                        [print(x,i) for i in range(y-1,arr[0][1]-1,-1)]
                    y = arr[0][1] 
                    rem_add(arr,x,y,True)
                
                elif arr[0][1] == y:
                    if (x < arr[0][0]):
                        [print(i,y) for i in range(x+1,arr[0][0]+1)]
                    elif(x > arr[0][0]):
                        [print(i,y) for i in range(x-1,arr[0][0]-1,-1)]
                    x = arr[0][0]
                    rem_add(arr,x,y,True)
    else:
        print("X or Y higher than weigh or height. Program stopped")

def func():
    arr = []
    func1(arr=arr)

    for i in arr:
        func2(saveArr,i[0],int(i[1]))

func()