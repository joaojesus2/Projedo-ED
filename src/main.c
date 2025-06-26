#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char arquivoPilha[50];
char arquivoFila[50];
char arquivoFilaPrioridade[50];

typedef struct No{
    char data[50];
    struct No *prox;
}No;

//// Implementação Pilha - Alocação Dinâmica ////

// Verifica se a pilha está vazia
int pilhaVazia(No *topo){
    if(topo == NULL){
        printf("Nenhum paciente foi atendido ainda\n");
        return 1;
    }
    return 0;
}

// Exibe a pilha
void mostrarPilha(No *topo){
    printf("\nPacientes atendidos:\n");
    No *pNo = topo;
    while(pNo != NULL){
        printf("\t| %s |\n",pNo->data);
        pNo = pNo->prox;
    }
}

// Adiciona um nó a pilha 
void push(No **topo, const char *data) {
    No *novoNo = (No*) malloc(sizeof(No));

    strcpy(novoNo->data, data);

    novoNo->prox = *topo;
    *topo = novoNo;
}

// Remove um paciente da pilha
int pop(No **topo) {
    if (pilhaVazia(*topo)) {
        return -1;
    } 
    
    No* tmp = *topo;     
    *topo = tmp->prox;    
    free(tmp);

    return 0;
}

// Retorna paciente do topo da pilha
const char* top(No *topo) {
    if (pilhaVazia(topo)) {
        return "ERRO";
    }
    
    return topo->data;
}

//// Implementação Fila - Alocação Dinâmica ////

// Verifica se a fila está vazia
int filaVazia(No *inicio){
    if(inicio == NULL)
        return 1;
    return 0;
}

// Adiciona o paciente na fila
void adicionarFila(No **front, No **back, const char *valor){
    No *novoNo = (No *)malloc(sizeof(No));
    strcpy(novoNo->data, valor);
    novoNo->prox = NULL;
    if(*back == NULL){
        *front = novoNo;
        *back = novoNo;
    }else{
        (*back)->prox = novoNo;
        *back = novoNo;
    }
    printf("Paciente adicionado à fila\n");
}

// Exibe a fila
void mostrarFila(No *f, No *fP){
    printf("\nPacientes a serem atendidos:\n");
    No *no = f;
    No *noP = fP;
    while(noP != NULL){
        printf("\t| %s |\n", noP->data);
        noP = noP->prox;
    }
    while(no != NULL){
        printf("\t| %s |\n", no->data);
        no = no->prox;
    }
}

// Remove o primeiro paciente da fila
int removerPacienteFila(No **front, No **back) {
    if (*front == NULL) return -1;

    No* tmp = *front;
    *front = (*front)->prox;
    
    if (*front == NULL) *back = NULL;
    free(tmp);
    
    return 0;
}

// Remove o paciente da fila com base na sua identidade
No* removerPacienteFilaPorValor(No **lista, const char *valor) {
    No *atual = *lista;
    No *anterior = NULL;
    
    while(atual != NULL && strcmp(atual->data, valor) != 0){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL) return 0;

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    atual->prox = NULL;

    return atual;
}

// Insere um paciente em uma posição específica com base no paciente anterior
void inserirPacientePosicao(No **inicio, No *anterior, No *paciente) {
    if (anterior == NULL) {
        paciente->prox = *inicio;
        *inicio = paciente;
    } else {
        paciente->prox = anterior->prox;
        anterior->prox = paciente;
    }
}

// Libera a memória de fila e pilha
void limparLista(No *lista){
    No *temp;
    while (lista != NULL){
        temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

//// Persistência de Dados - fila.txt, fila_prioridade.txt, pilha.txt ////

// Carrega os dados dos arquivos de fila
int carregarDadosFilaTXT(No **inicio, No **fim, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) return -1;

    char linha[50];
    
    // Percorre linha a linha do arquivo e adiciona a fila os pacientes
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        adicionarFila(inicio, fim, linha);
    }

    fclose(arquivo);
    return 0;
}

// Carrega os dados do arquivo da pilha 
int carregarDadosPilhaTXT(No **topo) {
    FILE *arquivo = fopen(arquivoPilha, "r");    // Abre o arquivo para leitura 
    if (arquivo == NULL) return -1;     // Erro 
    
    char linha[50];

    // Percorre linha a linha e adiciona os dados na pilha
    while(fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        push(topo, linha);
    }
    
    fclose(arquivo);
    return 0;
}

