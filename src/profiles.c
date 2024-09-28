#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

// The function looks for strings starting with `Name=` and
// returns the array of corresponding values
char** profile_profiles_internal(char* filename, int* count)
{
    *count = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    // TODO: document overlong userprofiles are not supported
    char line[MAX_LINE_LENGTH];
    char** profiles = NULL;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (strncmp(line, "Name=", 5) == 0) {
            profiles = realloc(profiles, (*count + 1) * sizeof(char*));
            profiles[*count] = malloc(MAX_LINE_LENGTH * sizeof(char));

            sscanf(line, "Name=%[^\n]", profiles[*count]);
            (*count)++;
        }
    }

    if (fclose(file)) {
        (*count) = 0;
        return NULL;
    }

    return profiles;
}

StringArray get_profiles()
{
    StringArray result;

    // TODO: check MAX_LINE_LENGTH is not exceeded
    // TODO: get profiles.ini from config
    char filename[MAX_LINE_LENGTH];
    strcpy(filename, getenv("HOME"));
    strcat(filename, "/.mozilla/firefox/profiles.ini");

    result.data = profile_profiles_internal(filename, &result.length);

    if (!result.data) {
        result.length = 0;
        result.data = NULL;
        return result;
    }

    return result;
}

// Can be used for consistency testss
int print_profiles()
{
    StringArray profiles = get_profiles();

    for (int i = 0; i < profiles.length; i++) {
        printf("%s %d\n", profiles.data[i], i);
        free(profiles.data[i]);
    }
    free(profiles.data);

    return 0;
}
