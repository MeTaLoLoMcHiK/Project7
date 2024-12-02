#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** split_into_words(const char* str, int* count) {
    
    char* copy = _strdup(str);
    if (!copy) {
        fprintf(stderr, "Memory allocation error for string copy.\n");
        exit(EXIT_FAILURE);
    }

    char* token = NULL;
    char** words = NULL;
    int words_count = 0;

    
    token = strtok(copy, " ");
    while (token != NULL) {
        
        char** temp = realloc(words, sizeof(char*) * (words_count + 1));
        if (!temp) {
            fprintf(stderr, "Memory allocation error during realloc.\n");
            
            free(copy);
            for (int i = 0; i < words_count; i++) {
                free(words[i]);
            }
            free(words);
            exit(EXIT_FAILURE);
        }

        words = temp;
        words[words_count] = _strdup(token);
        if (!words[words_count]) {
            fprintf(stderr, "Memory allocation error for word copy.\n");
            free(copy);
            for (int i = 0; i < words_count; i++) {
                free(words[i]);
            }
            free(words);
            exit(EXIT_FAILURE);
        }

        words_count++;
        token = strtok(NULL, " ");
    }

    
    *count = words_count;

    
    free(copy);

    return words;
}


void print_words(char** words, int count) {
    for (int i = 0; i < count; i++) {
        printf("Word %d: %s\n", i + 1, words[i]);
        free(words[i]);
    }
    free(words);
}

int main() {
    const char* text = "Hello world! This is a test.";
    int word_count = 0;

    
    char** words = split_into_words(text, &word_count);

    
    printf("Found %d words:\n", word_count);
    print_words(words, word_count);

    return 0;
}
