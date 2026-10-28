/*
 * Student Task Manager
 * DSA Mini Project using a Singly Linked List
 *
 * Features:
 * 1. Add a task
 * 2. View all tasks
 * 3. Search a task by ID
 * 4. Mark a task as completed
 * 5. Delete a task
 * 6. Exit
 *
 * Compile: gcc student_task_manager.c -o student_task_manager
 * Run:     ./student_task_manager
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int id;
    char title[100];
    int completed;
    struct Task *next;
} Task;

Task *head = NULL;
int nextID = 1;

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard remaining input */
    }
}

void readTitle(char title[], size_t size) {
    if (fgets(title, (int)size, stdin) != NULL) {
        size_t len = strlen(title);
        if (len > 0 && title[len - 1] == '\n') {
            title[len - 1] = '\0';
        } else {
            clearInputBuffer();
        }
    }
}

void addTask(void) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("Memory allocation failed. Please try again.\\n");
        return;
    }

    newTask->id = nextID++;
    printf("Enter task title: ");
    readTitle(newTask->title, sizeof(newTask->title));

    if (newTask->title[0] == '\0') {
        printf("Task title cannot be empty. Task not added.\\n");
        free(newTask);
        nextID--;
        return;
    }

    newTask->completed = 0;
    newTask->next = NULL;

    if (head == NULL) {
        head = newTask;
    } else {
        Task *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTask;
    }

    printf("Task added successfully! Task ID: %d\\n", newTask->id);
}

void viewTasks(void) {
    if (head == NULL) {
        printf("No tasks available. Add a task first.\\n");
        return;
    }

    printf("\\n--- Student Tasks ---\\n");
    printf("%-6s %-35s %s\\n", "ID", "Task Title", "Status");
    printf("---------------------------------------------------------------\\n");

    Task *current = head;
    while (current != NULL) {
        printf("%-6d %-35s %s\\n",
               current->id,
               current->title,
               current->completed ? "Completed" : "Pending");
        current = current->next;
    }
}

Task *findTask(int id) {
    Task *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void searchTask(void) {
    int id;
    printf("Enter task ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID. Please enter a number.\\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    Task *task = findTask(id);
    if (task == NULL) {
        printf("Task with ID %d was not found.\\n", id);
    } else {
        printf("\\nTask ID: %d\\nTitle: %s\\nStatus: %s\\n",
               task->id, task->title,
               task->completed ? "Completed" : "Pending");
    }
}

void completeTask(void) {
    int id;
    printf("Enter task ID to mark as completed: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID. Please enter a number.\\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    Task *task = findTask(id);
    if (task == NULL) {
        printf("Task with ID %d was not found.\\n", id);
    } else if (task->completed) {
        printf("This task is already completed.\\n");
    } else {
        task->completed = 1;
        printf("Task marked as completed!\\n");
    }
}

void deleteTask(void) {
    int id;
    printf("Enter task ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID. Please enter a number.\\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    Task *current = head;
    Task *previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Task with ID %d was not found.\\n", id);
        return;
    }

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Task deleted successfully.\\n");
}

void freeTasks(void) {
    Task *current = head;
    while (current != NULL) {
        Task *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

int main(void) {
    int choice;

    do {
        printf("\\n===== STUDENT TASK MANAGER =====\\n");
        printf("1. Add Task\\n");
        printf("2. View All Tasks\\n");
        printf("3. Search Task\\n");
        printf("4. Mark Task as Completed\\n");
        printf("5. Delete Task\\n");
        printf("6. Exit\\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number from 1 to 6.\\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: searchTask(); break;
            case 4: completeTask(); break;
            case 5: deleteTask(); break;
            case 6: printf("Thank you for using Student Task Manager!\\n"); break;
            default: printf("Invalid choice. Please select 1 to 6.\\n");
        }
    } while (choice != 6);

    freeTasks();
    return 0;
}
