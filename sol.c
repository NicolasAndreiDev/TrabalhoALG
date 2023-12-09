#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idContact;
    char name[100];
    char telephone[15];
    char contactType[10];
} CONTATO;

int findUserById(CONTATO *allContacts, int tamanho, int findId);
void addContact(CONTATO **allContacts, int *tamanho, int *id);
void findContact(CONTATO *allContacts, int tamanho);
void getContacts(CONTATO *allContacts, int tamanho);
void updateContact(CONTATO *allContacts, int tamanho);
void deleteContact(CONTATO **allContacts, int *tamanho);

int main() { 
    int id = 1;
    int tamanho = 0;
    CONTATO *allContacts = NULL;
    int operation;

    start:
    
    printf("----------------------------------\n");
    printf("Escolha uma das opcao abaixo:\n\n");
    printf("Incluir um novo contato - 1\n");
    printf("Excluir um contato existente - 2\n");
    printf("Alterar um contato existente - 3\n");
    printf("Listar todos os contatos cadastrados - 4\n");
    printf("Localizar um contato - 5\n");
    printf("Encerrar o programa - 6\n\n");
    printf("Insira o numero da operacao: ");
    scanf("%d", &operation);
    printf("----------------------------------\n");


    switch (operation) {
        case 1:
            addContact(&allContacts, &tamanho, &id);
            goto start;
            break;
        case 2:
            deleteContact(&allContacts, &tamanho);
            goto start;
            break;
        case 3:
            updateContact(allContacts, tamanho);
            goto start;
            break;
        case 4: 
            getContacts(allContacts, tamanho);
            goto start;
            break;
        case 5: 
            findContact(allContacts, tamanho);
            goto start;
            break;
        case 6: 
            printf("Programa finalizado!\n");
            printf("----------------------------------\n");
            break;
        default:
            printf("--- Insira uma opercao valida! ---\n");
            goto start;
    }

    return 0;
}

void addContact(CONTATO **allContacts, int *tamanho, int *id) {
    addNewContact:
    
    (*tamanho)++;
    *allContacts = realloc(*allContacts, (*tamanho) * sizeof(CONTATO));
    (*allContacts)[*tamanho-1].idContact = (*id);

    int c; while ((c = getchar()) != '\n' && c != EOF);

    printf("Informe um nome para o contato: ");
    fgets((*allContacts)[*tamanho-1].name, sizeof((*allContacts)[*tamanho-1].name), stdin);

    printf("Informe o telefone do contato: \n");
    printf("Informe o DDD do telefone: ");
    char DDD[5]; scanf("%s", DDD);
    printf("Informe os outros numeros do telefone: ");
    char contactTelephone[15]; scanf("%s", contactTelephone);
    sprintf((*allContacts)[*tamanho-1].telephone, "(%s) %s", DDD, contactTelephone);

    tipoDoContato:

    printf("Informe o tipo do contato com uma das opcoes abaixo: \n\n");
    printf("Pessoal - 1\n");
    printf("Trabalho - 2\n\n");
    printf("Insira o numero do tipo: ");
    int tipo; scanf("%d", &tipo);

    if (tipo == 1) strcpy((*allContacts)[*tamanho-1].contactType, "Pessoal");
    else if (tipo == 2) strcpy((*allContacts)[*tamanho-1].contactType, "Trabalho");
    else {
        printf("--- Informe um valor valido! ---"); 
        goto tipoDoContato;
    }

    printf("----------------------------------\n");
    printf("Contato adicionado com sucesso!\n\n");
    (*id)++;

    options:

    printf("Adicionar novo contato - 1\n");
    printf("Voltar para o menu principal - 2\n\n");
    printf("Insira o numero da operacao: ");
    int newOperation; scanf("%d", &newOperation);

    if(newOperation == 1) goto addNewContact;
    else if(newOperation != 2) {
        printf("\n");
        printf("--- Insira uma operacao valida! ---\n\n");
        goto options;
    }
}

int findUserById(CONTATO *allContacts, int tamanho, int findId) {
    if(tamanho > 0) {
        int left = 0, right = tamanho;
        while(left <= right) {
        int mid = left + (right - left) / 2;
        if(allContacts[mid].idContact == findId) return mid;
        
        if(allContacts[mid].idContact < findId) left = mid + 1;
        else right = mid - 1;
        }
    }
    
    printf("--- Nao existe um usuario com o id: %d ---\n", findId);
    return -1;
}

void findContact(CONTATO *allContacts, int tamanho) {
    findUser:
    
    printf("Informe o id do usuario que voce gostaria de saber as informacoes: ");
    int findId; scanf("%d", &findId);
    int contact = findUserById(allContacts, tamanho, findId);

    if(contact != -1) {
        printf("Essas sao as informacoes do contato com id: %d\n\n", findId);
        printf("Nome: %s", allContacts[contact].name);
        printf("Telefone: %s\n", allContacts[contact].telephone);
        printf("Tipo de contato: %s\n", allContacts[contact].contactType);
    } else {
        printf("--- Informe o id de um usuario valido! ---\n");
        goto options;
    }

    options: 

    printf("----------------------------------\n"); 
    printf("Escolha uma das opcao abaixo:\n\n");
    printf("Pesquisar por outro usuario - 1\n");
    printf("Voltar para o menu principal - 2\n\n");
    printf("Insira o numero da operacao: ");
    int newOperation; scanf("%d", &newOperation);

    if(newOperation == 1) {
        printf("----------------------------------\n");
        goto findUser;
    }
    else if(newOperation != 2) {
        printf("\n");
        printf("--- Insira uma operacao valida! ---\n\n");
        goto options;
    } 
}

