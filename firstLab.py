class Robot():

    height, weight = 100, 100

    def __init__(self,x:int,y:int,forbidden):
        self.x = x
        self.y = y
        self.zapret_zones = forbidden
        self.commands = []
        self.result = []
        self.changes = []
        self.saveArr = [(x,y),(x,y)]

    def enter_commands(self):
        while True:
            command = input().strip(' ').split(',')

            command[0] = command[0].upper()

            if command[0] == "B" and len(command) == 1:
                command.append(1)

            if command == ['']:
                break

            self.commands.append(command)
            self.changes = [*self.commands]

    def _rem_add(self,back=False):
        if not back:    
            self.saveArr.remove(self.saveArr[0])
            self.saveArr.append((x,y))
        else:
            self.saveArr.remove(self.saveArr[1])
            self.saveArr.append((x,y))

    def _checkCrash(self,steps,direction):
        checkBorder = True
        if direction == "R":
            checkBorder = self.x+steps < 100
        elif direction == "L":
            checkBorder = self.x-steps > 0
        elif direction == "U":
            checkBorder = self.y-steps > 0
        elif direction == "D":
            checkBorder = self.y+steps < 100
        if not checkBorder:
           print("Out of borders") 
           exit()
        for x in range(self.x,self.x+steps+1):
            for y in range(self.y,self.y+steps+1):
                if (x,y) in self.zapret_zones:
                    print(f'x,y occured in forbidden zone. Program stopped')
                    exit()

    def move(self,directon:str, steps:int) -> str:
        self._checkCrash(steps=steps,direction=directon)
        if directon == "R":
            self.result.extend((i,self.y) for i in range(self.x+1,self.x+steps+1))
            self.x += steps
            self._rem_add()

        elif directon == "L":
            self.result.extend([(i,self.y) for i in range(self.x-1,self.x-steps-1,-1)])          
            self.x = self.x - steps
            self._rem_add()


        elif directon == "U":
            self.result.extend([(self.x,i) for i in range(self.y-1,self.y-steps-1,-1)])               
            self.y = self.y - steps
            self._rem_add()

        elif directon == "D":
            self.result.extend([(self.x,i) for i in range(self.y+1,self.y+steps+1)])            
            self.y += steps
            self._rem_add()

        elif directon == "B":
            if steps >= len(self.changes): 
                steps = len(self.changes)-1
            for i in range(len(self.changes)):
                if self.changes[i][0] == "B":
                    mustBeCompleted = self.changes[i-steps:i]
                    del self.changes[i - steps: i + 1] 
                    a = i
                    for j in mustBeCompleted[::-1]:
                        self.move({"R": "L", "L": "R", "U": "D", "D": "U"}.get(j[0]),int(j[1]))
                        a += 1
                    break

        else:
            print("You've put unknown command. Program stopped")
            raise KeyError

    def run(self):
        self.enter_commands()

        for command in self.commands:
            self.move(command[0],int(command[1]))

        for steps in self.result:
            print(*steps)

def create_zones():
    try:
        NumZones = int(input("Enter the number of zones: "))
        zapret = set()
        for _ in range(NumZones):
            print(
    """
    Enter the X and Y of the zone and weight and heigh.
    Remember that you put left up angle of rectangle
    Example:20 20 100 100: """
                )
            zone = input().split(",")
            xzone, yzone, hzone, wzone = int(zone[0]),int(zone[1]), int(zone[2]), int(zone[3])
            for x in range(xzone, xzone+wzone):
                for y in range(yzone, yzone+hzone):
                    zapret.add((x,y))   
        return zapret

    except:
        print("You've put something odd. INT type required")       
         
if __name__ == "__main__":
    zones = create_zones()
    x = 1
    y = 1
    turtle = Robot(x=x,y=y,forbidden=zones)
    turtle.run()
