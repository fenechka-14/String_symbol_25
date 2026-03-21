#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Объявления всех тестовых функций
void test_create_free_char(void);
void test_append_get_char(void);
void test_set_char(void);
void test_create_free_string(void);
void test_append_get_string(void);
void test_set_string(void);
void test_concat_char(void);
void test_concat_mismatch(void);
void test_subarray_char(void);
void test_split_words(void);
void test_split_empty(void);
void test_split_only_spaces(void);

int main() {
    // Устанавливаем кодировку UTF-8 для консоли Windows
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    printf("Running unit tests for polymorphic collection...\n\n");

    test_create_free_char();
    test_append_get_char();
    test_set_char();
    test_create_free_string();
    test_append_get_string();
    test_set_string();
    test_concat_char();
    test_concat_mismatch();
    test_subarray_char();
    test_split_words();
    test_split_empty();
    test_split_only_spaces();

    printf("\nAll tests passed successfully!\n");
    return 0;
}