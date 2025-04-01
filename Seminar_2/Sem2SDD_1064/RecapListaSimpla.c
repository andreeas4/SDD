#include <stdio.h>
#include<malloc.h>

//lista simpla


typedef struct
{
	int cod;
	char* nume;
	float* dimensiuni;
	int nrDimensiuni;

}parfum;

typedef struct
{
	parfum info;//informatii despre parfum->cod,nume,dimensiuni,nrDimensiuni
	struct nod*next;//pointer de legatura
}nod;//nodul care contine informatia si pointeaza catre urm nod

nod* initializareNod(parfum p)
{
	nod* nou = (nod*)malloc(sizeof(nod));//aloc memorie pentru o lista =>care va fi returnata de functie
	//nou->info = p; ===============shallow copy
	//----------------------------->am scris in wordu ala dif dintre shallow copy si deep copy-----
	//---DEEPCOPY---
	nou->info.cod = p.cod;
	nou->info.nume = (char*)malloc((strlen(p.nume)+1)*sizeof(char));
	strcpy(nou->info.nume, p.nume);
	nou->info.nrDimensiuni = p.nrDimensiuni;
	nou->info.dimensiuni = (float*)malloc(p.nrDimensiuni * sizeof(float));
	for (int i = 0; i < p.nrDimensiuni; i++)
		nou->info.dimensiuni[i] = p.dimensiuni[i];
	//------
	nou->next=NULL;
	return nou;// indicând că acest nod nu este încă conectat la altul
}
nod* inserareNod1(nod* cap, parfum p)
{
	nod* nou = initializareNod(p);
	if (cap == NULL)
		cap = nou;
	else
	{
		nod* temp = cap;//nodul temporar primeste pointerul la cap
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
	
}
void inserareNod2(nod** cap, parfum p)
{
	nod** nou = initializareNod(p);
	if (*cap == NULL)
		*cap = nou;
	else
	{
		nod*temp = *cap;
		if (temp->next != NULL)
			temp = temp->next;
		else temp->next = nou;
	}

}
void traversareLista(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		printf("COD : %d , NUME : %s  are %d dimensiuni : ", temp->info.cod, temp->info.nume, temp->info.nrDimensiuni);
		for (int i = 0; i < temp->info.nrDimensiuni; i++)
			printf(" %5.2f ml ,", temp->info.dimensiuni[i]);
		printf("\n");
		temp = temp->next;
		
	}

}
void dezalocareLista(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		nod* aux = temp->next;
		free(temp->info.nume);
		free(temp->info.dimensiuni);
		free(temp);
		temp = aux;
		
	}
}

void salvareParfumuriCareAuDimPestePrag()
{

}
void main()
{
	nod* cap = NULL;

	// Adăugăm manual câteva parfumuri
	float dim1[] = { 50.5, 75.0 };
	parfum p1 = { 101, "Dior", dim1, 2 };

	float dim2[] = { 30.0, 50.0, 100.0 };
	parfum p2 = { 102, "Chanel", dim2, 3 };

	float dim3[] = { 25.0, 75.0 };
	parfum p3 = { 103, "Versace", dim3, 2 };

	// Inserare folosind prima metodă
	cap = inserareNod1(cap, p1);
	cap = inserareNod1(cap, p2);

	// Inserare folosind a doua metodă
	inserareNod2(&cap, p3);

	// Afișare listă
	printf("Lista parfumurilor:\n");
	traversareLista(cap);

	// Eliberare memorie
	dezalocareLista(cap);

	return 0;
}
