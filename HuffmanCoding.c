#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define nullptr NULL

uint8_t *readWholeFile(const char *filePath, size_t *fileSize) {
    int ret = -1;
    FILE *fp = nullptr;
    uint8_t *data = nullptr;

    if (0 == strlen(filePath)) {
        return nullptr;
    }
    if (nullptr == fileSize) {
        return nullptr;
    }

    fp = fopen(filePath, "r");
    if (nullptr == fp) {
        fprintf(stderr, "open file err: %s\n", filePath);
        return nullptr;
    }

    ret = fseek(fp, 0, SEEK_END);
    if (ret < 0) {
        goto close;
    }
    size_t size = ftell(fp);
    if (size < 0) {
        ret = -1;
        goto close;
    }
    ret = fseek(fp, 0, SEEK_SET);
    if (ret < 0) {
        goto close;
    }

    data = (uint8_t *)malloc(size);
    if (nullptr == data) {
        ret = -1;
        goto close;
    }

    ret = fread(data, 1, size, fp);
    if (ret != size) {
        ret = -1;
        goto close;
    }

    *fileSize = size;

close:
    if (fp) {
        fclose(fp);
    }
    if (ret < 0 && data) {
        free(data);
        data = nullptr;
    }
    return data;
}

int doFileStatistics(const char *filePath, int stat[256], size_t statSize) {
    if (nullptr == stat) {
        return -1;
    }
    if (statSize != 256) {
        return -1;
    }

    FILE *fp = fopen(filePath, "r");
    if (nullptr == fp) {
        fprintf(stderr, "open file err: %s\n", filePath);
        return -1;
    }

    int ret = 0;
    int readSize = 0;
    int byte = 0;
    do {
        readSize = fread(&byte, 1, 1, fp);
        if (readSize != 1 && !feof(fp)) {
            fprintf(stderr, "read file err\n");
            ret = -1;
            break;
        }
        if (byte > 0xff) {
            fprintf(stderr, "read invalid byte: %#x\n", byte);
            ret = -1;
            break;
        }
        stat[byte]++;
    } while (!feof(fp));

    fclose(fp);

    return ret;
}

typedef struct SymbolStatistics {
    int symbol;
    int freq;
} SymbolStatistics;

void printSymbolTable(struct SymbolStatistics *tbl, size_t symbolNum) {
    fprintf(stdout, "Symbol Table\n");
    for (int i = 0; i < symbolNum; i++) {
        struct SymbolStatistics *stat = &tbl[i];
        fprintf(stdout, "%d: %d\n", stat->symbol, stat->freq);
    }
}

static void swap(struct SymbolStatistics *a, struct SymbolStatistics *b) {
    struct SymbolStatistics tmp;

    tmp.symbol = a->symbol;
    tmp.freq = a->freq;
    a->symbol = b->symbol;
    a->freq = b->freq;
    b->symbol = tmp.symbol;
    b->freq = tmp.freq;
}

static int compare(const struct SymbolStatistics *a, const struct SymbolStatistics *b) {
    if (a->freq < b->freq) {
        return -1;
    } else if (a->freq > b->freq) {
        return 1;
    }
    return 0;
}

void quickSort(struct SymbolStatistics *tbl, int symbolNum) {
    if (symbolNum <= 1) {
        return;
    }

    int left = 0;
    int right = symbolNum - 1;
    while (left < right) {
        while (left < right && compare(&tbl[left], &tbl[right]) <= 0) {
            right--;
        }
        if (left >= right) {
            break;
        }
        //fprintf(stdout, "left[%d][%d] > right[%d][%d], swap\n", left, tbl[left].freq, right, tbl[right].freq);
        swap(&tbl[left], &tbl[right]);
        left++;

        while (left < right && compare(&tbl[right], &tbl[left]) >= 0) {
            left++;
        }
        if (left >= right) {
            break;
        }
        //fprintf(stdout, "right[%d][%d] < left[%d][%d], swap\n", right, tbl[right].freq, left, tbl[left].freq);
        swap(&tbl[left], &tbl[right]);
        right--;
    }

    quickSort(&tbl[0], left);
    quickSort(&tbl[left+1], symbolNum-left-1);

    return;
}

typedef struct HuffmanCode {
    int symbol;
    int code;
    int codeBits;
} HuffmanCode;

struct TreeNode {
    int symbol;
    int freq;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

struct ListNode {
    struct TreeNode *data;
    struct ListNode *next;
} ListNode;

struct ListNode *allocateNewListNode(void) {
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (nullptr == node) {
        return nullptr;
    }

    memset(node, 0x00, sizeof(struct ListNode));
    node->data = nullptr;
    node->next = nullptr;

