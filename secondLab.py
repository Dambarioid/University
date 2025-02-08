class FileManager:

    errorSample = """Perhaps you forgot some values. Sample:"""
    
    def __init__(self,fileName):
        self.fileName = fileName
        self.history = []
        self.copied_text = ""
        self.file = []
        self.valid = True
        self.commands_list = {
            "insert": self.insert,
            "del": self.delete,
            "delrow": self.delrow,
            "delcol": self.delcol,
            "swap": self.swap,
            "undo": self.undo,
            "copy": self.copy,
            "paste": self.paste,
            "save": self.save,
            "show": self.show,
            "exit": self.exit,
            "help": self.help,
        }

    
    def _largeCheck(self,rowNumber):
        if int(rowNumber) > len(self.file):
            self.file.extend(["\n" for _ in range(int(rowNumber)-len(self.file))])

    def insert(self,command):
        try:
            text, num_row, num_col  =  command[1], int(command[2]), int(command[3])
            self._largeCheck(num_row)
            line = " "  * (num_col - 1) + text 
            self.file[num_row-1] = line[1:len(line)-1] + '\n' 
        except:    
            print(self.errorSample + """insert "text" [num_row] [num_col]""")
            self.valid = False

    def delete(self,command):
        self.file = []
    
    def delrow(self,command):
        try:
            num_row = int(command[1])
            self._largeCheck(num_row)
            self.file[num_row-1] = ""
        except:
            print(self.errorSample + """delrow num_row""")
            self.valid = False

    def delcol(self,command):
        try:
            num_col = int(command[1])
            for num in range(len(self.file)):
                line = self.file[num]
                if len(line) >= num_col:
                    line = list(self.file[num])
                    line[num_col-1] = ""
                    self.file[num] = ''.join(line) 
        except:
            print(self.errorSample + "delcol num_col")
            self.valid = False


    def swap(self,command):
        try:
            first_line, second_line = int(command[1]), int(command[2])
            self._largeCheck(max(first_line, second_line))
            self.file[first_line-1], self.file[second_line-1] = self.file[second_line-1], self.file[first_line-1]
        except:
            print(self.errorSample + """swap num_row_1 num_row_2 """)
            self.valid = False
    
    def undo(self,command):
        try:
            canceled = 1
            if len(command) == 2:
                canceled = int(command[1]) 
            self.history = [self.history[i] for i in range(len(self.history)) if i < len(self.history) - canceled - 1]
            self.file = []
            for operation in self.history:
                command_type = operation[0]
                self.commands_list[command_type](operation)
        except:
            print(self.errorSample + """undo [num_operations]""")
            self.valid = False

        
    def copy(self,command):
        try:
            num_row = int(command[1])
            start = command[2]
            end = ""
            if len(command) == 4:
                end = command[3]
            self._largeCheck(num_row)
            copied_row = self.file[num_row-1]
            self.copied_text = copied_row[copied_row.find(start):copied_row.rfind(end)+1]
        except:
            print(self.errorSample + """copy num_row [start] [end]""")
            self.valid = False

    def paste(self,command):
        try:
            num_row = int(command[1])
            self._largeCheck(num_row)
            self.file[num_row-1] = self.copied_text
        except:
            print(self.errorSample + """ paste num_row """)
            self.valid = False
    
    def save(self,command):
        with open(self.fileName,"w") as file:
            file.writelines(self.file)

    def show(self,command):
        [print(line) for line in self.file]
    
    def exit(self,command):
        answer = input("Do you want to save this file? Type y-(yes) or n-(no)")
        if answer == "y":
            self.save
        exit(0)
    
    def help(self,command):
        print(
"""
insert - вставка текста.
insert "text" [num_row] [num_col] 

del - удалять все содержимое файла.
del 

delrow - удаляет строку.
delrow num_row

delcol - удаляет столбец текста в строках, где это возможно
delcol num_col 

swap - поменять строки местами.
swap num_row_1 num_row_2 

undo - отменить последние операции.
undo [num_operations] 

copy - копировать текст из строки num_row. 
copy num_row [start] [end] 

paste - вставить скопированный текст в num_row.
paste num_row 

save - сохранить файл.
save

show - просмотреть текущее состояние файла.
show 

exit - выйти из редактора. 
exit 
            
""")
    def run(self):
        while True:
            command = input().split()
            command_type = command[0]
            if command_type in self.commands_list:
                if command_type != "show" and self.valid == True:
                    self.history.append(command)
                self.commands_list[command_type](command)
            else:
                print("Unknown command type help to see all available commands")
            self.valid = True
    
if __name__ == "__main__":
    fileName = input("Enter the file name: ")
    TextEditor = FileManager(fileName=fileName)
    TextEditor.run()


# def largeCheck(rowNumber,log):
#     if int(rowNumber) > len(log):
        
#         log.extend(["\n" for _ in range(int(rowNumber)-len(log))])

# def insert(command, log):
#     largeCheck(command[2],log)
#     log[int(command[2])-1] = ' ' * (int(command[3]) - 1) + command[1]

# def delrow(command,log):
#     try:
#         log[command[1]-1] = ""
#     except:
#         print("You didn't mention row number")

# def delcol(command,log):
#     try:
#         for i in log:
#             i[command[1]-1] = ""
#     except:
#         print("You didn't mention column number")

# def swap(command,log):
#     largeCheck(command[1],len(log))
#     log[command[1]-1], log[command[2]-1] = log[command[2]-1], log[command[1]-1]

# def copy(command,log,copied):
#     largeCheck(command[1],len(log))
#     copied = log[command[1]-1]
#     copied = copied[copied.find(command[2]):copied.rfind(command[3])]

# def undo(history,logs,copied,name,cancel=1):
#     commands = {
#     "insert": insert,
#     "delrow": delrow,
#     "delcol": delcol,
#     "swap": swap,
#     "copy": copy,
#     "paste": paste,
#     "save": save,
#     }
#     history = history[0:len(history)-1-cancel]   
#     logs = []
#     copied = ""
#     for command in history:
#         if command[0] == "paste" or command[0] == "copy":
#             commands[command[0]](command,logs,copied)

#         elif command[0] == "save":
#             commands[command[0]](logs,name)
        
#         elif command[0] == "show":
#             print(111)
#             [print(i) for i in logs]
#         elif command[0] == "exit":
#             break
#         elif command[0] == "del":
#             logs = []
#         else:
#             commands[command[0]](command,logs)

# def paste(command,log,copied):
#     largeCheck(command[1],len(log))
#     log[command[1]-1] = copied

# def save(log,name):
#     with open(name,"w") as file:
#         file.writelines(log)
    
# def commandhandler():
#     pathToFile = input("Enter the file path")
#     history = []
#     copied_text = ""
#     changes = []
#     commands = {
#         "insert": insert,
#         "delrow": delrow,
#         "delcol": delcol,
#         "swap": swap,
#         "copy": copy,
#         "undo": undo,
#         "paste": paste,
#         "save": save,
#     }
#     while True:
#         arr = input().split()
#         if arr[0] == "paste" or arr[0] == "copy":
#             commands[arr[0]](arr,changes,copied_text)
        
#         elif arr[0] == "undo":
#             commands[arr[0]](history,changes,copied_text,pathToFile)

#         elif arr[0] == "save":
#             commands[arr[0]](changes,pathToFile)
        
#         elif arr[0] == "show":
#             print(111)
#             [print(i) for i in changes]
#         elif arr[0] == "exit":
#             break
#         elif arr[0] == "del":
#             changes = []
#         else:
#             commands[arr[0]](arr,changes)
    
#         history.append(arr)

# commandhandler()
        
    