#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replaceSpace(char* s) {
    if (!s) {
        return NULL;
    }

    size_t sLen = strlen(s);
    size_t spaceCnt = 0;
    for (int i = 0; i < sLen; i++) {
        if (s[i] == ' ') {
            spaceCnt++;
        }
    }

    if (spaceCnt == 0) {
        return s;
    }

    size_t newSLen = sLen+spaceCnt*2+1;
    char *newS = malloc(newSLen);
    if (!newS) {
        return NULL;
    }
    memset(newS, 0x00, newSLen);

    size_t newSOffset = 0;
    for (int i = 0; i < sLen; i++) {
        if (s[i] == ' ') {
            memcpy(newS+newSOffset, "%20", 3);
            newSOffset += 3;
        } else {
            memcpy(newS+newSOffset, s+i, 1);
            newSOffset += 1;
        }
    }

    return newS;
}

int main(void) {
    char *s = "We are happy.";
    char *replacedS = replaceSpace(s);
    printf("replacedS: %s\n", replacedS);
    if (replacedS) {
        free(replacedS);
    }
}
