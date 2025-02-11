class Robot():

    height, weight = 100, 100

    def __init__(self,x:int,y:int,forbidden):
        self.x = x
        self.y = y
        self.zapret_zones = forbidden
        self.commands = []
        self.saveArr = [(x,y),(x,y)]

    def enter_commands(self):
        while True:
            command = input().strip(' ').split(',')

            command[0] = command[0].upper()

            if command[0] == "B":
                command.append(1)

            if command == ['']:
                break

            self.commands.append(command)

    def _rem_add(self,back=False):
        if not back:    
            self.saveArr.remove(self.saveArr[0])
            self.saveArr.append((x,y))
        else:
            self.saveArr.remove(self.saveArr[1])
            self.saveArr.append((x,y))

    def _checkCrash(self,steps):
        for x in range(self.x,self.x+steps+1):
            for y in range(self.y,self.y+steps+1):
                if (x,y) in self.zapret_zones:
                    print(f'{x},{y} occured in forbidden zone. Program stopped')
                    exit()

    def move(self,directon:str, steps:int) -> str:
        if (((self.x+steps < self.weight) and (-self.weight<self.x-steps)) and ((self.y+steps < self.height) and (-self.height<self.y-steps))):

            self._checkCrash(steps=steps)

            if directon == "R":
                [print(i,self.y) for i in range(self.x+1,self.x+steps+1)]
                self.x += steps
                self._rem_add()

            elif directon == "L":
                [print(i,self.y) for i in range(self.x-1,self.x-steps-1,-1)]                
                self.x -= steps
                self._rem_add()


            elif directon == "U":
                [print(self.x,i) for i in range(self.y+1,self.y+steps+1)]                
                self.y += steps
                self._rem_add()

            elif directon == "D":
                [print(self.x,i) for i in range(self.y-1,self.y-steps-1,-1)]                
                self.y -= steps
                self._rem_add()

            elif directon == "B":
                for i in range(len(self.commands)):
                    if self.commands[i][0] == "B":
                        self.commands[i] = ["",""]
                        mustBeCompleted = self.commands[i-steps:i]
                        a = i
                        print(mustBeCompleted,"-----------_TEst")
                        for j in mustBeCompleted:
                            self.commands.insert(a+1,[{"R": "L", "L": "R", "U": "D", "D": "U"}.get(j[0]),j[1]])
                            a += 1
                        print(self.commands)
                        break
            else:
                print("You've put unknown command. Program stopped")
                raise KeyError
        else:
            print("X or Y higher than weigh or height. Program stopped")

    def run(self):
        self.enter_commands()

        for command in self.commands:
            self.move(command[0],int(command[1]))


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
            zone = input().split(" ")
            xzone, yzone, hzone, wzone = int(zone[0]),int(zone[1]), int(zone[2]), int(zone[3])
            for x in range(xzone, xzone+wzone):
                for y in range(yzone, yzone-hzone,-1):
                    zapret.add((x,y))   
        return zapret
    except:
        print("You've put something odd. INT type required")       
         
if __name__ == "__main__":
    try:
        zones = create_zones()
        x = int(input("Enter the x: "))
        y = int(input("Enter the y: "))
        turtle = Robot(x=x,y=y,forbidden=zones)
        turtle.run()
    except:
        print("You've input not int type. Program Stopped")
