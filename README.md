# Trabalho-av3-Estruturas-Dados

## Integrantes

* Luiz Gustavo Alcântara Couto
* Filipe Araújo de Souza
* Matheus Xavier Dantas
* Marco Antônio Veloso Sousa

## Turma

Turma B

## Temas Escolhidos

### Trabalho A — Listas Simples

**Tema A2: Controle de Estoque**

### Trabalho B — Pilhas Simples

**Tema B2: Chamadas de Emergência**

### Trabalho C — Filas Simples

**Tema C2: Fila de Impressão**

## Estrutura do Repositório

```text
Trabalho_Final_Estruturas_Dados/
├── README.md
├── Trabalho_A/
│   ├── trabalho_a.c
│   └── dados_a.csv
├── Trabalho_B/
│   ├── trabalho_b.c
│   └── dados_b.csv
├── Trabalho_C/
│   ├── trabalho_c.c
│   └── dados_c.csv
└── relatorio.md
```

## Descrição dos Programas

### Trabalho A – Controle de Estoque

O programa simula um sistema de controle de estoque utilizando lista simples implementada com vetor de struct. Cada produto possui código, nome, quantidade e preço. Os produtos permanecem ordenados automaticamente pelo código.

Funcionalidades implementadas:

* cadastrar produto;
* buscar produto por código;
* editar produto;
* excluir produto;
* listar produtos;
* buscar por nome;
* exibir estatísticas;
* salvar em CSV;
* carregar CSV;
* gerar relatório TXT.

### Trabalho B – Chamadas de Emergência

O programa simula uma pilha de chamadas de emergência utilizando a lógica LIFO (Last In, First Out). A última chamada registrada é a primeira chamada atendida.

Funcionalidades implementadas:

* registrar chamada;
* atender chamada;
* consultar topo da pilha;
* buscar chamada por protocolo;
* listar chamadas;
* exibir estatísticas;
* salvar em CSV;
* carregar CSV;
* gerar relatório TXT.

### Trabalho C – Fila de Impressão

O programa simula uma fila de impressão utilizando uma fila normal simples e uma fila circular simples para trabalhos prioritários.

Os trabalhos prioritários são processados antes dos trabalhos normais.

Funcionalidades implementadas:

* cadastrar trabalho de impressão;
* processar próximo trabalho;
* consultar próximo trabalho;
* buscar trabalho por ID;
* cancelar trabalho;
* listar filas;
* exibir estatísticas;
* salvar em CSV;
* carregar CSV;
* gerar relatório TXT.

## Instruções para Compilar

### Trabalho A

```bash
gcc Trabalho_A/trabalho_a.c -o trabalho_a
```

### Trabalho B

```bash
gcc Trabalho_B/trabalho_b.c -o trabalho_b
```

### Trabalho C

```bash
gcc Trabalho_C/trabalho_c.c -o trabalho_c
```

## Instruções para Executar

### Linux

```bash
./trabalho_a
./trabalho_b
./trabalho_c
```

### Windows

```bash
trabalho_a.exe
trabalho_b.exe
trabalho_c.exe
```

## Arquivos CSV

Os programas utilizam persistência de dados em arquivos CSV.

Arquivos utilizados:

* dados_a.csv
* dados_b.csv
* dados_c.csv

Ao iniciar, cada programa tenta carregar automaticamente os dados do respectivo arquivo. Caso o arquivo não exista, o sistema inicia normalmente com a estrutura vazia.

## Extras Implementados

Foram adicionadas algumas funcionalidades extras além dos requisitos obrigatórios:

* estatísticas dos registros;
* geração de relatórios TXT;
* mensagens mais amigáveis;
* validações adicionais;
* confirmação antes de operações críticas;
* salvamento automático ao encerrar;
* busca complementar quando aplicável.

## Dificuldades Encontradas

Durante o desenvolvimento, uma das principais dificuldades foi a exibição das informações no terminal. Em alguns testes, as operações eram executadas corretamente, porém o programa retornava rapidamente ao menu principal, dificultando a visualização dos resultados.

Para solucionar esse problema, foi adicionada uma função de pausa após operações importantes, permitindo que o usuário visualize as informações antes de retornar ao menu.

Outra dificuldade foi implementar corretamente a persistência em arquivos CSV, garantindo o carregamento dos dados na inicialização e o salvamento sem perda de informações.

Também foram realizados testes para evitar registros duplicados, tratar estruturas vazias, estruturas cheias e garantir a consistência dos dados após exclusões.

## Observações sobre o Funcionamento

Os três programas foram desenvolvidos de forma independente, conforme solicitado pelo professor, podendo ser compilados e executados separadamente.

A implementação principal utiliza vetores de struct, seguindo os requisitos obrigatórios da disciplina. A utilização de estruturas encadeadas e alocação dinâmica foi estudada, porém não foi utilizada na versão principal do projeto.