// Atualiza os dados da fila no arquivo - sobrescrita
int atualizarDadosFilaTXT(No *inicio, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");    
    if (arquivo == NULL) return -1;     
    No *atual = inicio;
    
    // Atualiza o arquivo com os dados da fila atual 
    while (atual != NULL) {
        fprintf(arquivo, "%s\n", atual->data);
        atual = atual->prox;
    }

    fclose(arquivo); 
    return 0;
}

// Atualiza os dados da pilha no arquivo - sobrescrita
int atualizarDadosPilhaTXT(No *topo) {
    int tamanho = 0;
    No *atual = topo;

    while (atual != NULL) {
        tamanho++;
        atual = atual->prox;
    }

    No **vetor = (No **)malloc(tamanho * sizeof(No *));
    atual = topo;

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = atual;
        atual = atual->prox;
    }

    FILE *arquivo = fopen(arquivoPilha, "w"); 
    
    if (arquivo == NULL) {
        free(vetor);
        return -1;
    }

    for (int i = tamanho - 1; i >= 0; i--) {
        fprintf(arquivo, "%s\n", vetor[i]->data);
    }

    fclose(arquivo);
    free(vetor);

    return 0;
}

// Carrega as filas e a pilha com os dados armazenados
int inicializarDadosTXT(No **inicio, No **fim, No **inicioP, No **fimP, No **topo) {
    
    // Abre o arquivo da fila não prioritária e carrega os dados 
    if (carregarDadosFilaTXT(inicio, fim, arquivoFila) == -1) {
        return -1;
    }

    // Abre o arquivo da fila prioritária e carrega os dados
    if (carregarDadosFilaTXT(inicioP, fimP, arquivoFilaPrioridade) == -1) {
        return -1;
    }

    // Abre o arquivo da pilha e carrega os dados
    if(carregarDadosPilhaTXT(topo, arquivoPilha) == -1) {
        return -1;
    }
}

//// Funções para desfazer alterações caso haja erro na escrita dos arquivos de dados ////

// Insere paciente no início da fila
void inserirPacienteInicioFila(No **front, No**back, const char *data) {
    No *novoNo = (No *)malloc(sizeof(No));
    strcpy(novoNo->data, data);
    novoNo->prox = *front;
    *front = novoNo;
    if (*back == NULL) {
        *back = novoNo;
    }
}

// Atende o paciente
void atenderPaciente(No **front, No **back, No **topo, const char *nomeArquivoFila){
    
    char data[50];  
    strcpy(data, (*front)->data);   
    removerPacienteFila(front, back);   
    push(topo, data);   

    // Tenta atualizar os arquivos com as alterações - caso não dê alerta e desfaz as alterações
    if (atualizarDadosFilaTXT(*front, nomeArquivoFila) == -1 || atualizarDadosPilhaTXT(*topo, arquivoPilha) == -1) {
        printf("Não foi possível atualizar a base de dados.\nTente novamente...\n\n");
        pop(topo);
        inserirPacienteInicioFila(front, back, data);
    } else {
        printf("\nPaciente Atendido!\n");
    }
    
}

