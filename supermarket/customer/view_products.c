#include<stdio.h>
#include<ctype.h>
#include"view_products.h"

static int equalsIgnoreCase(const char *left, const char *right)
{
    while(*left != '\0' && *right != '\0') {
        if(tolower((unsigned char)*left) != tolower((unsigned char)*right)) {
            return 0;
        }
        left++;
        right++;
    }

    return *left == '\0' && *right == '\0';
}

static void printProductDetails(const struct Product *product)
{
    printf("\nID: %d\n", product->id);
    printf("Name: %s\n", product->name);
    printf("Category: %s\n", product->category);
    printf("Price: %.2f\n", product->price);
    printf("Quantity: %d\n", product->quantity);
    printf("Status: %s\n", product->quantity > 0 ? "Available" : "Out of Stock");
}

void viewProducts()
{
    int choice;

    do {
        printf("\n----------------------------------------------");
        printf("\nVIEW PRODUCTS");
        printf("\n----------------------------------------------");
        printf("\n1. View All Products");
        printf("\n2. View Available Products");
        printf("\n3. View Category Products");
        printf("\n4. View New Products");
        printf("\n5. View Product Details");
        printf("\n6. Back");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                viewAllProducts();
                break;
            case 2:
                viewAvailableProducts();
                break;
            case 3:
                viewCategoryProducts();
                break;
            case 4:
                viewNewProducts();
                break;
            case 5:
                viewProductDetails();
                break;
            case 6:
                printf("\nReturning to customer menu...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while(choice != 6);
}

void viewAllProducts()
{
    int i;

    if(count == 0) {
        printf("\nNo products available!\n");
        return;
    }

    printf("\n--- All Products ---\n");
    for(i = 0; i < count; i++) {
        printf("\nProduct %d:\n", i + 1);
        printProductDetails(&products[i]);
    }
}

void viewAvailableProducts()
{
    int i;
    int found = 0;

    if(count == 0) {
        printf("\nNo products available!\n");
        return;
    }

    printf("\n--- Available Products ---\n");
    for(i = 0; i < count; i++) {
        if(products[i].quantity > 0) {
            printf("\nProduct %d:\n", i + 1);
            printProductDetails(&products[i]);
            found = 1;
        }
    }

    if(found == 0) {
        printf("\nNo available products found!\n");
    }
}

void viewCategoryProducts()
{
    char category[50];
    int i;
    int found = 0;

    if(count == 0) {
        printf("\nNo products available!\n");
        return;
    }

    printf("\nEnter category to view: ");
    scanf(" %49[^\n]", category);

    printf("\n--- Products in Category: %s ---\n", category);
    for(i = 0; i < count; i++) {
        if(equalsIgnoreCase(products[i].category, category)) {
            printf("\nProduct %d:\n", i + 1);
            printProductDetails(&products[i]);
            found = 1;
        }
    }

    if(found == 0) {
        printf("\nNo products found in this category!\n");
    }
}

void viewNewProducts()
{
    int i;
    int startIndex;

    if(count == 0) {
        printf("\nNo products available!\n");
        return;
    }

    startIndex = count > 5 ? count - 5 : 0;

    printf("\n--- New Products ---\n");
    for(i = startIndex; i < count; i++) {
        printf("\nProduct %d:\n", i + 1);
        printProductDetails(&products[i]);
    }
}

void viewProductDetails()
{
    int id;
    int i;
    int found = 0;

    if(count == 0) {
        printf("\nNo products available!\n");
        return;
    }

    printf("\nEnter Product ID to view details: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(products[i].id == id) {
            printf("\n--- Product Details ---\n");
            printProductDetails(&products[i]);
            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("\nProduct not found!\n");
    }
}