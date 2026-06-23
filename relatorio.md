# Relatório do Trabalho Prático – Estruturas de Dados

## Integrantes

* Luiz Gustavo Alcântara Couto
* Filipe Araújo de Souza
* Matheus Xavier Dantas
* Marco Antônio Veloso Sousa

## Turma

Turma B

---

# Introdução

Este trabalho teve como objetivo aplicar os conceitos estudados na disciplina de Estruturas de Dados por meio da implementação de três programas independentes em linguagem C. Cada programa utilizou uma estrutura de dados específica estudada durante o semestre: listas simples, pilhas simples e filas simples/circulares.

Os programas foram desenvolvidos utilizando vetores de struct, conforme solicitado nas orientações do trabalho, além da utilização de arquivos CSV para persistência dos dados.

---

# Escolha dos Temas

Para o desenvolvimento do trabalho foram escolhidos os seguintes temas:

## Trabalho A – Controle de Estoque

O tema Controle de Estoque foi escolhido por representar uma aplicação prática para listas simples. Além disso, permitiu trabalhar com inserção ordenada, busca, edição, exclusão e listagem de registros.

## Trabalho B – Chamadas de Emergência

O tema Chamadas de Emergência foi escolhido por representar claramente o funcionamento de uma pilha simples. A lógica LIFO (Last In, First Out) pode ser observada facilmente quando a última chamada registrada é a primeira a ser atendida.

## Trabalho C – Fila de Impressão

O tema Fila de Impressão foi escolhido por permitir a utilização simultânea de uma fila simples e de uma fila circular simples. O tema também possibilita demonstrar a prioridade de processamento dos trabalhos classificados como prioritários.

---

# Estruturas Utilizadas

## Lista Simples

No Trabalho A foi utilizada uma lista simples implementada através de um vetor de struct e uma variável de controle chamada quantidade.

A lista armazena os produtos cadastrados e mantém os registros ordenados automaticamente pelo código do produto.

Principais operações implementadas:

* inserção;
* busca;
* edição;
* exclusão;
* listagem;
* carregamento e salvamento em CSV.

---

## Pilha Simples

No Trabalho B foi utilizada uma pilha simples implementada através de vetor de struct e da variável topo.

A pilha segue a lógica LIFO, onde o último elemento inserido é o primeiro a ser removido.

Principais operações implementadas:

* push (registrar chamada);
* pop (atender chamada);
* peek (consultar topo);
* listagem;
* carregamento e salvamento em CSV.

---

## Fila Simples e Fila Circular

No Trabalho C foram utilizadas duas filas:

* fila simples para trabalhos normais;
* fila circular simples para trabalhos prioritários.

A fila simples segue a lógica FIFO (First In, First Out), enquanto a fila circular utiliza os índices de início e fim para reaproveitamento das posições do vetor.

Principais operações implementadas:

* enfileirar;
* desenfileirar;
* consulta do próximo elemento;
* busca;
* cancelamento;
* carregamento e salvamento em CSV.

---

# Decisões de Implementação

Durante o desenvolvimento optou-se por utilizar vetores de struct em todos os programas, seguindo a recomendação da versão obrigatória do trabalho.

Também foi adotada uma organização baseada em funções específicas para cada operação, tornando o código mais organizado e facilitando a manutenção.

Os arquivos CSV foram carregados automaticamente no início da execução dos programas e salvos novamente ao final, permitindo a persistência dos dados entre diferentes execuções.

Além dos requisitos obrigatórios, foram implementados alguns recursos extras, como:

* estatísticas dos registros;
* geração de relatórios em arquivo TXT;
* mensagens mais amigáveis;
* validações adicionais;
* confirmações antes de operações críticas.

---

# Dificuldades Encontradas

Uma das principais dificuldades encontradas foi o controle da exibição das informações no terminal.

Durante os testes iniciais, algumas operações eram executadas corretamente, porém o programa retornava rapidamente ao menu principal, dificultando a visualização dos resultados pelo usuário.

Para resolver esse problema, foi criada uma função de pausa após operações importantes, permitindo que as informações permanecessem visíveis antes do retorno ao menu.

Outra dificuldade foi garantir a persistência correta dos dados utilizando arquivos CSV. Foi necessário validar a leitura dos arquivos, ignorar o cabeçalho e evitar registros duplicados durante o carregamento.

Também foram realizados testes para tratar corretamente situações como:

* estrutura vazia;
* estrutura cheia;
* chaves duplicadas;
* remoção de registros;
* busca de registros inexistentes;
* carregamento de arquivos inexistentes.

---

# Testes Realizados

Foram realizados diversos testes para verificar o funcionamento dos programas.

Entre os testes realizados estão:

* inserção de registros;
* busca de registros existentes;
* busca de registros inexistentes;
* edição de registros;
* exclusão de registros;
* listagem completa;
* salvamento em CSV;
* carregamento automático do CSV;
* funcionamento das estruturas vazias;
* funcionamento das estruturas cheias;
* validação de chaves duplicadas.

Os testes demonstraram que as funcionalidades implementadas atendem aos requisitos definidos para o trabalho.

---

# Conclusão

O desenvolvimento deste trabalho permitiu aplicar na prática os conceitos estudados sobre listas, pilhas e filas.

A implementação das estruturas utilizando vetores de struct contribuiu para a compreensão do funcionamento interno de cada estrutura de dados, bem como das operações de inserção, remoção, busca e organização dos registros.

Além disso, a utilização de arquivos CSV possibilitou a persistência dos dados e tornou os programas mais próximos de aplicações reais.

O trabalho contribuiu para o fortalecimento dos conhecimentos em linguagem C e Estruturas de Dados, demonstrando a aplicação prática dos conteúdos estudados durante o semestre.
