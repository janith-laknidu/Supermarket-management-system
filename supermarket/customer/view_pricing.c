#include <stdio.h>
#include <string.h>
#include "view_pricing.h"
#include "../employee/product_management.h"

void viewPricesMenu();

void viewPrices() {
    viewPricesMenu();
}

void viewAllPrices();
void highestPrice();
void lowestPrice();
void discountPrices();
void sortPrices();
void viewPricesMenu();

void viewPricesMenu()
{
    int choice;

    do
    {
        printf("\n");
        printf("         VIEW PRICES MENU\n");
        printf("\n");
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

void viewAllPrices()
{
    int i;

    printf("\n");
    printf("               PRODUCT PRICES\n");
    printf("\n");

    if(count == 0)
    {
        printf("No Products Available!\n");
        return;
    }

    printf("%-10s %-20s %-10s\n",
           "ID",
           "Product",
           "Price");

    for(i = 0; i < count; i++)
    {
        printf("%-10d %-20s %.2f\n",
               products[i].id,
               products[i].name,
               products[i].price);
    }
}

void highestPrice()
{
    int i, maxIndex = 0;

    if(count == 0)
    {
        printf("No Products Available!\n");
        return;
    }

    for(i = 1; i < count; i++)
    {
        if(products[i].price > products[maxIndex].price)
        {
            maxIndex = i;
        }
    }

    printf("\n");
    printf("      HIGHEST PRICE PRODUCT\n");
    printf("\n");

        printf("ID      : %d\n",
            products[maxIndex].id);

    printf("Name    : %s\n",
           products[maxIndex].name);

    printf("Price   : %.2f\n",
           products[maxIndex].price);
}

void lowestPrice()
{
    int i, minIndex = 0;

    if(count == 0)
    {
        printf("No Products Available!\n");
        return;
    }

    for(i = 1; i < count; i++)
    {
        if(products[i].price < products[minIndex].price)
        {
            minIndex = i;
        }
    }

    printf("\n");
    printf("       LOWEST PRICE PRODUCT\n");
    printf("\n");

        printf("ID      : %d\n",
            products[minIndex].id);

    printf("Name    : %s\n",
           products[minIndex].name);

    printf("Price   : %.2f\n",
           products[minIndex].price);
}

void discountPrices()
{
    int i;
    float discountedPrice;

    if(count == 0)
    {
        printf("No Products Available!\n");
        return;
    }

    printf("\n");
    printf("              PRODUCTS WITH 10%% DISCOUNT\n");
    printf("\n");

    printf("%-10s %-20s %-15s %-15s\n",
           "ID",
           "Product",
           "Original",
           "Discounted");

    for(i = 0; i < count; i++)
    {
        discountedPrice =
            products[i].price -
            (products[i].price * 0.10);

        printf("%-10d %-20s %-15.2f %-15.2f\n",
               products[i].id,
               products[i].name,
               products[i].price,
               discountedPrice);
    }
}


void sortPrices()
{
    int i, j;

    struct Product tempProducts[MAX_PRODUCTS];
    struct Product temp;

    if(count == 0)
    {
        printf("No Products Available!\n");
        return;
    }

    for(i = 0; i < count; i++)
    {
        tempProducts[i] = products[i];
    }

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

    printf("\n");
    printf("         PRODUCTS SORTED BY PRICE\n");
    printf("\n");

    printf("%-10s %-20s %-10s\n",
           "ID",
           "Product",
           "Price");

    for(i = 0; i < count; i++)
    {
        printf("%-10d %-20s %.2f\n",
               tempProducts[i].id,
               tempProducts[i].name,
               tempProducts[i].price);
    }
}
