#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1024

void ClearInputBuffer();
void CleanMemory(char **buffer, const int index);
int ValidateIndex(const int lines, const int index);
char** ShrinkToFit(char **buffer, const int size);
void ShrinkToFitError(char ***buffer, char **temp, int *lines);
void AddNewLine(char ***buffer, int *lines);
void InsertLine(char ***buffer, int *lines, const int index);
void DeleteLine(char ***buffer, int *lines, const int index);
int Compare(const void *str1, const void *str2);
void SortLines(char **buffer, const int lines);
void Search(char **buffer, const int lines, char *searchText);
void EditLine(char **buffer, const int lines, const int index);
int CountChar(char **buffer, const int lines);
int AvgLength(char **buffer, const int lines);
void DisplayLines(char **buffer, const int lines);
int LoadFromFile(char ***buffer, const char *fileName);
void SaveToFile(char **buffer, const int lines, const char *fileName);

#endif