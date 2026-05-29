#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cadastro {
    char CNPJ[15];
    char RazaoSocial[50];
    char Cidade[30];
    char Fone[12];
} TCadastro;

typedef struct NoI {
    TCadastro *Dados;
    struct NoI *Prox;
} TNoI;

typedef struct NoC {
    TCadastro *Dados;
    struct NoC *Ant;
    struct NoC *Prox;
} TNoC;

typedef struct NoS {
    TCadastro *Dados;
    struct NoS *Ant;
    struct NoS *Prox;
} TNoS;

typedef struct DescritorS {
    TNoS *Inicio;
    int Tamanho;
    TNoS *Fim;
} TDescritorS;

typedef struct CadastroU {
    char CNPJ[15];
    char RazaoSocial[50];
    char Cidade[30];
    char Fone[12];
    char Tipo;
} TCadastroU;

typedef struct NoU {
    TCadastroU *Dados;
    struct NoU *Ant;
    struct NoU *Prox;
} TNoU;

typedef struct DescritorU {
    TNoU *Inicio;
    int Tamanho;
    TNoU *Fim;
} TDescritorU;

static void inicializar_servicos(TDescritorS *lista) {
    if (lista == NULL) {
        return;
    }

    lista->Inicio = NULL;
    lista->Tamanho = 0;
    lista->Fim = NULL;
}

static void inicializar_unificada(TDescritorU *lista) {
    if (lista == NULL) {
        return;
    }

    lista->Inicio = NULL;
    lista->Tamanho = 0;
    lista->Fim = NULL;
}

static void copiar_texto(char *destino, size_t tamanho, const char *origem) {
    if (destino == NULL || tamanho == 0) {
        return;
    }

    if (origem == NULL) {
        destino[0] = '\0';
        return;
    }

    strncpy(destino, origem, tamanho - 1);
    destino[tamanho - 1] = '\0';
}

static void remover_quebra_linha(char *texto) {
    if (texto == NULL) {
        return;
    }

    texto[strcspn(texto, "\r\n")] = '\0';
}

static int parse_cadastro(char *linha, TCadastro *cadastro) {
    char *campos[4];
    int i;

    if (linha == NULL || cadastro == NULL) {
        return 0;
    }

    remover_quebra_linha(linha);

    campos[0] = strtok(linha, ";");
    for (i = 1; i < 4; i++) {
        campos[i] = strtok(NULL, ";");
    }

    if (campos[0] == NULL || campos[1] == NULL || campos[2] == NULL || campos[3] == NULL) {
        return 0;
    }

    copiar_texto(cadastro->CNPJ, sizeof(cadastro->CNPJ), campos[0]);
    copiar_texto(cadastro->RazaoSocial, sizeof(cadastro->RazaoSocial), campos[1]);
    copiar_texto(cadastro->Cidade, sizeof(cadastro->Cidade), campos[2]);
    copiar_texto(cadastro->Fone, sizeof(cadastro->Fone), campos[3]);

    return 1;
}

static TCadastro *criar_cadastro(const TCadastro *origem) {
    TCadastro *novo = (TCadastro *)malloc(sizeof(TCadastro));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente para cadastro.\n");
        return NULL;
    }

    if (origem != NULL) {
        *novo = *origem;
    }

    return novo;
}

static TNoI *criar_no_industria(const TCadastro *cadastro) {
    TNoI *novo = (TNoI *)malloc(sizeof(TNoI));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente para no de industria.\n");
        return NULL;
    }

    novo->Dados = criar_cadastro(cadastro);
    if (novo->Dados == NULL) {
        free(novo);
        return NULL;
    }

    novo->Prox = NULL;
    return novo;
}

static TNoC *criar_no_comercio(const TCadastro *cadastro) {
    TNoC *novo = (TNoC *)malloc(sizeof(TNoC));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente para no de comercio.\n");
        return NULL;
    }

    novo->Dados = criar_cadastro(cadastro);
    if (novo->Dados == NULL) {
        free(novo);
        return NULL;
    }

    novo->Ant = NULL;
    novo->Prox = NULL;
    return novo;
}

static TNoS *criar_no_servico(const TCadastro *cadastro) {
    TNoS *novo = (TNoS *)malloc(sizeof(TNoS));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente para no de servico.\n");
        return NULL;
    }

    novo->Dados = criar_cadastro(cadastro);
    if (novo->Dados == NULL) {
        free(novo);
        return NULL;
    }

    novo->Ant = NULL;
    novo->Prox = NULL;
    return novo;
}

