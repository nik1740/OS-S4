#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size;
    int is_free;
    int block_number;
    struct Block* next;
} Block;

typedef struct Process {
    int size;
    int allocated;
    int block_number; // the block it was allocated to
} Process;

Block* head = NULL;
int block_counter = 1;

Block* create_block(int size, int number) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->size = size;
    new_block->is_free = 1;
    new_block->block_number = number;
    new_block->next = NULL;
    return new_block;
}

void insert_block(int size) {
    Block* new_block = create_block(size, block_counter++);
    if (head == NULL) {
        head = new_block;
    } else {
        Block* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_block;
    }
}

void split_block(Block* target, int size) {
    if (target->size > size) {
        Block* split = create_block(target->size - size, block_counter++);
        split->next = target->next;
        target->next = split;
        target->size = size;
    }
}

Block* find_block(int process_size, int strategy) {
    Block* temp = head;
    Block* target = NULL;

    if (strategy == 1) {
        // First Fit
        while (temp) {
            if (temp->is_free && temp->size >= process_size) {
                target = temp;
                break;
            }
            temp = temp->next;
        }
    } else if (strategy == 2) {
        // Best Fit
        int min = __INT_MAX__;
        while (temp) {
            if (temp->is_free && temp->size >= process_size && (temp->size - process_size) < min) {
                min = temp->size - process_size;
                target = temp;
            }
            temp = temp->next;
        }
    } else if (strategy == 3) {
        // Worst Fit
        int max = -1;
        while (temp) {
            if (temp->is_free && temp->size >= process_size && (temp->size - process_size) > max) {
                max = temp->size - process_size;
                target = temp;
            }
            temp = temp->next;
        }
    }

    return target;
}

void allocate_all(Process* processes, int n, int strategy) {
    for (int i = 0; i < n; i++) {
        Block* b = find_block(processes[i].size, strategy);
        if (b) {
            split_block(b, processes[i].size);
            b->is_free = 0;
            processes[i].allocated = 1;
            processes[i].block_number = b->block_number;
        } else {
            processes[i].allocated = 0;
        }
    }
}

void print_allocation(Process* processes, int n) {
    for (int i = 0; i < n; i++) {
        printf("Process %d -> Size: %d -> ", i + 1, processes[i].size);
        if (processes[i].allocated)
            printf("Allocated in Block %d\n", processes[i].block_number);
        else
            printf("Not Allocated\n");
    }
}

void print_free_blocks() {
    printf("\nFree Blocks:\n");
    Block* temp = head;
    while (temp) {
        if (temp->is_free) {
            printf("Block %d -> Size: %d\n", temp->block_number, temp->size);
        }
        temp = temp->next;
    }
}

int main() {
    int n_blocks, n_processes, size, strategy;

    printf("Enter number of memory blocks: ");
    scanf("%d", &n_blocks);
    for (int i = 0; i < n_blocks; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &size);
        insert_block(size);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &n_processes);
    Process processes[n_processes];

    for (int i = 0; i < n_processes; i++) {
        printf("Enter size of Process %d: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].allocated = 0;
        processes[i].block_number = -1;
    }

    printf("\nChoose Allocation Strategy:\n");
    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter option: ");
    scanf("%d", &strategy);

    printf("\n");

    allocate_all(processes, n_processes, strategy);
    print_allocation(processes, n_processes);
    print_free_blocks();

    return 0;
}
