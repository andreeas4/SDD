
#include <malloc.h>
#include <stdio.h>
typedef struct
{
	int zi, luna, an;
}data;

typedef struct {
	int cod;
	char* companie;
	float pret;
	data dataZbor;
}zbor; 

typedef struct {
	zbor inf;
	struct nodArb* stanga, * dreapta;//8 byte
}nodArb;//38 bytes

//functii

nodArb* creareNod(zbor z, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.cod = z.cod;
	nou->inf.companie = (char*)malloc((strlen(z.companie) + 1) * sizeof(char));
	strcpy(nou->inf.companie, z.companie);
	nou->inf.pret = z.pret;
	nou->inf.dataZbor.zi = z.dataZbor.zi;
	nou->inf.dataZbor.luna = z.dataZbor.luna;
	nou->inf.dataZbor.an = z.dataZbor.an;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}
nodArb* inserareNod(nodArb* rad, zbor z)//rad=radacina
{
	if (rad != NULL)
	{
		if (z.cod < rad->inf.cod)
		{
			rad->stanga = inserareNod(rad->stanga, z);//apel recursiv care intra inca o data in functie
			return rad;//radacina initiala care se modifica doar 
		}

		else if (z.cod > rad->inf.cod)
		{
			rad->dreapta = inserareNod(rad->dreapta, z);//apel recursiv care intra inca o data in functie
			return rad;//radacina initiala care se modifica doar 
		}
		else return rad;
	}
	else
		return creareNod(z, NULL, NULL);
	
}
//RSD --radacica prima preordine
void preordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nCod=%d,Companie=%s,Pret=%5.2f,Data=%d.%d.%d",
			rad->inf.cod, rad->inf.companie,rad->inf.pret, rad->inf.dataZbor.zi, rad->inf.dataZbor.luna, rad->inf.dataZbor.an);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}
//SRD --inordine

//SDR --radacina ultima postordine
void postordine(nodArb* rad)
{
	if (rad != NULL)
	{	postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("\nCod=%d,Companie=%s,Pret=%5.2f,Data=%d.%d.%d",
			rad->inf.cod, rad->inf.companie,  rad->inf.pret, rad->inf.dataZbor.zi, rad->inf.dataZbor.luna, rad->inf.dataZbor.an);
		
	}
}

void dezalocare(nodArb* rad)
{
	//preordine
	if (rad != NULL)
	{
		nodArb* st = rad->stanga;//pastram pointerii
		nodArb* dr = rad->dreapta;
		free(rad->inf.companie);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}

}
// sa salveze intr un vector zborurile din anul 2023
void SalvareZboruriVector(nodArb* rad, zbor* Vect, int* nr, int anPrag)
{
	if (rad != NULL)
	{
		if (rad->inf.dataZbor.an == anPrag)
		{
			Vect[*nr].cod = rad->inf.cod;
			Vect[*nr].companie = (char*)malloc((strlen(rad->inf.companie) + 1) * sizeof(char));
			strcpy(Vect[*nr].companie, rad->inf.companie);
			Vect[*nr].pret = rad->inf.pret;
			Vect[*nr].dataZbor.zi = rad->inf.dataZbor.zi;
			Vect[*nr].dataZbor.luna = rad->inf.dataZbor.luna;
			Vect[*nr].dataZbor.an = rad->inf.dataZbor.an;
			(*nr)++;

		}
		SalvareZboruriVector(rad->stanga, Vect, nr, anPrag);
		SalvareZboruriVector(rad->dreapta, Vect, nr, anPrag);
	}
}


void main()
{
	nodArb* rad = NULL;
	zbor z;
	char* buffer[20];
	int nrZboruri;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrZboruri);
	for (int i = 0; i < nrZboruri; i++)
	{
		fscanf(f, "%d", &z.cod);
		fscanf(f, "%s", buffer);
		z.companie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(z.companie, buffer);
		fscanf(f, "%f", &z.pret);
		fscanf(f, "%d", &z.dataZbor.zi);
		fscanf(f, "%d", &z.dataZbor.luna);
		fscanf(f, "%d", &z.dataZbor.an);
		rad = inserareNod(rad, z);
		free(z.companie);
		
	}
	printf("\n----------------------------------\n");
	preordine(rad);
	printf("\n----------------------------------\n");
	postordine(rad);

	dezalocare(rad);
	fclose(f);
}

