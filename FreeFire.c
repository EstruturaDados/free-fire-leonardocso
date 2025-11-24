#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define MAX 10 // Maximum capacity of backpack
int count = 0; // Control of itens array

typedef struct {
    char name[50];
    char type[50];
    int qtd;
} item;

bool is_alpha(char *string[]) {
    if (string[0] == '\n' || string[0] == '\0') return false;
    for (int i == 0; string[i] != '\0'; i++) {
        if (!isalpha(string[i]) == 0) {
            return false;
        }
    }
    
    return true;
}

bool is_number(char *string[]) {
    if (string[0] == '\n' || string[0] == '\0') return false;
    for (int i == 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i]) == 0) {
            return false;
        }
    
    return true;
}

void add_to_backpack(item *backpack);
void remove_from_backpack(char *name[]);
void list_items(item *backpack[]);
void show_menu(void);

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    item backpack[MAX];
    int option, ok;
    char item_name;

    while (true) {
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
            printf("Saindo do jogo...\n");
            return 0;
        case 1:
            if (count == MAX) {
                printf("A mochila já está cheia. Remova um item para poder adicionar outro.\n");
                continue;
            }
            add_to_backpack(&backpack);
            break;
        case 2:
            if(count == 0) {
                printf("Não há itens a serem removidos. Adicione um item na mochila para poder removê-lo.\n");
                continue;
            }
            remove_from_backpack(&item_name);
            break;
        case 3:
            if(count == 0) {
                printf("Não há itens na mochila. Adicione um item primeiro para poder visualizá-lo.\n");
                continue;
            }
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
    printf("2 - Remover item da mochila\n");
    printf("3 - Listar itens na mochila\n");
    printf(" -------------------------- \n");
}