static TNoU *criar_no_unificado(const TCadastro *cadastro, char tipo) {
    TNoU *novo = (TNoU *)malloc(sizeof(TNoU));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente para no unificado.\n");
        return NULL;
    }

    novo->Dados = (TCadastroU *)malloc(sizeof(TCadastroU));
    if (novo->Dados == NULL) {
        printf("Erro: memoria insuficiente para cadastro unificado.\n");
        free(novo);
        return NULL;
    }

    copiar_texto(novo->Dados->CNPJ, sizeof(novo->Dados->CNPJ), cadastro->CNPJ);
    copiar_texto(novo->Dados->RazaoSocial, sizeof(novo->Dados->RazaoSocial), cadastro->RazaoSocial);
    copiar_texto(novo->Dados->Cidade, sizeof(novo->Dados->Cidade), cadastro->Cidade);
    copiar_texto(novo->Dados->Fone, sizeof(novo->Dados->Fone), cadastro->Fone);
    novo->Dados->Tipo = tipo;
    novo->Ant = NULL;
    novo->Prox = NULL;

    return novo;
}

static int inserir_industria(TNoI **inicio, const TCadastro *cadastro) {
    TNoI *novo;
    TNoI *atual;

    if (inicio == NULL || cadastro == NULL) {
        return 0;
    }

    novo = criar_no_industria(cadastro);
    if (novo == NULL) {
        return 0;
    }

    if (*inicio == NULL) {
        *inicio = novo;
        return 1;
    }

    atual = *inicio;
    while (atual->Prox != NULL) {
        atual = atual->Prox;
    }

    atual->Prox = novo;
    return 1;
}

static int inserir_comercio(TNoC **inicio, const TCadastro *cadastro) {
    TNoC *novo;
    TNoC *atual;

    if (inicio == NULL || cadastro == NULL) {
        return 0;
    }

    novo = criar_no_comercio(cadastro);
    if (novo == NULL) {
        return 0;
    }

    if (*inicio == NULL) {
        *inicio = novo;
        return 1;
    }

    atual = *inicio;
    while (atual->Prox != NULL) {
        atual = atual->Prox;
    }

    atual->Prox = novo;
    novo->Ant = atual;
    return 1;
}

static int inserir_servico(TDescritorS *lista, const TCadastro *cadastro) {
    TNoS *novo;

    if (lista == NULL || cadastro == NULL) {
        return 0;
    }

    novo = criar_no_servico(cadastro);
    if (novo == NULL) {
        return 0;
    }

    if (lista->Inicio == NULL) {
        lista->Inicio = novo;
        lista->Fim = novo;
    } else {
        novo->Ant = lista->Fim;
        lista->Fim->Prox = novo;
        lista->Fim = novo;
    }

    lista->Tamanho++;
    return 1;
}

static int inserir_unificado(TDescritorU *lista, const TCadastro *cadastro, char tipo) {
    TNoU *novo;

    if (lista == NULL || cadastro == NULL) {
        return 0;
    }

    novo = criar_no_unificado(cadastro, tipo);
    if (novo == NULL) {
        return 0;
    }

    if (lista->Inicio == NULL) {
        lista->Inicio = novo;
        lista->Fim = novo;
    } else {
        novo->Ant = lista->Fim;
        lista->Fim->Prox = novo;
        lista->Fim = novo;
    }

    lista->Tamanho++;
    return 1;
}

static int carregar_arquivo_industria(const char *nome_arquivo, TNoI **lista) {
    FILE *arquivo;
    char linha[256];
    int carregados = 0;
    int linha_atual = 0;

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir %s.\n", nome_arquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        TCadastro cadastro;
        linha_atual++;

        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') {
            continue;
        }

        if (!parse_cadastro(linha, &cadastro)) {
            printf("Aviso: linha %d invalida em %s.\n", linha_atual, nome_arquivo);
            continue;
        }

        if (inserir_industria(lista, &cadastro)) {
            carregados++;
        }
    }

    fclose(arquivo);
    return carregados;
}

static int carregar_arquivo_comercio(const char *nome_arquivo, TNoC **lista) {
    FILE *arquivo;
    char linha[256];
    int carregados = 0;
    int linha_atual = 0;

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir %s.\n", nome_arquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        TCadastro cadastro;
        linha_atual++;

        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') {
            continue;
        }

        if (!parse_cadastro(linha, &cadastro)) {
            printf("Aviso: linha %d invalida em %s.\n", linha_atual, nome_arquivo);
            continue;
        }

        if (inserir_comercio(lista, &cadastro)) {
            carregados++;
        }
    }

    fclose(arquivo);
    return carregados;
}

static int carregar_arquivo_servico(const char *nome_arquivo, TDescritorS *lista) {
    FILE *arquivo;
    char linha[256];
    int carregados = 0;
    int linha_atual = 0;

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir %s.\n", nome_arquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        TCadastro cadastro;
        linha_atual++;

        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') {
            continue;
        }

        if (!parse_cadastro(linha, &cadastro)) {
            printf("Aviso: linha %d invalida em %s.\n", linha_atual, nome_arquivo);
            continue;
        }

        if (inserir_servico(lista, &cadastro)) {
            carregados++;
        }
    }

    fclose(arquivo);
    return carregados;
}

