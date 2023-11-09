#include<stdio.h>
#include<stdlib.h>

int adicionar_tarefa();
void imprimir_tarefas();
void alterar_tarefa();
void salvar_lista();
int leitura_arquivo();
int excluir_tarefa();

typedef struct{
	char tarefa[50];
}Tarefas;

int main(void)
{
	Tarefas *tarefa[50];
	int tam, quant = 0, escolha;
	char arquivo[] = {"todolist.txt"};
	
	tam = sizeof(tarefa) / 8;
	
	quant += leitura_arquivo(tarefa,arquivo);
	
	do
	{
		system("cls");
		printf("Escolha uma das opcoes\n");
		printf("[0] - Sair\t\t[1] - Adicionar tarefa\n[2] - Alterar tarefa\t[3] - Salvar \n[4] - Imprimir tarefas\t[5] - Excluir tarefa\n[6] - Resetar lista\n\n");
		printf("Escolha: ");
		scanf("%d", &escolha);
		scanf("%c");
		
		switch(escolha)
		{
			case 0:
				return 0;
			break;
			
			case 1:
				quant += adicionar_tarefa(tarefa, tam, quant);
			break;
			
			case 2:
				alterar_tarefa(tarefa, quant);
			break;
			
			case 3:
				salvar_lista(tarefa, quant, arquivo);
			break;
			
			case 4:
				system("cls");
				imprimir_tarefas(tarefa, quant);
				system("pause");
			break;
			
			case 5:
				quant = excluir_tarefa(tarefa,quant);
			break;
			
			case 6:
				quant = 0;
			break;
		}
	}while(escolha != 0);
}

int adicionar_tarefa(Tarefas **t, int tam, int quant)
{
	
	system("cls");

	if(quant >= tam)
	{
		printf("Limite de itens na lista excedido");	
	}
	else if(quant < tam)
	{
		Tarefas *novo = malloc(sizeof(Tarefas));
		printf("Digite a tarefa que deseja adicionar\n\nInput: ");
		fgets(novo->tarefa,50,stdin);
		
		t[quant] = novo;
		return 1;
	}
	else
	{
		printf("Um erro desconhecido foi encontrado");
	}
}

void imprimir_tarefas(Tarefas **t, int quant)
{
	int i;
	
	printf("\t\tLISTA DE TAREFAS\n\n");
	for(i = 0; i < quant; i++)
	{
		printf("[%d] %s\n", i+1, t[i] -> tarefa);
	}
}

void alterar_tarefa(Tarefas **t, int quant)
{
	int id;
	system("cls");
	imprimir_tarefas(t, quant);
	printf("\n\n");
	printf("Digite o numero da tarefa que deseja alterar: ");
	scanf("%d", &id);
	getchar();
	id--;
	
	system("cls");
	if(id >= 0 && id < quant)
	{
		Tarefas *novo = malloc(sizeof(Tarefas));
		printf("Digite a tarefa\nInput: ");
		fgets(novo->tarefa,50,stdin);
		
		t[id] = novo;	
	}	
	else
	{
		printf("Codigo invalido");
		system("pause");
	}
}

void salvar_lista(Tarefas **t, int quant,char arq[])
{
	FILE *file = fopen(arq, "w");
	int i;
	
	if(file)
	{
		fprintf(file, "Quantidade de tarefas: %d\n", quant);
		
		for(i = 0; i < quant; i++)
		{
			
			fputs(t[i]->tarefa,file);
		}
		fclose(file);
	}
	else
	{
		printf("Arquivo nao encontrado ou sem acesso ao arquivo");
	}
}

int leitura_arquivo(Tarefas **t, char arq[])
{
	FILE *file = fopen(arq, "r");
	int quant = 0, i;
	Tarefas *novo = malloc(sizeof(Tarefas));
	
	if(file)
	{
		fscanf(file, "Quantidade de tarefas: %d\n", &quant);	
		
		if(quant != 0)
		{
			for(i = 0; i < quant; i++)
			{
				fgets(novo->tarefa,50,file);
				t[i] = novo;
				
				novo = malloc(sizeof(Tarefas));
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		printf("Sem acesso ao arquivo ou inexistente");
	}
	fclose(file);
	return quant;
}

int excluir_tarefa(Tarefas **t, int quant)
{
	int i, id;
	imprimir_tarefas(t,quant);
	printf("Escolha o numero da tarefa que deseja deletar: ");
	scanf("%d", &id);
	scanf("%c");
	id--;
	
	if(id < quant)
	{
		for(i = id; i < quant; i++)
		{
			t[i] = t[i+1];
		}
		quant--;
	}
	return quant;
}
