//lista dubla

#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int cod; //4B
	char* titlu; //4B
	float* vectPreturi; //4B
	int nrPreturi;
} carte;

typedef struct
{
	carte info; //informatie utila 12B
	struct nodLS* next, * prev;//2 pointeri de legatura 8B
} nodLD;

nodLD* initializareNod(carte c)
{
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));
	//nou->info = c;
	nou->info.cod = c.cod;
	nou->info.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, c.titlu);
	nou->info.nrPreturi = c.nrPreturi;
	nou->info.vectPreturi = (float*)malloc(nou->info.nrPreturi * sizeof(float));
	for (int i = 0; i < c.nrPreturi; i++)
		nou->info.vectPreturi[i] = c.vectPreturi[i];
	nou->next = nou;
	nou->prev = nou;
	return nou;
}

nodLD* inserareNod1(nodLD* capLD, nodLD** coadaLD, carte c)
{
	nodLD* nou = initializareNod(c);
	if (capLD == NULL)
	{
		capLD = nou;
		*coadaLD = nou;
	}
	else
	{
		/nodLD temp = capLD;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		coadaLD = nou;/

		//mai eficient
		(*coadaLD)->next = nou;
		nou->prev = *coadaLD;
		*coadaLD = nou;
		(*coadaLD)->next = capLD;
		capLD->prev = *coadaLD;
	}
	return capLD;
}

void inserareNod2(nodLD** capLD, nodLD** coadaLD, carte c)
{
	nodLD* nou = initializareNod(c);
	if (*capLD == NULL)
	{
		*capLD = nou;
		*coadaLD = nou;
	}
	else
	{
		nodLD* temp = *capLD;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coadaLD = nou;
		(*coadaLD)->next = *capLD;
		(*capLD)->prev = *coadaLD;
	}
}

void traversareLista(nodLD* capLD)
{
	nodLD* temp = capLD;
	while (temp->next != capLD)
	{
		printf("\nCod = %d, Titlu = %s, Nr. preturi = %d",
			temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
		for (int i = 0; i < temp->info.nrPreturi; i++)
			printf(" Pret = %5.2f", temp->info.vectPreturi[i]);
		temp = temp->next;
	}

	//parcurge ultimul nod
	printf("\nCod = %d, Titlu = %s, Nr. preturi = %d",
		temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
	for (int i = 0; i < temp->info.nrPreturi; i++)
		printf(" Pret = %5.2f", temp->info.vectPreturi[i]);
}

void traversareListaInvers(nodLD** coadaLD)
{
	nodLD* temp = coadaLD;
	while (temp->prev != coadaLD)
	{
		printf("\nCod = %d, Titlu = %s, Nr. preturi = %d",
			temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
		for (int i = 0; i < temp->info.nrPreturi; i++)
			printf(" Pret = %5.2f", temp->info.vectPreturi[i]);
		temp = temp->prev;
	}

	//parcurgere primul nod
	printf("\nCod = %d, Titlu = %s, Nr. preturi = %d",
		temp->info.cod, temp->info.titlu, temp->info.nrPreturi);
	for (int i = 0; i < temp->info.nrPreturi; i++)
		printf(" Pret = %5.2f", temp->info.vectPreturi[i]);
}

void dezalocareLista(nodLD* capLD)
{
	nodLD* temp = capLD;
	while (temp->next != capLD)
	{
		nodLD* aux = temp->next;
		free(temp->info.titlu);
		free(temp->info.vectPreturi);
		free(temp);
		temp = aux;
	}

	//dezalocare ultimul nod
	free(temp->info.titlu);
	free(temp->info.vectPreturi);
	free(temp);
}

void salvareCartiVector(nodLD* capLD, carte* vect, int* nrElem, int prag)
{
	nodLD* temp = capLD;
	while (temp->next != capLD)
	{
		if (temp->info.nrPreturi >= prag)
		{
			vect[*nrElem] = temp->info;
			(*nrElem)++;
		}
		temp = temp->next;
	}

	//salvare si ultimul nod
	if (temp->info.nrPreturi >= prag)
	{
		vect[*nrElem] = temp->info;
		(*nrElem)++;
	}
}


void stergeCarteDupaTitlu(nodLD** capLD, nodLD** coadaLD, char* titlu)
{
	//cazul 1: nodul sters este primul
	if (strcmp((*capLD)->info.titlu, titlu) == 0)
	{
		nodLD* temp = *capLD;
		*capLD = (*capLD)->next;
		
		


		//actualizare legatura
		 (*capLD)->prev = *coadaLD;
		 (*coadaLD)->next = *capLD;
		 

		//dezalocare practic stergerea
		free(temp->info.titlu);
		free(temp->info.vectPreturi);
		free(temp);
		return;
	}
	//cazul 2: nodul sters este ultimul
	else if (strcmp((*coadaLD)->info.titlu, titlu) == 0)
	{
		nodLD* temp = *coadaLD;
		*coadaLD = (*coadaLD)->prev;

		//actualizare legatura
		(*coadaLD)->next = *capLD;
		(*capLD)->prev = *coadaLD;

		//dezalocare
		free(temp->info.titlu);
		free(temp->info.vectPreturi);
		free(temp);
		return;
	}
	//caz general
	else
	{
		nodLD* temp = *capLD;
		while (temp != NULL)
		{
			if (strcmp(temp->info.titlu, titlu) == 0)
			{
				//trb sa stim vecinii nodului sters pt a face leg
				nodLD* anterior = temp->prev;
				nodLD* urmator = temp->next;

				//actualizare leg
				anterior->next = urmator;
				urmator->prev = anterior;

				//dezalocare
				free(temp->info.titlu);
				free(temp->info.vectPreturi);
				free(temp);
			}
			else temp = temp->next; //continua sa caute titlul
		}
	}
}

void main()
{
	int nrCarti;
	carte c;
	nodLD* capLD = NULL, * coadaLD = NULL;
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
		capLD = inserareNod1(capLD, &coadaLD, c);
		free(c.titlu);
		free(c.vectPreturi);
	}
	fclose(f);

	traversareLista(capLD);
	printf("\n-------------Traversare inversa--------------\n");
	traversareListaInvers(coadaLD);

	printf("\n--------------Vector--------------\n");
	carte* vect = (carte*)malloc(nrCarti * sizeof(carte));
	int nrElem = 0;
	salvareCartiVector(capLD, vect, &nrElem, 3);
	for (int i = 0; i < nrElem; i++)
	{
		printf("\nCod = %d, Titlu = %s, Nr. preturi = %d",
			vect[i].cod, vect[i].titlu, vect[i].nrPreturi);
		for (int j = 0; j < vect[i].nrPreturi; j++)
			printf(" Pret = %5.2f", vect[i].vectPreturi[j]);
	}
	free(vect);

	printf("\n-------------Stergere--------------\n");
	stergeCarteDupaTitlu(&capLD, &coadaLD, "Baltagul");
	traversareLista(capLD);
	printf("\n-------------Traversare inversa--------------\n");
	traversareListaInvers(coadaLD);

	dezalocareLista(capLD);
}