static void imprimir_cadastro(const TCadastro *cadastro) {
    if (cadastro == NULL) {
        return;
    }

    printf("CNPJ: %s | Razao Social: %s | Cidade: %s | Fone: %s\n",
           cadastro->CNPJ,
           cadastro->RazaoSocial,
           cadastro->Cidade,
           cadastro->Fone);
}

static void imprimir_cadastro_unificado(const TCadastroU *cadastro) {
    if (cadastro == NULL) {
        return;
    }

    printf("CNPJ: %s | Razao Social: %s | Cidade: %s | Fone: %s | Tipo: %c\n",
           cadastro->CNPJ,
           cadastro->RazaoSocial,
           cadastro->Cidade,
           cadastro->Fone,
           cadastro->Tipo);
}

static void imprimir_industrias(TNoI *inicio) {
    int contador = 0;

    printf("\n--- Relatorio: Industrias ---\n");
    while (inicio != NULL) {
        contador++;
        printf("%d. ", contador);
        imprimir_cadastro(inicio->Dados);
        inicio = inicio->Prox;
    }

    if (contador == 0) {
        printf("Lista vazia.\n");
    }
}

static void imprimir_comercio(TNoC *inicio) {
    int contador = 0;

    printf("\n--- Relatorio: Comercio ---\n");
    while (inicio != NULL) {
        contador++;
        printf("%d. ", contador);
        imprimir_cadastro(inicio->Dados);
        inicio = inicio->Prox;
    }

    if (contador == 0) {
        printf("Lista vazia.\n");
    }
}

