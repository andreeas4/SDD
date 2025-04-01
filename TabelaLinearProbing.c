//liste,coada,stiva,tabela de dispersie,lista de liste,tabela linearprobing de dispersie

//4*5+3=23 de pozitii in vector cu 5 

//implementare de la chain
//daca pe poz data de functia hash este ocupata noi trb sa cautam la stanga sau la dreapta prima pozitie libera (prima data la dreapta pana la final) dupa la stanga(dar nu de la final la inceput)
//se formeaza clustere -dezavantaj
//cautarea la stanga nu trebuie sa fie necesara si nici redimensionarea tabelei-avantaj
//quadratic probing (pozitia+c*i) la patrat -i= de cate ori am apelat functia hush
//lista dubla de studenti si apoi sa se verifice daca este simetrica
//-----------------------------------TABELA LINEAR PROBING---------------------------------------------
#include<stdio.h>
#include<malloc.h>

typedef struct
{

	int cod;
	char* nume;
	float medie;

}student;

typedef struct
{

	student** vect;
	int nrElem;
}hashT;


int functieHash(hashT tabela, int cheie) {
	return cheie % tabela.nrElem;

}

void inserareTabela(hashT tabela, student* s)
{
	int poz = functieHash(tabela, (*s).cod);
	if (tabela.vect[poz] == NULL)
		tabela.vect[poz] = s; //shallow copy 
	else
	{
		//coliziune

		int index = 1;
		while (poz + index < tabela.nrElem)
		{
			if (tabela.vect[poz + index] == NULL)
			{
				poz += index;
				tabela.vect[poz] = s;
				break;
			}
			else index++;
		}
	}
}

void traversareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
		{
			printf("\n pozitie = %d", i);
			printf("\nCod = %d, Nume = %s, Medie = %5.2f", tabela.vect[i]->cod, tabela.vect[i]->nume, tabela.vect[i]->medie);
		}
}

void dezalocareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
		{
			free(tabela.vect[i]->nume);
			free(tabela.vect[i]);
		}
	free(tabela.vect);

}
int stergereHash(hashT tabela ,int codDeSters)
{
	int poz = functieHash(tabela, codDeSters);
	if (tabela.vect[poz] == NULL)
		return -1;
	else
		if(tabela.vect[poz]->cod==codDeSters)
		{
			free(tabela.vect[poz]->nume);
			tabela.vect[poz]=NULL;
			free(tabela.vect);
		}
		else {
			int index = 1;
			while (poz + index < tabela.nrElem)
			{
				if (tabela.vect[poz + index]->cod == codDeSters)
				{
					poz += index;
					free(tabela.vect[poz]->nume);
					tabela.vect[poz]=NULL;
					free(tabela.vect);
				}
			}
		}
	return poz;

 }

void main()
{
	hashT tabela;
	tabela.nrElem = 23;
	tabela.vect = (student*)malloc(tabela.nrElem * sizeof(student));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;
	int nrStud;
	student* s;
	char buffer[100];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++) {
		s = (student*)malloc(sizeof(student));
		fscanf(f, "%d", &s->cod);
		fscanf(f, "%s", buffer);
		s->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s->nume, buffer);
		fscanf(f, "%f", &s->medie);
		inserareTabela(tabela, s);

	}

	fclose(f);

	traversareHash(tabela);
	dezalocareHash(tabela);
}
