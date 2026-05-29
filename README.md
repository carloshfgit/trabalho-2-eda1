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

## Como Compilar e Rodar

### Pré-requisitos
Antes de iniciar, certifique-se de ter instalado em seu sistema:
1. Um compilador C compatível com o padrão C11 (como `gcc` ou `clang`).
   - No **Linux (Ubuntu/Debian)**: `sudo apt install build-essential`
   - No **macOS**: `xcode-select --install`
   - No **Windows**: Use o [WSL](https://learn.microsoft.com/pt-br/windows/wsl/install) ou instale o [MinGW-w64](https://www.mingw-w64.org/).
2. Os arquivos de dados (`Industria.txt`, `Comercio.txt` e `Servico.txt`) localizados no mesmo diretório em que você executará o programa.

---

### Passo 1: Preparar o Ambiente
Abra o seu terminal/linha de comando e navegue até a pasta onde os arquivos do projeto foram extraídos ou clonados:

```bash
cd /caminho/para/a/pasta/do/trabalho-2-eda
```
*(Substitua `/caminho/para/a/pasta/...` pelo diretório real no seu computador)*

---

### Passo 2: Compilação
Compile o arquivo-fonte usando o `gcc` (ou o compilador de sua preferência):

```bash
# Compilação padrão utilizando flags de aviso estritas
gcc -std=c11 -Wall -Wextra -pedantic trabalho2_eda.c -o trabalho2_eda
```

---

### Passo 3: Execução
Após compilar com sucesso, execute o programa conforme o seu sistema operacional:

* **Linux / macOS / WSL**:
  ```bash
  ./trabalho2_eda
  ```
* **Windows (Prompt de Comando ou PowerShell)**:
  ```cmd
  trabalho2_eda.exe
  ```

---

### Fluxo de Teste Sugerido (Menu Interativo)
Ao iniciar o programa, um menu interativo será exibido. Para validar o funcionamento completo de todas as estruturas de dados, siga esta sequência:

1. Digite `1` e pressione `Enter` para carregar as três listas originais a partir dos arquivos `.txt`.
2. Digite `2` e pressione `Enter` para unificar os cadastros em uma quarta lista unificada (duplamente encadeada com descritor).
3. Digite `8` e pressione `Enter` para exibir o relatório da lista unificada na ordem direta.
4. Digite `9` e pressione `Enter` para exibir o relatório da lista unificada na ordem inversa.
5. Digite `10` e pressione `Enter` para esvaziar/liberar a memória de todas as listas.
6. Digite `0` e pressione `Enter` para sair com segurança (liberando qualquer memória restante).

---

### Teste Automático Rápido (Apenas Unix/Linux/macOS/WSL)
Você pode automatizar a execução do fluxo de teste sugerido enviando os comandos do menu diretamente por meio de um pipe:

```bash
printf '1\n2\n8\n9\n10\n0\n' | ./trabalho2_eda
```

---

### Verificação de Memory Leaks e Erros com Sanitizers
Para garantir a integridade da alocação dinâmica e certificar-se de que não há vazamentos de memória (*memory leaks*) ou acessos inválidos, compile o projeto com os *sanitizers* do GCC/Clang:

```bash
# Compilar com AddressSanitizer e UndefinedBehaviorSanitizer ativados
gcc -std=c11 -Wall -Wextra -pedantic -fsanitize=address,undefined -g trabalho2_eda.c -o trabalho2_eda_asan

# Executar o teste automático com a versão instrumentada
printf '1\n2\n8\n9\n10\n0\n' | ./trabalho2_eda_asan
```

Se o programa for finalizado sem imprimir mensagens de erro do AddressSanitizer/UB-Sanitizer no terminal, significa que a gerência de memória foi executada com absoluto sucesso e livre de vazamentos!