static void imprimir_comercio_invertida(TNoC *inicio) {
    TNoC *atual = inicio;
    int contador = 0;

    printf("\n--- Relatorio: Comercio Invertida ---\n");
    if (atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    while (atual->Prox != NULL) {
        atual = atual->Prox;
    }

    while (atual != NULL) {
        contador++;
        printf("%d. ", contador);
        imprimir_cadastro(atual->Dados);
        atual = atual->Ant;
    }
}

static void imprimir_servicos(TDescritorS *lista) {
    TNoS *atual;
    int contador = 0;

    printf("\n--- Relatorio: Servicos ---\n");
    if (lista == NULL || lista->Inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    atual = lista->Inicio;
    while (atual != NULL) {
        contador++;
        printf("%d. ", contador);
        imprimir_cadastro(atual->Dados);
        atual = atual->Prox;
    }
}

static void imprimir_servicos_invertida(TDescritorS *lista) {
    TNoS *atual;
    int contador = 0;

    printf("\n--- Relatorio: Servicos Invertida ---\n");
    if (lista == NULL || lista->Fim == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    atual = lista->Fim;
    while (atual != NULL) {
        contador++;
        printf("%d. ", contador);
        imprimir_cadastro(atual->Dados);
        atual = atual->Ant;
    }
}

static void imprimir_unificada(TDescritorU *lista) {
    TNoU *atual;
    int contador = 0;

    printf("\n--- Relatorio: Lista Unificada ---\n");
    if (lista == NULL || lista->Inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    atual = lista->Inicio;
    while (atual != NULL) {
        contador++;
        printf("%d. ", contador);
        imprimir_cadastro_unificado(atual->Dados);
        atual = atual->Prox;
    }
}

static void imprimir_unificada_invertida(TDescritorU *lista) {
    TNoU *atual;
    int contador = 0;

    printf("\n--- Relatorio: Lista Unificada Invertida ---\n");
    if (lista == NULL || lista->Fim == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    atual = lista->Fim;
    while (atual != NULL) {
        contador++;
        printf("%d. ", contador);
        imprimir_cadastro_unificado(atual->Dados);
        atual = atual->Ant;
    }
}

static void liberar_industria(TNoI **inicio) {
    TNoI *atual;

    if (inicio == NULL) {
        return;
    }

    atual = *inicio;
    while (atual != NULL) {
        TNoI *proximo = atual->Prox;
        free(atual->Dados);
        free(atual);
        atual = proximo;
    }

    *inicio = NULL;
}

static void liberar_comercio(TNoC **inicio) {
    TNoC *atual;

    if (inicio == NULL) {
        return;
    }

    atual = *inicio;
    while (atual != NULL) {
        TNoC *proximo = atual->Prox;
        free(atual->Dados);
        free(atual);
        atual = proximo;
    }

    *inicio = NULL;
}

static void liberar_servicos(TDescritorS *lista) {
    TNoS *atual;

    if (lista == NULL) {
        return;
    }

    atual = lista->Inicio;
    while (atual != NULL) {
        TNoS *proximo = atual->Prox;
        free(atual->Dados);
        free(atual);
        atual = proximo;
    }

    inicializar_servicos(lista);
}

static void liberar_unificada(TDescritorU *lista) {
    TNoU *atual;

    if (lista == NULL) {
        return;
    }

    atual = lista->Inicio;
    while (atual != NULL) {
        TNoU *proximo = atual->Prox;
        free(atual->Dados);
        free(atual);
        atual = proximo;
    }

    inicializar_unificada(lista);
}

static void apagar_todas_listas(TNoI **industria, TNoC **comercio, TDescritorS *servicos, TDescritorU *unificada) {
    liberar_industria(industria);
    liberar_comercio(comercio);
    liberar_servicos(servicos);
    liberar_unificada(unificada);
}

static void carregar_dados_entrada(TNoI **industria, TNoC **comercio, TDescritorS *servicos, TDescritorU *unificada) {
    int total_industria;
    int total_comercio;
    int total_servico;

    apagar_todas_listas(industria, comercio, servicos, unificada);

    total_industria = carregar_arquivo_industria("Industria.txt", industria);
    total_comercio = carregar_arquivo_comercio("Comercio.txt", comercio);
    total_servico = carregar_arquivo_servico("Servico.txt", servicos);

    printf("\nDados carregados:\n");
    printf("Industrias: %d\n", total_industria);
    printf("Comercios: %d\n", total_comercio);
    printf("Servicos: %d\n", total_servico);
}

static void gerar_lista_unificada(TNoI *industria, TNoC *comercio, TDescritorS *servicos, TDescritorU *unificada) {
    TNoI *atual_i;
    TNoC *atual_c;
    TNoS *atual_s;

    liberar_unificada(unificada);

    atual_i = industria;
    while (atual_i != NULL) {
        inserir_unificado(unificada, atual_i->Dados, 'I');
        atual_i = atual_i->Prox;
    }

    atual_c = comercio;
    while (atual_c != NULL) {
        inserir_unificado(unificada, atual_c->Dados, 'C');
        atual_c = atual_c->Prox;
    }

    if (servicos != NULL) {
        atual_s = servicos->Inicio;
        while (atual_s != NULL) {
            inserir_unificado(unificada, atual_s->Dados, 'S');
            atual_s = atual_s->Prox;
        }
    }

    printf("\nLista unificada gerada com %d registros.\n", unificada->Tamanho);
}

static void exibir_menu(void) {
    printf("\n========== MENU ==========\n");
    printf("1. Carregar Dados de Entrada\n");
    printf("2. Gerar Lista Unificada\n");
    printf("3. Relatorio: Industrias\n");
    printf("4. Relatorio: Comercio\n");
    printf("5. Relatorio: Comercio Invertida\n");
    printf("6. Relatorio: Servicos\n");
    printf("7. Relatorio: Servicos Invertida\n");
    printf("8. Relatorio: Lista Unificada\n");
    printf("9. Relatorio: Lista Unificada Invertida\n");
    printf("10. Apagar Listas\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    TNoI *lista_industria = NULL;
    TNoC *lista_comercio = NULL;
    TDescritorS lista_servicos;
    TDescritorU lista_unificada;
    int opcao = 0;

    inicializar_servicos(&lista_servicos);
    inicializar_unificada(&lista_unificada);

    do {
        exibir_menu();

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida. Encerrando leitura.\n");
            apagar_todas_listas(&lista_industria, &lista_comercio, &lista_servicos, &lista_unificada);
            return 1;
        }

        switch (opcao) {
            case 1:
                carregar_dados_entrada(&lista_industria, &lista_comercio, &lista_servicos, &lista_unificada);
                break;
            case 2:
                gerar_lista_unificada(lista_industria, lista_comercio, &lista_servicos, &lista_unificada);
                break;
            case 3:
                imprimir_industrias(lista_industria);
                break;
            case 4:
                imprimir_comercio(lista_comercio);
                break;
            case 5:
                imprimir_comercio_invertida(lista_comercio);
                break;
            case 6:
                imprimir_servicos(&lista_servicos);
                break;
            case 7:
                imprimir_servicos_invertida(&lista_servicos);
                break;
            case 8:
                imprimir_unificada(&lista_unificada);
                break;
            case 9:
                imprimir_unificada_invertida(&lista_unificada);
                break;
            case 10:
                apagar_todas_listas(&lista_industria, &lista_comercio, &lista_servicos, &lista_unificada);
                printf("Todas as listas foram apagadas.\n");
                break;
            case 0:
                apagar_todas_listas(&lista_industria, &lista_comercio, &lista_servicos, &lista_unificada);
                printf("Memoria liberada. Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
