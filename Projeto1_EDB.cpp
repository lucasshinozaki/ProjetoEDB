#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct noArv {
	int info;
	struct noArv* esq;
	struct noArv* dir;
}NoArv;

NoArv* arv_vazia() {
	return NULL;
}


NoArv* inserir(NoArv* a, int v) {
	if (a == NULL) {
		a = (NoArv*)malloc(sizeof(NoArv));
		a->info = v;
		a->esq = NULL;
		a->dir = NULL;
	}
	else if (v < a->info) {
		a->esq = inserir(a->esq, v);
	}
	else {
		a->dir = inserir(a->dir, v);
	}
	return a;
}


NoArv* remover(NoArv* a, int v) {
	if (a == NULL) {
		return NULL;
	}
	else {
		if (a->info > v) {
			a->esq = remover(a->esq, v);
		}
		else if (a->info < v) {
			a->dir = remover(a->dir, v);
		}
		else {
			if ((a->esq == NULL) && (a->dir == NULL)) {
				free(a);
				a = NULL;
			}
			else if (a->dir == NULL) {
				NoArv* tmp = a;
				a = a->esq;
				free(tmp);
			}
			else if (a->esq == NULL) {
				NoArv* tmp = a;
				a = a->dir;
				free(tmp);
			}
			else {
				NoArv* tmp = a->esq;
				while (tmp->dir != NULL) {
					tmp = tmp->dir;
				}
				a->info = tmp->info;
				tmp->info = v;
				a->esq = remover(a->esq, v);
			}
		}
	}
	return a;
}

NoArv* carregaArquivo(NoArv* a) {
	FILE* arq;
	int info;
	arq = fopen("arquivobinario.bin", "rb");
	if (arq != NULL) {
		while (!feof(arq)) {
			fread(&info, sizeof(int), 1, arq);
			if (!feof(arq))
				inserir(a, info);
		}
	}
	return a;
}

NoArv* carregaArquivo1(NoArv* a1) {
	FILE* arq;
	int info;
	arq = fopen("arquivobinario1.bin", "rb");
	if (arq != NULL) {
		while (!feof(arq)) {
			fread(&info, sizeof(int), 1, arq);
			if (!feof(arq))
				inserir(a1, info);
		}
	}
	return a1;
}

int maior(NoArv* a) {
	if (a->dir !=NULL) {
		return maior(a->dir);
	}
	else {
		return a->info;
	}
}

int menor(NoArv* a) {
	if (a->esq != NULL) {
		return menor(a->esq);
		}
	else{
		return a->info;
	}
}


int buscar(NoArv* a, int v) {
	if (a == NULL) {
		return 0;
	}
	else if (v < a->info) {
		return buscar(a->esq, v);
	}
	else if (v > a->info) {
		return buscar(a->dir, v);
	}
	else {
		return 1;
	}
}

int contador(NoArv* a) {
	if (a == NULL)
		return 0;
	else
		return 1 + contador(a->esq) + contador(a->dir);
}

int maior_usual(int a, int b) {
	if (a > b) {
		return a;
	}else{
		return b;
	}
}

int altura(NoArv* a) {
	if ((a == NULL) || (a->esq == NULL && a->dir == NULL)) {
		return 0;
	}
	else {
		return 1 + maior_usual(altura(a->esq), altura(a->dir));
	}
}

int pares(NoArv* a) {
	if (a == NULL) {
		return 0;
	}
	if(a->info % 2 == 0){
		return 1 + pares(a->esq) + pares(a->dir);
	} else{
		return pares(a->esq) + pares(a->dir);
	}
}

int impar(NoArv* a) {
	if (a == NULL) {
		return 0;
	}
	if (a->info % 3 == 0) {
		return 1 + impar(a->esq) + impar(a->dir);
	}
	else {
		return impar(a->esq) + impar(a->dir);
	}
}

int multiplosk(NoArv* a, int v) {
	if (a == NULL) {
		return 0;
	}
	if (a->info % v == 0) {
		printf("Os multilos sao %d\n", a->info);
		return 1 + multiplosk(a->esq, v) + multiplosk(a->dir, v);
	}
	else {
		return multiplosk(a->esq, v) + multiplosk(a->dir, v);
	}
}

int  somadosnos(NoArv* a) {	

	if (a == NULL) {
		return 0;
	}
	else {
		int soma = 0;
		soma += somadosnos(a->esq);
		soma += somadosnos(a->dir);
		soma += a->info;
		return soma;
	}
}

int media(NoArv* a) {
	int n, n1, media;
	if (a != NULL) {
		n1 = somadosnos(a);
		n = contador(a);
		media = n1 / n;
		return media;
	}
}

