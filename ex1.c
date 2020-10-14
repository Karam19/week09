#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t n;

typedef struct {
    size_t page_n;
    size_t bits;
} page_t;

int main() {
    printf("Please enter the number of frames\n");
    scanf("%zu", &n);

    size_t pages;
    printf("Please enter the number of pages\n");
    scanf("%zu", &pages);

    size_t ref;
    printf("Please enter the number of references\n");
    scanf("%zu", &ref);

    size_t hits = 0;
    size_t misses = 0;

    page_t* table = (page_t*)calloc(pages,sizeof(page_t));

    for (size_t i = 0; i < pages; ++i) {
        (table + i)->page_n = i;
    }

    page_t* m =(page_t*)calloc(n, sizeof(page_t));

    for (size_t i = 0; i < ref; i++) {
        size_t accessed;
        printf("Please enter accessed page number %zu\n",i+1);
        scanf("%zu", &accessed);

        int hit = 0;
        for (size_t j = 0; j < n; ++j) {
            page_t* page = m + j;
            if (page->page_n == accessed) {
                hit = 1;
                break;
            }
        }

        hits += hit;

        if (!hit) {
            misses++;
            size_t to_drop_n = 0;
            for (size_t j = 1; j < n; ++j) {
                if ((m + j)->page_n == 0) {
                    to_drop_n = j;
                    break;
                }
                if ((m + j)->bits < (m + to_drop_n)->bits) {
                    to_drop_n = j;
                }
            }

            *(m + to_drop_n) = *(table + accessed);
        }

        for (size_t j = 0; j < pages; ++j) {
            (table + j)->bits = ((j == accessed) << (sizeof(size_t) - 1)) | ((table + j)->bits >> 1);
        }
    }

    printf("hits: %zu, misses: %zu, ratio: %lf\n", hits, misses,(double)hits / misses);
    return 0;
}