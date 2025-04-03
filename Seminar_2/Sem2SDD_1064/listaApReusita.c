#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* nume;
	float* note;
	int nrNote;

}elev;

typedef struct {
	elev info;
	struct nod* next;
}nod;

nod* initializareNod(elev e)
{
	nod* nou=(nod*)malloc(sizeof(nod));
	//nou->info = e;
	nou->info.cod = e.cod;
	nou->info.nume = (char*)malloc((strlen(e.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, e.nume);
	nou->info.nrNote=e.nrNote;
	nou->info.note = (float*)malloc(e.nrNote * sizeof(float));
	for (int i = 0; i < e.nrNote; i++)
		nou->info.note[i] = e.note[i];

	nou->next = NULL;
	return nou;
	
}
void inserareNod1(nod** cap, elev e)
{
	nod* nou = initializareNod(e);
	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		nod* temp = *cap;
		while (temp->next != NULL)
			temp = temp->next;
		
		temp->next = nou;

	}
}

nod* inserareNod2(nod* cap, elev e)
{
	nod* nou = initializareNod(e);
	if (cap == NULL)
		cap = nou;
	else
	{
		nod* temp=cap;
		while(temp->next != NULL)
			temp=temp->next;
		temp->next=nou;
		
	}
	return cap;
}

void InserareaMea(nod** cap, elev e)
{
	nod* nou = initializareNod(e);

	if (*cap == NULL)
		*cap = nou;
	else
	{
		//trebuie sa fac un nod temporar pt ca trebuie sa tinem minte capul listei 
		//temp este o copie a capului in momentul in care capul are o valoare
		nod* temp = *cap;

		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		
	}
}

nod* InserareaMea2(nod* cap, elev e)
{
	nod* nou = initializareNod(e);

	if (cap == NULL)
		cap = nou;
	else
	{
		nod* temp = cap;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next= nou;
	}
	return cap;
}
void traversareLista(nod* cap)
{
	if (cap == NULL)
		printf("Nu exista elemente in lista!");
	else
	{
		nod*temp = cap;
		while (temp != NULL)
		{
			printf("ELEV\tcod: %d,\tnume: %s,\tNote: ",temp->info.cod,temp->info.nume);
			for (int i = 0; i < temp->info.nrNote; i++)
				printf("%5.2f ", temp->info.note[i]);
			printf("\n-------------------------\n");
			temp = temp->next;
		}
		
	}
}
void dezalocareLista(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		nod* aux = temp->next;
		free(temp->info.nume);
		free(temp->info.note);
		free(temp);
		temp = aux;
	}

}
void main()
{
	int nrElevi;
	elev e;
	nod* cap=NULL;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f,"%d", &nrElevi);
	for (int i = 0; i < nrElevi; i++)
	{
		fscanf(f, "%d", &e.cod);
		fscanf(f, "%s",buffer);
		e.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(e.nume, buffer);
		fscanf(f, "%d", &e.nrNote);
		e.note = (float*)malloc(e.nrNote * sizeof(float));
		for (int i = 0; i < e.nrNote; i++)
			fscanf(f, "%f", &e.note[i]);

		cap = inserareNod2(cap,e);
		free(e.nume);
		free(e.note);

	}
	traversareLista(cap);
	fclose(f);
	dezalocareLista(cap);
}
