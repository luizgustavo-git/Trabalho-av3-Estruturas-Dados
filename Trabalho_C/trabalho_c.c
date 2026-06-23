#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define ARQUIVO_CSV "dados_c.csv"
#define ARQUIVO_RELATORIO "relatorio_impressao.txt"

typedef struct {
    int id;
    char arquivo[50];
    int paginas;
    char tipo;
} Trabalho;

Trabalho filaNormal[MAX];
Trabalho filaPrioritaria[MAX];

int qtdNormal = 0;

int inicioP = 0;
int fimP = 0;
int qtdPrioritaria = 0;

int trabalhosProcessados = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerQuebraLinha(char texto[]) {
    texto[strcspn(texto, "\n")] = '\0';
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void cabecalho() {
    printf("\n=====================================\n");
    printf("          FILA DE IMPRESSAO\n");
    printf("=====================================\n");
}

int filaNormalCheia() {
    return qtdNormal == MAX;
}

int filaNormalVazia() {
    return qtdNormal == 0;
}

int filaPrioritariaCheia() {
    return qtdPrioritaria == MAX;
}

int filaPrioritariaVazia() {
    return qtdPrioritaria == 0;
}

int buscarNormal(int id) {
    int i;

    for (i = 0; i < qtdNormal; i++) {
        if (filaNormal[i].id == id) {
            return i;
        }
    }

    return -1;
}

int buscarPrioritaria(int id) {
    int i, pos;

    for (i = 0; i < qtdPrioritaria; i++) {
        pos = (inicioP + i) % MAX;

        if (filaPrioritaria[pos].id == id) {
            return pos;
        }
    }

    return -1;
}

int idExiste(int id) {
    if (buscarNormal(id) != -1 || buscarPrioritaria(id) != -1) {
        return 1;
    }

    return 0;
}

void enfileirarNormal(Trabalho novo) {
    if (filaNormalCheia()) {
        printf("Fila normal cheia.\n");
        return;
    }

    filaNormal[qtdNormal] = novo;
    qtdNormal++;
}

void enfileirarPrioritaria(Trabalho novo) {
    if (filaPrioritariaCheia()) {
        printf("Fila prioritaria cheia.\n");
        return;
    }

    filaPrioritaria[fimP] = novo;
    fimP = (fimP + 1) % MAX;
    qtdPrioritaria++;
}

Trabalho desenfileirarNormal() {
    Trabalho removido;
    int i;

    removido.id = -1;

    if (filaNormalVazia()) {
        return removido;
    }

    removido = filaNormal[0];

    for (i = 0; i < qtdNormal - 1; i++) {
        filaNormal[i] = filaNormal[i + 1];
    }

    qtdNormal--;

    return removido;
}

Trabalho desenfileirarPrioritaria() {
    Trabalho removido;

    removido.id = -1;

    if (filaPrioritariaVazia()) {
        return removido;
    }

    removido = filaPrioritaria[inicioP];
    inicioP = (inicioP + 1) % MAX;
    qtdPrioritaria--;

    return removido;
}

void cadastrarTrabalho() {
    Trabalho novo;

    cabecalho();

    printf("Digite o ID do trabalho: ");
    scanf("%d", &novo.id);
    limparBuffer();

    if (novo.id <= 0) {
        printf("ID invalido.\n");
        return;
    }

    if (idExiste(novo.id)) {
        printf("Erro: ja existe um trabalho com esse ID.\n");
        return;
    }

    printf("Digite o nome do arquivo: ");
    fgets(novo.arquivo, sizeof(novo.arquivo), stdin);
    removerQuebraLinha(novo.arquivo);

    printf("Digite a quantidade de paginas: ");
    scanf("%d", &novo.paginas);
    limparBuffer();

    if (novo.paginas <= 0) {
        printf("Quantidade de paginas invalida.\n");
        return;
    }

    printf("Digite o tipo do trabalho (N - normal / P - prioritario): ");
    scanf(" %c", &novo.tipo);
    limparBuffer();

    if (novo.tipo >= 'a' && novo.tipo <= 'z') {
        novo.tipo = novo.tipo - 32;
    }

    if (novo.tipo != 'N' && novo.tipo != 'P') {
        printf("Tipo invalido. Use N ou P.\n");
        return;
    }

    if (strlen(novo.arquivo) == 0) {
        printf("Nome do arquivo nao pode ficar vazio.\n");
        return;
    }

    if (novo.tipo == 'N') {
        if (filaNormalCheia()) {
            printf("Fila normal cheia.\n");
            return;
        }

        enfileirarNormal(novo);
    } else {
        if (filaPrioritariaCheia()) {
            printf("Fila prioritaria cheia.\n");
            return;
        }

        enfileirarPrioritaria(novo);
    }

    printf("Trabalho de impressao cadastrado com sucesso.\n");
}

void processarProximo() {
    Trabalho trabalho;

    cabecalho();

    if (filaPrioritariaVazia() && filaNormalVazia()) {
        printf("Nenhum trabalho na fila de impressao.\n");
        return;
    }

    if (!filaPrioritariaVazia()) {
        trabalho = desenfileirarPrioritaria();
    } else {
        trabalho = desenfileirarNormal();
    }

    if (trabalho.id != -1) {
        trabalhosProcessados++;

        printf("Trabalho processado:\n");
        printf("ID: %d\n", trabalho.id);
        printf("Arquivo: %s\n", trabalho.arquivo);
        printf("Paginas: %d\n", trabalho.paginas);
        printf("Tipo: %c\n", trabalho.tipo);
    }
}

void consultarProximo() {
    Trabalho trabalho;

    cabecalho();

    if (filaPrioritariaVazia() && filaNormalVazia()) {
        printf("Nenhum trabalho aguardando impressao.\n");
        return;
    }

    if (!filaPrioritariaVazia()) {
        trabalho = filaPrioritaria[inicioP];
    } else {
        trabalho = filaNormal[0];
    }

    printf("Proximo trabalho a ser processado:\n");
    printf("ID: %d\n", trabalho.id);
    printf("Arquivo: %s\n", trabalho.arquivo);
    printf("Paginas: %d\n", trabalho.paginas);
    printf("Tipo: %c\n", trabalho.tipo);
}

void listarFilas() {
    int i, pos;

    cabecalho();

    if (filaPrioritariaVazia() && filaNormalVazia()) {
        printf("As duas filas estao vazias.\n");
        return;
    }

    printf("\nFILA PRIORITARIA:\n");

    if (filaPrioritariaVazia()) {
        printf("Nenhum trabalho prioritario.\n");
    } else {
        for (i = 0; i < qtdPrioritaria; i++) {
            pos = (inicioP + i) % MAX;

            printf("\nID: %d\n", filaPrioritaria[pos].id);
            printf("Arquivo: %s\n", filaPrioritaria[pos].arquivo);
            printf("Paginas: %d\n", filaPrioritaria[pos].paginas);
            printf("Tipo: %c\n", filaPrioritaria[pos].tipo);
        }
    }

    printf("\nFILA NORMAL:\n");

    if (filaNormalVazia()) {
        printf("Nenhum trabalho normal.\n");
    } else {
        for (i = 0; i < qtdNormal; i++) {
            printf("\nID: %d\n", filaNormal[i].id);
            printf("Arquivo: %s\n", filaNormal[i].arquivo);
            printf("Paginas: %d\n", filaNormal[i].paginas);
            printf("Tipo: %c\n", filaNormal[i].tipo);
        }
    }
}

void buscarTrabalho() {
    int id, pos;

    cabecalho();

    if (filaPrioritariaVazia() && filaNormalVazia()) {
        printf("Nenhum trabalho cadastrado.\n");
        return;
    }

    printf("Digite o ID do trabalho: ");
    scanf("%d", &id);
    limparBuffer();

    pos = buscarPrioritaria(id);

    if (pos != -1) {
        printf("\nTrabalho encontrado na fila prioritaria:\n");
        printf("ID: %d\n", filaPrioritaria[pos].id);
        printf("Arquivo: %s\n", filaPrioritaria[pos].arquivo);
        printf("Paginas: %d\n", filaPrioritaria[pos].paginas);
        printf("Tipo: %c\n", filaPrioritaria[pos].tipo);
        return;
    }

    pos = buscarNormal(id);

    if (pos != -1) {
        printf("\nTrabalho encontrado na fila normal:\n");
        printf("ID: %d\n", filaNormal[pos].id);
        printf("Arquivo: %s\n", filaNormal[pos].arquivo);
        printf("Paginas: %d\n", filaNormal[pos].paginas);
        printf("Tipo: %c\n", filaNormal[pos].tipo);
        return;
    }

    printf("Trabalho nao encontrado.\n");
}

void cancelarNormal(int pos) {
    int i;

    for (i = pos; i < qtdNormal - 1; i++) {
        filaNormal[i] = filaNormal[i + 1];
    }

    qtdNormal--;
}

void cancelarPrioritaria(int id) {
    Trabalho temp[MAX];
    int qtdTemp = 0;
    int i, pos;

    for (i = 0; i < qtdPrioritaria; i++) {
        pos = (inicioP + i) % MAX;

        if (filaPrioritaria[pos].id != id) {
            temp[qtdTemp] = filaPrioritaria[pos];
            qtdTemp++;
        }
    }

    inicioP = 0;
    fimP = 0;
    qtdPrioritaria = 0;

    for (i = 0; i < qtdTemp; i++) {
        enfileirarPrioritaria(temp[i]);
    }
}

void cancelarTrabalho() {
    int id, pos;
    char confirma;

    cabecalho();

    if (filaPrioritariaVazia() && filaNormalVazia()) {
        printf("Nenhum trabalho para cancelar.\n");
        return;
    }

    printf("Digite o ID do trabalho que deseja cancelar: ");
    scanf("%d", &id);
    limparBuffer();

    pos = buscarPrioritaria(id);

    if (pos != -1) {
        printf("Trabalho encontrado na fila prioritaria.\n");
        printf("Deseja realmente cancelar? (S/N): ");
        scanf(" %c", &confirma);
        limparBuffer();

        if (confirma == 'S' || confirma == 's') {
            cancelarPrioritaria(id);
            printf("Trabalho cancelado com sucesso.\n");
        } else {
            printf("Cancelamento interrompido.\n");
        }

        return;
    }

    pos = buscarNormal(id);

    if (pos != -1) {
        printf("Trabalho encontrado na fila normal.\n");
        printf("Deseja realmente cancelar? (S/N): ");
        scanf(" %c", &confirma);
        limparBuffer();

        if (confirma == 'S' || confirma == 's') {
            cancelarNormal(pos);
            printf("Trabalho cancelado com sucesso.\n");
        } else {
            printf("Cancelamento interrompido.\n");
        }

        return;
    }

    printf("Trabalho nao encontrado.\n");
}

void estatisticas() {
    cabecalho();

    printf("Trabalhos prioritarios aguardando: %d\n", qtdPrioritaria);
    printf("Trabalhos normais aguardando: %d\n", qtdNormal);
    printf("Total aguardando: %d\n", qtdPrioritaria + qtdNormal);
    printf("Trabalhos processados nesta execucao: %d\n", trabalhosProcessados);
}

void salvarCSV() {
    FILE *arquivo;
    int i, pos;

    arquivo = fopen(ARQUIVO_CSV, "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar o arquivo CSV.\n");
        return;
    }

    fprintf(arquivo, "id;arquivo;paginas;tipo\n");

    for (i = 0; i < qtdPrioritaria; i++) {
        pos = (inicioP + i) % MAX;

        fprintf(arquivo, "%d;%s;%d;%c\n",
                filaPrioritaria[pos].id,
                filaPrioritaria[pos].arquivo,
                filaPrioritaria[pos].paginas,
                filaPrioritaria[pos].tipo);
    }

    for (i = 0; i < qtdNormal; i++) {
        fprintf(arquivo, "%d;%s;%d;%c\n",
                filaNormal[i].id,
                filaNormal[i].arquivo,
                filaNormal[i].paginas,
                filaNormal[i].tipo);
    }

    fclose(arquivo);
}

