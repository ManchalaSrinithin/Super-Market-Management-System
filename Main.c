#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold credentials
struct Credentials {
    char username[20];
    char password[20];
    char email[50];
};

// Define a structure for store products
typedef struct store {
    int id;
    char name[30], category[30];
    int price, qty;
    struct store *link, *link1;
} node;

// Global variables
node *header = NULL;
node *header1 = NULL;
struct Credentials cred;

// Function prototypes
node *get_node();
node* search_node(int id);
void delay(int k);
void loading();
void swap(node *p1, node *p2);
void sort_id(node *header);
void sort_price(node *header);
void sort_qty(node *header);
void insert();
void add_cart(int id, int qty);
void display_cart();
void del();
void displaycat();
void update();
void display();
void bill();
void load_credentials(struct Credentials* cred);
void save_credentials(struct Credentials* cred);
void forgot_password(struct Credentials* cred);
int authenticate(struct Credentials* cred);

// Delay function for loading animation
void delay(int k) {
    int i = 0, j;
    for(i = 0; i < k; ++i) {
        for(j = 0; j < k; ++j) {}
    }
}

// Loading animation function
void loading() {
    int i;
    for(i = 0; i <= 1; ++i) {
        delay(1000);
        printf(".");
        fflush(stdout); // Ensure the dot appears immediately
    }
}

// Swap function for sorting
void swap(node *p1, node *p2) {
    int temp_id, temp_price, temp_qty;
    char temp_cat[30], temp_name[30];

    temp_id = p1->id;
    p1->id = p2->id;
    p2->id = temp_id;

    temp_price = p1->price;
    p1->price = p2->price;
    p2->price = temp_price;

    temp_qty = p1->qty;
    p1->qty = p2->qty;
    p2->qty = temp_qty;

    strcpy(temp_name, p1->name);
    strcpy(p1->name, p2->name);
    strcpy(p2->name, temp_name);

    strcpy(temp_cat, p1->category);
    strcpy(p1->category, p2->category);
    strcpy(p2->category, temp_cat);
}

// Get a new node
node *get_node() {
    return (node*)malloc(sizeof(node));
}

// Load credentials from file
void load_credentials(struct Credentials* cred) {
    FILE *fp = fopen("credentials.txt", "r");
    if(fp == NULL) {
        perror("Unable to open file");
        exit(1);
    }
    fscanf(fp, "%s", cred->username);
    fscanf(fp, "%s", cred->password);
    fscanf(fp, "%s", cred->email);
    fclose(fp);
}

// Save credentials to file
void save_credentials(struct Credentials* cred) {
    FILE *fp = fopen("credentials.txt", "w");
    if(fp == NULL) {
        perror("Unable to open file");
        exit(1);
    }
    fprintf(fp, "%s\n%s\n%s\n", cred->username, cred->password, cred->email);
    fclose(fp);
}

// Handle forgot password
void forgot_password(struct Credentials* cred) {
    printf("Enter new username: ");
    scanf("%s", cred->username);
    printf("Enter new password: ");
    scanf("%s", cred->password);
    printf("Enter new email: ");
    scanf("%s", cred->email);
    save_credentials(cred);
    printf("Credentials updated successfully\n");
}

