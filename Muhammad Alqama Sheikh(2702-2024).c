#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX 100

float pkrToUsd = 0.00359, usdToPkr = 278.5, gbpToEur = 1.203, jpyToCny = 0.047, cnyToJpy = 21.408;
float eurToGbp = 0.831, audToCad = 0.901, cadToAud = 1.11, inrToSgd = 0.016, sgdToInr = 62.958;

void displayMenu();
void adminPortal();
void loginUser();
void registerUser();
void currencyConverter();
void viewAllUsers();
void viewConversionHistory();
void userHistory(const char *username, const char *conversionDetails);

char username[MAX];
char password[MAX];
char email[MAX];

int main() {
    int choice;

    displayMenu();
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        adminPortal();
    } else if (choice == 2) {
        loginUser();
    } else {
        printf("\tInvalid choice! Kindly choose 1 or 2.\n");
    }

    return 0;
}

void displayMenu() {
    printf("\t--- Currency Converter Application ---\n");
    printf("\t1. Admin Portal\n");
    printf("\t2. Login User\n");
}

void adminPortal() {
    char adminName[MAX], adminPassword[MAX];

    printf("\t--- Admin Portal ---\n");
    printf("\tEnter Admin Username: ");
    getchar();
    scanf("%[^\n]", adminName);

    printf("\tEnter Admin Password: ");
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            adminPassword[i] = '\0';
            break;
        } else if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        } else if (i < MAX - 1) {
            adminPassword[i] = ch;
            i++;
            printf("*");
        }
    }

    printf("\t\nWelcome! Admin.\n");

    FILE *file = fopen("admin_history.txt", "a");
    if (!file) {
        printf("\tError logging admin history.\n");
        return;
    }

    fprintf(file, "AdminName: %s, AdminPassword: %s\n", adminName, adminPassword);
    fclose(file);

    int adminChoice;
    while (1) {
        printf("\n\t--- Admin Options ---\n");
        printf("\t1. View All User History\n");
        printf("\t2. View Conversion History\n");
        printf("\t3. Logout\n");
        printf("\tEnter your choice: ");
        scanf("%d", &adminChoice);

        switch (adminChoice) {
        case 1:
            viewAllUsers();
            break;
        case 2:
            viewConversionHistory();
            break;
        case 3:
            printf("\tLogging out...\n");
            return;
        default:
            printf("\tInvalid choice! Please try again.\n");
        }
    }
}

void loginUser() {
    printf("\t--- Login ---\n");

    printf("\tEnter your username: ");
    getchar();
    scanf("%[^\n]", username);

    printf("\tEnter your password: ");
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            password[i] = '\0';
            break;
        } else if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        } else if (i < MAX - 1) {
            password[i] = ch;
            i++;
            printf("*");
        }
    }

    printf("\t\nLogin successful! Welcome, %s!\n", username);

    registerUser();

    currencyConverter();

    FILE *file = fopen("user_login_history.txt", "a");
    if (!file) {
        printf("\tError logging user history.\n");
        return;
    }

    fprintf(file, "Username: %s, Password: %s\n", username, password);
    fclose(file);
}

void registerUser() {
    printf("\t--- Register User ---\n");
    printf("\tPlease enter your details to register.\n");

    printf("\tEnter your name: ");
    getchar();
    scanf("%[^\n]", username);

    printf("\tEnter your password: ");
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            password[i] = '\0';
            break;
        } else if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        } else if (i < MAX - 1) {
            password[i] = ch;
            i++;
            printf("*");
        }
    }

    while (1) {
        printf("\n\tEnter your email: ");
        scanf("%s", email);

        char *at = strchr(email, '@');
        char *dot = strrchr(email, '.');

        if (at && dot && at < dot) {
            break;
        } else {
            printf("\tInvalid email! Please enter a valid email address.\n");
        }
    }

    FILE *file = fopen("user_registration.txt", "a");
    if (!file) {
        printf("\tError saving user registration.\n");
        return;
    }

    fprintf(file, "Username: %s, Password: %s, Email: %s\n", username, password, email);
    fclose(file);

    printf("\tThank you for registering, %s!\n", username);
}

