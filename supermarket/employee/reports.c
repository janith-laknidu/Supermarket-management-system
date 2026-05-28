#include<stdio.h>
#include"reports.h"

struct Report {
    int totalProducts;
    int totalStock;
    float inventoryValue;
};


void reportsMenu()
{
    int choice;
    do {
        printf("\n");
        printf("\n======== REPORTS MENU ========\n\n");

        printf("1. Total Products Report\n");
        printf("2. Total Stock Report\n");
        printf("3. Inventory Value Report\n");
        printf("4. Low Stock Report\n");
        printf("5. Product Price Report\n");
        printf("6. Back to Employee Menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                totalProductsReport();
                break;
            case 2:
                totalStockReport();
                break;
            case 3:
                inventoryValueReport();
                break;
            case 4:
                lowStockReport();
                break;
            case 5:
                productPriceReport();
                break;
            case 6:
                printf("Returning to Employee Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

void totalProductsReport() {
    struct Report report;
    report.totalProducts = count;

    printf("\n====== Total Products Report ======\n");
    printf("\nTotal Products: %d\n", report.totalProducts);
}
void totalStockReport() {

    struct Report report;
    int i;
    report.totalStock = 0;

    for (i = 0; i < count; i++) {
        report.totalStock += products[i].quantity;
    }
    printf("\n====== Total Stock Report ======\n");
    printf("\nTotal Stock: %d\n", report.totalStock);
}
void inventoryValueReport() {
    struct Report report;
    int i;
    report.inventoryValue = 0.0;

    for (i = 0; i < count; i++) {
        report.inventoryValue += products[i].price * products[i].quantity;
    }
    printf("\n====== Inventory Value Report ======\n");
    printf("\nInventory Value: %.2f\n", report.inventoryValue);
}
void lowStockReport() {
    printf("\n====== LOW STOCK REPORT ======\n");
    printf("\nProducts with Low Stock (less than 5):\n");
    int i;
    int found = 0;
    for (i = 0; i < count; i++) {
        if (products[i].quantity < 5) {
            printf("\nID: %d\n", products[i].id);
            printf("Name: %s\n", products[i].name);
            printf("Quantity: %d\n", products[i].quantity);
            found = 1;
        }
    }
    if (found==0) {
        printf("\nNo products with low stock.\n");
    }
}
void productPriceReport() {

    printf("\n====== PRODUCT PRICE REPORT ======\n");

    printf("\nProduct Prices:\n");
    int i;
    for (i = 0; i < count; i++) {
        printf("\nName: %s\n", products[i].name);
        printf("Price: %.2f\n", products[i].price);
    }
}
