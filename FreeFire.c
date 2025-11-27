#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX 10 // Maximum capacity of backpack
int count = 0; // Control of itens array

/*Clears remaining input from stdin when string exceeds buffer*/
void clean_buffer(void) {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
}

/*Validates if string contains only letters, spaces or hyphens*/
bool is_alpha(char str[]) {
    if (str[0] == '\0') return false;

    bool has_letter = false;

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)str[i];

        if (isdigit(ch)) return false;
        if (!isspace(ch)) has_letter = true;
    }
    return has_letter;
}

/*Validates number-only input*/
bool is_number(char str[]) {
    if (str[0] == '\n' || str[0] == '\0') return false;
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)str[i];
        if (!isdigit(ch)) {
            return false;
        }
    }
    
    return true;
}

/*Remove newline and detect if buffer was exceeded*/
void remove_newline(char str[]) {
    size_t len = strcspn(str, "\n");

    if (str[len] == '\n') {
        str[len] = '\0';
    } else {
        clean_buffer();
    }
}

typedef struct {
    char name[50];
    char type[50];
    int qtd;
} item;

void add_to_backpack(item backpack[]);
bool remove_from_backpack(item backpack[]);
void list_items(item backpack[]);
void show_menu(void);
int search_item(item backpack[], char name[]);

/*Main*/
int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    item backpack[MAX];
    int option, ok;

    while (true) {
        do {
            show_menu();
            ok = scanf("%d", &option);
            clean_buffer();
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
            add_to_backpack(backpack);
            break;
        case 2:
            if(count == 0) {
                printf("Não há itens a serem removidos. Adicione um item na mochila para poder removê-lo.\n");
                continue;
            }
            list_items(backpack);
            if (remove_from_backpack(backpack)) {
                printf("Item removido com sucesso!\n");
            } else {
                printf("Item não encontrado.\n");
            }
            break;
        case 3:
            if(count == 0) {
                printf("Não há itens na mochila.\n");
                continue;
            }
            list_items(backpack);
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
    printf("1 - Adicionar item a mochila\n");
    printf("2 - Remover item da mochila\n");
    printf("3 - Listar itens na mochila\n");
    printf(" -------------------------- \n");
}

/*Check for duplicate names*/
bool exists(item backpack[], char name[]) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp(backpack[i].name, name) == 0) return true;
    }
    return false;
}

/*Add items*/
void add_to_backpack(item backpack[]) {
    char raw_input[50];
    bool valid;
    /*------ Name ------*/
    do {
    printf("Digite o nome do item: ");
    fgets(raw_input, sizeof(raw_input), stdin);
    remove_newline(raw_input);

    if (!is_alpha(raw_input)) {
        printf("Entrada inválida. Digite apenas letras, espaços ou hífen.\n");
        valid = false;
        continue;
    }
    if (exists(backpack, raw_input)) {
        printf("Este item já está na mochila.\n");
        valid = false;
        continue;
    }
    strcpy(backpack[count].name, raw_input);
    valid = true;
    } while(!valid);

    /*------ Type ------*/
    do {
        printf("Tipo de item: ");
        fgets(raw_input, sizeof(raw_input), stdin);
        remove_newline(raw_input);
        strcpy(backpack[count].type, raw_input);
        valid = true;
    } while(!valid);
    
    /*------ Quantity ------*/
    do {
        printf("Quantidade: ");
        fgets(raw_input, sizeof(raw_input), stdin);
        remove_newline(raw_input);
        if (!is_number(raw_input)) {
            printf("Entrada inválida. Digite apenas números inteiros.\n");
            valid = false;
            continue;
        }
        backpack[count].qtd = atoi(raw_input);
        if (backpack[count].qtd <= 0) {
            printf("Digite um número inteiro positivo.\n");
            valid = false;
            continue;
        }
        valid = true;
    } while(!valid);

    count++;
    printf("Cadastro %d de %d realizado com sucesso!\n", count, MAX);
}


/*List items in table format*/
void list_items(item backpack[]) {
    printf("\n-------------------- MOCHILA --------------------\n");
    printf("%-5s %-20s %-20s %-15s\n", "ID", "Nome", "Tipo", "Quantidade");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-20s %-15d\n", i + 1, backpack[i].name, backpack[i].type, backpack[i].qtd);
    }
    printf("-------------------------------------------------\n");
}

/*Search by name*/
int search_item(item backpack[], char name[]) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp(backpack[i].name, name) == 0) return i;
    }
    return -1;
}

/*Remove by name*/
bool remove_from_backpack(item backpack[]) {
    char raw_input[50];
    printf("Digite o nome do item que deseja remover: ");
    fgets(raw_input, sizeof(raw_input), stdin);
    remove_newline(raw_input);

    int idx = search_item(backpack, raw_input);
    if (idx == -1) return false;

    for (int i = idx; i < count - 1; i++) {
        strcpy(backpack[i].name, backpack[i + 1].name);
        strcpy(backpack[i].type, backpack[i + 1].type);
        backpack[i].qtd = backpack[i + 1].qtd;
    }

    backpack[count - 1].name[0] = '\0';
    backpack[count - 1].type[0] = '\0';
    backpack[count - 1].qtd = 0;

    count--;
    return true;
}
