#ifndef PRODUCT_MANAGEMENT_H
#define PRODUCT_MANAGEMENT_H

#define MAX_PRODUCTS 100

struct Product {
    int id;
    char name[100];
    float price;
    int quantity;
};

extern struct Product products[MAX_PRODUCTS];
extern int count;

void productManagement();

void addProduct();
void viewproducts();
void searchProduct();
void updateProduct();
void deleteProduct();

#endif // PRODUCT_MANAGEMENT_H


