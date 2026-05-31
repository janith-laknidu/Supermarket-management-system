#include <stdio.h>
#include <string.h>
#include "billing.h"
#include "../employee/product_management.h"

#define NAME_LEN 50
#define MAX_CART 50

/* keep `Product` typedef name for compatibility */
typedef struct Product Product;

/* ── CartItem Structure ── */
typedef struct {
    int productId;
    char productName[NAME_LEN];
    float unitPrice;
    int qty;
    float subtotal;
} CartItem;

/* products[] and count are defined in product_management.c */

/* ── Bill state ── */
static CartItem bill[MAX_CART];
static int      billSize  = 0;
static float    billTotal = 0.0f;

/* ── Helper: find product index ── */
static int findById(int id) {
    for (int i = 0; i < count; i++) {
        if (products[i].id == id) return i;
    }
    return -1;
}

/* ── 1. addItemToBill() ── */
void addItemToBill() {
    ensureProductCatalog();

    if (billSize >= MAX_CART) {
        printf("\n  [!] Bill is full. Please complete checkout first.\n");
        return;
    }

    printf("\n  ------------------------------------------------------\n");
    printf("    AVAILABLE PRODUCTS\n");
    printf("  ------------------------------------------------------\n");
    printf("  %-6s  %-24s  %-14s  %s\n", "ID", "Name", "Category", "Price(Rs)");
    printf("  ------------------------------------------------------\n");

    int availableCount = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].quantity > 0) {
            printf("  %-6d  %-24s  %-14s  %.2f\n",
                   products[i].id,
                   products[i].name,
                   products[i].category,
                   products[i].price);
            availableCount++;
        }
    }
    if (availableCount == 0) {
        printf("  [!] No products available in stock right now.\n");
    }
    printf("  ------------------------------------------------------\n");

    printf("\n  Enter Product ID to add  : ");
    int id;
    if (scanf("%d", &id) != 1) {
        printf("  [!] Invalid input.\n");
        while(getchar() != '\n');
        return;
    }

    int idx = findById(id);
    if (idx == -1) {
        printf("  [!] Product not found. Please check the ID.\n");
        return;
    }
    if (products[idx].quantity == 0) {
        printf("  [!] Sorry, '%s' is currently out of stock.\n", products[idx].name);
        return;
    }

    printf("  Enter Quantity           : ");
    int qty;
    if (scanf("%d", &qty) != 1) {
        printf("  [!] Invalid input.\n");
        while(getchar() != '\n');
        return;
    }

    if (qty <= 0) {
        printf("  [!] Quantity must be greater than zero.\n");
        return;
    }
    if (qty > products[idx].quantity) {
        printf("  [!] Not enough stock. Available: %d\n", products[idx].quantity);
        return;
    }

    for (int i = 0; i < billSize; i++) {
        if (bill[i].productId == id) {
            int newQty = bill[i].qty + qty;
            if (newQty > products[idx].quantity) {
                printf("  [!] Total quantity would exceed stock (%d available).\n", products[idx].quantity);
                return;
            }
            bill[i].qty      = newQty;
            bill[i].subtotal = bill[i].unitPrice * newQty;
            products[idx].quantity -= qty;
            printf("\n  [OK] Updated '%s' quantity to %d in bill.\n", bill[i].productName, newQty);
            return;
        }
    }

    bill[billSize].productId = id;
    bill[billSize].unitPrice = products[idx].price;
    bill[billSize].qty       = qty;
    bill[billSize].subtotal  = products[idx].price * qty;

    strncpy(bill[billSize].productName, products[idx].name, NAME_LEN - 1);
    bill[billSize].productName[NAME_LEN - 1] = '\0';

    products[idx].quantity -= qty;
    billSize++;
    printf("\n  [OK] '%s' x%d added to bill. (Rs. %.2f)\n", products[idx].name, qty, products[idx].price * qty);
    printProductsTable(1);
}

/* ── 2. viewBill() ── */
void viewBill() {
    if (billSize == 0) {
        printf("\n  [!] Bill is empty. Please add items first.\n");
        return;
    }

    printf("\n  +----------------------------------------------------------+\n");
    printf("  |                  CURRENT BILL                            |\n");
    printf("  +----------------------------------------------------------+\n");
    printf("  | %-3s  %-22s  %8s  %4s  %10s |\n", "No.", "Product", "UnitPrice", "Qty", "Subtotal");
    printf("  +----------------------------------------------------------+\n");

    float runningTotal = 0.0f;
    for (int i = 0; i < billSize; i++) {
        printf("  | %-3d  %-22s  %8.2f  %4d  %10.2f |\n",
               i + 1, bill[i].productName, bill[i].unitPrice, bill[i].qty, bill[i].subtotal);
        runningTotal += bill[i].subtotal;
    }

    printf("  +----------------------------------------------------------+\n");
    printf("  |  Items in bill : %-3d                                    |\n", billSize);
    printf("  |  Gross Total   : Rs. %-10.2f                        |\n", runningTotal);
    printf("  +----------------------------------------------------------+\n");
}

