#include<stdio.h>
#include"employee/employee.h"
#include"customer/customer.h"

    int main()
    {
        int choice;
        do{
            printf("\n==============================================");
            printf("\nSUPER MARKET MANAGEMENT SYSTEM");
            printf("\n==============================================");
            
            printf("\n1. Employee");
            printf("\n2. Customer");
            printf("\n3. Exit");

            printf("\n\nEnter your choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
                case 1:
                    printf("\nEmployee Section");
                    employeeSection();
                    break;
                case 2:
                    printf("\nCustomer Section");
                    customerSection();
                    break;
                case 3:
                    printf("\nExiting the program. Goodbye!");
                    break;
                default:
                    printf("\nInvalid choice. Please try again.");
            }
        } while(choice != 3);
        return 0;   
    }