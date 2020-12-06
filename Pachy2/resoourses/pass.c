#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
char bufferp[50];
FILE *pin=popen("sudo su","r");
fgets(bufferp, sizeof(bufferp), pin);
//system(bufferp);
pclose(pin);
return 0;
}
