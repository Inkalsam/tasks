#include "tasks.h"
#include <stdlib.h>
#include <string.h>

// Counts the number of times pattern occurs in string
// Example: count("aybabtu", "bab") -> 1
// Example: count("aaaaaa", "aa") -> 5
int count(char *string, char *pattern) {
    int a = strlen(string);
    int b = strlen(pattern);
    int result = 0;
    
    if (b == 0 || b > a)
        return 0;

    for (int i = 0; i <= a - b; i++ ) {
        if (strncmp(string + i, pattern, b) == 0) {
            result++;
        }
    }
    return result;
}

// Checks if string starts with prefix
// Example: starts_with("aybabtu", "ayb") -> 1
// Example: starts_with("aybabtu", "lol") -> 0
int starts_with(char *string, char *prefix) {
    int a = strlen(string);
    int b = strlen(prefix);

    if (b > a) return 0;

    return strncmp(string, prefix, b) == 0;
}

// Checks if string ends with suffix
// Example: ends_with("aybabtu", "btu") -> 1
// Example: ends_with("aybabtu", "lol") -> 0
int ends_with(char *string, char *suffix) {
    int a = strlen(string);
    int b = strlen(suffix);

    if (b > a) return 0;

    return strncmp(string + (a - b), suffix, b) == 0;
}

// Concatenates the strings in the array into a single string
// Example: {"apina", "banaani", "cembalo"} -> "apinabanaanicembalo"
char* concat(char **array, int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += strlen(array[i]);
    }
    char *result = malloc(total + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (int i = 0; i < n; i++) {
        strcat (result, array[i]);
    }
    return result;
}

// Returns the first position where pattern occurs in string
//   - If pattern doesn't occur in string, return -1
// Example: find("aybabtu", "bab") -> 2
// Example: find("aybabtu", "lol") -> -1
int find(char *string, char *pattern) {
    int a = strlen(string);
    int b = strlen(pattern);

    if (b > a) return -1;

    for (int i = 0; i <= a - b; i++) {
        if (strncmp (string + i, pattern, b) == 0) {
            return i;
        }
    }
    return -1;
}


// Creates a string that repeats pattern n times
// Example: repeat("abc", 4) -> "abcabcabcabc"
char* repeat(char *pattern, int n) {
    int len = strlen(pattern);

    char *result = malloc(len * n + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(result, pattern);
    }
    return result;
}

// Removes spaces around the string
// Example: trim(" aybabtu   ") -> "aybabtu"
char* trim(char *string) {
    if (string == NULL) return NULL;

    const char *start = string;
    while (isspace((unsigned char)*start)) start++;

    const char *end = string + strlen(string);
    while (end > start && isspace((unsigned char)end[-1])) end--;

    size_t length = end - start;
    char *result = malloc(length + 1);
    if (result == NULL) return NULL;

    memcpy(result, start, length);
    result[length] = '\0';
    return result;
}


// Replaces characters a-z with A-Z in string
// Example: upper("aybabtu") -> "AYBABTU"
// Example: upper("AyBaBtU") -> "AYBABTU"
char* upper(char *string) {
    if (string == NULL) return NULL;

    size_t length = strlen(string);
    char *result = malloc(length + 1);
    if (result == NULL) return NULL;

    memcpy(result, string, length + 1);
    for (size_t i = 0; result[i] != '\0'; i++) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] = result[i] - 'a' + 'A';
        }
    }

    return result;
}

// Replaces characters A-Z with a-z in string
// Example: upper("AYBABTU") -> "aybabtu"
// Example: upper("AyBaBtU") -> "aybabtu"
char* lower(char *string) {
    if (string == NULL) return NULL;

    size_t length = strlen(string);
    char *result = malloc(length + 1);
    if (result == NULL) return NULL;

    memcpy (result, string, length +1);
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] - 'A' + 'a';
        }
    }
    return result;
}

// Returns a substring from the string
//   - Stop if the position goes past the end of the string
// Example: substr("aybabtu", 2, 3) -> "bab"
// Example: substr("aybabtu", 10, 3) -> ""
// Example: substr("aybabtu", 2, 10) -> "babtu"
char* substr(char *string, int start, int length) {
    if (string == NULL) return NULL;

    size_t source_length = strlen(string);
    const char *slice = string;
    size_t slice_length = 0;

    if (start >= 0 && length > 0 && (size_t)start < source_length) {
        slice = string + start;
        size_t available = source_length - (size_t)start;
        slice_length = (size_t)length < available ? (size_t)length : available;
    }

    char *result = malloc(slice_length + 1);
    if (result == NULL) return NULL;

    memcpy(result, slice, slice_length);
    result[slice_length] = '\0';
    return result;

}

// Replaces all occurrences of old with new in string
//   - Don't replace an already replaced character
// Example: replace("aybabtu", "bab", "lol") -> "ayloltu"
// Example: replace("aa", "a", "aa") -> "aaaa"
char* replace(char *string, char *old, char *new) {
    if (string == NULL || old == NULL || new == NULL) return NULL;

    size_t source_length = strlen(string);
    size_t old_len = strlen(old);
    size_t new_len = strlen(new);
    if (source_length == SIZE_MAX) return NULL;

    if (old_len == 0) {
        char *result = malloc(source_length + 1);
        if (result == NULL) return NULL;
        memcpy(result, string, source_length + 1);
        return result;
    }

    size_t matches = 0;
    for (size_t i = 0; i < source_length;) {
        if (old_len <= source_length - i &&
            strncmp(string + i, old, old_len) == 0) {
            matches++;
            i += old_len;
        } else {
            i++;
        }
    }

    size_t output_length;
    if (new_len >= old_len) {
        size_t growth = new_len - old_len;
        if (growth != 0 &&
            matches > (SIZE_MAX - source_length - 1) / growth) {
            return NULL;
        }
        output_length = source_length + matches * growth;
    } else {
        output_length = source_length - matches * (old_len - new_len);
    }

    char *result = malloc(output_length + 1);
    if (result == NULL) return NULL;

    size_t src = 0;
    size_t dst = 0;
    while (src < source_length) {
        if (old_len <= source_length - src &&
            strncmp(string + src, old, old_len) == 0) {
            memcpy(result + dst, new, new_len);
            src += old_len;
            dst += new_len;
        } else {
            result[dst++] = string[src++];
        }
    }

    result[dst] = '\0';
    return result;
}

// Applies ROT13 transformation to string
//   - Rotate each letter (a-z and A-Z) 13 steps
//   - More information: https://en.wikipedia.org/wiki/ROT13
// Example: rot13("aybabtu") -> "nlonogh"
char* rot13(char *string) {
    // TODO
}

// Concatenates the strings into a single string using a delimiter
// Example: {"apina", "banaani", "cembalo"} '|' -> "apina|banaani|cembalo"
char* join(char **array, int n, char delimiter) {
    // TODO
}

// Splits the string into an array using a delimiter
//   - Return the array length
//   - Reserve memory for the array
// Example: "apina|banaani|cembalo" '|' -> {"apina", "banaani", "cembalo"}
int split(char* string, char delimiter, char*** array) {
    // TODO
}

// Sorts the given array of strings
//   - Use strcmp to compare the strings
// Example: {"all", "your", "base", "are", "belong", "to", "us"} ->
//          {"all", "are", "base", "belong", "to", "us", "your"}
void sort_strings(char **array, int n) {
    // TODO
}
