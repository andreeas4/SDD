//coada si stiva
#include <malloc.h>
#include <stdio.h>

typedef struct
{
	int zi, luna, an;

}dataReceptionare;

typedef struct
{
	dataReceptionare data;
	char* expeditor;
	float dimensiune;
}mesaj;

typedef struct{

	mesaj info;//20B
	struct nodStiva* next;//4B

}nodStiva;
//fct de inserare nod in stiva
void push(nodStiva** varf, mesaj m) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info.data.zi = m.data.zi;
	nou->info.data.luna = m.data.luna;
	nou->info.data.an = m.data.an;
	nou->info.expeditor = (char*)malloc((strlen(m.expeditor) + 1 )* sizeof(char));
	strcpy(nou->info.expeditor, m.expeditor);
	nou->info.dimensiune = m.dimensiune;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}
	//fct de extragere nod din stiva
	int pop(nodStiva** varf, mesaj* m) 
	{
		if (*varf == NULL)
			return 1;
		else {
			(*m).data.zi = (*varf)->info.data.zi;
			(*m).data.luna = (*varf)->info.data.luna;
			(*m).data.an = (*varf)->info.data.an;
			(*m).expeditor= (char*)malloc((strlen((*varf)->info.expeditor) + 1 )* sizeof(char));
			strcpy((*m).expeditor, (*varf)->info.expeditor);
			(*m).dimensiune = (*varf)->info.dimensiune;
			nodStiva* temp = *varf;
			*varf = (*varf)->next;
			free(temp->info.expeditor);
			free(temp);
			return 0;

		}

	}
	void afisareStiva(nodStiva* varf)
	{
		nodStiva* temp = varf;
		while (temp)
		{
			printf("\nData=%d/%d/%d,Expeditor=%s,Dimensiune=%5.3f",
				temp->info.data.zi, temp->info.data.luna, temp->info.data.an, temp->info.expeditor, temp->info.dimensiune);
			temp = temp->next;
		}
	}
	void dezalocareStiva(nodStiva* varf)
	{
		mesaj m;
		while (pop(&varf, &m) == 0)
			free(m.expeditor);
	}
void main() 
{
	int nrMesaje;
	nodStiva* varf = NULL;
	mesaj m;
	char buffer[30];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrMesaje);
	for (int i = 0; i < nrMesaje; i++)
	{
		fscanf(f, "%d", &m.data.zi);
		fscanf(f, "%d", &m.data.luna);
		fscanf(f, "%d", &m.data.an);
		fscanf(f, "%s", buffer);
		m.expeditor= (char*)malloc((strlen(buffer) + 1 )* sizeof(char));
		strcpy(m.expeditor, buffer);
		fscanf(f, "%f", &m.dimensiune);
		//inserare de stiva
		push(&varf, m);
		free(m.expeditor);
	}
	fclose(f);
	afisareStiva(varf);
	dezalocareStiva(varf);
}
