# Компилятор и флаги
# Компилятор и флаги
CC = gcc
CFLAGS = -g -Wall

# Цель по умолчанию
all: task6

# Цель для создания исполняемого файла task6
task6: dict1.o
	$(CC) $(CFLAGS) -o task6 dict1.o

# Цель для компиляции dict1.o
dict1.o: dict1.c
	$(CC) $(CFLAGS) -c dict1.c -o dict1.o

# Цель для очистки проекта
clean:
	rm -rf task6 *.o