// Authenticate user
int authenticate(struct Credentials* cred) {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    if(strcmp(username, cred->username) == 0 && strcmp(password, cred->password) == 0) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

// Insert product into the list
void insert() {
    int id;
    char name[30], category[30];
    int price, qty;
    node *p, *temp;

    printf("\t\t\t\t:Add Products:");
    printf("\n\n\nEnter ID:");
    scanf("%d", &id);
    for(temp = header; temp != NULL; temp = temp->link) {
        if(temp->id == id) {
            printf("\n\n ID Exists. Try Again.");
            return;
        }
    }
    printf("\nEnter product name:");
    scanf("%s", name);
    printf("\nEnter category:");
    scanf("%s", category);
    printf("\nEnter price:");
    scanf("%d", &price);
    printf("\nEnter quantity:");
    scanf("%d", &qty);

    p = get_node();
    p->id = id;
    p->price = price;
    p->qty = qty;
    strcpy(p->name, name);
    strcpy(p->category, category);
    p->link = NULL;

    if(header == NULL)
        header = p;
    else {
        p->link = header;
        header = p;
    }
    printf("\n\n Product added");
    loading();
}

// Add product to the cart
void add_cart(int id, int qty) {
    node *temp;
    int k = 0;
    for(temp = header; temp != NULL; temp = temp->link) {
        if(id == temp->id) {
            k = 1;
            break;
        }
    }
    if(k == 1) {
        k = 0;
        node *p;
        if(temp->qty == 0)
            printf("\n\n\tProduct Not In stock");
        else {
            temp->qty = temp->qty - qty;
            if(temp->qty < 0) {
                temp->qty = temp->qty + qty;
                printf("\n\n\tChoose fewer items (limited stock)");
                while((temp->qty - qty) < 0) {
                    printf("\n\n\tEnter quantity:");
                    scanf("%d", &qty);
                    temp->qty = temp->qty - qty;
                }
            }
            p = get_node();
            p->id = temp->id;
            p->price = temp->price;
            p->qty = qty;
            strcpy(p->name, temp->name);
            strcpy(p->category, temp->category);
            p->link = NULL;
            if(header1 == NULL)
                header1 = p;
            else {
                p->link1 = header1;
                header1 = p;
            }
            printf("\n\n Product added");
            loading();
        }
    } else {
        printf("\n\n ID not Found. Check Again.");
    }
}

// Display products in the cart
void display_cart() {
    node *temp;
    int total = 0;
    for(temp = header1; temp != NULL; temp = temp->link1) {
        printf("\n\n\tID:%d", temp->id);
        printf("\n\tProduct name:%s", temp->name);
        printf("\n\tCategory:%s", temp->category);
        printf("\n\tPrice:%d", temp->price);
        printf("\n\tQuantity:%d\n\n", temp->qty);
        total += (temp->price) * (temp->qty);
    }
    printf("\n\n\t TOTAL = %d", total);
    printf("\n\n\t Press enter to continue");
    getchar(); // Wait for user input
    getchar(); // To consume the newline character
}

// Delete a product from the list
void del() {
    if(header == NULL) {
        printf("Empty List\n");
        return;
    } else {
        int id;
        printf("Enter ID of product:\n");
        scanf("%d", &id);
        node* curr = header;
        while(curr != NULL) {
            if(curr->id == id) {
                break;
            }
            curr = curr->link;
        }
        if(curr == NULL) {
            printf("There is no such product. Please enter valid choice.\n");
        } else {
            if(curr == header) {
                node *temp = header->link;
                printf("Deleted product is:\n");
                printf("ID:%d", curr->id);
                printf("\nProduct name:%s", curr->name);
                printf("\nCategory:%s", curr->category);
                printf("\nPrice:%d", curr->price);
                printf("\nQuantity:%d", curr->qty);
                free(curr);
                header = temp;
            } else {
                node *temp = header;
                while(temp->link != curr) {
                    temp = temp->link;
                }
                temp->link = curr->link;
                printf("Deleted product is:\n");
                printf("ID:%d", curr->id);
                printf("\nProduct name:%s", curr->name);
                printf("\nCategory:%s", curr->category);
                printf("\nPrice:%d", curr->price);
                printf("\nQuantity:%d", curr->qty);
                free(curr);
            }
        }
    }
    printf("\n\n Press enter to continue");
    getchar(); // Wait for user input
    getchar(); // To consume the newline character
}

// Display product categories
void displaycat() {
    node *temp;
    char unique_categories[30][30];
    int k = 0;
    for(temp = header; temp != NULL; temp = temp->link) {
        int flag = 0;
        for(int i = 0; i < k; i++) {
            if(strcmp(unique_categories[i], temp->category) == 0) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            strcpy(unique_categories[k], temp->category);
            k++;
        }
    }
    printf("\nCategories:\n");
    for(int i = 0; i < k; i++) {
        printf("%d. %s\n", i + 1, unique_categories[i]);
    }
    printf("\nSelect a category number to view products:\n");
    int cat;
    scanf("%d", &cat);
    if(cat <= 0 || cat > k) {
        printf("\nInvalid Category Number.");
        return;
    }
    char selected_category[30];
    strcpy(selected_category, unique_categories[cat - 1]);
    printf("\nSelected Category: %s", selected_category);
    printf("\n\nProducts in the selected category:\n");
    for(temp = header; temp != NULL; temp = temp->link) {
        if(strcmp(temp->category, selected_category) == 0) {
            printf("\n\n\tID:%d", temp->id);
            printf("\n\tProduct name:%s", temp->name);
            printf("\n\tCategory:%s", temp->category);
            printf("\n\tPrice:%d", temp->price);
            printf("\n\tQuantity:%d\n\n", temp->qty);
        }
    }
    printf("\n\n Press enter to continue");
    getchar(); // Wait for user input
    getchar(); // To consume the newline character
}

// Update product information
void update() {
    if(header == NULL) {
        printf("Empty List\n");
        return;
    } else {
        int id;
        printf("Enter ID to update:\n");
        scanf("%d", &id);
        node* curr = header;
        while(curr != NULL) {
            if(curr->id == id) {
                break;
            }
            curr = curr->link;
        }
        if(curr == NULL) {
            printf("There is no such product. Please enter valid choice.\n");
        } else {
            int choice;
            printf("Choose:\n1. Update name\n2. Update category\n3. Update price\n4. Update quantity\n");
            scanf("%d", &choice);
            switch(choice) {
                case 1:
                    printf("Enter new name:\n");
                    scanf("%s", curr->name);
                    break;
                case 2:
                    printf("Enter new category:\n");
                    scanf("%s", curr->category);
                    break;
                case 3:
                    printf("Enter new price:\n");
                    scanf("%d", &curr->price);
                    break;
                case 4:
                    printf("Enter new quantity:\n");
                    scanf("%d", &curr->qty);
                    break;
                default:
                    printf("Invalid choice\n");
            }
        }
    }
    printf("\n\n Press enter to continue");
    getchar(); // Wait for user input
    getchar(); // To consume the newline character
}

// Display all products
void display() {
    node *temp;
    if(header == NULL) {
        printf("No products available\n");
        return;
    }
    for(temp = header; temp != NULL; temp = temp->link) {
        printf("\n\n\tID:%d", temp->id);
        printf("\n\tProduct name:%s", temp->name);
        printf("\n\tCategory:%s", temp->category);
        printf("\n\tPrice:%d", temp->price);
        printf("\n\tQuantity:%d\n\n", temp->qty);
    }
    printf("\n\n Press enter to continue");
    getchar(); // Wait for user input
    getchar(); // To consume the newline character
}

// Generate bill and display
void bill() {
    int total = 0;
    node *temp;
    for(temp = header1; temp != NULL; temp = temp->link1) {
        printf("\n\n\tID:%d", temp->id);
        printf("\n\tProduct name:%s", temp->name);
        printf("\n\tCategory:%s", temp->category);
        printf("\n\tPrice:%d", temp->price);
        printf("\n\tQuantity:%d\n\n", temp->qty);
        total += (temp->price) * (temp->qty);
    }
    printf("\n\n\t TOTAL = %d", total);
    printf("\n\n\t Press enter to continue");
    getchar(); // Wait for user input
    getchar(); // To consume the newline character
}

// Main function
int main() {
    // Load credentials
    load_credentials(&cred);

    // Authenticate user
    if (!authenticate(&cred)) {
        printf("Invalid credentials. Exiting.\n");
        return 0;
    }

    // Main menu
    while(1) {
        system("cls");
        int choice;
        printf("1. Insert Product\n");
        printf("2. Display Product\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Add to Cart\n");
        printf("6. Display Cart\n");
        printf("7. Generate Bill\n");
        printf("8. Display Categories\n");
        printf("9. Forgot Password\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                insert();
                break;
            case 2: 
                display();
                break;
            case 3: 
                update();
                break;
            case 4: 
                del();
                break;
            case 5: 
                {
                    int id, qty;
                    printf("Enter product ID: ");
                    scanf("%d", &id);
                    printf("Enter quantity: ");
                    scanf("%d", &qty);
                    add_cart(id, qty);
                }
                break;
            case 6: 
                display_cart();
                break;
            case 7: 
                bill();
                break;
            case 8: 
                displaycat();
                break;
            case 9:
                forgot_password(&cred);
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
