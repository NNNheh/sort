#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void sort_bubble(int arr[], int n);
void sort_kokteil(int arr[], int n);
void sort_select(int arr[], int n);
void sort_insert(int arr[], int n);

int main() {
    setlocale(LC_ALL, "RUS");
    int i, j;
    clock_t start, end;
    double time_spent; 

    srand((unsigned int)time(NULL));

    printf("СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ\n");
    printf("=================================\n\n");

    int sizes[] = { 100, 1000, 10000 };

    for (i = 0; i < 3; i++) {
        int n = sizes[i];
        printf("Размер массива: %d\n", n);

        int* arr = (int*)malloc(n * sizeof(int));
        int* arr_copy = (int*)malloc(n * sizeof(int));

        if (arr == NULL || arr_copy == NULL) {
            printf("Ошибка выделения памяти!\n");
            return 1;
        }

        for (j = 0; j < n; j++) {
            arr[j] = rand() % 10000;
        }

        printf("+----------------+--------+------------+------------+-------------------+\n");
        printf("| Алгоритм       | Размер | Тип данных | Время (с)  | Отн. скорость     |\n");
        printf("+----------------+--------+------------+------------+-------------------+\n");


        for (j = 0; j < n; j++) {
            arr_copy[j] = arr[j];
        }

        start = clock();
        sort_select(arr_copy, n);
        end = clock();
        time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("| Выбором        | %-6d | Случайный  | %-10.6f | 1.00              |\n", n, time_spent);
        double base_time = time_spent;
        for (j = 0; j < n; j++) {
            arr_copy[j] = arr[j];
        }

        start = clock();
        sort_bubble(arr_copy, n);
        end = clock();
        time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
        double speed = (time_spent > 0) ? base_time / time_spent : 0;
        printf("| Пузырьковая    | %-6d | Случайный  | %-10.6f | %-17.2f |\n", n, time_spent, speed);


        for (j = 0; j < n; j++) {
            arr_copy[j] = arr[j];
        }

        start = clock();
        sort_kokteil(arr_copy, n);
        end = clock();
        time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
        speed = (time_spent > 0) ? base_time / time_spent : 0;
        printf("| Коктельная     | %-6d | Случайный  | %-10.6f | %-17.2f |\n", n, time_spent, speed);

        for (j = 0; j < n; j++) {
            arr_copy[j] = arr[j];
        }
        start = clock();
        sort_insert(arr_copy, n);
        end = clock();
        time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;

        speed = (time_spent > 0) ? base_time / time_spent : 0;
        printf("| Вставками      | %-6d | Случайный  | %-10.6f | %-17.2f |\n", n, time_spent, speed);

        printf("+----------------+--------+------------+------------+-------------------+\n\n");

        free(arr);
        free(arr_copy);
    }

    return 0;
}

void sort_bubble(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sort_kokteil(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    int swapped = 1;
    int i, temp;

    while (left < right&& swapped) {
        swapped = 0;

        for (i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        right--;
        for (i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
        left++;
    }
}
void sort_select(int arr[], int n) {
    int i, j, min_index, temp;

    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}
void sort_insert(int arr[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}