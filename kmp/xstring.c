#include "xstring.h"
#include "common.h"

//void destroy(char* T) {
//        free(T);
//}

void string_init(xstring* s, int len) {
        s->T = Malloc(sizeof(char) * (len + 1));
        s->T[0] = len;

        //s->func_destroy = destroy;
}

void compute_prefix_function(xstring* pattern_string, int next[]) {
        char *P = pattern_string->T;
        int m = P[0];
        next[1] = 0;
        int k = 0;

        for (int q = 2; q <= m; q++) {
                while (k > 0 && P[k + 1] != P[q])
                        k = next[k];

                if (P[k + 1] == P[q])
                        k = k + 1;
                next[q] = k;
                printf("iteration: %d next[%d]: %d\n", q, k, k);
        }
        print_array(next, m + 1);
}

bool kmp_matcher(xstring* text_string, xstring* pattern_string) {
        char *T = text_string->T;
        char *P = pattern_string->T;
        int n = T[0];
        int m = P[0];

        int* next = Malloc(sizeof(int) * (m + 1));
        compute_prefix_function(pattern_string, next);

        int q = 0;
        for (int i = 1; i <= n; i++) {
                while (q > 0 && P[q + 1] != T[i])
                        q = next[q];

                if (P[q + 1] == T[i])
                        q = q + 1;

                if (q == m) {
                        printf ("Pattern occurs with shifts: %d\n", i - m);
                        q = next[q];
                }
        }

}
