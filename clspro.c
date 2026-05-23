#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
typedef struct personal_detail {
    char name[25];
    char father_name[25];
    char DOB[20];
    char gender[10];
    char pNumber[15];
    char Email[50];
    char address[100];

} CustomerPersonalDetails;

CustomerPersonalDetails customerDetails;

typedef struct account_detail {
    long long int acc_number;
    char acc_type[20];
    float initial_amt;
    char nominee_name[20];
    char nominee_relation[20];
    float balance;
} BankAccountDetails;

BankAccountDetails accountDetails;

typedef struct security_setup {
    char set_password[15];
    char confirm_password[15];
    int PIN;
    char security_que[50];
} AccountSecurityDetails;

AccountSecurityDetails securityDetails;
float transactionAmount =0.0;
long long int enteredAccountNumber;
char line[150];
typedef struct CustomerAccountSession_data{
    long long int acc;
    char name[20];
    char acc_type[20];
    float balance;
    char password[20];
    char accountStatus[20];
} CustomerAccountSession;
CustomerAccountSession loggedInCustomer;
typedef struct loan_data{
    int loanID;
    long long accountNumber;
    float loanAmount;
    int loanStatus;

} LoanDetails;
LoanDetails loan;

void applyForLoan();
void viewLoanStatus();
void approveLoanRequest();
void displayFraudDetectionLogs();
int detectFraudulentTransaction(float amount);
void displayAllTransactionLogs();
void deleteCustomerAccount();
void freezeCustomerAccount();
void displayFraudDetectionLogs();
void displayAllCustomerAccounts();
void adminControlPanel();
void removeTrailingNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}
void generateSecurityAlert();
int detectFraudulentTransaction(float amount);
void logTransactionRecord(char type[], float amount, long long receiverAcc);
void trimWhitespace(char str[]);
void updateAccountBalance(float newbalance);
long long generateUniqueAccountNumber();
void createBankAccount();
void displayTransactionHistory();
void userlogin();
void authenticateAdmin();
void collectPersonalInformation();
void collectAccountInformation();
void setupSecurityCredentials();
void displayAccountSummary();
void processDepositTransaction();
void processFundTransfer();
void withdrawMoney();
void authenticateCustomer();
int main() {
    int choice;

    do {
        printf("\n====================================================\n");
        printf("\t\tBANK MANAGEMENT SYSTEM\n");
        printf("====================================================\n");

        printf("\n1. Customer\n");
        printf("2. Admin\n");
        printf("3. EXIT\n");

        printf("\nEnter Your Choice : ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                authenticateCustomer(); 
                break;

            case 2:
                printf("\n====================================================\n");
                    printf("\t\tADMIN LOGIN\n");
                printf("====================================================\n");
                authenticateAdmin();
                break;

            // case 3:
            //     printf("\n====================================================\n");
            //     printf("====================================================\n");
            //     break;

            // case 4:
            //     printf("\n====================================================\n");
            //     printf("\t\tQUICK SERVICE\n");
            //     printf("====================================================\n");
            //     break;

            // case 5:
            //     printf("\n====================================================\n");
            //     printf("\t\tHELP OR ABOUT\n");
            //     printf("====================================================\n");
            //     break;

            case 3:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Input!\n");
        }

    } while(choice != 3);

    return 0;
}

