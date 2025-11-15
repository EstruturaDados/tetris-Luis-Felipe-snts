#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Representa um bloco do jogo
struct bloco {
    char formato;
    int codigo;
};

// Representa a fila circular de blocos
struct fila_blocos {
    struct bloco lista[TAM_FILA];
    int posInicio;
    int posFim;
    int quantidade;
};

int gerador_codigo = 0;

// Cria um bloco aleatório
struct bloco gerar_bloco() {
    struct bloco novoBloco;
    char formatos[] = {'I', 'O', 'T', 'L'};
    
    novoBloco.formato = formatos[rand() % 4];
    novoBloco.codigo = gerador_codigo;
    gerador_codigo++;
    
    return novoBloco;
}

// Inicializa a fila
void inicializar_fila(struct fila_blocos *fila) {
    fila->posInicio = 0;
    fila->posFim = 0;
    fila->quantidade = 0;
    
    int i;
    for (i = 0; i < TAM_FILA; i++) {
        fila->lista[fila->posFim] = gerar_bloco();
        fila->posFim = (fila->posFim + 1) % TAM_FILA;
        fila->quantidade++;
    }
}

// Verifica se está vazia
int fila_vazia(struct fila_blocos *fila) {
    return fila->quantidade == 0;
}

// Verifica se está cheia
int fila_cheia(struct fila_blocos *fila) {
    return fila->quantidade == TAM_FILA;
}

// Remove bloco da fila
struct bloco obter_bloco(struct fila_blocos *fila) {
    struct bloco retirado;
    
    if (fila_vazia(fila)) {
        printf("Nenhum bloco disponível!\n");
        retirado.formato = '?';
        retirado.codigo = -1;
        return retirado;
    }
    
    retirado = fila->lista[fila->posInicio];
    fila->posInicio = (fila->posInicio + 1) % TAM_FILA;
    fila->quantidade--;
    
    return retirado;
}

// Insere bloco novo
int inserir_bloco(struct fila_blocos *fila) {
    if (fila_cheia(fila)) {
        printf("Fila cheia! Não é possível adicionar agora.\n");
        return 0;
    }
    
    fila->lista[fila->posFim] = gerar_bloco();
    fila->posFim = (fila->posFim + 1) % TAM_FILA;
    fila->quantidade++;
    
    return 1;
}

// Exibe a fila atual
void exibir_fila(struct fila_blocos *fila) {
    printf("\n-- Próximos blocos --\n");
    
    if (fila_vazia(fila)) {
        printf("A fila está vazia!\n");
        return;
    }
    
    int pos = fila->posInicio;
    int i;
    for (i = 0; i < fila->quantidade; i++) {
        printf("[%c %d] ", fila->lista[pos].formato, fila->lista[pos].codigo);
        pos = (pos + 1) % TAM_FILA;
    }
    printf("\n");
}

// Menu principal
void menu() {
    printf("\nSelecione uma ação:\n");
    printf("1 - Usar próximo bloco\n");
    printf("2 - Adicionar novo bloco\n");
    printf("0 - Encerrar\n");
    printf("Opção: ");
}

int main() {
    struct fila_blocos filaPrincipal;
    int escolha;
    struct bloco retirado;
    
    srand(time(NULL));
    
    inicializar_fila(&filaPrincipal);
    
    printf("======= GERENCIADOR DE BLOCOS - TETRIS =======\n");
    printf("Controle a fila de blocos do jogo.\n");
    
    while (1) {
        exibir_fila(&filaPrincipal);
        menu();
        scanf("%d", &escolha);
        
        if (escolha == 1) {
            retirado = obter_bloco(&filaPrincipal);
            if (retirado.codigo >= 0) {
                printf("Bloco utilizado: [%c %d]\n", retirado.formato, retirado.codigo);
            }
        } 
        else if (escolha == 2) {
            if (inserir_bloco(&filaPrincipal)) {
                printf("Novo bloco inserido!\n");
            }
        }
        else if (escolha == 0) {
            printf("Encerrando programa. Até logo!\n");
            break;
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
    }
    
    return 0;
}