#include<stdio.h>
#include<string.h>
#include"employee.h"
#include"product_management.h"
#include"stock_management.h"
#include"reports.h"

#define EMPLOYEE_PASSWORD "1234"

static int verifyEmployeePassword()
{
    char enteredPassword[32];
    int attempts;

    for(attempts = 0; attempts < 3; attempts++) {
        printf("\nEnter employee password: ");
        scanf(" %31s", enteredPassword);

        if(strcmp(enteredPassword, EMPLOYEE_PASSWORD) == 0) {
            return 1;
        }

        printf("Incorrect password. ");
        if(attempts < 2) {
            printf("Please try again.\n");
        }
    }

    printf("\nAccess denied. Returning to main menu...\n");
    return 0;
}

void employeeSection()
{
    int choice;

    if(verifyEmployeePassword() == 0) {
        return;
    }

    do{
        printf("\n==============================================");
        printf("\nWELCOME TO THE EMPLOYEE SECTION!");
        printf("\n==============================================");
        
        printf("\n1. Product Management");
        printf("\n2. Stock Management");
        printf("\n3. Reports");
        printf("\n4. Return to Main Menu");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nThis is the product management section...");
                productManagement();
                break;
            case 2:
                printf("\nThis is the stock management section...");
                stockManagement();
                break;
            case 3:
                printf("\nThis is the reports section...");
                reportsMenu();
                break;
            case 4:
                printf("\nReturning to the main menu...");
                break;
            default:
                printf("\nInvalid choice. Please try again.");
        }
    } while(choice != 4);
    
}
