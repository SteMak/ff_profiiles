typedef struct StringArray {
    int length;
    char** data;
} StringArray;

typedef struct FFParamsAll {
    StringArray profiles;
    char* url;
} FFParamsAll;

typedef struct FFParams {
    char* profile;
    char* url;
} FFParams;