void carregarCSV() {
    FILE *arquivo;
    char linha[256];
    Trabalho trabalho;
    char *campo;

    arquivo = fopen(ARQUIVO_CSV, "r");

    if (arquivo == NULL) {
        printf("Arquivo dados_c.csv nao encontrado. Iniciando filas vazias.\n");
        return;
    }

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        trabalho.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(trabalho.arquivo, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        trabalho.paginas = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        trabalho.tipo = campo[0];

        if (trabalho.tipo >= 'a' && trabalho.tipo <= 'z') {
            trabalho.tipo = trabalho.tipo - 32;
        }

        if (trabalho.id <= 0 || trabalho.paginas <= 0) {
            continue;
        }

        if (idExiste(trabalho.id)) {
            continue;
        }

        if (trabalho.tipo == 'P' && !filaPrioritariaCheia()) {
            enfileirarPrioritaria(trabalho);
        } else if (trabalho.tipo == 'N' && !filaNormalCheia()) {
            enfileirarNormal(trabalho);
        }
    }

    fclose(arquivo);
}

void gerarRelatorioTXT() {
    FILE *arquivo;
    int i, pos;

    cabecalho();

    arquivo = fopen(ARQUIVO_RELATORIO, "w");

    if (arquivo == NULL) {
        printf("Erro ao gerar relatorio.\n");
        return;
    }

    fprintf(arquivo, "RELATORIO DA FILA DE IMPRESSAO\n");
    fprintf(arquivo, "==============================\n\n");

    fprintf(arquivo, "Trabalhos prioritarios aguardando: %d\n", qtdPrioritaria);
    fprintf(arquivo, "Trabalhos normais aguardando: %d\n", qtdNormal);
    fprintf(arquivo, "Total aguardando: %d\n", qtdPrioritaria + qtdNormal);
    fprintf(arquivo, "Trabalhos processados nesta execucao: %d\n\n", trabalhosProcessados);

    fprintf(arquivo, "FILA PRIORITARIA:\n");

    if (filaPrioritariaVazia()) {
        fprintf(arquivo, "Nenhum trabalho prioritario.\n");
    } else {
        for (i = 0; i < qtdPrioritaria; i++) {
            pos = (inicioP + i) % MAX;

            fprintf(arquivo, "\nID: %d\n", filaPrioritaria[pos].id);
            fprintf(arquivo, "Arquivo: %s\n", filaPrioritaria[pos].arquivo);
            fprintf(arquivo, "Paginas: %d\n", filaPrioritaria[pos].paginas);
            fprintf(arquivo, "Tipo: %c\n", filaPrioritaria[pos].tipo);
        }
    }

    fprintf(arquivo, "\nFILA NORMAL:\n");

    if (filaNormalVazia()) {
        fprintf(arquivo, "Nenhum trabalho normal.\n");
    } else {
        for (i = 0; i < qtdNormal; i++) {
            fprintf(arquivo, "\nID: %d\n", filaNormal[i].id);
            fprintf(arquivo, "Arquivo: %s\n", filaNormal[i].arquivo);
            fprintf(arquivo, "Paginas: %d\n", filaNormal[i].paginas);
            fprintf(arquivo, "Tipo: %c\n", filaNormal[i].tipo);
        }
    }

    fclose(arquivo);

    printf("Relatorio gerado com sucesso em relatorio_impressao.txt\n");
}