    return node;
}

struct ListNode *createLinkedList() {
    return allocateNewListNode();
}

int destroyLinkedList(struct ListNode **root) {
    if (nullptr == root || nullptr == (*root)) {
        return -1;
    }
    struct ListNode *head = nullptr, *node = nullptr;
    head = *root;
    while (head) {
        node = head;
        head = node->next;
        free(node);
        node = nullptr;
    }
    *root = nullptr;

    return 0;
}

int insertNodeInAscendingOrder(struct ListNode *root, struct TreeNode *data) {
    struct ListNode *last = root;
    struct ListNode *current = root->next;
    struct TreeNode *currentData = nullptr;
    while (current) {
        currentData = current->data;
        if (currentData->freq > data->freq) {
            break;
        }
        last = current;
        current = current->next;
    }

    if (nullptr == last) {
        return -1;
    }

    struct ListNode *newNode = allocateNewListNode();
    newNode->data = data;
    struct ListNode *nextNode = last->next;
    last->next = newNode;
    newNode->next = nextNode;

    return 0;
}

struct TreeNode *popMininumDataNode(struct ListNode *root) {
    struct ListNode *current = root->next;
    if (nullptr == current) {
        return nullptr;
    }
    struct TreeNode *currentData = current->data;
    root->next = current->next;

    free(current);
    current = nullptr;

    return currentData;
}

void printLinkedList(struct ListNode *root) {
    struct ListNode *current = root->next;
    fprintf(stdout, "Linked List\n");
    while (current) {
        struct TreeNode *currentData = current->data;
        fprintf(stdout, "%d: %d\n", currentData->symbol, currentData->freq);
        current = current->next;
    }
}

struct TreeNode *allocateNewTreeNode(int symbol, int freq) {
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (nullptr == node) {
        return nullptr;
    }

    memset(node, 0x00, sizeof(struct TreeNode));
    node->symbol = symbol;
    node->freq = freq;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

void preOrderTraversal(struct TreeNode *top, int code, int codeBits) {
    if (nullptr == top) {
        return;
    }
    if (nullptr == top->left && nullptr == top->right) {
        struct HuffmanCode huffmanCode;
        struct HuffmanCode *hCode = &huffmanCode;
        hCode->symbol = top->symbol;
        hCode->code = code;
        hCode->codeBits = codeBits;
        fprintf(stdout, "%d[%#x.%d]: %d\n", hCode->symbol, hCode->code, hCode->codeBits, top->freq);
    }

    code = code << 1;
    codeBits++;
    preOrderTraversal(top->left, code, codeBits);
    preOrderTraversal(top->right, code + 1, codeBits);
}

struct TreeNode *buildHuffmanTree(struct SymbolStatistics *tbl, int symbolNum, bool excludeZeroFreq) {
    int ret = -1;

    struct ListNode *root = allocateNewListNode();
    for (int i = 0; i < symbolNum; i++) {
        if (true == excludeZeroFreq && 0 == tbl[i].freq) {
            continue;
        }

        struct TreeNode *data = allocateNewTreeNode(tbl[i].symbol, tbl[i].freq);
        ret = insertNodeInAscendingOrder(root, data);
        if (ret != 0) {
            fprintf(stderr, "insert node into linked-list err\n");
            break;
        }
    }
    if (ret != 0) {
        // TODO(bjweare): free linked-list
        fprintf(stderr, "build linked-list err\n");
        return nullptr;
    }
    printLinkedList(root);

    struct TreeNode *top = nullptr;
    while (root->next) {
        struct TreeNode *min1 = nullptr, *min2 = nullptr;
        struct TreeNode *parent = nullptr;

        min1 = popMininumDataNode(root);
        min2 = popMininumDataNode(root);
        if (nullptr == min2) {
            top = min1;
            break;
        }
        parent = allocateNewTreeNode(-1, min1->freq + min2->freq);
        parent->left = min1;
        parent->right = min2;
        ret = insertNodeInAscendingOrder(root, parent);
        if (ret != 0) {
            fprintf(stderr, "insert node into linked-list err\n");
            break;
        }
    }
    // TODO(bjweare): free linked-list

    if (nullptr == top) {
        // TODO(bjweare): free binary-tree
        fprintf(stderr, "build huffman tree err\n");
        return nullptr;
    }

    return top;
}

int main(int argc, const char *argv[]) {
    if (argc != 2 || (argc > 1 && 0 == strlen(argv[1]))) {
        fprintf(stderr, "Usage: %s file_path\n", argv[0]);
        return -1;
    }

    const char *filePath = argv[1];
    int stat[256] = {0};
    size_t symbolNum = sizeof(stat)/sizeof(int);
    memset(stat, 0x00, sizeof(stat));

    int ret = doFileStatistics(filePath, stat, symbolNum);
    if (ret != 0) {
        fprintf(stdout, "do statistics err: %d\n", ret);
        return ret;
    }

    //symbolNum = 10;
    struct SymbolStatistics statTbl[256];
    for (int i = 0; i < symbolNum; i++) {
        statTbl[i].symbol = i;
        statTbl[i].freq = stat[i];
        //statTbl[i].freq = rand() % symbolNum;
    }

    //quickSort(statTbl, symbolNum);
    printSymbolTable(statTbl, symbolNum);
    struct TreeNode *top = buildHuffmanTree(statTbl, symbolNum, true);
    if (nullptr == top) {
        return -1;
    }
    fprintf(stdout, "Huffman Tree\n");
    preOrderTraversal(top, 0, 0);

    return 0;
}
