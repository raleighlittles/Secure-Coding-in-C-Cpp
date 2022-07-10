#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LIMIT 50

int main() {
  char *secret = "I've got a secret!";
  char *user = malloc(LIMIT);
  char *output = malloc(2*LIMIT);
  printf("Please enter your name:\n");
  gets(user);
  output[0] = '\0';
  strcpy(output, "Welcome ");
  strcat(output, user);
  printf(output);
  free(user);
  free(output);
  return 0;
}
