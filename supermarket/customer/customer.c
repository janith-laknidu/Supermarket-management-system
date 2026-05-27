#include<stdio.h>
#include"customer.h"

void customerSection()
{
    int choice;
    do{
        printf("\n----------------------------------------------");
        printf("\nWELCOME TO THE CUSTOMER SECTION!");
        printf("\n----------------------------------------------");
        
        printf("\n1. View Products");
        printf("\n2. Search Products");
        printf("\n3. View prices");
        printf("\n4. Billing");
        printf("\n5. Return to Main Menu");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nViewing products...");
                void viewProducts();
                break;
            case 2:
                printf("\nSearching products...");
                void searchProducts();
                break;
            case 3:
                printf("\nViewing prices...");
                void viewPrices();
                break;
            case 4:
                printf("\nProcessing billing...");
                void processBilling();
                break;
            case 5:
                printf("\nReturning to main menu...");
                break;
            default:
                printf("\nInvalid choice. Please try again.");
        }
    } while(choice != 5);
    // You can add more functionality here as needed
}