#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.c"
#include "binary_search_tree.c"

void quick_sort (int *v, int size);

int main ()
{
	int i, lim, chosen, comp_list, comp_tree;
	node *list = create_linked_list();
	binary_tree *bt = create_empty_binary_tree();
	
	FILE *arq = fopen("plot.txt", "w");

	printf("LISTA ENCADEADA vs ARVORE DE BUSCA BINARIA\nDigite a quantidade de numeros: ");
	scanf("%d", &lim);
	int numbers[lim], aux_list[lim], aux_tree[lim];
	
	printf("Intervalo: [0,%d]\n", lim-1);

	srand(time(NULL));
	
	for (i = 0; i <= lim; i++)
	{
		numbers[i] = 0;
	}

	for(i = 0; i < lim; i++)
	{
		do
		{
			chosen = rand() % lim; 
		} while (numbers[chosen]);
		
		printf("%d\n", chosen);
		numbers[chosen] = 1;
		
		list = add_list(list, chosen);
		bt = add_tree(bt, chosen);
	}

	for(i = 0; i < lim; i++)
	{
		comp_list = search_list(list, i);
		comp_tree = search_tree(bt, i);
		aux_list[i] = comp_list;
		aux_tree[i] = comp_tree;
	}
	
	printf("Ordenar?\n1 - Sim, 0 - Nao\n");
	int op;
	scanf("%d", &op);
	if(op == 1)
	{
		quick_sort (aux_list, lim);
		quick_sort (aux_tree, lim);
	}
	
	fprintf(arq, "numero comp_lista comp_arvore\n");
	for(i = 0; i < lim; i++)
	{
		fprintf(arq, "%d %d %d\n", i, aux_list[i], aux_tree[i]);
	}
	
	fclose(arq);
	
	return 0;
}

void swap (int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

void quick_sort (int *v, int size)
{
	if (size <= 1)
	{
		return;
	} else
	{
		int aux, pivot = v[size/2], a = 0, b = size - 1;
		while (a < b)
		{
			while (v[a] < pivot) a++;
			while (v[b] > pivot) b--;
			if (a < b)
			{
				swap (&v[a], &v[b]);
				if (v[a] == v[b]) a++;
			}
		}
		
		quick_sort (v, b);
		quick_sort (v+a, size-a);
	}
}