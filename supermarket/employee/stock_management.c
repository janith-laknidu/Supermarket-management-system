#include<stdio.h>
#include"stock_management.h"

void stockManagement()
{
    int choice;

    ensureProductCatalog();
    
    do {
        printf("\n");
        printf("\n======= STOCK MANAGEMENT =======\n");

        printf("1. Add Stock\n");
        printf("2. View Stock\n");
        printf("3. Update Stock\n");
        printf("4. Low Stock Alert\n");
        printf("5. Remove Damaged Stock\n");
        printf("6. Back to Employee Menu\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStock();
                break;
            case 2:
                viewStock();
                break;
            case 3:
                updateStock();
                break;
            case 4:
                lowStockAlert();
                break;
            case 5:
                removeDamagedStock();
                break;
            case 6:
                printf("Returning to Employee Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);
}

void addStock() {
    int id;
    int amount;
    int i;
    int found = 0;

    ensureProductCatalog();

    printf("Enter Product ID to add stock: ");
    scanf("%d", &id);

    for(i=0;i<count;i++) {
        if(products[i].id == id) {
            printf("Current Quantity: %d\n", products[i].quantity);

            printf("Enter amount to add: ");
            scanf("%d", &amount);

            products[i].quantity += amount;

            printf("Stock updated successfully! \n");
            printf("New Quantity: %d\n", products[i].quantity);
            printProductsTable(0);
            found = 1;
            break;
        }
    }

    if(found==0) {
        printf("\nProduct not Found!\n");
    }
}
void viewStock() {
    ensureProductCatalog();

    printf("\n======= STOCK DETAILS =======\n");
    printProductsTable(0);
    
}
void updateStock() {
    int id;
    int newQty;
    int i;
    int found = 0;

    ensureProductCatalog();

    printf("Enter Product ID to update stock: ");
    scanf("%d", &id);

    for(i=0;i<count;i++) {
        if(products[i].id == id) {
            printf("Current Quantity: %d\n", products[i].quantity);

            printf("Enter new quantity: ");
            scanf("%d", &newQty);

            products[i].quantity = newQty;

            printf("Stock updated successfully! \n");
            printf("New Quantity: %d\n", products[i].quantity);
            printProductsTable(0);
            found = 1;
            break;
        }
    }

    if(found==0) {
        printf("\nProduct not Found!\n");
    }
}   
void lowStockAlert() {
    int i;
    int found = 0;

    ensureProductCatalog();

    printf("\n======= LOW STOCK ALERT =======\n");

    for(i=0;i<count;i++) {
        if(products[i].quantity < 5) { 

            printf("\nProduct ID: %d\n", products[i].id);
            printf("Name: %s\n", products[i].name);
            printf("Quantity: %d\n", products[i].quantity);

            found = 1;
        }
    }

    if(found == 0) {
        printf("\nAll products are sufficiently stocked.\n");
    }
}
void removeDamagedStock() {
    int id;
    int damagedQty;
    int i;
    int found = 0;

    ensureProductCatalog();

    printf("Enter Product ID to remove damaged stock: ");
    scanf("%d", &id);

    for(i=0;i<count;i++) {
        if(products[i].id == id) {
            printf("Current Quantity: %d\n", products[i].quantity);

            printf("Enter amount to remove: ");
            scanf("%d", &damagedQty);

            if(damagedQty > products[i].quantity) {
                printf("Cannot remove more than current stock! \n");
                return;
            }

            products[i].quantity -= damagedQty;

            printf("Damaged stock removed successfully! \n");
            printf("Remaining Quantity: %d\n", products[i].quantity);
            printProductsTable(0);
            found = 1;
            break;
        }
    }

    if(found==0) {
        printf("\nProduct not Found!\n");
    }
}