//// Programa Principal ////
int main()
{
    No *topo = NULL;    // topo - pilha
    No *inicio = NULL;  // início - fila de pacientes não prioritários
    No *fim = NULL; // fim - fila de pacientes não prioritários
    No *inicioP = NULL; // inicio - fila de prioridade
    No *fimP = NULL; // fim - fila de prioridade
    char valor[50];
    char simNao;
    char opcao = -1;

    strcpy(arquivoPilha, "db/pilha.txt");
    strcpy(arquivoFila, "db/fila.txt");
    strcpy(arquivoFilaPrioridade, "db/fila_prioridade.txt");

    if (inicializarDadosTXT(&inicio, &fim, &inicioP, &fimP, &topo) == -1) {
        printf("Erro ao carregar os dados da aplicação.\nEncerrando...");
        return -1;
    }
    
    do{
        // menu de opções
        printf("\n========================================\n"
               "    SISTEMA DE GERENCIAMENTO DE FILA    \n"
               "========================================\n"
               "1 - Adicionar paciente à fila\n"
               "2 - Atender próximo paciente\n"
               "3 - Mostrar fila de espera\n"
               "4 - Mostrar pacientes já atendidos\n"
               "5 - Ver próximo paciente\n"
               "6 - Ver último paciente atendido\n"
               "7 - Remover paciente da fila\n"
               "0 - Encerrar o programa\n\n"
               "Digite a opção desejada: ");

        scanf("%hhu",&opcao);
        switch(opcao){
            case 1:
                printf("Digite a identidade do paciente: ");
                scanf(" %49[^\n]", valor);
                printf("O paciente recebe atendimento prioritário? (y/n)\n");
                scanf(" %c", &simNao);
                if(simNao == 'n' || simNao == 'N') {
                    adicionarFila(&inicio, &fim, valor);

                    // Tenta atualizar a base de dados, e informa caso não dê, desfazendo as alterações
                    if (atualizarDadosFilaTXT(inicio, arquivoFila) == -1) {
                        removerPacienteFila(&inicio, &fim);
                        printf("Não foi possível adicionar o paciente...\nTente novamente!\n\n");
                    }
                } else if(simNao == 'y' || simNao == 'Y') {
                    adicionarFila(&inicioP, &fimP, valor);
                    
                    // Tenta atualizar a base de dados, e informa caso não dê, desfazendo as alterações
                    if (atualizarDadosFilaTXT(inicioP, arquivoFilaPrioridade) == -1) {
                        removerPacienteFila(&inicioP, &fimP);
                        printf("Não foi possível adicionar o paciente...\nTente novamente!\n\n");
                    }
                } else {
                    printf("Resposta inválida!");
                }
               break;
            case 2:
                if(!filaVazia(inicioP)){
                    atenderPaciente(&inicioP, &fimP, &topo, arquivoFilaPrioridade);
                }
                else if(!filaVazia(inicio)){
                    atenderPaciente(&inicio, &fim, &topo, arquivoFila);
                }
                else
                    printf("Nenhum paciente foi atendido, pois a fila estava vazia.");
                break;
            case 3:
                if(!filaVazia(inicio) || !filaVazia(inicioP))
                    mostrarFila(inicio, inicioP);
                else
                    printf("A fila está vazia\n");
                break;
            case 4:
                if(!pilhaVazia(topo))
                    mostrarPilha(topo);
                break;
            case 5:
                if(!filaVazia(inicioP))
                    printf("Próximo paciente é: %s\n",inicioP->data);
                else if(!filaVazia(inicio))
                    printf("Próximo paciente é: %s\n",inicio->data);
                break;
            case 6:
                if(!pilhaVazia(topo))
                    printf("Último paciente atendido foi:  %s\n",topo->data);
                break;
            case 7:   
                if(!filaVazia(inicio) || !filaVazia(inicioP)){
                    printf("Digite a identidade do paciente: ");
                    scanf(" %[^\n]", valor);
                    
                    // Armazena paciente anterior para desfazer remoção caso tenha problema na escrita do arquivo 
                    No *anterior = NULL, *atual = inicio;
                    while (atual && strcmp(atual->data, valor) != 0) {
                        anterior = atual;
                        atual = atual->prox;
                    }

                    No *pacienteRemovido = removerPacienteFilaPorValor(&inicio, valor);
                    if(pacienteRemovido) {
                        if (atualizarDadosFilaTXT(inicio, arquivoFila) == -1) {
                            inserirPacientePosicao(&inicio, anterior, pacienteRemovido);
                            printf("\nNão foi possível remover o paciente...\nTente Novamente!\n");
                        } else {
                            free(pacienteRemovido);
                            printf("O paciente foi removido da fila\n");
                        }
                        
                    } else {
                        // Armazena paciente anterior para desfazer remoção caso tenha problema na escrita do arquivo
                        anterior = NULL;
                        atual = inicioP;
                        while (atual && strcmp(atual->data, valor) != 0) {
                            anterior = atual;
                            atual = atual->prox;
                        }

                        pacienteRemovido = removerPacienteFilaPorValor(&inicioP, valor);
                        if (pacienteRemovido) {
                            if (atualizarDadosFilaTXT(inicioP, arquivoFilaPrioridade) == -1) {
                                inserirPacientePosicao(&inicioP, anterior, pacienteRemovido);
                                printf("\nNão foi possível remover o paciente...\nTente Novamente!\n");
                            } else {
                                free(pacienteRemovido);
                                printf("O paciente foi removido da fila\n");
                            }
                        } else {
                            printf("O paciente não foi encontrado\n");
                        }
                    }  
                } else {
                    printf("Não há pacientes na fila...\n");
                }
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    printf("Encerrando o programa...\n");

    // Limpa memória
    limparLista(inicioP);   
    limparLista(inicio);    
    limparLista(topo);  
    
    return 0;
}
