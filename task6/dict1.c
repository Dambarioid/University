/**
 * dict1.c -- программа чтения словаря и печати словарной статьи по номеру
 *
 * Copyright (c) 2022, Student Name <student@cs.petrsu.ru>
 *
 * This code is licensed under MIT license.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1023

int reverseCheck(char *str, char *comp, int size);
char *withoutLast(char *str);
void show_entries(char *pattern, FILE *stream);

char current_line[MAXLINE + 1] = "";

int main(int argc, char *argv[]) {
  // Если на вход подается лишь исполняемый файл то ошибка
  if (argc != 2) {
    fprintf(stderr, "Неправильное число аргументов.\n");
    fprintf(stderr, "Использование: make mueller.dict1");
    return EXIT_FAILURE;
  }

  /* Файл словаря */
  FILE *dict = NULL;

  // Если на вход подается не тот словарь,то ошибка
  if (strcmp(argv[1], "mueller.dict") != 0) {
    fprintf(stderr, "Файл не может быть прочитан или отсутсвует");
    return EXIT_FAILURE;
  }


  /* Открываем файл словаря */
  dict = fopen(argv[1], "r");
  while (1) {
    char *slovo = (char *)malloc(100 * sizeof(char));
    if (slovo == NULL){
      printf("Malloc allocation failed\n");
      free(slovo);
      continue;
    }
    scanf("%s", slovo);
    show_entries(slovo, dict);
    printf("%s\n", slovo);
    fseek(dict, 0, SEEK_SET); 
    free(slovo);
  }

  return EXIT_SUCCESS;
}

void show_entries(char *pattern, FILE *stream) {
  // Получаем слово без символов ^ и $
  char *withoutsym = (char *)malloc(100 * sizeof(char));
  strcpy(withoutsym, withoutLast(pattern));

  int flag = 0;

  // Сканируем файл попутно выводим нужные строки
  while (fgets(current_line, MAXLINE, stream) != NULL) {

    // Если у слова есть ^ и $ то сравниваем совпадает ли сова на нынешней
    // строчке с нашим бессимвольным словом
    if (pattern[0] == '^' && pattern[strlen(pattern) - 1] == '$' &&
        !isspace(current_line[0])) {
      if (strncmp(current_line, withoutsym, strlen(current_line) - 1) == 0) {
        printf("%s", current_line);
        flag = 1;
        continue;
      }
    }

    // Если у слова есть $ то сравниваем совпадает ли сова на нынешней строчке с
    // нашим бессимвольным словом
    else if (pattern[strlen(withoutsym)] == '$' && pattern[0] != '^' &&
             !isspace(current_line[0])) {
      int a = reverseCheck(current_line, withoutsym, strlen(withoutsym));
      if (a == 0) {
        printf("%s", current_line);
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
        printf("%s", current_line);
        flag = 1;
        free(passarr);
        continue;
      }
    } else if (pattern[0] != '^' && pattern[strlen(pattern) - 1] != '$' &&
               !isspace(current_line[0])) {
      if (strstr(current_line, pattern) != NULL) {
        printf("%s\n", current_line);
        flag = 1;
        continue;
      }
    }

    // Если условия оказались верными то выводим нужную нам строку
    if (flag == 1 && isspace(current_line[0]))
      printf("%s", current_line);
    else
      flag = 0;
  }
  printf("\n");
  free(withoutsym); // Завершаем работу с файлом словаря и освобождаем нашу строку
}
int reverseCheck(char *str, char *comp, int size) {
  size_t str_len = strlen(str) - 1;
  size_t comp_len = strlen(comp);

  for (int i = 0; i < size; i++) {
    if (str[str_len - size + i] != comp[comp_len - size + i]) {
      return 1;
    }
  }
  return 0;
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
