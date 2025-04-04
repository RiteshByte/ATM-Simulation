#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define PIN_LENGTH 4
#define NAME_LENGTH 50
#define MOBILE_LENGTH 15
#define EMAIL_LENGTH 50
#define ACCOUNT_NO_LENGTH 10

typedef struct 
{
    char name[NAME_LENGTH];
    char father_name[NAME_LENGTH];
    char mobile[MOBILE_LENGTH];
    char email[EMAIL_LENGTH];
    char account_no[ACCOUNT_NO_LENGTH];
    char pin[PIN_LENGTH + 1];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int account_count = 0;

void clear_input_buffer() 
{
    while (getchar() != '\n');
}

void create_account() 
{
    if (account_count >= MAX_ACCOUNTS) 
    {
        printf("Account limit reached. Cannot create more accounts.\n");
        return;
    }
    
    Account new_account;
    
    printf("Enter your name: ");
    scanf(" %[^\n]", new_account.name);
    clear_input_buffer();
    
    printf("Enter your father's name: ");
    scanf(" %[^\n]", new_account.father_name);
    clear_input_buffer();
    
    printf("Enter your mobile number: ");
    scanf("%s", new_account.mobile);
    clear_input_buffer();
    
    printf("Enter your email ID: ");
    scanf("%s", new_account.email);
    clear_input_buffer();
    
    printf("Enter a new account number: ");
    scanf("%s", new_account.account_no);
    clear_input_buffer();
    
    printf("Set a 4-digit PIN: ");
    scanf("%4s", new_account.pin);
    clear_input_buffer();
    
    new_account.balance = 0.0;
    accounts[account_count] = new_account;
    account_count++;
    
    printf("Account created successfully! Your account number is %s\n", new_account.account_no);
}

int authenticate() 
{
    char entered_account_no[ACCOUNT_NO_LENGTH];
    char entered_pin[PIN_LENGTH + 1];
    
    printf("Enter your account number: ");
    scanf("%s", entered_account_no);
    clear_input_buffer();
    
    printf("Enter your PIN: ");
    scanf("%4s", entered_pin);
    clear_input_buffer();
    
    for (int i = 0; i < account_count; i++) 
    {
        if (strcmp(entered_account_no, accounts[i].account_no) == 0 &&
            strcmp(entered_pin, accounts[i].pin) == 0) 
        {
            return i;
        }
    }
    return -1;
}

void check_balance(int account_index) 
{
    printf("Your current balance is: $%.2f\n", accounts[account_index].balance);
}

void deposit(int account_index) 
{
    float amount;
    printf("Enter amount to deposit: ");
    if (scanf("%f", &amount) != 1) 
    {
        printf("Invalid input. Please enter a valid number.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    if (amount > 0) 
    {
        accounts[account_index].balance += amount;
        printf("Successfully deposited: $%.2f\n", amount);
        check_balance(account_index);
    } 
    else 
    {
        printf("Deposit amount must be greater than zero.\n");
    }
}

void withdraw(int account_index) 
{
    float amount;
    printf("Enter amount to withdraw: ");
    if (scanf("%f", &amount) != 1) 
    {
        printf("Invalid input. Please enter a valid number.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    if (amount > accounts[account_index].balance) 
    {
        printf("Insufficient funds for this withdrawal.\n");
    } 
    else if (amount <= 0) 
    {
        printf("Withdrawal amount must be greater than zero.\n");
    } 
    else 
    {
        accounts[account_index].balance -= amount;
        printf("Successfully withdrew: $%.2f\n", amount);
        check_balance(account_index);
    }
}

void transfer(int account_index) 
{
    float amount;
    char recipient_account_no[ACCOUNT_NO_LENGTH];
    
    printf("Enter amount to transfer: ");
    if (scanf("%f", &amount) != 1) 
    {
        printf("Invalid input. Please enter a valid number.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    if (amount > accounts[account_index].balance) 
    {
        printf("Insufficient funds for this transfer.\n");
        return;
    } 
    else if (amount <= 0) 
    {
        printf("Transfer amount must be greater than zero.\n");
        return;
    }
    
    printf("Enter recipient account number: ");
    scanf("%s", recipient_account_no);
    clear_input_buffer();
    
    int recipient_index = -1;
    for (int i = 0; i < account_count; i++) 
    {
        if (strcmp(recipient_account_no, accounts[i].account_no) == 0) 
        {
            recipient_index = i;
            break;
        }
    }
    
    if (recipient_index == -1 || recipient_index == account_index)
    {
        printf("Invalid recipient account. You cannot transfer money to your own account.\n");
        return;
    }
    
    accounts[account_index].balance -= amount;
    accounts[recipient_index].balance += amount;
    
    printf("Successfully transferred: $%.2f to account %s\n", amount, recipient_account_no);
    check_balance(account_index);
}

void display_menu() 
{
    printf("\nATM Menu:\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Transfer\n");
    printf("5. Exit to Main Menu\n");
}

int main() 
{
    int choice;

    while (1) 
    {
        printf("\nSBI Bank ATM Simulation\n");
        printf("1. Create Account\n");
        printf("2. Use ATM\n");
        printf("3. Exit\n");
        printf("Select an option (1-3): ");

        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (choice == 1) 
        {
            create_account();
        } 
        else if (choice == 2) 
        {
            if (account_count == 0) 
            {
                printf("No accounts found. Please create an account first.\n");
                continue;
            }

            int account_index = authenticate();
            if (account_index == -1) 
            {
                printf("Incorrect account number or PIN. Access denied.\n");
                continue;
            }

            while (1) 
            {
                display_menu();
                printf("Select an option (1-5): ");
                if (scanf("%d", &choice) != 1) 
                {
                    printf("Invalid input. Please enter a number.\n");
                    clear_input_buffer();
                    continue;
                }
                clear_input_buffer();

                switch (choice) 
                {
                    case 1: check_balance(account_index); break;
                    case 2: deposit(account_index); break;
                    case 3: withdraw(account_index); break;
                    case 4: transfer(account_index); break;
                    case 5: printf("Returning to main menu.\n"); break;
                    default: printf("Invalid option. Please try again.\n");
                }
                if (choice == 5) break;
            }
        } 
        else if (choice == 3) 
        {
            printf("Exiting program. Thank you!\n");
            break;
        } 
        else 
        {
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
