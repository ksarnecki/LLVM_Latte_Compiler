#include <cstdio>
#include <string.h>
#include <stdlib.h>
int main() {
const char* name = "hello";
const char* extension = ".txt";

char* name_with_extension;
name_with_extension = (char*)malloc(strlen(name)+strlen(extension)+4); /* make space for the new string (should check the return value ...) */
strcpy(name_with_extension, name); /* copy name into the new var */
strcat(name_with_extension, extension); /* add the extension */

printf("%s", name_with_extension);

}
