def create_zones(self,x,y,h,w):
    for zone in range(NumZones):
        xzone = int(input("Enter the beginning of the zone x: "))
        yzone = int(input("Enter the beginning of the zone y"))
        hzone = int(input("Enter the beginning of the zone height"))
        wzone = int(input("Enter the beginning of the zone weigh"))
        for i in range(xzone, xzone+wzone):
            for j in range(yzone, yzone-hzone,-1):
                zapret.add((i,j))
class Robot():

    height, weight = 100, 100

    def __init__(self,x:int,y:int):
        self.x = x
        self.y = y
        self.zapret_zones = []
        self.commands = []
        self.saveArr = [(x,y),(x,y)]
        

    def rem_add(self,back=False):
        if not back:    
            self.saveArr.remove(self.saveArr[0])
            self.saveArr.append((x,y))
        else:
            self.saveArr.remove(self.saveArr[1])
            self.saveArr.append((x,y))

    def _enter_commands(self):
        while True:
            command = input().strip(' ').split(',')

            command[0] = command[0].upper()

            if command[0] == "B":
                command.append(1)

            if command == ['']:
                break

            self.commands.append(command)
    def _checkCrash(self,steps):
        for x in range(self.x,self.x+steps+1):
            for y in range(self.y,self.y+steps+1):
                if (x,y) in zapret:
                    print(f'{x},{y} occured in forbidden zone. Program stopped')
                    exit()
    def move(self,directon:str, steps:int) -> str:
        if (((self.x+steps < self.weight) and (-self.weight<self.x-steps)) and ((self.y+steps < self.height) and (-self.height<self.y-steps))):
            self._checkCrash(steps=steps)

            if directon  == "R":
                [print(i,self.y) for i in range(self.x+1,self.x+steps+1)]
                x += steps
                self.rem_add()

            elif directon  == "L":
                [print(i,self.y) for i in range(self.x-1,self.x-steps-1,-1)]
                x -= steps
                self.rem_add()

            elif directon  == "U":
                [print(self.x,i) for i in range(self.y+1,self.y+steps+1)]
                y += steps
                self.rem_add()

            elif directon  == "D":
                [print(self.x,i) for i in range(self.y-1,self.y-steps-1,-1)]
                y -= steps
                self.rem_add()

            elif directon == "B":
                for i in range(len(history)):
                    if history[i][0] == "B":
                        del history[i]
                        mustBeCompleted = history[steps:i]
                        for j in mustBeCompleted:
                            j[0] = {"R": "L", "L": "R", "U": "D", "D": "U"}.get(j[0])
                            func2(j)
                        
                        

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

    def run(self):
        pass

try:
    x = int(input("Enter the x: "))
    y = int(input("Enter the y: "))
except:
    print("You've input incorrect vars, int type expected")

if __name__ == "__main__":
    turtle = Robot(x=x,y=y)
    turtle.run()


print("X and Y are the beginning of the left")
NumZones = int(input("Enter the number of zones"))
zapret = set()
def create_zones(x,y,h,w):
    for zone in range(NumZones):
        xzone = int(input("Enter the beginning of the zone x: "))
        yzone = int(input("Enter the beginning of the zone y"))
        hzone = int(input("Enter the beginning of the zone height"))
        wzone = int(input("Enter the beginning of the zone weigh"))
        for i in range(xzone, xzone+wzone):
            for j in range(yzone, yzone-hzone,-1):
                zapret.add((i,j))


    

def func():
    history = []
    func1(arr=history)

    for command in history:
        func2(history,saveArr,command[0],int(command[1]))

func()
