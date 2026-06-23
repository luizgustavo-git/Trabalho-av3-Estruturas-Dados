#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define ARQUIVO_CSV "dados_b.csv"
#define ARQUIVO_RELATORIO "relatorio_chamadas.txt"

typedef struct {
    int protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
} Chamada;

Chamada pilha[MAX];
int topo = -1;
int chamadasAtendidas = 0;

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
    printf("      CHAMADAS DE EMERGENCIA\n");
    printf("=====================================\n");
}

int pilhaVazia() {
    return topo == -1;
}

int pilhaCheia() {
    return topo == MAX - 1;
}

int buscarPorProtocolo(int protocolo) {
    int i;

    for (i = topo; i >= 0; i--) {
        if (pilha[i].protocolo == protocolo) {
            return i;
        }
    }

    return -1;
}

void push(Chamada nova) {
    if (pilhaCheia()) {
        printf("Pilha cheia. Nao e possivel registrar nova chamada.\n");
        return;
    }

    topo++;
    pilha[topo] = nova;
}

Chamada pop() {
    Chamada removida;

    removida.protocolo = -1;

    if (pilhaVazia()) {
        printf("Pilha vazia. Nenhuma chamada para atender.\n");
        return removida;
    }

    removida = pilha[topo];
    topo--;

    return removida;
}

void registrarChamada() {
    Chamada nova;

    cabecalho();

    if (pilhaCheia()) {
        printf("Pilha cheia. Nao e possivel registrar chamada.\n");
        return;
    }

    printf("Digite o protocolo da chamada: ");
    scanf("%d", &nova.protocolo);
    limparBuffer();

    if (nova.protocolo <= 0) {
        printf("Protocolo invalido.\n");
        return;
    }

    if (buscarPorProtocolo(nova.protocolo) != -1) {
        printf("Erro: ja existe uma chamada com esse protocolo.\n");
        return;
    }

    printf("Digite o local da emergencia: ");
    fgets(nova.local, sizeof(nova.local), stdin);
    removerQuebraLinha(nova.local);

    printf("Digite o tipo da ocorrencia: ");
    fgets(nova.tipo, sizeof(nova.tipo), stdin);
    removerQuebraLinha(nova.tipo);

    printf("Digite o horario da chamada: ");
    fgets(nova.horario, sizeof(nova.horario), stdin);
    removerQuebraLinha(nova.horario);

    if (strlen(nova.local) == 0 || strlen(nova.tipo) == 0 || strlen(nova.horario) == 0) {
        printf("Erro: os campos de texto nao podem ficar vazios.\n");
        return;
    }

    push(nova);

    printf("Chamada registrada com sucesso.\n");
}

void atenderChamada() {
    Chamada chamada;
    char confirma;

    cabecalho();

    if (pilhaVazia()) {
        printf("Pilha vazia. Nenhuma chamada para atender.\n");
        return;
    }

    printf("Proxima chamada a ser atendida:\n");
    printf("Protocolo: %d\n", pilha[topo].protocolo);
    printf("Local: %s\n", pilha[topo].local);
    printf("Tipo: %s\n", pilha[topo].tipo);
    printf("Horario: %s\n", pilha[topo].horario);

    printf("\nConfirmar atendimento? (S/N): ");
    scanf(" %c", &confirma);
    limparBuffer();

    if (confirma != 'S' && confirma != 's') {
        printf("Atendimento cancelado.\n");
        return;
    }

    chamada = pop();

    if (chamada.protocolo != -1) {
        chamadasAtendidas++;
        printf("\nChamada atendida com sucesso:\n");
        printf("Protocolo: %d\n", chamada.protocolo);
        printf("Local: %s\n", chamada.local);
        printf("Tipo: %s\n", chamada.tipo);
        printf("Horario: %s\n", chamada.horario);
    }
}

void consultarTopo() {
    cabecalho();

    if (pilhaVazia()) {
        printf("Pilha vazia. Nao existe chamada no topo.\n");
        return;
    }

    printf("Ultima chamada registrada:\n");
    printf("Protocolo: %d\n", pilha[topo].protocolo);
    printf("Local: %s\n", pilha[topo].local);
    printf("Tipo: %s\n", pilha[topo].tipo);
    printf("Horario: %s\n", pilha[topo].horario);
}

void buscarChamada() {
    int protocolo, pos;

    cabecalho();

    if (pilhaVazia()) {
        printf("Pilha vazia. Nenhuma chamada para buscar.\n");
        return;
    }

    printf("Digite o protocolo da chamada: ");
    scanf("%d", &protocolo);
    limparBuffer();

    pos = buscarPorProtocolo(protocolo);

    if (pos == -1) {
        printf("Chamada nao encontrada.\n");
    } else {
        printf("\nChamada encontrada:\n");
        printf("Protocolo: %d\n", pilha[pos].protocolo);
        printf("Local: %s\n", pilha[pos].local);
        printf("Tipo: %s\n", pilha[pos].tipo);
        printf("Horario: %s\n", pilha[pos].horario);

        if (pos == topo) {
            printf("Situacao: esta chamada esta no topo da pilha.\n");
        } else {
            printf("Situacao: esta chamada ainda nao esta no topo.\n");
        }
    }
}

