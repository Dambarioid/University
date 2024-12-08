#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1023

char current_line[MAXLINE + 1] = "";
char *withoutLast(char *str);
char *load_dictionary(char *dictionary, FILE *stream);
char *filter_dictionary(char *pattern, char *dictionary, char *entries);

int reverseCheck(char *str, char *comp, int size);
char *fgetsBuff(char *current_line, int maxline, char *dictionary, int *count);

int main(int argc, char *argv[]) {
  // Проверяем на наличие словаря
  if (argc != 2) {
    fprintf(stderr, "Неправильное число аргументов.\n");
    fprintf(stderr, "Использование: make mueller.dict1");
    return EXIT_FAILURE;
  }

  /* Файл словаря */
  FILE *dict = NULL;
  // Проверяем нужный словарь
  if (strcmp(argv[1], "mueller.dict") != 0) {
    fprintf(stderr, "Файл не может быть прочитан или отсутсвует");
    return EXIT_FAILURE;
  }

  // Загрузка в буффер
  // Создаем файл словаря
  FILE *DICT = NULL;
  DICT = fopen(argv[1], "r");

  // Входные данные
  char *loadBuffer = (char *)malloc(sizeof(char) * 1024 * 1024 * 10);
  load_dictionary(loadBuffer, DICT);
  // Буфер отработанных данных
  while (1) {

    char *pattern = (char *)malloc(100 * sizeof(char));
    fgets(pattern,100,stdin);
    pattern[strlen(pattern)-1] = '\0';
    char *afterBuffer = (char *)malloc(sizeof(char) * 1024 * 1024 * 10);
    filter_dictionary(pattern, loadBuffer, afterBuffer);
    free(pattern);
  }
}

char *load_dictionary(char *dictionary, FILE *stream) {

  // Записываем данные из файла в буффер
  size_t buffersize = fread(dictionary, 2, 10 * 1024 * 1024, stream);
  return dictionary;
}

char *filter_dictionary(char *pattern, char *dictiсonary, char *entries) {

  // Создаем переменную без символов $ и ^
  char *NoSym = (char *)malloc(sizeof(char) * 100);
  strncpy(NoSym, withoutLast(pattern), strlen(withoutLast(pattern)));

  // Создаем три переменные i-символ словаря flag-флаг,который дает указания на
  // добавление test-символ обработанных данных
  long long i = 0, flag = 1, test = 0;
  int count = 0;

  while (fgetsBuff(current_line, MAXLINE, dictiсonary, &count) != 0) {

    // Если у слова есть ^ и $ то сравниваем совпадает ли сова на нынешней
    // строчке с нашим бессимвольным словом

    if (pattern[0] == '^' && pattern[strlen(pattern) - 1] == '$' &&
        !isspace(current_line[0])) {
      if (strncmp(current_line, NoSym, strlen(pattern)) == 0) {
        printf("%s\n", current_line);
        flag = 1;
        continue;
      }
    }

    // Если у слова есть $ то сравниваем совпадает ли сова на нынешней строчке с
    // нашим бессимвольным словом
    else if (pattern[strlen(NoSym)] == '$' && pattern[0] != '^' &&
             !isspace(current_line[0])) {
      int a = reverseCheck(current_line, NoSym, strlen(NoSym));
      if (a == 0) {
        printf("%s\n", current_line);
        flag = 1;
        continue;
      }
    }

    // Если у слова есть ^ то сравниваем совпадает ли сова на нынешней строчке с
    // нашим бессимвольным словом
    else if (pattern[0] == '^' && pattern[strlen(pattern) - 1] != '$' &&
             !isspace(current_line[0])) {
      char *passarr = (char *)malloc(strlen(pattern + 1) * sizeof(char));
      strncpy(passarr, current_line, strlen(pattern + 1));
      if (strncmp(passarr, pattern + 1, strlen(pattern + 1)) == 0) {
        printf("%s\n", current_line);
        flag = 1;
        continue;
      }
    }

    else if (pattern[0] != '^' && pattern[strlen(pattern) - 1] != '$' &&
             !isspace(current_line[0])) {
      if (strstr(current_line, pattern) != NULL) {
        printf("%s\n", current_line);
        flag = 1;
        continue;
      }
    }

    // Если условия оказались верными то выводим нужную нам строку
    if (flag == 1 && isspace(current_line[0]))
      printf("%s\n", current_line);
    else
      flag = 0;
  }
  // Завершаем работу с файлом словаря и освобождаем нашу строку
}
char *withoutLast(char *str) {
  char *newstr = (char *)malloc(100 * sizeof(char));
  if (str[strlen(str) - 1] == '$' && str[0] == '^') {
    strncpy(newstr, str + 1, strlen(str) - 2);
  }
  if (str[strlen(str) - 1] != '$' && str[0] == '^') {
    strcpy(newstr, str + 1);
  }
  if (str[strlen(str) - 1] == '$' && str[0] != '^') {
    strncpy(newstr, str, strlen(str) - 1);
  }
  return newstr;
}
char *fgetsBuff(char *current_line, int maxline, char *dictionary, int *count) {
  int i;
  for (i = 0; i < maxline - 1; i++) {
    current_line[i] = dictionary[*count];
    (*count)++;

    if (dictionary[*count] == '\n') {
      current_line[i + 1] = '\0';
      (*count)++;
      return current_line;
    }

    if (dictionary[*count] == '\0') {
      current_line[i] = '\0';
      return current_line;
    }
    if (dictionary[*count] == EOF)
      return 0;
  }

  current_line[i] = '\0';
  return current_line;
}

int reverseCheck(char *str, char *comp, int size) {
  size_t str_len = strlen(str) - 1;
  size_t comp_len = strlen(comp);

  for (int i = 0; i < size; i++) {
    if (str[str_len - size + i + 1] != comp[comp_len - size + i]) {
      return 1;
    }
  }
  return 0;
}
