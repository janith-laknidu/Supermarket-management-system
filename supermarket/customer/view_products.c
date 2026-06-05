#include<stdio.h>
#include<ctype.h>
#include "../employee/product_management.h"
#include "view_products.h"

/*
 * Module: view_products.c
 * -----------------------
 * Provides a set of functions for displaying products to customers.
 * Most functions read from the `products` array and `count` defined
 * in `product_management.h`. The functions below include utility
 * helpers (case-insensitive string compare and pretty-printer) and
 * various view modes (all products, available only, by category,
 * newest items, and lookup by ID).
 */

/*
 * equalsIgnoreCase
 * -----------------
 * Perform a case-insensitive comparison of two NUL-terminated strings.
 * Uses `tolower` on unsigned char values to avoid undefined behavior
 * on platforms where `char` is signed. Returns 1 when strings are
 * equal (ignoring case), otherwise 0.
 */
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

/*
 * printProductDetails
 * -------------------
 * Nicely prints all fields of a single `struct Product` to stdout.
 * This centralizes display logic so other view functions can reuse it
 * and ensures a consistent product representation across the UI.
 */
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

/*
    * Menu loop: prompt the user for a choice, then dispatch using
    * a switch statement. Uses `scanf` to read an integer choice.
    * The loop continues until the user selects the "Back" option.
    */
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

/*
 * viewAllProducts
 * ----------------
 * Iterates over every product in the global `products` array and
 * prints details using `printProductDetails`. Checks `count` first
 * to avoid iterating an empty list.
 */
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

/*
 * viewAvailableProducts
 * ---------------------
 * Filters products by `quantity > 0` to show only in-stock items.
 * Uses a `found` flag to detect when no matching products were found
 * and informs the user accordingly.
 */
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

/*
 * viewCategoryProducts
 * --------------------
 * Allows customers to view products that belong to a specific
 * category. Uses `equalsIgnoreCase` to compare categories without
 * considering letter case differences.
 */
void viewCategoryProducts()
{
    char category[50];
    int i;
    int found = 0;

    if(count == 0) {
        printf("\nNo products available!\n");
        return;
    }

    /*
     * Read a category string (up to 49 chars) and print all products
     * whose `category` matches case-insensitively. `scanf(" %49[^\n]")`
     * prevents buffer overflow by limiting the number of characters read.
     */
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

/*
 * viewNewProducts
 * ----------------
 * Shows the most recent up to 5 products added to the list by
 * starting from `count - 5` (or 0 if there are fewer than 5).
 */
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

/*
 * viewProductDetails
 * ------------------
 * Prompts the user for a numeric product ID and performs a linear
 * search through the `products` array to find a product with the
 * matching `id`. If found, prints the product; otherwise informs
 * the user that the product was not found.
 */
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
