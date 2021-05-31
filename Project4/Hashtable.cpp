#include <iostream>

using namespace std;

struct Animal {
	int id;
	char* nume;
	int nrPicioare;
};

Animal creareAnimal(int id, const char* nume, int nrPicioare) {
	Animal a;
	a.id = id;
	a.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(a.nume, nume);
	a.nrPicioare = nrPicioare;
	return a;
}

void afisareAnimal(Animal a) {
	printf("Animalul cu id-ul %d cu numele %s are %d picioare.\n", a.id, a.nume, a.nrPicioare);
}


struct nod {
	Animal info;
	nod* next;
};

nod* creareNod(Animal info, nod* next) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareAnimal(info.id, info.nume, info.nrPicioare);
	nou->next = next;
	return nou;
}

nod* inserareInceput(nod* cap, Animal a) {
	nod* nou = creareNod(a, NULL);
	if (cap) {
		nou->next = cap;
		cap = nou;
		return cap;
	}
	else {
		cap = nou;
		return cap;
	}
}

void afisareLista(nod* cap) {
	if (cap) {
		nod* p = cap;
		while (p) {
			afisareAnimal(p->info);
			p = p->next;
		}
	}
}

struct Hashtable {
	nod** vector;
	int dim;
};

Hashtable creareHashtable(int dim) {
	Hashtable hash;
	hash.dim = dim;
	hash.vector = (nod**)malloc(sizeof(nod*) * dim);
	for (int i = 0;i < dim;i++) {
		hash.vector[i] = NULL;
	}
	return hash;
}

int hashcode(int id, int dim) {
	return id % dim;
}
Hashtable inserarehash(Hashtable h, Animal a) {
	if (h.vector) {
		int poz = hashcode(a.id, h.dim);
		if (h.vector[poz]) {
			//avem coliziune
			h.vector[poz] = inserareInceput(h.vector[poz], a);
		}
		else {
			h.vector[poz] = inserareInceput(h.vector[poz], a);
		}
	}
	return h;
}

void afisareHash(Hashtable h) {
	if (h.vector) {
		for (int i = 0; i < h.dim; i++) {
			printf("\n pe pozitia %d: \n", i);
			nod* p = h.vector[i];
			afisareLista(p);
		}
	}
}
Animal cautaAnimal(int id, Hashtable h) {
	if (h.vector) {
		int poz = hashcode(id, h.dim);
		if (h.vector[poz]) {
			nod* p = h.vector[poz];
			while (p) {
				if (p->info.id == id) return p->info;
				p = p->next;
			}
		}
		else return creareAnimal(-1, "", 0);
	}
	else return creareAnimal(-1, "", 0);
}
void main() {
	Hashtable h = creareHashtable(5);
	h = inserarehash(h, creareAnimal(0, "gdsjgf", 4));
	h = inserarehash(h, creareAnimal(1, "gfb", 4));
	h = inserarehash(h, creareAnimal(8, "gdsjgf", 4));
	h = inserarehash(h, creareAnimal(3, "gdsjgf", 4));
	h = inserarehash(h, creareAnimal(10, "gdsjgf", 4));
	h = inserarehash(h, creareAnimal(5, "gdsjgf", 4));

	afisareHash(h);
	printf("\n animal cautat: \n");

	afisareAnimal(cautaAnimal(8, h));
}