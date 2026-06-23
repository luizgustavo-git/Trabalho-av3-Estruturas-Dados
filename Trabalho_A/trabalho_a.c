#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define ARQUIVO_CSV "dados_a.csv"
#define ARQUIVO_RELATORIO "relatorio_estoque.txt"

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

Produto lista[MAX];
int quantidade = 0;

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
    printf("       CONTROLE DE ESTOQUE\n");
    printf("=====================================\n");
}

int buscarPosicaoPorCodigo(int codigo) {
    int i;

    for (i = 0; i < quantidade; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}

void listarProdutos() {
    int i;

    cabecalho();

    if (quantidade == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nLISTA DE PRODUTOS:\n");

    for (i = 0; i < quantidade; i++) {
        printf("\nCodigo: %d\n", lista[i].codigo);
        printf("Nome: %s\n", lista[i].nome);
        printf("Quantidade: %d\n", lista[i].quantidade);
        printf("Preco: R$ %.2f\n", lista[i].preco);
    }
}

void inserirProdutoOrdenado(Produto novo) {
    int i = quantidade - 1;

    while (i >= 0 && lista[i].codigo > novo.codigo) {
        lista[i + 1] = lista[i];
        i--;
    }

    lista[i + 1] = novo;
    quantidade++;
}

void cadastrarProduto() {
    Produto novo;

    cabecalho();

    if (quantidade >= MAX) {
        printf("Lista cheia. Nao e possivel cadastrar mais produtos.\n");
        return;
    }

    printf("Digite o codigo do produto: ");
    scanf("%d", &novo.codigo);
    limparBuffer();

    if (buscarPosicaoPorCodigo(novo.codigo) != -1) {
        printf("Erro: ja existe um produto com esse codigo.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    removerQuebraLinha(novo.nome);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novo.quantidade);

    while (novo.quantidade < 0) {
        printf("Quantidade invalida. Digite novamente: ");
        scanf("%d", &novo.quantidade);
    }

    printf("Digite o preco unitario: ");
    scanf("%f", &novo.preco);

    while (novo.preco < 0) {
        printf("Preco invalido. Digite novamente: ");
        scanf("%f", &novo.preco);
    }

    limparBuffer();

    inserirProdutoOrdenado(novo);

    printf("Produto cadastrado com sucesso.\n");
}

void buscarProduto() {
    int codigo, pos;

    cabecalho();

    if (quantidade == 0) {
        printf("Lista vazia. Nenhum produto para buscar.\n");
        return;
    }

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    limparBuffer();

    pos = buscarPosicaoPorCodigo(codigo);

    if (pos == -1) {
        printf("Produto nao encontrado.\n");
    } else {
        printf("\nProduto encontrado:\n");
        printf("Codigo: %d\n", lista[pos].codigo);
        printf("Nome: %s\n", lista[pos].nome);
        printf("Quantidade: %d\n", lista[pos].quantidade);
        printf("Preco: R$ %.2f\n", lista[pos].preco);
    }
}

void editarProduto() {
    int codigo, pos;

    cabecalho();

    if (quantidade == 0) {
        printf("Lista vazia. Nenhum produto para editar.\n");
        return;
    }

    printf("Digite o codigo do produto que deseja editar: ");
    scanf("%d", &codigo);
    limparBuffer();

    pos = buscarPosicaoPorCodigo(codigo);

    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("\nEditando produto codigo %d\n", lista[pos].codigo);

    printf("Novo nome: ");
    fgets(lista[pos].nome, sizeof(lista[pos].nome), stdin);
    removerQuebraLinha(lista[pos].nome);

    printf("Nova quantidade: ");
    scanf("%d", &lista[pos].quantidade);

    while (lista[pos].quantidade < 0) {
        printf("Quantidade invalida. Digite novamente: ");
        scanf("%d", &lista[pos].quantidade);
    }

    printf("Novo preco: ");
    scanf("%f", &lista[pos].preco);

    while (lista[pos].preco < 0) {
        printf("Preco invalido. Digite novamente: ");
        scanf("%f", &lista[pos].preco);
    }

    limparBuffer();

    printf("Produto editado com sucesso. O codigo nao foi alterado.\n");
}

void excluirProduto() {
    int codigo, pos, i;
    char confirma;

    cabecalho();

    if (quantidade == 0) {
        printf("Lista vazia. Nenhum produto para excluir.\n");
        return;
    }

    printf("Digite o codigo do produto que deseja excluir: ");
    scanf("%d", &codigo);
    limparBuffer();

    pos = buscarPosicaoPorCodigo(codigo);

    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("\nProduto encontrado: %s\n", lista[pos].nome);
    printf("Deseja realmente excluir? (S/N): ");
    scanf(" %c", &confirma);
    limparBuffer();

    if (confirma != 'S' && confirma != 's') {
        printf("Exclusao cancelada.\n");
        return;
    }

    for (i = pos; i < quantidade - 1; i++) {
        lista[i] = lista[i + 1];
    }

    quantidade--;

    printf("Produto excluido com sucesso.\n");
}

void buscarPorNome() {
    char termo[50];
    int i, encontrou = 0;

    cabecalho();

    if (quantidade == 0) {
        printf("Lista vazia. Nenhum produto para buscar.\n");
        return;
    }

    printf("Digite parte do nome do produto: ");
    fgets(termo, sizeof(termo), stdin);
    removerQuebraLinha(termo);

    printf("\nResultado da busca:\n");

    for (i = 0; i < quantidade; i++) {
        if (strstr(lista[i].nome, termo) != NULL) {
            printf("\nCodigo: %d\n", lista[i].codigo);
            printf("Nome: %s\n", lista[i].nome);
            printf("Quantidade: %d\n", lista[i].quantidade);
            printf("Preco: R$ %.2f\n", lista[i].preco);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum produto encontrado com esse nome.\n");
    }
}

void estatisticasEstoque() {
    int i;
    int totalItens = 0;
    float valorTotal = 0;

    cabecalho();

    if (quantidade == 0) {
        printf("Lista vazia. Nao ha estatisticas para mostrar.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        totalItens += lista[i].quantidade;
        valorTotal += lista[i].quantidade * lista[i].preco;
    }

    printf("Total de produtos cadastrados: %d\n", quantidade);
    printf("Quantidade total de itens em estoque: %d\n", totalItens);
    printf("Valor total do estoque: R$ %.2f\n", valorTotal);
}

void salvarCSV() {
    FILE *arquivo;
    int i;

    arquivo = fopen(ARQUIVO_CSV, "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar o arquivo CSV.\n");
        return;
    }

    fprintf(arquivo, "codigo;nome;quantidade;preco\n");

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d;%s;%d;%.2f\n",
                lista[i].codigo,
                lista[i].nome,
                lista[i].quantidade,
                lista[i].preco);
    }

    fclose(arquivo);
}

void carregarCSV() {
    FILE *arquivo;
    char linha[256];
    Produto produto;
    char *campo;

    arquivo = fopen(ARQUIVO_CSV, "r");

    if (arquivo == NULL) {
        printf("Arquivo dados_a.csv nao encontrado. Iniciando lista vazia.\n");
        return;
    }

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        produto.codigo = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(produto.nome, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        produto.quantidade = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        produto.preco = atof(campo);

        if (quantidade < MAX && buscarPosicaoPorCodigo(produto.codigo) == -1) {
            inserirProdutoOrdenado(produto);
        }
    }

    fclose(arquivo);
}

void gerarRelatorioTXT() {
    FILE *arquivo;
    int i;
    int totalItens = 0;
    float valorTotal = 0;

    cabecalho();

    arquivo = fopen(ARQUIVO_RELATORIO, "w");

    if (arquivo == NULL) {
        printf("Erro ao gerar relatorio.\n");
        return;
    }

    fprintf(arquivo, "RELATORIO DO CONTROLE DE ESTOQUE\n");
    fprintf(arquivo, "=================================\n\n");

    if (quantidade == 0) {
        fprintf(arquivo, "Nenhum produto cadastrado.\n");
    } else {
        for (i = 0; i < quantidade; i++) {
            fprintf(arquivo, "Codigo: %d\n", lista[i].codigo);
            fprintf(arquivo, "Nome: %s\n", lista[i].nome);
            fprintf(arquivo, "Quantidade: %d\n", lista[i].quantidade);
            fprintf(arquivo, "Preco: R$ %.2f\n\n", lista[i].preco);

            totalItens += lista[i].quantidade;
            valorTotal += lista[i].quantidade * lista[i].preco;
        }

        fprintf(arquivo, "Total de produtos cadastrados: %d\n", quantidade);
        fprintf(arquivo, "Quantidade total de itens: %d\n", totalItens);
        fprintf(arquivo, "Valor total do estoque: R$ %.2f\n", valorTotal);
    }

    fclose(arquivo);

    printf("Relatorio gerado com sucesso em relatorio_estoque.txt\n");
}

void menu() {
    printf("\n========== MENU ==========\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Buscar produto por codigo\n");
    printf("3 - Editar produto\n");
    printf("4 - Excluir produto\n");
    printf("5 - Listar produtos\n");
    printf("6 - Buscar produto por nome\n");
    printf("7 - Estatisticas do estoque\n");
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
                cadastrarProduto();
                salvarCSV();
                pausar();
                break;

            case 2:
                buscarProduto();
                pausar();
                break;

            case 3:
                editarProduto();
                pausar();
                break;

            case 4:
                excluirProduto();
                pausar();
                break;

            case 5:
                listarProdutos();
                pausar();
                break;

            case 6:
                buscarPorNome();
                pausar();
                break;

            case 7:
                estatisticasEstoque();
                pausar();
                break;

            case 8:
                gerarRelatorioTXT();
                printf("Relatorio TXT gerado com sucesso\n");
                pausar();
                break;

            case 9:
                salvarCSV();
                printf("Dados salvos com sucesso em dados_a.csv\n");
                pausar();
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
