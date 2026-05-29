# Trabalho 2 - EDA

Este projeto implementa, em linguagem C, uma solucao para padronizar dados legados de contribuintes armazenados em tres listas diferentes:

- Industria: lista simplesmente encadeada.
- Comercio: lista duplamente encadeada sem descritor.
- Servicos: lista duplamente encadeada com descritor.

Depois de carregar os dados dessas listas, o programa gera uma quarta lista unificada, tambem duplamente encadeada com descritor, adicionando o campo `Tipo` para identificar a origem de cada cadastro:

- `I`: Industria
- `C`: Comercio
- `S`: Servico

## Arquivos

- `trabalho2_eda.c`: codigo-fonte completo do programa.
- `Industria.txt`: dados mock da lista de industrias.
- `Comercio.txt`: dados mock da lista de comercios.
- `Servico.txt`: dados mock da lista de servicos.

Os arquivos `.txt` usam o seguinte formato por linha:

```txt
CNPJ;RazaoSocial;Cidade;Fone
```

Exemplo:

```txt
11111111000101;Metal Forte Ltda;Brasilia;6133330001
```

## Estrutura Da Solucao

O programa define as estruturas exigidas no enunciado:

- `TCadastro`: dados originais de cada contribuinte.
- `TNoI`: no da lista simplesmente encadeada de industrias.
- `TNoC`: no da lista duplamente encadeada de comercio.
- `TNoS` e `TDescritorS`: lista de servicos com descritor.
- `TCadastroU`: cadastro unificado, com o campo extra `Tipo`.
- `TNoU` e `TDescritorU`: lista unificada com descritor.

A implementacao foi modularizada em funcoes para:

- inicializar descritores;
- carregar e interpretar arquivos `.txt`;
- inserir registros em cada tipo de lista;
- gerar a lista unificada;
- imprimir relatorios em ordem normal e invertida;
- liberar toda a memoria alocada dinamicamente.

Ao carregar dados novamente, o programa apaga as listas anteriores antes de recria-las. Ao gerar uma nova lista unificada, a lista unificada anterior tambem e liberada antes da nova geracao. Isso evita vazamentos de memoria quando o usuario repete operacoes no menu.

## Menu Do Programa

O programa possui as seguintes opcoes:

1. Carregar Dados de Entrada
2. Gerar Lista Unificada
3. Relatorio: Industrias
4. Relatorio: Comercio
5. Relatorio: Comercio Invertida
6. Relatorio: Servicos
7. Relatorio: Servicos Invertida
8. Relatorio: Lista Unificada
9. Relatorio: Lista Unificada Invertida
10. Apagar Listas
0. Sair

A opcao `0` tambem libera a memoria antes de encerrar o programa.

## Como Compilar

Abra um terminal no diretorio do projeto:

```bash
cd /home/carloshf/UNB/eda1/trabalho-2-eda
```

Compile com `gcc`:

```bash
gcc -std=c11 -Wall -Wextra -pedantic trabalho2_eda.c -o trabalho2_eda
```

## Como Rodar

Depois de compilar, execute:

```bash
./trabalho2_eda
```

No menu, uma sequencia basica para testar tudo e:

1. Escolha `1` para carregar os arquivos de entrada.
2. Escolha `2` para gerar a lista unificada.
3. Escolha `8` para imprimir a lista unificada.
4. Escolha `9` para imprimir a lista unificada invertida.
5. Escolha `10` para apagar as listas.
6. Escolha `0` para sair.

## Teste Automatico Simples

Tambem e possivel executar uma sequencia de menu automaticamente:

```bash
printf '1\n2\n8\n9\n10\n0\n' | ./trabalho2_eda
```

## Verificacao Com Sanitizers

Para verificar erros de memoria durante a execucao:

```bash
gcc -std=c11 -Wall -Wextra -pedantic -fsanitize=address,undefined -g trabalho2_eda.c -o trabalho2_eda_asan
printf '1\n2\n8\n9\n10\n0\n' | ./trabalho2_eda_asan
```

Se a execucao terminar sem mensagens do AddressSanitizer, nao foram detectados acessos invalidos ou vazamentos nessa execucao.
