#include <iostream>

using namespace std;

struct Masina {
	char* marca;
	int nrKm;
	int an;
};

Masina creareMasina(const char* marca, int nrKm, int an) {
	Masina m;
	m.marca = (char*)malloc(sizeof(char) * strlen(marca) + 1);
	strcpy(m.marca, marca);
	m.nrKm = nrKm;
	m.an = an;
	return m;
}

void afisareMasina(Masina m) {
	printf("Masina %s din anul %d are %d kilometri.\n", m.marca, m.an, m.nrKm);
}

struct nod {
	Masina info;
	nod* next;
};

nod* creareNod(Masina info, nod* next) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareMasina(info.marca, info.nrKm, info.an);
	nou->next = next;
	return nou;
}

nod* inserareInceput(nod* cap, Masina m) {
	nod* nou = creareNod(m, NULL);
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
			afisareMasina(p->info);
			p = p->next;
		}
	}
}

//hashtable=vector de liste;
//dim=numarul de elemente din vector(nr. de liste);
struct Hashtable {
	nod** vector;
	int dim;
};

Hashtable creareHashtable(int dim) {
	Hashtable hash;
	hash.dim = dim;
	hash.vector = (nod**)malloc(sizeof(nod*) * dim);
	for (int i = 0; i < dim; i++) {
		hash.vector[i] = NULL;
	}
	return hash;
}

//noi alegem parametrul in functie de care il calculam;
int hashcode(int nrKm, int dim) {
	return nrKm % dim;
}

Hashtable inserarehash(Hashtable h, Masina m) {
	if (h.vector) {
		int poz = hashcode(m.nrKm, h.dim);
		if (h.vector[poz]) {
			//daca exista, avem coliziune
			h.vector[poz] = inserareInceput(h.vector[poz], m);
		}
		else {
			h.vector[poz] = inserareInceput(h.vector[poz], m);
		}
	}
	return h;
}

void afisareHash(Hashtable h) {
	if (h.vector) {
		for (int i = 0; i < h.dim; i++) {
			printf("\nPe pozitia %d: \n", i);
			nod* p = h.vector[i];
			afisareLista(p);
		}
	}
}

//cauta o maisna in functie de id (daca asta am pus in hash)
Masina cautaMasina(int nrKm, Hashtable h) {
	if (h.vector) {
		int poz = hashcode(nrKm, h.dim);
		if (h.vector[poz]) {
			nod* p = h.vector[poz];
			while (p) {
				if (p->info.nrKm == nrKm) return p->info;
				p = p->next;
			}
		}
		else return creareMasina("", 0, -1);
	}
	else return creareMasina("", 0, -1);
}

void main() {
	Masina m;
	m=creareMasina("Renault", 256000, 2009);
	afisareMasina(m);

	Hashtable h = creareHashtable(10); //de la 0 la 9
	h = inserarehash(h, m);
	h = inserarehash(h, creareMasina("Dacia", 349746, 2011));
	h = inserarehash(h, creareMasina("Audi", 12860, 2002));
	h = inserarehash(h, creareMasina("BMW", 17508, 2005));
	h = inserarehash(h, creareMasina("BMW", 340012, 2009));
	h = inserarehash(h, creareMasina("Skoda", 31125, 2017));
	h = inserarehash(h, creareMasina("Ford", 11097, 2020));
	h = inserarehash(h, creareMasina("Renaul", 11007, 2019));
	h = inserarehash(h, creareMasina("Volkswagen", 26019, 2018));
	h = inserarehash(h, creareMasina("Audi", 100257, 2008));
	afisareHash(h);

	printf("\nMasina cautata: ");
	int x;
	scanf("%d", &x);
	afisareMasina(cautaMasina(x, h));
}