int variacao(NoArv* a) {
	int v, n;
	
	if (a == NULL) {
		return 0;
	}
	else {
		n = media(a);
		int soma = 0;
		soma += somadosnos(a->esq) - n;
		soma += somadosnos(a->dir) - n;
		soma += a->info - n;
		return soma * soma;
	}
}

int desvio(NoArv* a) {
	int n, n1, desvio;
	n = contador(a);
	n1 = variacao(a);
	desvio = sqrtf(n1 / n);
	return desvio;
}

int qtdNull(NoArv* a) {
	if (a) {
		return 0 + qtdNull(a->dir) + qtdNull(a->esq);
	}
	else {
		return 1;
	}
}

int doisfilho(NoArv* a) {
	
	if (a == NULL) {
		return 0;
	}
	if (a->esq != NULL && a->dir != NULL) {
		return 1 + contador(a->esq) + contador(a->dir);
	}

}

int umfilho(NoArv* a) {
	if (a == NULL) {
		return 0;
	}
	if (a->esq != NULL && a->dir == NULL) {
		return 1 + umfilho(a->esq) + umfilho(a->dir);
	}
	if (a->esq == NULL && a->dir != NULL) {
		return 1 + umfilho(a->esq) + umfilho(a->dir);
	}
}

int folhas(NoArv* a) {
	if (a == NULL) {
		return 0;
	}
	if ((!a->esq) && (!a->dir)) {
		return 1 + folhas(a->dir) + folhas(a->esq);
	}
	else {
		return folhas(a->dir) + folhas(a->esq);
	}
}

int compara(NoArv* a, NoArv* a1) {
	if (a == NULL || a1 == NULL) {
		return 0;
	}
	if (a->info == a1->info) {
		printf("Os valores que pertecem as duas sao %d\n", a->info);
		return 1 + compara(a->esq, a1->esq) + compara(a->dir, a1->dir);
	}
	else {
		return compara(a->esq, a1->esq) + compara(a->dir, a1->dir);
	}
}

void emordem(NoArv* arv) {
	if (arv != NULL) {
		emordem(arv->esq);
		printf("%d, ", arv->info);
		emordem(arv->dir);
	}
}

void pre_ordem(NoArv* arv) {
	if (arv != NULL) {
		printf("%d, ", arv->info);
		pre_ordem(arv->esq);
		pre_ordem(arv->dir);
	}
}

void in_ordem(NoArv* arv) {
	if (arv != NULL) {
		in_ordem(arv->esq);
		printf("%d, ", arv->info);
		in_ordem(arv->dir);
	}
}

void imprimirCrescente(NoArv* a) {
	if (a != NULL) {
		imprimirCrescente(a->esq);
		printf("%d ", a->info);
		imprimirCrescente(a->dir);
	}
}

void imprimirDecrescente(NoArv* a) {
	if (a != NULL) {
		imprimirDecrescente(a->dir);
		printf("%d ", a->info);
		imprimirDecrescente(a->esq);
	}
}

void gravarItem(NoArv* a, FILE* arq) {
	fwrite(&a->info, sizeof(int), 1, arq);
	if (a->esq)gravarItem(a->esq, arq);
	if (a->dir)gravarItem(a->dir, arq);
}

void gravarArquivo(NoArv* a) {
	FILE* arq;
	arq = fopen("arquivobinario.bin", "wb");
	gravarItem(a, arq);
	fclose(arq);
}

void gravarArquivo1(NoArv* a1) {
	FILE* arq;
	arq = fopen("arquivobinario1.bin", "wb");
	gravarItem(a1, arq);
	fclose(arq);
}



void menu() {
	printf("|------------------------------------------------------------------------------------------------------------------------------------|\n");
	printf("|Menu :                                                                                                                              |\n");
	printf("|1 - Insercao de um elemento n na arvore                                                                                             |\n");
	printf("|2 - Remocao de um elemento n                                                                                                        |\n");
	printf("|3 - Busca de um elemento n                                                                                                          |\n");
	printf("|4 - Informar o valor do maior elemento armazenado                                                                                   |\n");
	printf("|5 - Informar o valor no menor elemento armazenado                                                                                   |\n");
	printf("|6 - Informar a quantidade de elementos (nos) da arvore                                                                              |\n");
	printf("|7 - Informar a altura da arvore                                                                                                     |\n");
	printf("|8 - Informar quandos elementos pares e quantos elementos impares estao armazenados                                                  |\n");
	printf("|9 - Dado um valor k inserido pelo usuario, imprimir todos os valores multiplos de k presente no arvore, bem como a quantidade       |\n");
	printf("|10 - Imprimir os valores armazenados em ordem crescente                                                                             |\n");
	printf("|11 - Imprimir os valores armazenados em ordem descrescente                                                                          |\n");
	printf("|12 - Imprimir a soma dos valores dos nos                                                                                            |\n");
	printf("|13 - Imprimir a media dos valores dos nos                                                                                           |\n");
	printf("|14 - Imprimir o desvio padrao dos valores dos nos                                                                                   |\n");
	printf("|15 - Imprimir a quantidade de NULLs presents na arvores                                                                             |\n");
	printf("|16 - Imprimir a quantidade de nos com dois filhos                                                                                   |\n");
	printf("|17 - Imprimir a quantidade de nós com um filho                                                                                      |\n");
	printf("|18 - Imprimir a quantidade de folhas                                                                                                |\n");
	printf("|19 - Percorrer a arvore em ordem                                                                                                    |\n");
	printf("|20 - Percorrer a arvore em preordem                                                                                                 |\n");
	printf("|21 - Percorrer a arvore em posordem                                                                                                 |\n");
	printf("|22 - Percorrer a arvore em largura                                                                                                  |\n");
	printf("|23 - Salva a arvore em arquivo                                                                                                      |\n");
	printf("|24 - Recuperar a arvore de arquivo                                                                                                  |\n");
	printf("|25 - Trocar de arvore                                                                                                               |\n");
	printf("|26 - Comparar duas arvores                                                                                                          |\n");
	printf("|0 - Sair do programa                                                                                                                |\n");
	printf("|------------------------------------------------------------------------------------------------------------------------------------|\n");
	printf("Escolha uma das opcoes : ");

}


