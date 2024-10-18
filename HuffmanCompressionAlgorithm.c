#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_MAX 128
#define MAX_LEN 8

typedef struct NODE {
    struct NODE *left, *right;
    int ascii;
    int cnt;
} NODE;

typedef struct {
    NODE *heap[ASCII_MAX];
    int size;
} PirorityQueue;

void insert_node(PirorityQueue* pq, NODE* node) {
    pq->heap[pq->size] = node;

    NODE* temp;
    for(int i = pq->size; i > 0; i--) {
        if(pq->heap[i]->cnt < pq->heap[i-1]->cnt) {
            temp = pq->heap[i-1];
            pq->heap[i-1] = pq->heap[i];
            pq->heap[i] = temp;
        }
        else break;
    }

    pq->size++;
}

NODE* PirorityQueue_pop(PirorityQueue* pq) {
    NODE* node = pq->heap[0];
    
    for(int i = 0; i < pq->size-1; i++) {
        pq->heap[i] = pq->heap[i+1];
    }
    pq->heap[--pq->size] = NULL;

    return node;
}

NODE* HuffmanCoding(char* file_name) {
    int input[ASCII_MAX] = {0};

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("%s 파일을 열 수 없음.\n", file_name);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* inputs = (char*)malloc(file_size+1);
    fscanf(file, "%s", inputs);
    fclose(file);

    for(int i = 0; i < file_size; i++) {
        input[inputs[i]]++;
    }

    PirorityQueue* pq = (PirorityQueue*)malloc(sizeof(PirorityQueue));

    for(int i = 0; i < ASCII_MAX; i++) {
        if(input[i] > 0 ) {
           NODE* node = (NODE*)malloc(sizeof(NODE));
           node->ascii = i;
           node->cnt = input[i];
           node->left = node->right = NULL;

           insert_node(pq, node);
        }
    }

    while(pq->size >= 2) {
        NODE* left = PirorityQueue_pop(pq);
        NODE* right = PirorityQueue_pop(pq);

        NODE* node = (NODE*)malloc(sizeof(NODE));
        node->cnt = left->cnt + right->cnt;
        node->left = left;
        node->right = right;

        insert_node(pq, node);
    }

    return pq->heap[0];
}

void getCode(NODE* node, char code[][MAX_LEN], char c[]) {
    char left[MAX_LEN];
    char right[MAX_LEN];

    if(node->left == NULL && node->left == NULL) {
        strcpy(code[node->ascii], c);
        return ;
    }
    if(node->left != NULL) {
        strcpy(left, c);
        strcat(left, "0");
        getCode(node->left, code, left);
    }
    if(node->right != NULL){
        strcpy(right, c);
        strcat(right, "1");
        getCode(node->right, code, right);
    }
}

void HuffmanEncoding(NODE* root, char* file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("%s 파일을 열 수 없음.\n", file_name);
        return ;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* inputs = (char*)malloc(file_size+1);
    fscanf(file, "%s", inputs);
    fclose(file);

    char code[ASCII_MAX][MAX_LEN];
    char c[MAX_LEN] = "";
    for(int i = 0; i < ASCII_MAX; i++) {
        code[i][0] = '\0';
    }
    getCode(root, code, c);
    
    FILE* output = fopen("Huffman_encoded.txt", "w");
    if (output == NULL) {
        printf("Huffman_encoded.txt 파일을 열 수 없음.\n");
        return ;
    }

    for(int i = 0; i < file_size; i++) {
        fprintf(output, "%s", code[inputs[i]]);
    }
    fclose(output);
}

void HuffmanDecoding(NODE* root, char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("%s 파일을 열 수 없음.\n", file_name);
        return ;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* inputs = (char*)malloc(file_size+1);
    fscanf(file, "%s", inputs);
    fclose(file);

    FILE* output = fopen("Huffman_decoded.txt", "w");
    if (output == NULL) {
        printf("Huffman_decoded.txt 파일을 열 수 없음.\n");
        return ;
    }

    NODE* node = root;
    for(int i = 0; i < file_size; i++) {
        if(node->left == NULL && node->right == NULL) {
            fprintf(output, "%c", node->ascii);
            node = root;
        }
        if(inputs[i] == '0') {
            node = node->left;
        }
        else if(inputs[i] == '1') {
            node = node->right;
        }
    }
    if(node->left == NULL && node->right == NULL) {
        fprintf(output, "%c", node->ascii);
        node = root;
    }
    fclose(output);
}

int main() {
    NODE* root = HuffmanCoding("Huffman_input.txt");
    HuffmanEncoding(root, "Huffman_input.txt");
    HuffmanDecoding(root, "Huffman_input2.txt");

    return 0;
}