void getContacts(CONTATO *allContacts, int tamanho) {
    getAllContacts:

    if(tamanho == 0) printf("--- Ainda nao ha contatos existentes! ---\n"); 
    else {
        printf("Contatos existentes:\n\n");
        for(int i=0;i<tamanho;i++) {
            printf("Id: %d\n", allContacts[i].idContact);
            printf("Nome: %s", allContacts[i].name);
            printf("Telefone: %s\n", allContacts[i].telephone);
            printf("Tipo de contato: %s\n\n", allContacts[i].contactType);
        }
        printf("----------------------------------\n");
    }

    options:

    printf("Escolha uma das opcao abaixo:\n\n");
    printf("Mostrar os contatos novamente - 1\n");
    printf("Voltar para o menu principal - 2\n\n");
    printf("Insira o numero da operacao: ");
    int newOperation; scanf("%d", &newOperation);

    if(newOperation == 1) {
        printf("----------------------------------\n"); 
        goto getAllContacts;
    } else if(newOperation != 2) {
        printf("\n");
        printf("--- Insira uma operacao valida! ---\n\n");
        goto options;
    }
}

void updateContact(CONTATO *allContacts, int tamanho) {
    update:
    
    printf("Informe o id do contato que voce quer atualizar: ");
    int findId; scanf("%d", &findId);
    int contact = findUserById(allContacts, tamanho, findId);

    if(contact != -1) {
        printf("Essas sao as informacoes atuais do contato: \n\n");
        printf("Nome: %s", allContacts[contact].name);
        printf("Telefone: %s\n", allContacts[contact].telephone);
        printf("Tipo do contato: %s\n\n", allContacts[contact].contactType);

        printf("Nome - 1\n");
        printf("Telefone - 2\n");
        printf("Tipo de contato - 3\n\n");
        printf("Informe o que voce gostaria de atualizar: ");
        int atualizar; scanf("%d", &atualizar);

        switch (atualizar){
        case 1:
            printf("Novo nome: ");
            int c; while ((c = getchar()) != '\n' && c != EOF);
            char contactName[100]; fgets(contactName, sizeof(contactName), stdin);
            strcpy(allContacts[contact].name, contactName);
            break;
        case 2:
            printf("Novo telefone: \n");
            printf("Informe o DDD: ");
            char DDD[5]; scanf("%s", &DDD);
            printf("Informe os proximos numeros do telefone: ");
            char contactTelephone[15]; scanf("%14s", contactTelephone);
            sprintf(allContacts[contact].telephone, "(%s) %s", DDD, contactTelephone);
            break;
        case 3:
            Type:
            
            printf("Novo tipo de contato:\n");
            printf("Trabalho - 1\n");
            printf("Pessoal - 2\n");
            printf("Insira o tipo do contato: ");
            int contactType; scanf("%d", &contactType);
            
            switch (contactType) {
            case 1:
                strcpy(allContacts[contact].contactType, "Trabalho");
                break;
            case 2:
                strcpy(allContacts[contact].contactType, "Pessoal");
                break;
            default:
                printf("--- Informe uma operacao valida! ---\n");
                goto Type;
            }
        }

        printf("\n");
        printf("--- Contato atualizado com sucesso! ---\n");
    } else {
        printf("--- Informe o id de um usuario valido! ---\n");
        goto options;
    }

    options:

    printf("----------------------------------\n"); 
    printf("Escolha uma das opcao abaixo:\n\n");
    printf("Atualizar outro contato - 1\n");
    printf("Voltar para o menu principal - 2\n\n");
    printf("Insira o numero da operacao: ");
    int newOperation; scanf("%d", &newOperation);

    if(newOperation == 1) {
        printf("----------------------------------\n");
        goto update;
    }
    else if(newOperation != 2) {
        printf("\n");
        printf("--- Insira uma operacao valida! ---\n\n");
        goto options;
    }
}

void deleteContact(CONTATO **allContacts, int *tamanho) {
    delete:

    printf("Informe o id do contato que voce quer excluir: ");
    int findId; scanf("%d", &findId);
    int contact = findUserById(*allContacts, *tamanho, findId);

    if(contact != -1) {
        for(int i=contact;i<(*tamanho) - 1;i++) (*allContacts)[i] = (*allContacts)[i + 1];

        (*tamanho)--;
        *allContacts = realloc(*allContacts, (*tamanho) * sizeof(CONTATO));
        printf("Contato excluido com sucesso!\n");
    } else {
        printf("--- Informe o id de um usuario valido! ---\n");
        goto options;
    }

    options:

    printf("----------------------------------\n");
    printf("Escolha uma das opcao abaixo:\n\n");
    printf("Excluir outro contato - 1\n");
    printf("Voltar para o menu principal - 2\n\n");
    printf("Insira o numero da operacao: ");
    int newOperation; scanf("%d", &newOperation);

    if(newOperation == 1) {
        printf("----------------------------------\n");
        goto delete;
    }
    else if(newOperation != 2) {
        printf("\n");
        printf("--- Insira uma operacao valida! ---\n\n");
        goto options;
    }
}