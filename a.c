#include <cstdio>
#include <string.h>
#include <stdlib.h>

int readInt() {
  int x;
  scanf("%d", &x);
  return x;
}

void printInt(int i) {
  printf("%d\n", i);
}

char* readString() {
  char* s = (char*) malloc(1024 * sizeof(char));
  scanf("%1023s", s);
  return s;
}

void printString(char* s) {
  printf("%s\n", s);
}

void error() {
  printf("runtime error\n");
  exit(0);
}

char* concatenate(char* s1, char* s2) {
  char* ret = (char*) malloc(strlen(s1)+strlen(s2)+1);
  strcpy(ret, s1);
  strcat(ret, s2);
  return ret;
}

struct RT {
  int lenght;
  int* tab;
};

void s(int* s) {
  RT r;
  r.tab[5] = 12;
  7 % 4;
}

int modulo(int a, int b) {
  return a % b;
}

int tab() {
  int x[4];
  x[1]=2;
  return x[1];
}

int main() {
  char* s1 = "test";
  char* s3 = readString();
  printString(concatenate(s1, s3));
}