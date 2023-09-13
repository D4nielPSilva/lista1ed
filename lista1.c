#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXSIZE 10

typedef struct Aluno {
    char nome[20];
    int matricula;
    float nota;
} Aluno;

typedef struct ListaAlunos {
    Aluno alunos[MAXSIZE];
    int numElem;
} ListaAlunos;

void preencheAluno(Aluno* ptrAluno, int matricula, float nota, char* nome) {
    (*ptrAluno).matricula = matricula;
    (*ptrAluno).nota = nota;
    strcpy((*ptrAluno).nome, nome);
}

void inicializaLista(ListaAlunos* listaAlunos) {
    listaAlunos->numElem = 0;
}

void exibeLista(ListaAlunos* listaAlunos) {
    int index;
    printf("Exibindo lista...\n");
    for (index = 0; index < listaAlunos->numElem; index++) {
        printf("Aluno %d\n", index);
        printf("Nome: %s\n", listaAlunos->alunos[index].nome);
        printf("Matricula: %d\n", listaAlunos->alunos[index].matricula);
        printf("Nota: %.1f\n", listaAlunos->alunos[index].nota);
    }
}

bool insereAlunoNaLista(ListaAlunos* listaAlunos, Aluno aluno, int posicao) {
    if (listaAlunos->numElem >= MAXSIZE || posicao < 0 || posicao > MAXSIZE) {
        printf("Insercao em posicao invalida!!!\n");
        return false;
    }
    
    // Validar matrícula duplicada
    for (int i = 0; i < listaAlunos->numElem; i++) {
        if (listaAlunos->alunos[i].matricula == aluno.matricula) {
            printf("Matricula duplicada! Nao pode inserir.\n");
            return false;
        }
    }
    
    if (posicao > listaAlunos->numElem)
        posicao = listaAlunos->numElem;  // Inserir no final se a posição for maior que o número de elementos
    
    for (int index = listaAlunos->numElem; index > posicao; index--) {
        listaAlunos->alunos[index] = listaAlunos->alunos[index - 1];
    }
    listaAlunos->alunos[posicao] = aluno;
    listaAlunos->numElem++;
    return true;
}

bool excluiElementoDaLista(ListaAlunos* listaAlunos, int posicao) {
    if (posicao < 0 || posicao >= listaAlunos->numElem) {
        printf("Exclusao em posicao invalida!!!\n");
        return false;
    }
    
    // Resetar os valores na posição da struct removida
    for (int i = posicao; i < listaAlunos->numElem - 1; i++) {
        listaAlunos->alunos[i] = listaAlunos->alunos[i + 1];
    }
    
    // Zerar os valores do último elemento
    memset(&listaAlunos->alunos[listaAlunos->numElem - 1], 0, sizeof(Aluno));
    
    listaAlunos->numElem--;
    return true;
}

// Busca sequencial por nome de aluno
int buscaAlunoPorNome(ListaAlunos* listaAlunos, char* nome) {
    for (int i = 0; i < listaAlunos->numElem; i++) {
        if (strcmp(listaAlunos->alunos[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1; // Nome não encontrado
}

// Busca sequencial por matrícula de aluno
int buscaAlunoPorMatricula(ListaAlunos* listaAlunos, int matricula) {
    for (int i = 0; i < listaAlunos->numElem; i++) {
        if (listaAlunos->alunos[i].matricula == matricula) {
            return i;
        }
    }
    return -1; // Matrícula não encontrada
}

// Retorno do enésimo aluno na lista
Aluno retornaAlunoNaPosicao(ListaAlunos* listaAlunos, int posicao) {
    if (posicao >= 0 && posicao < listaAlunos->numElem) {
        return listaAlunos->alunos[posicao];
    } else {
        Aluno alunoVazio; // Retornar uma struct vazia se a posição for inválida
        memset(&alunoVazio, 0, sizeof(Aluno));
        return alunoVazio;
    }
}

int main() {
    ListaAlunos listaAlunos;
    inicializaLista(&listaAlunos);

    Aluno aluno0, aluno1, aluno2;
    preencheAluno(&aluno0, 15424242, 9.5, "Joao");
    preencheAluno(&aluno1, 10101011, 10, "Ana");
    preencheAluno(&aluno2, 22222222, 7, "Bia");

    insereAlunoNaLista(&listaAlunos, aluno0, 0);
    insereAlunoNaLista(&listaAlunos, aluno1, 0);
    insereAlunoNaLista(&listaAlunos, aluno2, 1);

    exibeLista(&listaAlunos);
    printf("Excluindo elemento.............\n");
    excluiElementoDaLista(&listaAlunos, 1);
    exibeLista(&listaAlunos);

    // Teste das novas funcionalidades
    int posicaoNome = buscaAlunoPorNome(&listaAlunos, "Ana");
    if (posicaoNome != -1) {
        printf("Aluno encontrado por nome:\n");
        exibeLista(&listaAlunos);
    } else {
        printf("Aluno nao encontrado por nome.\n");
    }

    int posicaoMatricula = buscaAlunoPorMatricula(&listaAlunos, 15424242);
    if (posicaoMatricula != -1) {
        printf("Aluno encontrado por matricula:\n");
        exibeLista(&listaAlunos);
    } else {
        printf("Aluno nao encontrado por matricula.\n");
    }

    int n = 1; // Obter o segundo aluno na lista
    Aluno enesimoAluno = retornaAlunoNaPosicao(&listaAlunos, n);
    if (strcmp(enesimoAluno.nome, "") != 0) {
        printf("Enesimo aluno na lista (posicao %d):\n", n);
        printf("Nome: %s\n", enesimoAluno.nome);
        printf("Matricula: %d\n", enesimoAluno.matricula);
        printf("Nota: %.1f\n", enesimoAluno.nota);
    } else {
        printf("Posicao invalida.\n");
    }

    return 0;
}
