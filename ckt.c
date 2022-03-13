#include <stdlib.h>
#include <stdio.h>

#include <ckt/common.h>
#include <ckt/interpreter.h>

int main(int argc, char **argv) {

    if (argc > 2) {
        // Usage: ckt file.ckt
        return 1;
    }

    CktInterpreter *i = newCktInterpreter();
    if (i == NULL) {
        // failed to initialise interpreter
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        // No such file or directory
        destroyCktInterpreter(i);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);

    char buf[len + 1];
    buf[len] = '\0';

    if ((long)fread(buf, 1, len, f) != len) {
        // failed to read file
        goto cleanup;
    }

    if (loadCktInterpreterSource(i, buf)) {
        // failed to initialise interpreter
        goto cleanup;
    };

    CktError exit_code = startCktInterpreter(i);

    destroyCktInterpreter(i);
    fclose(f);

    return exit_code;

cleanup:
    destroyCktInterpreter(i);
    fclose(f);

    return 1;
}