void viewAllUsers() {
    FILE *file = fopen("user_registration.txt", "r");
    if (!file) {
        printf("\tNo registered users found.\n");
        return;
    }

    char line[MAX];
    printf("\t--- Registered Users ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("\t%s", line);
    }

    fclose(file);
}

void viewConversionHistory() {
    FILE *file = fopen("user_conversion_history.txt", "r");
    if (!file) {
        printf("\tNo conversion history found.\n");
        return;
    }

    char line[MAX];
    printf("\t--- Conversion History ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("\t%s", line);
    }

    fclose(file);
}

void userHistory(const char *username, const char *conversionDetails) {
    FILE *file = fopen("user_conversion_history.txt", "a");
    if (!file) {
        printf("\tError saving conversion history.\n");
        return;
    }

    fprintf(file, "User: %s, %s\n", username, conversionDetails);
    fclose(file);
}

void currencyConverter() {
    while (1) {
        float amount, convertedAmount;
        int conversion;

        printf("\tCurrency Converter:\n");
        printf("\t1. PKR to USD\n");
        printf("\t2. USD to PKR\n");
        printf("\t3. GBP to EUR\n");
        printf("\t4. EUR to GBP\n");
        printf("\t5. AUD to CAD\n");
        printf("\t6. CAD to AUD\n");
        printf("\t7. JPY to CNY\n");
        printf("\t8. CNY to JPY\n");
        printf("\t9. INR to SGD\n");
        printf("\t10. SGD to INR\n");
        printf("\tEnter your choice (1-10): ");
        scanf("%d", &conversion);

        if (conversion < 1 || conversion > 10) {
            printf("\tInvalid conversion choice! Please select between 1-10.\n");
            continue;
        }

        printf("\tEnter the amount: ");
        scanf("%f", &amount);
        if (amount <= 0) {
            printf("\tAmount must be greater than 0.\n");
            continue;
        }

        char conversionDetails[MAX];
        if (conversion == 1) {
            convertedAmount = amount * pkrToUsd;
            sprintf(conversionDetails, "%.2f PKR is %.2f USD", amount, convertedAmount);
        } else if (conversion == 2) {
            convertedAmount = amount * usdToPkr;
            sprintf(conversionDetails, "%.2f USD is %.2f PKR", amount, convertedAmount);
        } else if (conversion == 3) {
            convertedAmount = amount * gbpToEur;
            sprintf(conversionDetails, "%.2f GBP is %.2f EUR", amount, convertedAmount);
        } else if (conversion == 4) {
            convertedAmount = amount * eurToGbp;
            sprintf(conversionDetails, "%.2f EUR is %.2f GBP", amount, convertedAmount);
        } else if (conversion == 5) {
            convertedAmount = amount * audToCad;
            sprintf(conversionDetails, "%.2f AUD is %.2f CAD", amount, convertedAmount);
        } else if (conversion == 6) {
            convertedAmount = amount * cadToAud;
            sprintf(conversionDetails, "%.2f CAD is %.2f AUD", amount, convertedAmount);
        } else if (conversion == 7) {
            convertedAmount = amount * jpyToCny;
            sprintf(conversionDetails, "%.2f JPY is %.2f CNY", amount, convertedAmount);
        } else if (conversion == 8) {
            convertedAmount = amount * cnyToJpy;
            sprintf(conversionDetails, "%.2f CNY is %.2f JPY", amount, convertedAmount);
        } else if (conversion == 9) {
            convertedAmount = amount * inrToSgd;
            sprintf(conversionDetails, "%.2f INR is %.2f SGD", amount, convertedAmount);
        } else if (conversion == 10) {
            convertedAmount = amount * sgdToInr;
            sprintf(conversionDetails, "%.2f SGD is %.2f INR", amount, convertedAmount);
        } else {
            printf("\tInvalid conversion type.\n");
            continue;
        }

        printf("\t%s\n", conversionDetails);
        userHistory(username, conversionDetails);

        int again;
        printf("\tDo you want to convert again? (1 for Yes, 0 for No): ");
        scanf("%d", &again);
        if (again != 1) {
            break;
        }
    }
}
