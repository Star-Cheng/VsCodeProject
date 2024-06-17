#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 10
#define MAX_FIRST_FOLLOW 10

typedef struct {
    char lhs;
    char rhs[MAX_SYMBOLS];
} Production;

Production productions[MAX_PRODUCTIONS];
int num_productions = 0;

char nonterminals[MAX_SYMBOLS];
int num_nonterminals = 0;

char terminals[MAX_SYMBOLS];
int num_terminals = 0;

char first_sets[MAX_SYMBOLS][MAX_FIRST_FOLLOW];
int num_first_sets[MAX_SYMBOLS] = {0};

char follow_sets[MAX_SYMBOLS][MAX_FIRST_FOLLOW];
int num_follow_sets[MAX_SYMBOLS] = {0};

int contains(char *arr, int len, char symbol) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == symbol) {
            return 1;
        }
    }
    return 0;
}

void add_to_set(char set[MAX_FIRST_FOLLOW], int *num_elements, char symbol) {
    if (!contains(set, *num_elements, symbol)) {
        set[(*num_elements)++] = symbol;
    }
}

void compute_first_sets() {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < num_productions; i++) {
            Production prod = productions[i];
            char lhs = prod.lhs;
            char rhs[MAX_SYMBOLS];
            memcpy(rhs, prod.rhs, sizeof(prod.rhs));
            int rhs_len = strlen(rhs);

            int j = 0;
            while (j < rhs_len) {
                char first_symbol = rhs[j];
                if (contains(terminals, num_terminals, first_symbol)) {
                    add_to_set(first_sets[lhs - 'A'], &num_first_sets[lhs - 'A'], first_symbol);
                    break;
                } else if (contains(nonterminals, num_nonterminals, first_symbol)) {
                    char *first_set = first_sets[first_symbol - 'A'];
                    int num_first = num_first_sets[first_symbol - 'A'];
                    for (int k = 0; k < num_first; k++) {
                        add_to_set(first_sets[lhs - 'A'], &num_first_sets[lhs - 'A'], first_set[k]);
                    }
                    if (!contains(first_set, num_first, 'e')) {
                        break;
                    }
                } else {
                    printf("Invalid symbol: %c\n", first_symbol);
                    exit(1);
                }
                j++;
            }
            if (j == rhs_len) {
                add_to_set(first_sets[lhs - 'A'], &num_first_sets[lhs - 'A'], 'e');
            }
        }
    }
}

void compute_follow_sets() {
    add_to_set(follow_sets[productions[0].lhs - 'A'], &num_follow_sets[productions[0].lhs - 'A'], '$');

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < num_productions; i++) {
            Production prod = productions[i];
            char lhs = prod.lhs;
            char rhs[MAX_SYMBOLS];
            memcpy(rhs, prod.rhs, sizeof(prod.rhs));
            int rhs_len = strlen(rhs);

            for (int j = 0; j < rhs_len; j++) {
                char cur_symbol = rhs[j];
                if (contains(nonterminals, num_nonterminals, cur_symbol)) {
                    int k = j + 1;
                    while (k < rhs_len) {
                        char next_symbol = rhs[k];
                        if (contains(terminals, num_terminals, next_symbol)) {
                            add_to_set(follow_sets[cur_symbol - 'A'], &num_follow_sets[cur_symbol - 'A'], next_symbol);
                            break;
                        } else if (contains(nonterminals, num_nonterminals, next_symbol)) {
                            char *first_set = first_sets[next_symbol - 'A'];
                            int num_first = num_first_sets[next_symbol - 'A'];
                            for (int l = 0; l < num_first; l++) {
                                add_to_set(follow_sets[cur_symbol - 'A'], &num_follow_sets[cur_symbol - 'A'], first_set[l]);
                            }
                            if (!contains(first_set, num_first, 'e')) {
                                break;
                            }
                        } else {
                            printf("Invalid symbol: %c\n", next_symbol);
                            exit(1);
                        }
                        k++;
                    }
                    if (k == rhs_len) {
                        char *follow_set = follow_sets[lhs - 'A'];
                        int num_follow = num_follow_sets[lhs - 'A'];
                        for (int l = 0; l < num_follow; l++) {
                            add_to_set(follow_sets[cur_symbol - 'A'], &num_follow_sets[cur_symbol - 'A'], follow_set[l]);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    productions[num_productions++] = (Production){'E', "T'E'"};
    productions[num_productions++] = (Production){'E', "e"};
    productions[num_productions++] = (Production){'E', "+T'E'"};
    productions[num_productions++] = (Production){'T', "FT'"};
    productions[num_productions++] = (Production){'T', "e"};
    productions[num_productions++] = (Production){'T', "*FT'"};
    productions[num_productions++] = (Production){'T', "e"};
    productions[num_productions++] = (Production){'F', "(E)"};
    productions[num_productions++] = (Production){'F', "i"};

    for (int i = 0; i < num_productions; i++) {
        Production prod = productions[i];

        if (!contains(nonterminals, num_nonterminals, prod.lhs)) {
            nonterminals[num_nonterminals++] = prod.lhs;
        }

        char rhs[MAX_SYMBOLS];
        memcpy(rhs, prod.rhs, sizeof(prod.rhs));
        int rhs_len = strlen(rhs);

        for (int j = 0; j < rhs_len; j++) {
            char symbol = rhs[j];
            if (symbol != 'e') {
                if (contains(terminals, num_terminals, symbol) == 0 && contains(nonterminals, num_nonterminals, symbol) == 0) {
                    nonterminals[num_nonterminals++] = symbol;
                }
            }
        }
    }

    for (int i = 0; i < num_nonterminals; i++) {
        char nonterminal = nonterminals[i];
        for (int j = 0; j < num_productions; j++) {
            Production prod = productions[j];
            if (prod.lhs == nonterminal) {
                char *rhs = prod.rhs;
                while (*rhs != '\0') {
                    if (contains(nonterminals, num_nonterminals, *rhs) == 0) {
                        terminals[num_terminals++] = *rhs;
                    }
                    rhs++;
                }
            }
        }
    }

    compute_first_sets();
    compute_follow_sets();

    printf("First sets:\n");
    for (int i = 0; i < num_nonterminals; i++) {
        char nonterminal = nonterminals[i];
        printf("FIRST(%c) = {", nonterminal);
        for (int j = 0; j < num_first_sets[nonterminal - 'A']; j++) {
            printf("%c, ", first_sets[nonterminal - 'A'][j]);
        }
        printf("}\n");
    }

    printf("\nFollow sets:\n");
    for (int i = 0; i < num_nonterminals; i++) {
        char nonterminal = nonterminals[i];
        printf("FOLLOW(%c) = {", nonterminal);
        for (int j = 0; j < num_follow_sets[nonterminal - 'A']; j++) {
            printf("%c, ", follow_sets[nonterminal - 'A'][j]);
        }
        printf("}\n");
    }

    return 0;
}