void listarChamadas() {
    int i;

    cabecalho();

    if (pilhaVazia()) {
        printf("Pilha vazia. Nenhuma chamada registrada.\n");
        return;
    }

    printf("CHAMADAS NA PILHA, DO TOPO PARA A BASE:\n");

    for (i = topo; i >= 0; i--) {
        printf("\nProtocolo: %d\n", pilha[i].protocolo);
        printf("Local: %s\n", pilha[i].local);
        printf("Tipo: %s\n", pilha[i].tipo);
        printf("Horario: %s\n", pilha[i].horario);

        if (i == topo) {
            printf("Posicao: TOPO\n");
        } else if (i == 0) {
            printf("Posicao: BASE\n");
        }
    }
}

void estatisticas() {
    cabecalho();

    printf("Total de chamadas pendentes na pilha: %d\n", topo + 1);
    printf("Total de chamadas atendidas nesta execucao: %d\n", chamadasAtendidas);

    if (!pilhaVazia()) {
        printf("Proxima chamada a ser atendida: protocolo %d\n", pilha[topo].protocolo);
    }
}

void salvarCSV() {
    FILE *arquivo;
    int i;

    arquivo = fopen(ARQUIVO_CSV, "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar o arquivo CSV.\n");
        return;
    }

    fprintf(arquivo, "protocolo;local;tipo;horario\n");

    for (i = 0; i <= topo; i++) {
        fprintf(arquivo, "%d;%s;%s;%s\n",
                pilha[i].protocolo,
                pilha[i].local,
                pilha[i].tipo,
                pilha[i].horario);
    }

    fclose(arquivo);
}

void carregarCSV() {
    FILE *arquivo;
    char linha[256];
    Chamada chamada;
    char *campo;

    arquivo = fopen(ARQUIVO_CSV, "r");

    if (arquivo == NULL) {
        printf("Arquivo dados_b.csv nao encontrado. Iniciando pilha vazia.\n");
        return;
    }

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        chamada.protocolo = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(chamada.local, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(chamada.tipo, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(chamada.horario, campo);

        if (!pilhaCheia() && chamada.protocolo > 0 && buscarPorProtocolo(chamada.protocolo) == -1) {
            push(chamada);
        }
    }

    fclose(arquivo);
}

void gerarRelatorioTXT() {
    FILE *arquivo;
    int i;

    cabecalho();

    arquivo = fopen(ARQUIVO_RELATORIO, "w");

    if (arquivo == NULL) {
        printf("Erro ao gerar relatorio.\n");
        return;
    }

    fprintf(arquivo, "RELATORIO DE CHAMADAS DE EMERGENCIA\n");
    fprintf(arquivo, "===================================\n\n");

    fprintf(arquivo, "Chamadas pendentes: %d\n", topo + 1);
    fprintf(arquivo, "Chamadas atendidas nesta execucao: %d\n\n", chamadasAtendidas);

    if (pilhaVazia()) {
        fprintf(arquivo, "Nenhuma chamada pendente.\n");
    } else {
        fprintf(arquivo, "Chamadas pendentes do topo para a base:\n");

        for (i = topo; i >= 0; i--) {
            fprintf(arquivo, "\nProtocolo: %d\n", pilha[i].protocolo);
            fprintf(arquivo, "Local: %s\n", pilha[i].local);
            fprintf(arquivo, "Tipo: %s\n", pilha[i].tipo);
            fprintf(arquivo, "Horario: %s\n", pilha[i].horario);
        }
    }

    fclose(arquivo);

    printf("Relatorio gerado com sucesso em relatorio_chamadas.txt\n");
}

void menu() {
    printf("\n========== MENU ==========\n");
    printf("1 - Registrar chamada\n");
    printf("2 - Atender chamada\n");
    printf("3 - Consultar ultima chamada\n");
    printf("4 - Buscar chamada por protocolo\n");
    printf("5 - Listar chamadas\n");
    printf("6 - Estatisticas\n");
    printf("7 - Gerar relatorio TXT\n");
    printf("8 - Salvar CSV\n");
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
                registrarChamada();
                pausar();
                break;

            case 2:
                atenderChamada();
                pausar();
                break;

            case 3:
                consultarTopo();
                pausar();
                break;

            case 4:
                buscarChamada();
                pausar();
                break;

            case 5:
                listarChamadas();
                pausar();
                break;

            case 6:
                estatisticas();
                pausar();
                break;

            case 7:
                gerarRelatorioTXT();
                printf("Relatorio TXT gerado com sucesso\n");
                pausar();
                break;

            case 8:
                salvarCSV();
                printf("Dados salvos com sucesso em dados_b.csv\n");
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