/* ── 3. calculateTotal() ── */
float calculateTotal() {
    float gross    = 0.0f;
    float discount = 0.0f;

    for (int i = 0; i < billSize; i++) {
        gross += bill[i].subtotal;
    }

    if (gross > 10000.0f) {
        discount = gross * 0.10f;
    } else if (gross > 5000.0f) {
        discount = gross * 0.05f;
    }

    billTotal = gross - discount;

    printf("\n  -----------------------------------------\n");
    printf("   BILL CALCULATION\n");
    printf("  -----------------------------------------\n");
    printf("  Gross Total   : Rs. %10.2f\n", gross);

    if (discount > 0.0f) {
        if (gross > 10000.0f)
            printf("  Discount      : 10%% off  -> Rs. %8.2f\n", discount);
        else
            printf("  Discount      :  5%% off  -> Rs. %8.2f\n", discount);
    } else {
        printf("  Discount      : None\n");
    }

    printf("  -----------------------------------------\n");
    printf("  TOTAL PAYABLE : Rs. %10.2f\n", billTotal);
    printf("  -----------------------------------------\n");

    return billTotal;
}

/* ── 4. printReceipt() ── */
void printReceipt() {
    if (billSize == 0) {
        printf("\n  [!] Nothing to print. Bill is empty.\n");
        return;
    }

    float total = calculateTotal();

    printf("\n  Enter Amount Given (Rs.): ");
    float given;
    if (scanf("%f", &given) != 1) {
        printf("  [!] Invalid amount.\n");
        while(getchar() != '\n');
        return;
    }

    if (given < total) {
        printf("  [!] Insufficient amount. Rs. %.2f more needed.\n", total - given);
        return;
    }

    float change = given - total;

    printf("\n");
    printf("  +----------------------------------------------------------+\n");
    printf("  |            FRESHMART SUPERMARKET                         |\n");
    printf("  |            Official Receipt                              |\n");
    printf("  +----------------------------------------------------------+\n");
    printf("  | %-3s  %-22s  %8s  %4s  %10s |\n", "No.", "Item", "Price", "Qty", "Subtotal");
    printf("  +----------------------------------------------------------+\n");

    float gross = 0.0f;
    for (int i = 0; i < billSize; i++) {
        printf("  | %-3d  %-22s  %8.2f  %4d  %10.2f |\n",
               i + 1, bill[i].productName, bill[i].unitPrice, bill[i].qty, bill[i].subtotal);
        gross += bill[i].subtotal;
    }

    float discount = gross - total;

    printf("  +----------------------------------------------------------+\n");
    printf("  |  Gross Total     : Rs. %-10.2f                      |\n", gross);

    if (discount > 0.0f)
        printf("  |  Discount        : Rs. %-10.2f                      |\n", discount);

    printf("  |  TOTAL PAYABLE   : Rs. %-10.2f                      |\n", total);
    printf("  |  Cash Given      : Rs. %-10.2f                      |\n", given);
    printf("  |  Change          : Rs. %-10.2f                      |\n", change);
    printf("  +----------------------------------------------------------+\n");
    printf("  |        Thank you for shopping with us!                   |\n");
    printf("  |             Please come again!                           |\n");
    printf("  +----------------------------------------------------------+\n");
}

/* ── 5. clearBill() ── */
void clearBill() {
    ensureProductCatalog();

    if (billSize == 0) {
        printf("\n  Bill is already empty.\n");
        return;
    }

    printf("\n  Clear bill and RESTORE stock? (y = cancel order / n = post-checkout clear)\n");
    printf("  Choice (y/n): ");
    char ch;
    scanf(" %c", &ch);

    if (ch == 'y' || ch == 'Y') {
        for (int i = 0; i < billSize; i++) {
            int idx = findById(bill[i].productId);
            if (idx != -1) {
                products[idx].quantity += bill[i].qty;
            }
        }
        printf("\n  [OK] Order cancelled. Stock restored.\n");
    } else {
        printf("\n  [OK] Bill cleared. Thank you!\n");
    }

    billSize  = 0;
    billTotal = 0.0f;
    printProductsTable(1);
}

/* ── Billing Sub-Menu ── */
void billingMenu() {
    int choice;
    do {
        printf("\n  +-------------------------------------+\n");
        printf("  |         BILLING SYSTEM              |\n");
        printf("  +-------------------------------------+\n");
        printf("  |  1. Add Item to Bill                |\n");
        printf("  |  2. View Current Bill                |\n");
        printf("  |  3. Calculate Total                 |\n");
        printf("  |  4. Print Receipt (Checkout)        |\n");
        printf("  |  5. Clear Bill                      |\n");
        printf("  |  0. Back                            |\n");
        printf("  +-------------------------------------+\n");
        printf("  Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\n  [!] Invalid choice. Try again.\n");
            while(getchar() != '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: addItemToBill();  break;
            case 2: viewBill();       break;
            case 3: calculateTotal(); break;
            case 4: printReceipt();
                    if (billSize > 0) {
                        billSize  = 0;
                        billTotal = 0.0f;
                        printf("  [OK] Bill cleared for next customer.\n");
                    }
                    break;
            case 5: clearBill();      break;
            case 0: break;
            default: printf("\n  [!] Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}

/* wrapper expected by customer.c */
void processBilling() {
    billingMenu();
}
