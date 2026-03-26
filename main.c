#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Collection.h"
#include "TypeInfo.h"
#include "operations.h"

/* ---------- вспомогательные функции ввода ---------- */
static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int scan_int(int *out) {
    if (scanf("%d", out) == 1) return 1;
    printf("  Ошибка: введите целое число!\n");
    flush_input();
    return 0;
}

static int scan_char(char *out) {
    if (scanf(" %c", out) == 1) return 1;
    printf("  Ошибка: введите один символ!\n");
    flush_input();
    return 0;
}

static int scan_word(char *buffer, size_t size) {
    if (scanf("%255s", buffer) == 1) return 1;
    printf("  Ошибка: введите слово!\n");
    flush_input();
    return 0;
}

static int scan_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';
        return 1;
    }
    return 0;
}

/* ---------- баннер и меню ---------- */
static void print_banner(void) {
    printf("\n");
    printf("   ____            _     _   _               \n");
    printf("  / ___| ___   ___| |_  | | | | ___  _ __   \n");
    printf(" | |    / _ \\ / __| __| | |_| |/ _ \\| '_ \\  \n");
    printf(" | |___| (_) | (__| |_  |  _  | (_) | | | | \n");
    printf("  \\____|\\___/ \\___|\\__| |_| |_|\\___/|_| |_| \n");
    printf("\n");
    printf("  Полиморфная коллекция (символы / строки)\n");
    printf("  ──────────────────────────────────────────\n\n");
}

static void print_menu(void) {
    printf("\n  ┌─────────────────────────────────────────┐\n");
    printf("  │  1. Создать коллекцию символов         │\n");
    printf("  │  2. Создать коллекцию строк            │\n");
    printf("  │  3. Добавить элемент                   │\n");
    printf("  │  4. Показать все коллекции             │\n");
    printf("  │  5. Получить элемент по индексу        │\n");
    printf("  │  6. Заменить элемент по индексу        │\n");
    printf("  │  7. Освободить коллекцию               │\n");
    printf("  │  8. Конкатенация (однотипные)          │\n");
    printf("  │  9. Подмассив (подстрока)              │\n");
    printf("  │ 10. Разбить строку на слова            │\n");
    printf("  │ 11. Ввести предложение в коллекцию сим │\n");
    printf("  │  0. Выход                              │\n");
    printf("  └─────────────────────────────────────────┘\n");
    printf("  Выберите: ");
}

/* ---------- печать коллекции ---------- */
static void print_collection(const Collection *col, const char *name) {
    if (!col) {
        printf("  %s = (не создана)\n", name);
        return;
    }
    printf("  %s (size %zu, cap %zu): [", name, size(col), capacity(col));
    for (size_t i = 0; i < size(col); ++i) {
        if (i > 0) printf(", ");
        void *elem = get(col, i);
        col->type->print(elem);
    }
    printf("]\n");
}

/* ---------- ввод предложения в коллекцию символов ---------- */
static void input_sentence(Collection *col) {
    if (!col) {
        printf("  Сначала создайте коллекцию символов!\n");
        return;
    }
    flush_input();

    char buffer[1024];
    printf("  Введите предложение (можно с пробелами): ");
    if (!scan_line(buffer, sizeof(buffer))) {
        printf("  Ошибка чтения строки.\n");
        return;
    }

    printf("  DEBUG: buffer = \"%s\" (длина %zu)\n", buffer, strlen(buffer));

    size_t added = 0;
    for (size_t i = 0; buffer[i] != '\0'; ++i) {
        if (!append(col, &buffer[i])) {
            printf("  Ошибка при добавлении символа '%c' на позиции %zu\n", buffer[i], i);
            break;
        }
        added++;
    }
    printf("  Добавлено %zu символов.\n", added);
}

/* ---------- ввод одного символа и добавление ---------- */
static void add_char(Collection *col) {
    if (!col) {
        printf("  Сначала создайте коллекцию символов!\n");
        return;
    }
    char c;
    printf("  Введите символ: ");
    if (!scan_char(&c)) return;
    if (append(col, &c))
        printf("  Символ добавлен.\n");
    else
        printf("  Ошибка добавления.\n");
}

