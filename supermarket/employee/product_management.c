#include<stdio.h>
#include<string.h>
#include"product_management.h"

void productManagement()
{
    printf("\nWelcome to the Product Management Section!");
    int choice;
    do {
        printf("\n1. Add Product");
        printf("\n2. View Products");
        printf("\n3. Search Product");
        printf("\n4. Update Product");
        printf("\n5. Delete Product");
        printf("\n6. Back ");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewproducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                deleteProduct();
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);
    // You can add more functionality here as needed
}

struct Product products[MAX_PRODUCTS] =
{
    {101, "Rice White kekulu 1kg", "Grocery", 250.00, 50},
    {102, "White Sugar 1kg", "Grocery", 280.00, 40},
    {103, "Milk Powder", "Dairy", 1200.00, 25},
    {104, "Soap", "Personal Care", 180.00, 100},
    {105, "Shampoo", "Personal Care", 650.00, 30}
};

int count = 5;

void addProduct() {
    if(count >= MAX_PRODUCTS) {
        printf("\nProduct list is full!\n");
        return;
    }

    printf("\nEnter Product ID: ");
    scanf("%d", &products[count].id);

       for (int i = 0; i < count; i++) {
        if(products[i].id == products[count].id) {
            printf("\nProduct ID already exists! Please try again.\n");
            return;
        }
    }

    printf("Enter Product Name: ");
    scanf(" %99[^\n]", products[count].name);

    printf("Enter Product Category: ");
    scanf(" %49[^\n]", products[count].category);

    printf("Enter Product Price: ");
    scanf("%f", &products[count].price);

    printf("Enter Product Quantity: ");
    scanf("%d", &products[count].quantity);

    count++;
    printf("\nProduct added successfully!\n");
    }
void viewproducts(){

    int i;
    if(count == 0) {
        printf("\nNo products available!\n");
        return;
    }
    printf("\n--- Product List ---\n");
    for(i = 0; i < count; i++) {
        printf("\nProduct %d:\n", i + 1);
        
        printf("ID: %d\n", products[i].id);
        printf("Name: %s\n", products[i].name);
        printf("Category: %s\n", products[i].category);
        printf("Price: %.2f\n", products[i].price);
        printf("Quantity: %d\n", products[i].quantity);
    }

}
void searchProduct()
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter Product ID to Search: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++)
    {
        if(products[i].id == id)
        {
            printf("\nProduct Found!\n");

            printf("ID: %d\n", products[i].id);
            printf("Name: %s\n", products[i].name);
            printf("Category: %s\n", products[i].category);
            printf("Price: %.2f\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nProduct Not Found!\n");
    }
}
void updateProduct()
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter Product ID to Update: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++)
    {
        if(products[i].id == id)
        {
            printf("\nEnter New Name: ");
            scanf(" %99[^\n]", products[i].name);

            printf("Enter New Price: ");
            scanf("%f", &products[i].price);

            printf("Enter New Quantity: ");
            scanf("%d", &products[i].quantity);
                printf("\nProduct Updated Successfully!\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nProduct Not Found!\n");
    }
}    
void deleteProduct()
{
    int id;
    int i;
    int j;
    int found = 0;

    printf("\nEnter Product ID to Delete: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++)
    {
        if(products[i].id == id)
        {
            for(j = i; j < count - 1; j++)
            {
                products[j] = products[j + 1];
            }

            count--;

            printf("\nProduct Deleted Successfully!\n");
                     found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nProduct Not Found!\n");
    }
}
