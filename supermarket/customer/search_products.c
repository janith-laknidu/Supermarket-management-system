#include <stdio.h>
#include <string.h>
#include "search_products.h"
#include "../employee/product_management.h"

// GLOBAL ARRAY
extern struct Product products[MAX_PRODUCTS];
extern int count;

void searchByID();
void searchByName();
void searchByCategory();
void searchByPrice();
void searchAvailableProducts();

void searchProducts()
{
    int choice;

    do
    {
        printf("\n=================================");
        printf("\n       SEARCH PRODUCTS");
        printf("\n=================================");

        printf("\n1. Search By ID");
        printf("\n2. Search By Name");
        printf("\n3. Search By Category");
        printf("\n4. Search By Price");
        printf("\n5. Search Available Products");
        printf("\n0. Back");

        printf("\n\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                searchByID();
                break;

            case 2:
                searchByName();
                break;

            case 3:
                searchByCategory();
                break;

            case 4:
                searchByPrice();
                break;

            case 5:
                searchAvailableProducts();
                break;

            case 0:
                printf("\nReturning...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(choice != 0);
}

void searchByID()
{
    int id;
    int found = 0;

    printf("\nEnter Product ID: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(products[i].id == id)
        {
            printf("\nProduct Found\n");
            printf("ID: %d\n", products[i].id);
            printf("Name: %s\n", products[i].name);
            printf("Category: %s\n", products[i].category);
            printf("Price: %.2f\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);

            found = 1;
        }
    }

    if(!found)
    {
        printf("\nProduct not found!\n");
    }
}

void searchByName()
{
    char name[50];
    int found = 0;

    printf("\nEnter Product Name: ");
    scanf("%s", name);

    for(int i = 0; i < count; i++)
    {
        if(strcmp(products[i].name, name) == 0)
        {
            printf("\nProduct Found\n");
            printf("ID: %d\n", products[i].id);
            printf("Name: %s\n", products[i].name);
            printf("Category: %s\n", products[i].category);
            printf("Price: %.2f\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);

            found = 1;
        }
    }

    if(!found)
    {
        printf("\nProduct not found!\n");
    }
}

void searchByCategory()
{
    char category[50];
    int found = 0;

    printf("\nEnter Category: ");
    scanf("%s", category);

    for(int i = 0; i < count; i++)
    {
        if(strcmp(products[i].category, category) == 0)
        {
            printf("\nID: %d", products[i].id);
            printf("\nName: %s", products[i].name);
            printf("\nPrice: %.2f", products[i].price);
            printf("\nQuantity: %d\n", products[i].quantity);

            found = 1;
        }
    }

    if(!found)
    {
        printf("\nNo products found!\n");
    }
}

void searchByPrice()
{
    float price;
    int found = 0;

    printf("\nEnter Price: ");
    scanf("%f", &price);

    for(int i = 0; i < count; i++)
    {
        if(products[i].price == price)
        {
            printf("\nID: %d", products[i].id);
            printf("\nName: %s", products[i].name);
            printf("\nCategory: %s", products[i].category);
            printf("\nQuantity: %d\n", products[i].quantity);

            found = 1;
        }
    }

    if(!found)
    {
        printf("\nNo products found!\n");
    }
}

void searchAvailableProducts()
{
    int found = 0;

    printf("\nAvailable Products\n");

    for(int i = 0; i < count; i++)
    {
        if(products[i].quantity > 0)
        {
            printf("\nID: %d", products[i].id);
            printf("\nName: %s", products[i].name);
            printf("\nCategory: %s", products[i].category);
            printf("\nPrice: %.2f", products[i].price);
            printf("\nQuantity: %d\n", products[i].quantity);

            found = 1;
        }
    }

    if(!found)
    {
        printf("\nNo available products!\n");
    }
}