/* ---------- ввод строки (слова) и добавление ---------- */
static void add_string(Collection *col) {
    if (!col) {
        printf("  Сначала создайте коллекцию строк!\n");
        return;
    }
    char buffer[256];
    printf("  Введите строку (одно слово): ");
    if (!scan_word(buffer, sizeof(buffer))) return;
    char *p = malloc(strlen(buffer) + 1);
    if (!p) {
        printf("  Не удалось выделить память.\n");
        return;
    }
    strcpy(p, buffer);
    if (append(col, &p)) {
        printf("  Строка добавлена.\n");
    } else {
        free(p);
        printf("  Ошибка добавления.\n");
    }
}

/* ---------- изменение элемента по индексу ---------- */
static void modify_element(Collection *col, int type_flag) {
    if (!col) {
        printf("  Сначала создайте коллекцию!\n");
        return;
    }
    size_t idx;
    int n;
    printf("  Введите индекс (от 0): ");
    if (!scan_int(&n)) return;
    idx = (size_t)n;
    if (idx >= size(col)) {
        printf("  Индекс вне диапазона.\n");
        return;
    }
    if (type_flag == 1) { // символ
        char c;
        printf("  Новый символ: ");
        if (!scan_char(&c)) return;
        set(col, idx, &c);
        printf("  Элемент заменён.\n");
    } else { // строка
        char buffer[256];
        printf("  Новая строка: ");
        if (!scan_word(buffer, sizeof(buffer))) return;
        char *p = malloc(strlen(buffer) + 1);
        if (!p) {
            printf("  Не удалось выделить память.\n");
            return;
        }
        strcpy(p, buffer);
        set(col, idx, &p);
        printf("  Элемент заменён.\n");
    }
}

/* ---------- получение элемента по индексу ---------- */
static void get_element(const Collection *col, int type_flag) {
    if (!col) {
        printf("  Сначала создайте коллекцию!\n");
        return;
    }
    size_t idx;
    int n;
    printf("  Введите индекс (от 0): ");
    if (!scan_int(&n)) return;
    idx = (size_t)n;
    if (idx >= size(col)) {
        printf("  Индекс вне диапазона.\n");
        return;
    }
    void *elem = get(col, idx);
    printf("  Элемент: ");
    col->type->print(elem);
    printf("\n");
}

