#include <stdio.h>
#include <string.h>
#include "../employee/product_management.h"
#include "billing.h"

#define MAX_BILL_ITEMS 100

struct BillItem
{
    int productId;
    char name[100];
    float price;
    int quantity;
};

struct BillItem bill[MAX_BILL_ITEMS];
int billCount = 0;

void billingMenu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("            BILLING MENU\n");
        printf("========================================\n");
        printf("1. Add Item To Bill\n");
        printf("2. View Bill\n");
        printf("3. Calculate Total\n");
        printf("4. Print Receipt\n");
        printf("5. Clear Bill\n");
        printf("6. Back\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addItemToBill();
                break;

            case 2:
                viewBill();
                break;

            case 3:
                printf("Total = %.2f\n", calculateTotal());
                break;

            case 4:
                printReceipt();
                break;

            case 5:
                clearBill();
                break;

            case 6:
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);
}


void addItemToBill()
{
    int id, qty;
    int found = 0;

    printf("Enter Product ID: ");
    scanf("%d", &id);

    printf("Enter Quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i < count; i++)
    {
        if (products[i].id == id)
        {
            found = 1;

            bill[billCount].productId = products[i].id;
            strcpy(bill[billCount].name, products[i].name);
            bill[billCount].price = products[i].price;
            bill[billCount].quantity = qty;

            billCount++;

            printf("Item added to bill successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("Product not found!\n");
    }
}

void viewBill()
{
    if (billCount == 0)
    {
        printf("Bill is empty!\n");
        return;
    }

    printf("\n========================================\n");
    printf("              CURRENT BILL\n");
    printf("========================================\n");

    for (int i = 0; i < billCount; i++)
    {
        printf("%d | %s | %.2f | Qty:%d\n",
               bill[i].productId,
               bill[i].name,
               bill[i].price,
               bill[i].quantity);
    }
}

float calculateTotal()
{
    float total = 0;

    for (int i = 0; i < billCount; i++)
    {
        total += bill[i].price * bill[i].quantity;
    }

    return total;
}

void printReceipt()
{
    float total = calculateTotal();

    printf("\n========================================\n");
    printf("             RECEIPT\n");
    printf("========================================\n");

    for (int i = 0; i < billCount; i++)
    {
        printf("%-15s x%d = %.2f\n",
               bill[i].name,
               bill[i].quantity,
               bill[i].price * bill[i].quantity);
    }

    printf("----------------------------------------\n");
    printf("TOTAL = %.2f\n", total);
    printf("========================================\n");
}

void clearBill()
{
    billCount = 0;
    printf("Bill cleared successfully!\n");
}
