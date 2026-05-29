# Trabalho 2 - Estrutura de Dados 1
## Carlos Henrique dos Santos Costa Filho - 242042350 - Turma 02 (10h)

Este projeto implementa, em linguagem C, uma solução para padronizar dados legados de contribuintes armazenados em três listas diferentes:

- Indústria: lista simplesmente encadeada.
- Comércio: lista duplamente encadeada sem descritor.
- Serviços: lista duplamente encadeada com descritor.

Depois de carregar os dados dessas listas, o programa gera uma quarta lista unificada, também duplamente encadeada com descritor, adicionando o campo `Tipo` para identificar a origem de cada cadastro:

- `I`: Indústria
- `C`: Comércio
- `S`: Serviço

## Arquivos

- `trabalho2_eda.c`: código-fonte completo do programa.
- `Industria.txt`: dados mock da lista de indústrias.
- `Comercio.txt`: dados mock da lista de comércios.
- `Servico.txt`: dados mock da lista de serviços.

Os arquivos `.txt` usam o seguinte formato por linha:

```txt
CNPJ;RazaoSocial;Cidade;Fone
```

Exemplo:

```txt
11111111000101;Metal Forte Ltda;Brasília;6133330001
```

## Estrutura da Solução

O programa define as estruturas exigidas no enunciado:

- `TCadastro`: dados originais de cada contribuinte.
- `TNoI`: nó da lista simplesmente encadeada de indústrias.
- `TNoC`: nó da lista duplamente encadeada de comércio.
- `TNoS` e `TDescritorS`: lista de serviços com descritor.
- `TCadastroU`: cadastro unificado, com o campo extra `Tipo`.
- `TNoU` e `TDescritorU`: lista unificada com descritor.

A implementação foi modularizada em funções para:

- inicializar descritores;
- carregar e interpretar arquivos `.txt`;
- inserir registros em cada tipo de lista;
- gerar a lista unificada;
- imprimir relatórios em ordem normal e invertida;
- liberar toda a memória alocada dinamicamente.

Ao carregar dados novamente, o programa apaga as listas anteriores antes de recriá-las. Ao gerar uma nova lista unificada, a lista unificada anterior também é liberada antes da nova geração. Isso evita vazamentos de memória quando o usuário repete operações no menu.

## Menu do Programa

O programa possui as seguintes opções:

1. Carregar Dados de Entrada
2. Gerar Lista Unificada
3. Relatório: Indústrias
4. Relatório: Comércio
5. Relatório: Comércio Invertida
6. Relatório: Serviços
7. Relatório: Serviços Invertida
8. Relatório: Lista Unificada
9. Relatório: Lista Unificada Invertida
10. Apagar Listas
0. Sair

A opção `0` também libera a memória antes de encerrar o programa.

## Como Compilar

Abra um terminal no diretório do projeto:

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

No menu, uma sequência básica para testar tudo é:

1. Escolha `1` para carregar os arquivos de entrada.
2. Escolha `2` para gerar a lista unificada.
3. Escolha `8` para imprimir a lista unificada.
4. Escolha `9` para imprimir a lista unificada invertida.
5. Escolha `10` para apagar as listas.
6. Escolha `0` para sair.

## Teste Automático Simples

Também é possível executar uma sequência de menu automaticamente:

```bash
printf '1\n2\n8\n9\n10\n0\n' | ./trabalho2_eda
```

## Verificação com Sanitizers

Para verificar erros de memória durante a execução:

```bash
gcc -std=c11 -Wall -Wextra -pedantic -fsanitize=address,undefined -g trabalho2_eda.c -o trabalho2_eda_asan
printf '1\n2\n8\n9\n10\n0\n' | ./trabalho2_eda_asan
```

Se a execução terminar sem mensagens do AddressSanitizer, não foram detectados acessos inválidos ou vazamentos nessa execução.
