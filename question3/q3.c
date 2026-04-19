#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Ok so I'm working off the hash map code from Lesson #11 (since the question's readme says to use the class hash map)
// -------------

// K&R Pg. 144-145

struct nlist {              // table entry:
    struct nlist *next;     // next entry in chain
    char *name;             // defined name
    char *defn;             // replacement text
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // pointer table

// hash: form hash value for string
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

// lookup:look for s in hashtab
struct nlist *lookup(char *s)
{
    struct nlist *np;

    // loop through linked list
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; // found

    return NULL;       // not found
}

struct nlist *lookup(char *);

// install:put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { // not found
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else // already there
        free((void *) np->defn); // free previous defn
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}


// OK THIS FUNCTION IS NEW; NOT PART OF LESSON 11 
void intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2)
{
    int i=0;
    int outIndex=0;
    char key[50];
    // insert all elements of array1 into the hash table
    for (i =0; i < lenArr1; i++){
        sprintf(key, "%d", array1[i]);
        install(key, "1"); // using function from class
    }
    // now, check array2 for matches
    for (i = 0; i< lenArr2; i++){
        sprintf(key, "%d", array2[i]);
        if (lookup(key) != NULL){
            output[outIndex] = array2[i];
            outIndex++;
            install(key, "0");
        }
    }
    output[outIndex] = -1; // mark the endpoint so it's easy to loop thru
}

int main() {
    int lenArr1;
    int lenArr2;
    int i;

    scanf("%d", &lenArr1);
    int array1[lenArr1];

    for (i=0; i<lenArr1; i++){
        scanf("%d", &array1[i]);
    }

    scanf("%d", &lenArr2);
    int array2[lenArr2];

    for (i=0; i<lenArr2; i++){
        scanf("%d", &array2[i]);
    }

    int output[lenArr1 < lenArr2 ? lenArr1 : lenArr2 + 1];

    intersection(output, array1, lenArr1, array2, lenArr2);

    for (i = 0; output[i]!=-1; i++){
        printf("%d ", output[i]);
    }

    return 0;
}
