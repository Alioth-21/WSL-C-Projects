// C-2:  To-do Notes
#include"c-2-1head.h"


int main() {
    printf("Welcome to the To-do Notes Management System!\n");
    // The implementation of the to-do notes management system will go here.
    int chioce= -1;

    // Initialize the linked list and stack
    PtrL L = NULL;
    PtrS S = NULL;
    if (!InitList(L, S)) {
        return -1;
    }

    while (chioce != 0) {
        printf("\nMenu:\n");
        printf("1. Add a new to-do item\n");
        printf("2. Delete a to-do item\n");
        printf("3. Cancel Edit\n");
        printf("4. Display all to-do items\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &chioce);
        switch (chioce) {
            case 1:
                AddItem(L);
                break;
            case 2:
                DeleteItem(L);
                break;
            case 3:
                // Cancel Edit
                Undo(L);
                break;
            case 4:
                DisplayItems(L);
                break;
            case 0:
                printf("Exiting the program.\n");
                DestoryList(L, S);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

//-------tools functions-------
bool InitList(PtrL L, PtrS S){
    L = (PtrL)malloc(sizeof(struct LinkList));
    S = (PtrS)malloc(sizeof(struct StackList));
    if (L == NULL && S == NULL) {
        return false;
    }
    L->Head = NULL;
    L->Last = NULL;
    L->ListSize = 0;
    S->Top = NULL;
    S->ListSize = 0;
    return true;
}
bool DestoryList(PtrL L, PtrS S){
    if (L != NULL) {
        free(L);
    }
    if (S != NULL) {
        free(S);
    }
    return true;
}
bool IsEmpty(PtrL List){
    return (List->ListSize == 0);
}
bool IsFull(PtrL List){
    return (List->ListSize == MAX_ITEMS);
}
Ptr CreateItem(){
    Ptr np = (Ptr)malloc(sizeof(struct Item));
    if (np == NULL) {
        return NULL;
    }
    printf("Enter ID for the new item: ");
    scanf("%d", &np->Id);
    getchar(); // Consume the newline character left by scanf
    printf("Enter content for the new item: ");
    fgets(np->Content, MAX_SIZE, stdin);
    np->Next = NULL;
    return np;
}
// 查找前驱节点
Ptr SearchPrveItemById(PtrL List, int id) {
    if (List->Head == NULL || List->Head->Id == id) {
        return NULL;   // 空链表，或目标就是头节点 → 没有前驱
    }
    
    Ptr p = List->Head;
    while (p->Next != NULL && p->Next->Id != id) {
        p = p->Next;
    }
    
    return (p->Next != NULL) ? p : NULL;  // 找到返回前驱，否则 NULL
}
void OutputItem(Ptr Item){
    if (Item != NULL) {
        printf("ID: %d\n", Item->Id);
        printf("Content: %s\n", Item->Content);
    }
}

//stack functions
bool push(PtrS S, Ptr Item){
    if(S->ListSize == MAX_ITEMS) {
        return false; // Stack is full
    }
    Item->Next = S->Top;
    S->Top = Item;
    S->ListSize++;
    return true;
}
bool pop(PtrS S){
    if(S->ListSize == 0) {
        return false; // Stack is empty
    }
    Ptr temp = S->Top;
    S->Top = S->Top->Next;
    free(temp);
    S->ListSize--;
    return true;
}

//-------operations functions-------
bool AddItem(PtrL List){
    if(IsFull(List)) {
        printf("List is full. Cannot add new item.\n");
        return false; // List is full
    }
    Ptr newItem = CreateItem();
    if (newItem == NULL) {
        printf("Memory allocation failed. Cannot add new item.\n");
        return false; // Memory allocation failed
    }

    // Add the new item to the list
    if (List->Head == NULL) {
        List->Head = newItem;
        List->Last = newItem;
    }
    else{
        List->Last->Next = newItem;
        List->Last = newItem;
    }
    List->ListSize++;
    return true;
}
bool FindItem(PtrL List){
    if(IsEmpty(List)) {
        printf("List is empty. No items to find.\n");
        return false; // List is empty
    }
    int id;
    printf("Enter the ID of the item to find: ");
    scanf("%d", &id);
    Ptr prve = SearchPrveItemById(List, id);
    if (List->Head->Id == id) {
        OutputItem(List->Head);
    } 
    else if(prve != NULL) {
        OutputItem(prve->Next);
    }
    else {
        printf("Item with ID %d not found.\n", id);
        return false; // Item not found
    }
    return true;
}
bool AlterItem(PtrL List){
    if(IsEmpty(List)) {
        printf("List is empty. No items to alter.\n");
        return false; // List is empty
    }
    int id;
    printf("Enter the ID of the item to alter: ");
    scanf("%d", &id);
    Ptr prve = SearchPrveItemById(List, id);
    if (List->Head->Id == id) {
        OutputItem(List->Head);
    } 
    else if(prve != NULL) {
        OutputItem(prve->Next);
    }
    else {
        printf("Item with ID %d not found.\n", id);
        return false; // Item not found
    }
    printf("Enter new content: ");
    getchar(); // Consume the newline character left by scanf
    if (List->Head->Id == id) {
        fgets(List->Head->Content, MAX_SIZE, stdin);
    } else if (prve != NULL) {
        fgets(prve->Next->Content, MAX_SIZE, stdin);
    }
    return true;
}
bool DeleteItem(PtrL List){
    if(IsEmpty(List)) {
        printf("List is empty. No items to delete.\n");
        return false; // List is empty
    }
    int id;
    printf("Enter the ID of the item to delete: ");
    scanf("%d", &id);
    Ptr prev = SearchPrveItemById(List, id);
    Ptr temp = NULL;
    if(List->Head->Id == id) {
        temp = List->Head;
        List->Head = List->Head->Next;
        if (List->Head == NULL) {
            List->Last = NULL; // List is now empty
        }
    } 
    else if(prev != NULL) {
        temp = prev->Next;
        prev->Next = temp->Next;
        if (temp == List->Last) {
            List->Last = prev; // Update last pointer if we deleted the last item
        }
    } 
    else {
        printf("Item with ID %d not found.\n", id);
        return false; // Item not found
    }
    free(temp);
    List->ListSize--;
    return true; // Item deleted successfully
}
bool Undo(PtrL List){


}
void DisplayItems(PtrL List){
    Ptr p = List->Head;
    while(p != NULL) {
        OutputItem(p);
        p = p->Next;
    }
}