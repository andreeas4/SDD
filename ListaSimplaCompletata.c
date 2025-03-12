
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

//LISTA SIMPLA
typedef struct
{
	int cod;
	char* titlu;
	float* vectPreturi;
	int nrPreturi;

 }carte;

typedef struct
{
	carte info;//o variabila de tip carte care retine informatii 
	struct nod*next;//pointer de legatura
}nod;

nod* initializareNod(carte c)
{
	nod* nou = (nod*)malloc(sizeof(nod));//alocare memorie
	//nou->info=c; shallow copy
	nou->info.cod = c.cod;
	nou->info.titlu = (char*)malloc((strlen(c.titlu)+1)*sizeof(char));
	strcpy(nou->info.titlu, c.titlu);
	nou->info.nrPreturi = c.nrPreturi;
	nou->info.vectPreturi = (float*)malloc(nou->info.nrPreturi * sizeof (float));
	for (int i = 0; i < c.nrPreturi; i++)
		nou->info.vectPreturi[i] = c.vectPreturi[i];
	nou->next = NULL;
	return nou;
	
}
nod* inserareNod1(nod* cap, carte c)
{
	nod *nou = initializareNod(c);
	if (cap == NULL)cap = nou;
	else
	{
		//acces secvential
		nod* temp = cap;
		while (temp->next != NULL)temp = temp->next;//sa se ajunga la ultimul nod nenul
		temp->next = nou;//inserarea noului nod
	}
	return cap;
	//cap si temp pointeaza spre aceeasi zona de memorie deci daca temp se modifica=>cap se modifica
}
void inserareNod2(nod** cap, carte c)
{
	nod* nou = initializareNod(c);
	if (*cap == NULL)*cap = nou;
	else
	{
		//acces secvential
		nod* temp = *cap;
		while (temp->next != NULL)temp = temp->next;//sa se ajunga la ultimul nod nenul
		temp->next = nou;//inserarea noului nod
	}

}//**cap pt ca functia intoarce prin parametrul cap
void traversareLista(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		printf("\n--------------------------------CARTE(nod)--------------------------------------");
		printf("\nCod: %d , Titlu: %s , Nr Preturi: %d ", temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
		printf(", Preturi:");
			for (int i = 0; i < temp->info.nrPreturi; i++)
				printf(" %5.2f ", temp->info.vectPreturi[i]);
			temp = temp->next;
			
	}
}
void dezalocareLista(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		nod* aux = temp->next;
		free(temp->info.titlu);
		free(temp->info.vectPreturi);
		free(temp);
		temp = aux;
	}
}
void salvareCartiVector(nod* capLS, carte* vect, int* nrElem, int prag)//care au nr de preturi peste prag
{
	nod* temp = capLS;
	while (temp != NULL)
	{
		if (temp->info.nrPreturi >= prag)
		{
			//vect[*nrElem] = temp->info;//SHALLOW COPY
			vect[*nrElem].cod = temp->info.cod;
			vect[*nrElem].nrPreturi = temp->info.nrPreturi;
			vect[*nrElem].titlu = (char*)malloc((strlen(temp->info.titlu) + 1) * sizeof(char));
			strcpy(vect[*nrElem].titlu, temp->info.titlu);
			vect[*nrElem].vectPreturi = (float*)malloc(temp->info.nrPreturi * sizeof(float));
			for (int i = 0; i < temp->info.nrPreturi; i++)
				vect[*nrElem].vectPreturi[i] = temp->info.vectPreturi[i];
			++(*nrElem);
		}
		temp = temp->next;

	}
}


void main()
{
	int nrCarti;
	carte c;
	nod* cap = NULL;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrCarti);
	for (int i = 0; i < nrCarti; i++)
	{
		fscanf(f, "%d", &c.cod);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);
		fscanf(f, "%d", &c.nrPreturi);
		c.vectPreturi = (float*)malloc(c.nrPreturi * sizeof(float));
		for (int i = 0; i < c.nrPreturi; i++)
			fscanf(f, "%f", &c.vectPreturi[i]);
		cap = inserareNod1(cap, c);
		
	}
	fclose(f);
	traversareLista(cap);
	
	carte* vect = (carte*)malloc(nrCarti * sizeof(carte));
	int nrElem = 0;
	printf("\nVECTOR-----------------------------------------------");
	salvareCartiVector(cap, vect, &nrElem, 3);
	for (int i = 0; i < nrElem; i++)
	{
		printf("\nCod = %d, Titlu = %s, Nr preturi = %d", vect[i].cod, vect[i].titlu, vect[i].nrPreturi);
		for (int j = 0; j < vect[i].nrPreturi; j++)
			printf(" Pret = %5.2f", vect[i].vectPreturi[j]);
	}
	free(vect);
	dezalocareLista(cap);
}
