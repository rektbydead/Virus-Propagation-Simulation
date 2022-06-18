
#ifndef person_h
#define person_h

typedef struct person person, *pPerson;

#define SICK 'D'
#define HEALTHY 'S'   
#define IMMUNE 'I'

struct person {
    char name[100];
    int age;
    char status;
    int nSickDays; // number of sick days
    int placeID;

    pPerson next;
};


void freePersons(pPerson c);

pPerson addPerson(pPerson p, pPerson pPerson);

void mostraTudo(pPerson c);

pPerson atribuirLocais(pPerson p, pRoom s, int total);

#endif