/* ---------- основная функция ---------- */
int main(void) {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    print_banner();

    Collection *col_char = NULL;
    Collection *col_str = NULL;
    Collection *result = NULL;

    int choice;

    while (1) {
        print_menu();
        if (!scan_int(&choice)) continue;

        switch (choice) {
            case 1:
                if (col_char) free_collection(col_char);
                col_char = create_collection(get_char_type());
                printf(col_char ? "  Коллекция символов создана.\n" : "  Ошибка создания.\n");
                break;

            case 2:
                if (col_str) free_collection(col_str);
                col_str = create_collection(get_string_type());
                printf(col_str ? "  Коллекция строк создана.\n" : "  Ошибка создания.\n");
                break;

            case 3: {
                int t;
                printf("  Тип (1-символ, 2-строка): ");
                if (!scan_int(&t)) break;
                if (t == 1) add_char(col_char);
                else if (t == 2) add_string(col_str);
                else printf("  Неверный тип.\n");
                break;
            }

            case 4:
                printf("\n");
                print_collection(col_char, "Символы");
                print_collection(col_str, "Строки");
                print_collection(result, "Результат операций");
                break;

            case 5: {
                int t;
                printf("  Тип (1-символ, 2-строка): ");
                if (!scan_int(&t)) break;
                if (t == 1) get_element(col_char, 1);
                else if (t == 2) get_element(col_str, 2);
                else printf("  Неверный тип.\n");
                break;
            }

            case 6: {
                int t;
                printf("  Тип (1-символ, 2-строка): ");
                if (!scan_int(&t)) break;
                if (t == 1) modify_element(col_char, 1);
                else if (t == 2) modify_element(col_str, 2);
                else printf("  Неверный тип.\n");
                break;
            }

            case 7: {
                int t;
                printf("  Тип (1-символ, 2-строка): ");
                if (!scan_int(&t)) break;
                if (t == 1) {
                    if (col_char) {
                        free_collection(col_char);
                        col_char = NULL;
                        printf("  Коллекция символов освобождена.\n");
                    } else {
                        printf("  Коллекция символов не создана.\n");
                    }
                } else if (t == 2) {
                    if (col_str) {
                        free_collection(col_str);
                        col_str = NULL;
                        printf("  Коллекция строк освобождена.\n");
                    } else {
                        printf("  Коллекция строк не создана.\n");
                    }
                } else {
                    printf("  Неверный тип.\n");
                }
                break;
            }

            case 8: { // конкатенация
                int t;
                printf("  Тип (1-символы, 2-строки): ");
                if (!scan_int(&t)) break;
                Collection *a = (t == 1) ? col_char : (t == 2) ? col_str : NULL;
                if (!a || !a->type) {
                    printf("  Коллекция не создана или неверный тип.\n");
                    break;
                }

                if (t == 1) {
                    // для символов: конкатенация сама с собой
                    if (result) free_collection(result);
                    result = concat(a, a);
                    if (result) {
                        printf("  Конкатенация выполнена. Результат сохранён в 'result'.\n");
                    } else {
                        printf("  Ошибка конкатенации.\n");
                    }
                } else { // t == 2, строки: выводим склеенную строку из элементов a
                    if (size(a) == 0) {
                        printf("  Коллекция пуста.\n");
                        break;
                    }
                    // Вычисляем общую длину с учётом пробелов
                    size_t total_len = 0;
                    for (size_t i = 0; i < size(a); ++i) {
                        const char *s = *(const char**)get(a, i);
                        if (s) total_len += strlen(s);
                    }
                    if (size(a) > 1) total_len += (size(a) - 1); // пробелы между словами

                    char *buffer = malloc(total_len + 1);
                    if (buffer) {
                        buffer[0] = '\0';
                        for (size_t i = 0; i < size(a); ++i) {
                            const char *s = *(const char**)get(a, i);
                            if (s) {
                                if (i > 0) strcat(buffer, " ");
                                strcat(buffer, s);
                            }
                        }
                        printf("  Результат (склеенная строка): \"%s\"\n", buffer);
                        free(buffer);
                    } else {
                        printf("  Не удалось выделить память для склейки.\n");
                    }
                }
                break;
            }

            case 9: { // подмассив
                int t;
                printf("  Тип (1-символы, 2-строки): ");
                if (!scan_int(&t)) break;
                Collection *src = (t == 1) ? col_char : (t == 2) ? col_str : NULL;
                if (!src) {
                    printf("  Коллекция не создана.\n");
                    break;
                }
                int i, j;
                printf("  Введите индексы i и j (отсчёт с 0): ");
                if (scanf("%d %d", &i, &j) != 2) {
                    flush_input();
                    printf("  Неверный ввод.\n");
                    break;
                }
                flush_input();
                if (result) free_collection(result);
                result = subarray(src, (size_t)i, (size_t)j);
                if (result) {
                    printf("  Подмассив создан.\n");
                } else {
                    printf("  Ошибка (неверные индексы или память).\n");
                }
                break;
            }

            case 10: // разбиение на слова
                if (!col_char) {
                    printf("  Создайте коллекцию символов.\n");
                    break;
                }
                if (result) free_collection(result);
                result = split_words(col_char);
                if (result)
                    printf("  Разбиение выполнено.\n");
                else
                    printf("  Ошибка разбиения.\n");
                break;

            case 11: // ввести предложение в коллекцию символов
                input_sentence(col_char);
                break;

            case 0:
                printf("\n  Освобождаем память и выходим...\n");
                if (col_char) free_collection(col_char);
                if (col_str) free_collection(col_str);
                if (result) free_collection(result);
                printf("  До свидания!\n\n");
                return 0;

            default:
                printf("  Неверная команда, попробуйте цифру из меню.\n");
        }
    }
}
