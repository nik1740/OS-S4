#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int block_number;
    int size;
    int is_free;
    struct Block* next;
} Block;

typedef struct Process {
    int process_number;
    int size;
    int allocated;        // 1 = allocated, 0 = not
    int block_number;     // -1 if not allocated
} Process;

Block* head = NULL;
int block_counter = 1;

// Function to add memory blocks to the linked list
void add_memory_block(int size) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->size = size;
    new_block->is_free = 1;
    new_block->block_number = block_counter++;
    new_block->next = NULL;

    if (head == NULL) {
        head = new_block;
    } else {
        Block* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new_block;
    }
}

// Function to perform First Fit allocation
void first_fit(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        Block* current = head;
        Block* chosen = NULL;

        while (current != NULL) {
            if (current->is_free && current->size >= processes[i].size) {
                chosen = current;
                break;  // First Fit: stop at first match
            }
            current = current->next;
        }

        if (chosen != NULL) {
            // Split block if extra space remains
            if (chosen->size > processes[i].size) {
                Block* leftover = (Block*)malloc(sizeof(Block));
                leftover->size = chosen->size - processes[i].size;
                leftover->is_free = 1;
                leftover->block_number = block_counter++;
                leftover->next = chosen->next;

                chosen->next = leftover;
                chosen->size = processes[i].size;
            }

            chosen->is_free = 0;
            processes[i].allocated = 1;
            processes[i].block_number = chosen->block_number;
        } else {
            processes[i].allocated = 0;
            processes[i].block_number = -1;
        }
    }
}

// Print the result of allocations
void print_allocations(Process processes[], int n) {
    printf("\nProcess Allocation:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d Size %d -> ", processes[i].process_number, processes[i].size);
        if (processes[i].allocated) {
            printf("Block %d\n", processes[i].block_number);
        } else {
            printf("Not Allocated\n");
        }
    }
}

// Print free blocks
void print_free_blocks() {
    printf("\nFree Blocks:\n");
    Block* current = head;
    while (current != NULL) {
        if (current->is_free) {
            printf("Block %d Size %d\n", current->block_number, current->size);
        }
        current = current->next;
    }
}

int main() {
    int num_blocks, size, num_processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &num_blocks);
    for (int i = 0; i < num_blocks; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &size);
        add_memory_block(size);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &num_processes);
    Process processes[num_processes];
    for (int i = 0; i < num_processes; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].process_number = i + 1;
        processes[i].allocated = 0;
        processes[i].block_number = -1;
    }

    printf("\nAllocating using First Fit...\n");
    first_fit(processes, num_processes);

    print_allocations(processes, num_processes);
    print_free_blocks();

    return 0;
}