void menu() {
    printf("\n========== MENU ==========\n");
    printf("1 - Cadastrar trabalho de impressao\n");
    printf("2 - Processar proximo trabalho\n");
    printf("3 - Consultar proximo trabalho\n");
    printf("4 - Buscar trabalho por ID\n");
    printf("5 - Cancelar trabalho\n");
    printf("6 - Listar filas\n");
    printf("7 - Estatisticas\n");
    printf("8 - Gerar relatorio TXT\n");
    printf("9 - Salvar CSV\n");
    printf("0 - Sair\n");
    printf("==========================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;

    carregarCSV();

    do {
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarTrabalho();
                pausar();
                break;

            case 2:
                processarProximo();
                pausar();
                break;

            case 3:
                consultarProximo();
                pausar();
                break;

            case 4:
                buscarTrabalho();
                pausar();
                break;

            case 5:
                cancelarTrabalho();
                pausar();
                break;

            case 6:
                listarFilas();
                pausar();
                break;

            case 7:
                estatisticas();
                pausar();
                break;

            case 8:
                gerarRelatorioTXT();
                printf("Relatorio TXT gerado com sucesso\n");
                pausar();
                break;

            case 9:
                salvarCSV();
                printf("Dados salvos com sucesso em dados_c.csv\n");
                break;

            case 0:
                salvarCSV();
                printf("Dados salvos. Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