void approveLoanRequest(){

    int targetLoanID;

    FILE *fp, *temp;

    char line[300];

    int found = 0;

    printf("Enter Loan ID : ");
    scanf("%d", &targetLoanID);

    fp = fopen("loan.txt", "r");

    temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL){

        printf("File Error!\n");

        return;
    }

    while(fgets(line, sizeof(line), fp)){

        int loanID;

        long long acc;

        float amount;

        char status[20];

        sscanf(line,
        "LoanID : %d | A/C : %lld | Amount : %f | Status : %s",

        &loanID,
        &acc,
        &amount,
        status);

        if(loanID == targetLoanID){

            found = 1;

            fprintf(temp,
            "LoanID : %d | A/C : %lld | Amount : %.2f | Status : APPROVED\n",

            loanID,
            acc,
            amount);

            printf("Loan Approved Successfully!\n");
        }

        else{

            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("loan.txt");

    rename("temp.txt", "loan.txt");

    if(found == 0){

        printf("Loan ID Not Found!\n");
    }
}
void viewLoanStatus(){

    FILE *fp;

    char line[300];

    int found = 0;

    fp = fopen("loan.txt", "r");

    if(fp == NULL){

        printf("No Loan Records Found!\n");

        return;
    }

    printf("\n=========== LOAN STATUS ===========\n");

    while(fgets(line, sizeof(line), fp)){

        long long acc;

        sscanf(line,
        "LoanID : %*d | A/C : %lld",
        &acc);

        if(acc == loggedInCustomer.acc){

            printf("%s", line);

            found = 1;
        }
    }

    if(found == 0){

        printf("No Loan Applied!\n");
    }

    fclose(fp);
}
void applyForLoan(){


    FILE *fp;

    printf("Enter Loan Amount : ");
    scanf("%f", &loan.loanAmount);

    if(loan.loanAmount <= 0){

        printf("Invalid Loan Amount!\n");

        return;
    }

    loan.loanID = rand() % 10000 + 1000;

    loan.accountNumber = loggedInCustomer.acc;

    loan.loanStatus = 0;

    fp = fopen("loan.txt", "a");

    if(fp == NULL){

        printf("File Error!\n");

        return;
    }

    fprintf(fp,
    "LoanID : %d | A/C : %lld | Amount : %.2f | Status : PENDING\n",

    loan.loanID,
    loan.accountNumber,
    loan.loanAmount);

    fclose(fp);

    printf("\n====================================\n");
    printf("Loan Request Submitted Successfully!\n");
    printf("Loan ID : %d\n", loan.loanID);
    printf("====================================\n");
}
void displayAllTransactionLogs(){
    FILE *fp;
    char line[300];
    fp=fopen("transactions.txt","r");
    if(fp==NULL){
        printf("No Transaction Logs Found !\n");
        return;
    }
    printf("\n====================================================\n");
    printf("ALL TRANSACTION LOGS");
    printf("\n====================================================\n");
    while(fgets(line,sizeof(line),fp)){
        printf("%s",line);
    }
    printf("\n====================================================\n");
    fclose(fp);
}
void deleteCustomerAccount(){
    long long targetAccount;
    FILE *fp,*temp;
    char line[300];
    int found = 0;
    printf("Enter Account Number To Delete : ");
    scanf("%lld",&targetAccount);
    fp = fopen("accounts.txt","r");
    temp = fopen("temp.txt","w");

    if(fp == NULL || temp == NULL){
        printf("file Error!\n");
        return;
    }
    while(fgets(line,sizeof(line),fp)){
        long long acc;
        sscanf(line,"A/C No. : %lld",&acc);
        if(acc == targetAccount){
            found = 1;
            printf("\nAccount Deleted Successfully!\n");
            continue;
        }
        fputs(line,temp);
    }
    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt","accounts.txt");

    if(found == 0){
        printf("Account Not Found !\n");
    }
}
void freezeCustomerAccount(){
    long long targetAccount;
    FILE *fp, *temp;
    char line[300];
    int found =0;
    printf("Enter Account Number To Block : ");
    scanf("%lld",&targetAccount);

    fp = fopen("accounts.txt","r");
    temp = fopen("temp.txt","w");

    if(fp == NULL || temp == NULL){
        printf("file Error !\n");
        return;
    }
    while(fgets(line,sizeof(line),fp)){
        long long acc;
        char name[50];
        float balance;
        char accType[20];
        char password[30];
        char status[20];
        sscanf(line,"A/C No. : %lld | Name : %[^|] | Balance : %f | A/C Type : %[^|] | Password : %s | Status : %s",
        &acc,
        name,
        &balance,
        accType,
        password,
        status);

        trimWhitespace(name);
        trimWhitespace(accType);

        if(acc == targetAccount){
            found = 1;
            fprintf(temp,"A/C No. : %lld | Name : %s | Balance : %.2f | A/C Type : %s | Password : %s | Status : BLOCKED\n",
            acc,
            name,
            balance,
            accType,
            password);
            printf("\nAccount Blocked Successfully!!\n");
        }
        else {
            fputs(line,temp);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt","accounts.txt");

    if(found == 0){
        printf("Account Not Found!\n");
    }
}
void displayFraudDetectionLogs(){

    FILE *fp;

    char line[300];

    fp = fopen("fraud_logs.txt", "r");

    if(fp == NULL){

        printf("No Fraud Logs Found!\n");

        return;
    }

    printf("\n========== FRAUD LOGS ==========\n");

    while(fgets(line, sizeof(line), fp)){

        printf("%s", line);
    }

    fclose(fp);
}
void displayAllCustomerAccounts(){

    FILE *fp;

    char line[300];

    fp = fopen("accounts.txt", "r");

    if(fp == NULL){

        printf("No Accounts Found!\n");

        return;
    }

    printf("\n========== CUSTOMER ACCOUNTS ==========\n");

    while(fgets(line, sizeof(line), fp)){

        printf("%s", line);
    }

    fclose(fp);
}
void adminControlPanel(){

    int choice;

    do{

        printf("\n====================================\n");
        printf("\tADMIN CONTROL PANEL");
        printf("\n====================================\n");

        printf("1. View All Accounts\n");
        printf("2. View Fraud Logs\n");
        printf("3. Freeze Customer Account\n");
        printf("4. Delete Customer Account\n");
        printf("5. View Transaction Logs\n");
        printf("6. Approve Loan Request\n");
        printf("7. Logout \n");

        printf("Enter Choice : ");
        scanf("%d", &choice);

        switch(choice){

            case 1:
                displayAllCustomerAccounts();
                break;

            case 2:
                displayFraudDetectionLogs();
                break;

            case 3:
                freezeCustomerAccount();
                break;

            case 4:
                deleteCustomerAccount();
                break;

            case 5:
                displayAllTransactionLogs();
                break;

            case 6:
                approveLoanRequest();
                break;
            case 7:
                return;

            default:
                printf("Invalid Choice!\n");
        }

    }while(choice != 6);
}
void authenticateAdmin(){
    int ops;
    char adminID[20];
    char adminPassword[20];

    printf("Enter Admin ID : ");
    scanf("%s", adminID);

    printf("Enter Password : ");
    scanf("%s", adminPassword);

    if(strcmp(adminID, "admin") == 0 &&
       strcmp(adminPassword, "admin123") == 0){

        printf("\nAdmin Login Successful!\n");

        adminControlPanel();
    }

    else{

        printf("Invalid Admin Credentials!\n");
        return;
    }
}
void generateSecurityAlert(){

    printf("\n=================================\n");
    printf("SECURITY ALERT GENERATED\n");
    printf("Admin Has Been Notified\n");
    printf("=================================\n");
}
int detectFraudulentTransaction(float amount){

    FILE *fp;

    if(amount > 100000){

        printf("\n!!! FRAUD ALERT !!!\n");

        fp = fopen("fraud_logs.txt", "a");

        fprintf(fp,
        "Suspicious Transaction Detected : %.2f\n",
        amount);

        fclose(fp);

        return 1;
    }

    return 0;
}
void logTransactionRecord(char type[], float amount, long long receiverAcc){

    FILE *fp;

    fp = fopen("transactions.txt", "a");

    if(fp == NULL){
        printf("Transaction File Error!\n");
        return;
    }

    // Current Time
    time_t t;
    time(&t);

    struct tm *current = localtime(&t);

    char dateTime[100];

    strftime(dateTime, sizeof(dateTime),
    "%d-%m-%Y %I:%M %p",
    current);

    // Deposit
    if(strcmp(type, "Deposit") == 0){

        fprintf(fp,
        "[%s] A/C : %lld | Deposit : %.2f\n",
        dateTime,
        loggedInCustomer.acc,
        amount);

        // Screen Print
        printf("\n[%s] Deposit Successful : %.2f\n",
        dateTime,
        amount);
    }

    // Withdraw
    else if(strcmp(type, "Withdraw") == 0){

        fprintf(fp,
        "[%s] A/C : %lld | Withdraw : %.2f\n",
        dateTime,
        loggedInCustomer.acc,
        amount);

        // Screen Print
        printf("\n[%s] Withdraw Successful : %.2f\n",
        dateTime,
        amount);
    }

    // Transfer
    else if(strcmp(type, "Transfer") == 0){

        fprintf(fp,
        "[%s] A/C : %lld | Transfer to %lld : %.2f\n",
        dateTime,
        loggedInCustomer.acc,
        receiverAcc,
        amount);

        // Screen Print
        printf("\n[%s] Transfer Successful to %lld : %.2f\n",
        dateTime,
        receiverAcc,
        amount);
    }

    fclose(fp);
}
void trimWhitespace(char str[]) {

    int start = 0;
    int end = strlen(str) - 1;

    // Leading spaces remove
    while(str[start] == ' ') {
        start++;
    }

    // Trailing spaces remove
    while(end > start && str[end] == ' ') {
        end--;
    }

    int i, j = 0;

    for(i = start; i <= end; i++) {
        str[j++] = str[i];
    }

    str[j] = '\0';
}
void updateAccountBalance(float newBalance){

    FILE *fp, *temp;
    char line[300];
    char status[20];

    fp = fopen("accounts.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL){
        printf("File Error!\n");
        return;
    }

    while(fgets(line, sizeof(line), fp)){

        long long acc;
        char name[50];
        float balance;
        char acc_type[20];
        char password[30];

        sscanf(line,
        "A/C No. : %lld | Name : %[^|] | Balance : %f | A/C Type : %[^|] | Password : %s | Status : %s",
        &acc,
        name,
        &balance,
        acc_type,
        password,
        status);
        trimWhitespace(name);
        trimWhitespace(acc_type);
        // Logged in account match
        if(acc == loggedInCustomer.acc){

            fprintf(temp,
            "A/C No. : %lld | Name : %s | Balance : %.2f | A/C Type : %s | Password : %s | Status : %s\n",
            acc,
            name,
            newBalance,
            acc_type,
            password,
            status);

        }else{

            // same old line copy
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    printf("Balance Updated Successfully!\n");
}
void processDepositTransaction(){
    printf("Enter the Amount        : ");
    scanf("%f",&transactionAmount);
    if(transactionAmount <= 0){
        printf("Invalid Amount!\n");
        return;
    }
    loggedInCustomer.balance+=transactionAmount;
    updateAccountBalance(loggedInCustomer.balance);
    logTransactionRecord("Deposit", transactionAmount, 0);
}
void withdrawMoney(){

    float amount;

    printf("Enter Amount to Withdraw : ");
    scanf("%f", &amount);

    if(amount <= 0){
        printf("Invalid Amount!\n");
        return;
    }

    if(amount > loggedInCustomer.balance){
        printf("Insufficient Balance!\n");
        return;
    }
    if(detectFraudulentTransaction(amount)){

    return;
    }

    loggedInCustomer.balance -= amount;

    updateAccountBalance(loggedInCustomer.balance);

    printf("Withdrawal Successful!\n");
    printf("Remaining Balance : %.2f\n", loggedInCustomer.balance);
    logTransactionRecord("Withdraw", amount, 0);
}
void processFundTransfer(){

    long long receiverAcc;
    float amount;
    char status[20];

    printf("Enter Receiver Account Number : ");
    scanf("%lld", &receiverAcc);

    if(receiverAcc == loggedInCustomer.acc){
        printf("Cannot Transfer To Same Account !\n");
        return;
    }

    printf("Enter Amount : ");
    scanf("%f", &amount);

    // Invalid amount
    if(amount <= 0){
        printf("Invalid Amount!\n");
        return;
    }

    // Insufficient balance
    if(amount > loggedInCustomer.balance){
        printf("Insufficient Balance!\n");
        return;
    }
    if(detectFraudulentTransaction(amount)){
        generateSecurityAlert();
        return;
    }

    FILE *fp, *temp;
    char line[300];

    fp = fopen("accounts.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL){
        printf("File Error!\n");
        return;
    }

    int found = 0;
    int senderFound = 0;
    while(fgets(line, sizeof(line), fp)){

        long long acc;
        char name[50];
        float balance;
        char acc_type[20];
        char password[30];

        sscanf(line,
        "A/C No. : %lld | Name : %[^|] | Balance : %f | A/C Type : %[^|] | Password : %s | Status : %s",
        &acc,
        name,
        &balance,
        acc_type,
        password,
        status);
        trimWhitespace(name);
        trimWhitespace(acc_type);
        trimWhitespace(status);
        if(acc == receiverAcc){           
            if(strcmp(status,"BLOCKED")==0){
                printf("Receiver Account Is BLOCKED!!\n");
            
                fclose(fp);
                fclose(temp);
                remove("temp.txt");
                return;
            }
        }
        // Sender account
        if(acc == loggedInCustomer.acc){

            balance -= amount;
            senderFound = 1;

            fprintf(temp,
            "A/C No. : %lld | Name : %s | Balance : %.2f | A/C Type : %s | Password : %s | Status : %s\n",
            acc,
            name,
            balance,
            acc_type,
            password,
            status);

            loggedInCustomer.balance = balance;
        }

        // Receiver account
        else if(acc == receiverAcc){

            balance += amount;

            fprintf(temp,
            "A/C No. : %lld | Name : %s | Balance : %.2f | A/C Type : %s | Password : %s | Status : %s\n",
            acc,
            name,
            balance,
            acc_type,
            password,
            status);

            found = 1;
        }

        else{
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    // Receiver not found
    if(found == 0 || senderFound == 0){

        remove("temp.txt");

        printf("Receiver Account Not Found!\n");
        return;
    }

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    printf("Transfer Successful!\n");
    printf("Remaining Balance : %.2f\n", loggedInCustomer.balance);
    logTransactionRecord("Transfer", amount, receiverAcc);
}
void displayAccountSummary(){
    printf("\n**************************************************\n");
    printf("Account Number      : %lld\n",loggedInCustomer.acc);
    printf("Name                : %s\n",loggedInCustomer.name);
    printf("Account Type        : %s\n",loggedInCustomer.acc_type);
    printf("Balance             : %.2f\n",loggedInCustomer.balance);
    printf("\n**************************************************\n");
    return;
}
void displayTransactionHistory(){

    FILE *fp;
    char line[300];
    int found = 0;

    fp = fopen("transactions.txt", "r");

    if(fp == NULL){
        printf("No Transaction History Found!\n");
        return;
    }

    printf("\n===============================================\n");
    printf("\tTRANSACTION HISTORY\n");
    printf("===============================================\n");

    while(fgets(line, sizeof(line), fp)){

        long long acc;

        // Read account number from line
        if(sscanf(line, "[%*[^]]] A/C : %lld", &acc) == 1){

            // Print only logged-in account transactions
            if(acc == loggedInCustomer.acc){

                printf("%s", line);
                found = 1;
            }
        }
    }

    if(found == 0){
        printf("No Transactions Found!\n");
    }

    printf("===============================================\n");

    fclose(fp);
}
void userlogin() {
    int found = 0;
    int try =0;
    long long int acc_id;
    char int_pass[20];
    float amount;
    FILE *read;

    read = fopen("accounts.txt", "r");

    if(read == NULL) {

        printf("\n<---- File Error ----->\n");
        return;
    }

    printf("Enter the A/C No.       : ");
    scanf("%lld", &enteredAccountNumber);

    while(fgets(line, sizeof(line), read) != NULL) {

        if(sscanf(line, "A/C No. : %lld", &acc_id) == 1) {

            if(acc_id == enteredAccountNumber) {

                found = 1;
                sscanf(line,"A/C No. : %lld | Name : %[^|] | Balance : %f | A/C Type : %[^|] | Password : %s | Status : %s",
                &loggedInCustomer.acc,
                loggedInCustomer.name,
                &loggedInCustomer.balance,
                loggedInCustomer.acc_type,
                loggedInCustomer.password,
                loggedInCustomer.accountStatus);
             break;
            }
        }
    }
    if(found ==0){
        printf("Invalid Account Number!\n");
        fclose(read);
        return;
    }
    printf("Enter the Password      : ");
    scanf("%s",int_pass);
    while(1) {

        if(strcmp(int_pass, loggedInCustomer.password) == 0) {
            if(strcmp(loggedInCustomer.accountStatus,"BLOCKED") == 0){
                printf("\n===================================\n");
                printf("THIS ACCOUNT IS BLOCKED\n");
                printf("CONTACT BANK ADMIN\n");
                printf("\n===================================\n");
                return;
            }
            printf("Login Successful!\n");
            break;
        }

        printf("Wrong Password! Try Again : ");
        scanf("%s", int_pass);
        try++;
        if(try>=4){
            FILE *fp;
            fp = fopen("fraud_logs.txt","a");
            fprintf(fp,"Multiple Wrong Password Attempts : %lld\n",enteredAccountNumber);
            fclose(fp);
            fclose(read);
            printf("Multiple Wrong Password Attempts !\n");
            return;
        }
    }
    fclose(read);
    int option;
    if(strcmp(int_pass, loggedInCustomer.password)==0){
        if(found==1){
            do {
                printf("\n***************** WELCOME ***********************\n");
                printf("\n1. Account Overview\n");
                printf("2. Deposite Money\n");
                printf("3. Withdraw Money\n");
                printf("4. Transfer Funds\n");
                printf("5. Transaction History\n");
                printf("6. Apply Loan\n");
                printf("7. View Loan Status\n");
                printf("8. Logout\n");

                printf("Enter your choice : ");
                scanf("%d", &option);

                switch(option) {
                case 1: 
                    displayAccountSummary();
                break;
                case 2:
                    processDepositTransaction();
                    break;
                case 3:
                    withdrawMoney();
                    break;
                case 4:
                    processFundTransfer();
                    break;
                case 5:
                    displayTransactionHistory();
                    break;
                case 6:
                    applyForLoan();
                    break;
                case 7:
                    viewLoanStatus();
                    break;
                case 8:
                    return;

                default:
                    printf("INVALID INPUT !\n");
                }

            } while(option != 8);
        }else {
            printf("Invalid Account Number !\n");
        }
    }
}
void collectPersonalInformation() {

    getchar();

    printf("Full Name           : ");
    fgets(customerDetails.name, 25, stdin);
    removeTrailingNewline(customerDetails.name);

    printf("Father Name         : ");
    fgets(customerDetails.father_name, 25, stdin);

    printf("DOB                 : ");
    fgets(customerDetails.DOB, 20, stdin);

    printf("Gender              : ");
    fgets(customerDetails.gender, 10, stdin);

    printf("Mobile Number       : ");
    scanf("%s",customerDetails.pNumber);
    // getchar();
    printf("Email ID            : ");
    scanf("%s",customerDetails.Email);
    getchar();

    printf("Address             : ");
    fgets(customerDetails.address, 100, stdin);
}
long long generateUniqueAccountNumber() {

    FILE *fp;
    char line[300];
    long long lastAcc = 10000;

    fp = fopen("accounts.txt", "r");

    if(fp == NULL) {
        return 10001;
    }

    while(fgets(line, sizeof(line), fp)) {

        long long temp;

        if(sscanf(line, "A/C No. : %lld", &temp) == 1) {
            lastAcc = temp;
        }
    }

    fclose(fp);

    return lastAcc + 1;
}
void collectAccountInformation() {
    accountDetails.balance =0.0;
    printf("Select account Type \n(Saving / Current)        : ");
    fgets(accountDetails.acc_type, 20, stdin);
    removeTrailingNewline(accountDetails.acc_type);

    printf("Initial Deposite    : ");
    scanf("%f", &accountDetails.initial_amt);

    getchar();

    printf("Nominee Name        : ");
    fgets(accountDetails.nominee_name, 20, stdin);
    printf("Nominee Relation    : ");
    fgets(accountDetails.nominee_relation, 20, stdin);
    accountDetails.acc_number = generateUniqueAccountNumber();
} 
void setupSecurityCredentials() {

    printf("Set Password        : ");
    scanf("%s", securityDetails.set_password);
    getchar();
    printf("Confirm Password    : ");
    scanf("%s", securityDetails.confirm_password);
    getchar();
    while(strcmp(securityDetails.set_password, securityDetails.confirm_password) != 0) {

        printf("Password Not Match ! Please Try Again : ");
        scanf("%s", securityDetails.confirm_password);
        getchar();
    }
    printf("Security Question :- \nYour First School Name   : ");
    fgets(securityDetails.security_que, 50, stdin);
    

}
void createBankAccount() {

    int op;

    while(1) {

        printf("************* PERSONAL DETAILS *************\n");
        collectPersonalInformation();

        printf("************* ACCOUNT DETAILS *************\n");
        collectAccountInformation();

        printf("************* ACCOUNT DETAILS *************\n");
        setupSecurityCredentials();

        printf("************* CONFIRMATION SCREEN *************\n");
        printf("Account Number   : %lld\n", accountDetails.acc_number);
        printf("Name             : %s\n", customerDetails.name);
        printf("Account Type     : %s\n", accountDetails.acc_type);
        printf("Initial Deposite : %.2f\n", accountDetails.initial_amt);

        printf("\nPress 1 to confirm and 2 to Edit : ");
        scanf("%d", &op);
        getchar();
        if(op == 1) {
            accountDetails.balance = accountDetails.initial_amt;

            FILE *fp,*facc;

            fp = fopen("accounts_details.txt", "a");
            facc = fopen("accounts.txt", "a");

            if(fp == NULL) {
                printf("File not found!\n");
                return;
            }
            if(facc == NULL) {
                printf("File not found!\n");
                return;
            }

            fprintf(fp, "===============================\n");
            fprintf(fp, "Account Number     : %lld\n", accountDetails.acc_number);
            fprintf(fp, "Name               : %s\n", customerDetails.name);
            fprintf(fp, "Father Name        : %s", customerDetails.father_name);
            fprintf(fp, "DOB                : %s", customerDetails.DOB);
            fprintf(fp, "Gender             : %s", customerDetails.gender);
            fprintf(fp, "Mobile Number      : %s \n", customerDetails.pNumber);
            fprintf(fp, "Email              : %s\n", customerDetails.Email);
            fprintf(fp, "Address            : %s", customerDetails.address);

            fprintf(fp, "Account Type       : %s\n", accountDetails.acc_type);
            fprintf(fp, "Initial Deposit    : %.2f\n", accountDetails.initial_amt);
            fprintf(fp, "Nominee Name       : %s", accountDetails.nominee_name);
            fprintf(fp, "Nominee Relation   : %s", accountDetails.nominee_relation);

            fprintf(fp, "Password           : %s\n", securityDetails.set_password);
            fprintf(fp, "Security Question  : %s", securityDetails.security_que);
                time_t t;
                struct tm *current;
                t = time(NULL);
                current = localtime(&t);
            fprintf(fp, "Created Date       : %02d-%02d-%d\n",
            current->tm_mday,
            current->tm_mon + 1,
            current->tm_year + 1900);

            fprintf(fp, "Created Time       : %02d:%02d:%02d\n",
            current->tm_hour,
            current->tm_min,
            current->tm_sec);

            fprintf(facc, "A/C No. : %lld | Name : %s | Balance : %.2f | A/C Type : %s | Password : %s | Status : ACTIVE\n",accountDetails.acc_number,customerDetails.name,accountDetails.balance,accountDetails.acc_type,securityDetails.set_password);
            fclose(fp);
            fclose(facc);

            printf("Account Created Successfully!\n");
            printf("Data Saved In File Successfully!\n");

            break;
        }
        else if(op == 2) {

            printf("Editing Details...\n\n");
            continue;
        }

        else {

            printf("Invalid choice\n");
        }
    }
    
}
void authenticateCustomer(){
    int op;
    do {
        printf("\n====================================================\n");
        printf("\t\tCUSTOMER");
        printf("\n====================================================\n");
        printf("\n1. User Login\n");
        printf("2. Create New A/C\n");
        printf("3. BACK\n");
        printf("\nEnter your choise : ");
        scanf("%d",&op);
        switch(op) {
            case 1:
            printf("\n====================================================\n");
            printf("\t\tUSER LOGIN");
            printf("\n====================================================\n");
            userlogin();
            break;
            case 2:
            printf("\n====================================================\n");
            printf("\t\tCREATE NEW A/C");
            printf("\n====================================================\n");
            createBankAccount();
            break;
            case 3:
            return;
            default :
            printf("INVALID INPUTE !!\n");
        }
    }while(op !=3);
}