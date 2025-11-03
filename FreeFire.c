#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define MAX 10 // Maximum capacity of backpack

typedef struct {
    char name[50];
    char type[50];
    int qtd;
} item;

void add_to_backpack(item *backpack);
void remove_from_backpack(char *name[]);
void list_items(item *backpack[]);
void show_menu(void);
bool is_full(item *backpack[]);

int main(void) {
    setlocale(LC_ALL, "pt-BR.UTF-8");
    item backpack[MAX];
    int option, ok;
    char item_name;

    bool run_game = true; // Flag to control game flow
    while (run_game) {
        do {
            show_menu();
            ok = scanf("%d", &option);
            if (option < 0 || option > 3) {
                printf("Opção inválida. Tente novamente.\n");
                continue;
            }

        } while (ok != 1);
        

        switch (option) {
        case 0:
            run_game = false;
            break;
        case 1:
            add_to_backpack(&backpack);
            break;
        case 2:
            remove_from_backpack(&item_name);
            break;
        case 3:
            list_items(&backpack);
            break;
        default:
            break;
        }
    }

    return 0;
}

/* ---------- UI ----------*/
void show_menu(void) {
    printf(" ---------- MENU ---------- \n");
    printf("0 - Sair\n");
    printf("1 - Adicionar item à mochila\n");
    printf("2 - Adicionar item à mochila\n");
    printf("3 - Adicionar item à mochila\n");
    printf(" -------------------------- \n");
}