int main(){

	int opt = 0, n, n1;
	int opt1 = 1;
	int soma = 0;
	NoArv* a = arv_vazia();
	NoArv* a1 = arv_vazia();

	do{
		
		menu();
		scanf("%d", &opt);
		switch (opt) {
		case 25:
			printf("Escolha uma arvore: \n");
			printf("1 - primeira arvore");
			printf("2 - segunda arvore");
			scanf("%d", &opt1);
			break;
		case 1:
			system("cls");
			printf("Digite um numero que deseja adicionar :");
			scanf("%d", &n);
			if (opt1 == 1) {
				inserir(a, n);
			}
			else if (opt1 == 2) {
				a1 = inserir(a1, n);
			}
			
			break;
		case 2:
			system("cls");
			printf("Digite um numero que deseja remover :");
			scanf("%d", &n);
			if (opt1 == 1) {
				a = remover(a, n);
			}else if (opt1 == 2) {
				a1 = remover(a1, n);
			}
			
			break;
		case 3:
			system("cls");
			printf("Digite um numero que deseja procurar :");
			scanf("%d", &n);
			if (opt1 == 1) {
				if (buscar(a, n) == 0) {
					printf("O numero nao existe na arvore\n");
				}
				else {
					printf("O numero existe dentro da arvore\n");
				}
			}
			else if (opt1 == 2) {
				if (buscar(a1, n) == 0) {
					printf("O numero nao existe na arvore\n");
				}
				else {
					printf("O numero existe dentro da arvore\n");
				}
			}
			
			break;
		case 4:
			
			if (opt1 == 1) {
				n = maior(a);
				printf("\n\n\n\n");
				printf("O maior numero na arvore %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = maior(a1);
				printf("\n\n\n\n");
				printf("O maior numero na avore %d\n", n);
				printf("\n\n\n\n");
			}
			break;
		case 5:
			if (opt1 == 1) {
				n = menor(a);
				printf("\n\n\n\n");
				printf("O menor numero na arvore %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = menor(a1);
				printf("\n\n\n\n");
				printf("O menor numero na arvore %d\n", n);
				printf("\n\n\n\n");
			}
			break;
		case 6:
			if (opt1 == 1) {
				n = contador(a);
				printf("\n\n\n\n");
				printf("A quantidade de elemento na arvore %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = contador(a1);
				printf("\n\n\n\n");
				printf("A quantidade de elemento na arvore %d\n", n);
				printf("\n\n\n\n");
			}
			break;
		case 7:
			if (opt1 == 1) {
				n = altura(a);
				printf("\n\n\n\n");
				printf("Altura da arvore %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = altura(a1);
				printf("\n\n\n\n");
				printf("Altura da arvore %d\n", n);
				printf("\n\n\n\n");
			}
			break;
		case 8:
			if (opt1 == 1) {
				n = pares(a);
				n1 = impar(a);
				printf("\n\n\n\n");
				printf("Quantidade de pares %d\n", n);
				printf("Quantidade de impares %d\n", n1);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = pares(a1);
				n1 = impar(a1);
				printf("\n\n\n\n");
				printf("Quantidade de pares¨%d\n", n);
				printf("Quantidade de impares %d\n", n1);
				printf("\n\n\n\n");
			}
			
			break;
		case 9:
			system("cls");
			if (opt1 == 1) {
				printf("Digite um multiplo: ");
				scanf("%d", &n);
				n1 = multiplosk(a, n);
				printf("Quantidade de multiplos: %d\n", n1);
			}
			else if (opt1 == 2) {
				printf("Digite um multiplo: ");
				scanf("%d", &n);
				n1 = multiplosk(a1, n);
				printf("Quantidade de multiplos: %d\n", n1);
			}
			break;
		case 10:
			if (opt1 == 1) {
				printf("\n\n\n\n");
				imprimirCrescente(a);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				printf("\n\n\n\n");
				imprimirCrescente(a1);
				printf("\n\n\n\n");
			}
			break;
		case 11:
			if (opt1 == 1) {
				printf("\n\n\n\n");
				imprimirDecrescente(a);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				printf("\n\n\n\n");
				imprimirDecrescente(a1);
				printf("\n\n\n\n");
			}
			break;
		case 12:
			if (opt1 == 1) {
				n = somadosnos(a);
				printf("\n\n\n\n");
				printf("Soma: %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = somadosnos(a1);
				printf("\n\n\n\n");
				printf("Soma: %d\n", n);
				printf("\n\n\n\n");
			}
			break;
		case 13:
			if (opt1 == 1) {
				n = media(a);
				printf("\n\n\n\n");
				printf("Media: %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = media(a1);
				printf("\n\n\n\n");
				printf("Media: %d\n", n);
				printf("\n\n\n\n");
			}
			break;
		case 14:
			if (opt1 == 1) {
				n = desvio(a);
				printf("\n\n\n\n");
				printf("Desvio medio: %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = desvio(a1);
				printf("\n\n\n\n");
				printf("Desvio medio  %d\n", n);
				printf("\n\n\n\n");
			}
			break;
		case 15:
			if (opt1 == 1) {
				n = qtdNull(a);
				printf("\n\n\n\n");
				printf("Quantidade de NULL: %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = qtdNull(a1);
				printf("\n\n\n\n");
				printf("Quantidade de NULL: %d\n", n);
				printf("\n\n\n\n");
			}
			break;
		case 16:
			if (opt1 == 1) {
				n = doisfilho(a);
				printf("\n\n\n\n");
				printf("Quantidade de nos com dois filhos : %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = doisfilho(a1);
				printf("\n\n\n\n");
				printf("Quantidade de nos com dois filhos: %d", n);
				printf("\n\n\n\n");
			}
			
			break;
		case 17:
			if (opt1 == 1) {
				n = umfilho(a);
				printf("\n\n\n\n");
				printf("Quantidade de nos com um filho : %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = umfilho(a1);
				printf("\n\n\n\n");
				printf("Quantidade de nos com um filho: %d\n", n);
				printf("\n\n\n\n");
			}
			
			break;
		case 18:
			if (opt1 == 1) {
				n = folhas(a);
				printf("\n\n\n\n");
				printf("Quantidade de folhas : %d\n", n);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				n = folhas(a1);
				printf("\n\n\n\n");
				printf("Quantidade de folhas : %d", n);
				printf("\n\n\n\n");
			}
			
			break;
		case 19:
			if (opt1 == 1) {
				printf("\n\n\n\n");
				emordem(a);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				printf("\n\n\n\n");
				emordem(a1);
				printf("\n\n\n\n");
			}
			break;
		case 20:
			if (opt1 == 1) {
				printf("\n\n\n\n");
				pre_ordem(a);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				printf("\n\n\n\n");
				pre_ordem(a1);
				printf("\n\n\n\n");
			}
			break;
		case 21:
			if (opt1 == 1) {
				printf("\n\n\n\n");
				in_ordem(a);
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				printf("\n\n\n\n");
				in_ordem(a1);
				printf("\n\n\n\n");
			}
			break;
		case 22:
			printf("Essa opcao nao foi concluida");
			break;
		case 23:
			if (opt1 == 1) {
				gravarArquivo(a);
				printf("\n\n\n\n");
				printf("Os dados foram salvas com sucesso para o arquivo (arquivobinario.bin)\n");
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				printf("\n\n\n\n");
				gravarArquivo1(a);
				printf("Os dados foram salvas com sucesso parao arquivo (arquivobinario1.bin)\n");
				printf("\n\n\n\n");
			}
			
			break;
		case 24:
			if (opt1 == 1) {
				carregaArquivo(a);
				printf("\n\n\n\n");
				printf("Os dados foram carregados com sucesso a partir do arquivo (arquivobinario.bin)\n");
				printf("\n\n\n\n");
			}
			else if (opt1 == 2) {
				carregaArquivo1(a1);
				printf("\n\n\n\n");
				printf("Os dados foram carregados com sucesso a partir do arquivo (arquivobinario1.bin)\n");
				printf("\n\n\n\n");
			}
			break;
		case 26:
			n = compara(a, a1);
			printf("\n\n\n\n");
			printf("Quantidade de elementos iguais: %d\n", n);
			printf("\n\n\n\n");
			break;
		}
	} while (opt != 0);
	
}