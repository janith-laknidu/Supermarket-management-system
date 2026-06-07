#include <stdio.h>
#include <string.h>
#include "view_pricing.h"
#include "../employee/product_management.h"

#define MAX_PRODUCTS 100

/*sructure*/

struct PriceProduct
{
    int id;
    char name[100];
    float price;
};

extern struct Product products[MAX_PRODUCTS];
extern int count;

/* Copy Data from Product Structure */

void loadPriceProducts(struct PriceProduct priceProducts[])
{
    int i;

    for(i = 0; i < count; i++)
    {
        priceProducts[i].id = products[i].id;
        strcpy(priceProducts[i].name, products[i].name);
        priceProducts[i].price = products[i].price;
    }
}

/* Main Menu */

void viewPricesMenu()
{
    int choice;

    do
    {
        printf("\n=================================\n");
        printf("         VIEW PRICES MENU\n");
        printf("=================================\n");
        printf("1. View All Prices\n");
        printf("2. Highest Price Product\n");
        printf("3. Lowest Price Product\n");
        printf("4. Discount Prices (10%% Off)\n");
        printf("5. Sort Prices (Ascending)\n");
        printf("6. Back\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                viewAllPrices();
                break;

            case 2:
                highestPrice();
                break;

            case 3:
                lowestPrice();
                break;

            case 4:
                discountPrices();
                break;

            case 5:
                sortPrices();
                break;

            case 6:
                printf("\nReturning...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 6);
}

/* View All Prices */

void viewAllPrices()
{
    int i;
    struct PriceProduct priceProducts[MAX_PRODUCTS];

    if(count == 0)
    {
        printf("\nNo Products Available!\n");
        return;
    }

    loadPriceProducts(priceProducts);

    printf("\n=================================================\n");
    printf("                PRODUCT PRICES\n");
    printf("=================================================\n");

    printf("%-10s %-25s %-10s\n",
           "ID",
           "Product",
           "Price");

    for(i = 0; i < count; i++)
    {
        printf("%-10d %-25s %.2f\n",
               priceProducts[i].id,
               priceProducts[i].name,
               priceProducts[i].price);
    }
}

/* Highest Price Product */

void highestPrice()
{
    int i, maxIndex = 0;
    struct PriceProduct priceProducts[MAX_PRODUCTS];

    if(count == 0)
    {
        printf("\nNo Products Available!\n");
        return;
    }

    loadPriceProducts(priceProducts);

    for(i = 1; i < count; i++)
    {
        if(priceProducts[i].price >
           priceProducts[maxIndex].price)
        {
            maxIndex = i;
        }
    }

    printf("\n=================================\n");
    printf("      HIGHEST PRICE PRODUCT\n");
    printf("=================================\n");

    printf("ID    : %d\n", priceProducts[maxIndex].id);
    printf("Name  : %s\n", priceProducts[maxIndex].name);
    printf("Price : %.2f\n", priceProducts[maxIndex].price);
}

/* Lowest Price Product */

void lowestPrice()
{
    int i, minIndex = 0;
    struct PriceProduct priceProducts[MAX_PRODUCTS];

    if(count == 0)
    {
        printf("\nNo Products Available!\n");
        return;
    }

    loadPriceProducts(priceProducts);

    for(i = 1; i < count; i++)
    {
        if(priceProducts[i].price <
           priceProducts[minIndex].price)
        {
            minIndex = i;
        }
    }

    printf("\n=================================\n");
    printf("       LOWEST PRICE PRODUCT\n");
    printf("=================================\n");

    printf("ID    : %d\n", priceProducts[minIndex].id);
    printf("Name  : %s\n", priceProducts[minIndex].name);
    printf("Price : %.2f\n", priceProducts[minIndex].price);
}

/* Discount Prices */

void discountPrices()
{
    int i;
    float discountedPrice;
    struct PriceProduct priceProducts[MAX_PRODUCTS];

    if(count == 0)
    {
        printf("\nNo Products Available!\n");
        return;
    }

    loadPriceProducts(priceProducts);

    printf("\n============================================================\n");
    printf("                PRODUCTS WITH 10%% DISCOUNT\n");
    printf("============================================================\n");

    printf("%-10s %-25s %-15s %-15s\n",
           "ID",
           "Product",
           "Original",
           "Discounted");

    for(i = 0; i < count; i++)
    {
        discountedPrice =
            priceProducts[i].price -
            (priceProducts[i].price * 0.10f);

        printf("%-10d %-25s %-15.2f %-15.2f\n",
               priceProducts[i].id,
               priceProducts[i].name,
               priceProducts[i].price,
               discountedPrice);
    }
}

/* Sort Prices */

void sortPrices()
{
    int i, j;
    struct PriceProduct tempProducts[MAX_PRODUCTS];
    struct PriceProduct temp;

    if(count == 0)
    {
        printf("\nNo Products Available!\n");
        return;
    }

    loadPriceProducts(tempProducts);

    for(i = 0; i < count - 1; i++)
    {
        for(j = 0; j < count - i - 1; j++)
        {
            if(tempProducts[j].price >
               tempProducts[j + 1].price)
            {
                temp = tempProducts[j];
                tempProducts[j] = tempProducts[j + 1];
                tempProducts[j + 1] = temp;
            }
        }
    }

    printf("\n=================================================\n");
    printf("          PRODUCTS SORTED BY PRICE\n");
    printf("=================================================\n");

    printf("%-10s %-25s %-10s\n",
           "ID",
           "Product",
           "Price");

    for(i = 0; i < count; i++)
    {
        printf("%-10d %-25s %.2f\n",
               tempProducts[i].id,
               tempProducts[i].name,
               tempProducts[i].price);
    }
}
