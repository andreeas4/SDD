#include <stdio.h>
#include <malloc.h>

typedef struct {
	int prioritate;
	char* descriere;
	float durata;
} task;

typedef struct {
	int nrTaskuri;
	task* vect;
} heap;

void filtrare(heap h, int index)// verifică doar o singură ramură, aceea pe care a făcut swap(unde copilul era mai mic decât părintele).
{
	int indexRad = index;//initializam indicele radacinii cu index
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrTaskuri && h.vect[indexSt].prioritate < h.vect[indexRad].prioritate) {//se verifica daca exista un copil cu prioritate mai mica decat parintele
		indexRad = indexSt;//indexRad devine copilul stang->practic viitoarea radacina
	}
	if (indexDr < h.nrTaskuri && h.vect[indexDr].prioritate < h.vect[indexRad].prioritate) {
		indexRad = indexDr;//indexRad devine copilul drept daca e mai mic decat cel stang sau parintele
	}
	if (index != indexRad)//daca am gasit un copil de acest fel trebuie sa facem swap
	{
		task aux = h.vect[index];//salvam temporar in aux parintele actual (index)
		h.vect[index] = h.vect[indexRad];//indexul de radacina (parinte) primeste copilul care nu respecta restrictia
		h.vect[indexRad] = aux;//punem parintele in locul copilului
		filtrare(h, indexRad);//refacem filtrarea recursiv pe ramura afectata
	}
}

heap inserare(heap h, task nou)
{
	task* vectNou = (task*)malloc((h.nrTaskuri + 1) * sizeof(task));
	for (int i = 0; i < h.nrTaskuri; i++)
		vectNou[i] = h.vect[i];
	h.nrTaskuri++;
	vectNou[h.nrTaskuri - 1] = nou;//adauga noul task la finalul vectorului
	free(h.vect);//eliberam vechiul vector
	h.vect = vectNou;
	for (int i = (h.nrTaskuri - 1) / 2; i >= 0; i--)
		filtrare(h, i);//filtreaza arborele de la ultimul nod parinte spre radacina
	return h;
}

heap extragere(heap h, task* extras)//extrage task-ul cu prioritatea cea mai mica (radacina)
{
	task* vectorNou = (task*)malloc((h.nrTaskuri - 1) * sizeof(task));
	//--------------------------
	task aux = h.vect[0];
	h.vect[0] = h.vect[h.nrTaskuri - 1];//radacina primeste ultimul task 
	h.vect[h.nrTaskuri - 1] = aux;//se face interschimbare intre radacina si ultimul task 
	//--------------------------> se izoleaza nodul cu cea mai mica prioritate la finalul vectorului
	*extras = h.vect[h.nrTaskuri - 1];//salvam task-ul extras in variabila extras
	h.nrTaskuri--;
	for (int i = 0; i < h.nrTaskuri; i++)
		vectorNou[i] = h.vect[i];//copiem elementele ramase intr-un vector nou
	free(h.vect);//eliberam vechiul vector
	h.vect = vectorNou;//actualizam vectorul heapului
	for (int i = (h.nrTaskuri - 1) / 2; i >= 0; i--)
		filtrare(h, i);//refacem structura de heap
	return h;
}

void afisareHeap(heap h)
{
	for (int i = 0; i < h.nrTaskuri; i++)
	{
		printf("Prioritate : %d \t Descriere : %s \t Durata : %.2f ;\n",
			h.vect[i].prioritate, h.vect[i].descriere, h.vect[i].durata);
	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrTaskuri; i++)
		free(h.vect[i].descriere);//eliberam memoria alocata pentru descriere
	free(h.vect);//eliberam vectorul de taskuri
}

int main()
{
	heap h;
	char buffer[100];
	FILE* f = fopen("fisier.txt", "r");

	if (!f) {
		printf("Eroare: fișierul nu a fost găsit.\n");
		return 1;
	}

	fscanf(f, "%d", &h.nrTaskuri);
	h.vect = (task*)malloc(h.nrTaskuri * sizeof(task));

	for (int i = 0; i < h.nrTaskuri; i++)
	{
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].descriere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].descriere, buffer);
		fscanf(f, "%f", &h.vect[i].durata);
	}

	fclose(f);

	for (int i = (h.nrTaskuri - 1) / 2; i >= 0; i--)
		filtrare(h, i);//formam un min-heap corect din vectorul citit

	printf("Heap-ul construit este:\n");
	afisareHeap(h);

	dezalocare(h);//eliberam toata memoria
	return 0;
}