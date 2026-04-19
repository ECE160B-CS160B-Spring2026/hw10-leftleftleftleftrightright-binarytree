#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct WordTree {
    char *word;
    int count;
    struct WordTree *left;
    struct WordTree *right;
} WordTree;

void treeInsertByWord(WordTree **tree, char *word) {
    if (*tree == NULL) {
        WordTree *node = malloc(sizeof(WordTree));
        node->word = word;
        node->count = 1;
        node->left = NULL;
        node->right = NULL;
        *tree = node;
    } else {
        int cmp = strcmp((*tree)->word, word);
        if (cmp < 0) {
            treeInsertByWord(&(*tree)->left, word);
        } else if (cmp > 0) {
            treeInsertByWord(&(*tree)->right, word);
        } else {
            (*tree)->count++;
        }
    }
}

void treeInsertByCount(WordTree **tree, char *word, int count) {
    if (*tree == NULL) {
        WordTree *node = malloc(sizeof(WordTree));
        node->word = word;
        node->count = count;
        node->left = NULL;
        node->right = NULL;
        *tree = node;
    } else {
        int cmp = count - (*tree)->count;
        if (cmp < 0) {
            treeInsertByCount(&(*tree)->left, word, count);
        } else {
            treeInsertByCount(&(*tree)->right, word, count);
        }
    }
}

void countify(WordTree **countRoot, WordTree **wordRoot) {
    if (*wordRoot == NULL) return;
    countify(countRoot, &(*wordRoot)->left);
    treeInsertByCount(countRoot, (*wordRoot)->word, (*wordRoot)->count);
    countify(countRoot, &(*wordRoot)->right);
}

void read(WordTree **tree) {
    if (*tree == NULL) return;
    read(&(*tree)->right);
    printf("%d %s ", (*tree)->count, (*tree)->word);
    read(&(*tree)->left);
}

int main() {
    WordTree *wordRoot = NULL;

    int n = 0;
    char buf[1000]; // large max word length;
    while (scanf("%s", buf) != EOF) {
        treeInsertByWord(&wordRoot, strdup(buf));
    }
    WordTree *countRoot = NULL;
    countify(&countRoot, &wordRoot);
    read(&countRoot);
    
    return 0;
}