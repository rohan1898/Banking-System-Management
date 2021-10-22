#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


class Bank
{
    
    char Name_[50], accountType_[50],address_[100];
    long accountNumber_;
    float balanceAmount_;
    
public:
    Bank() {}
    void DepositAmount();
    void WithdrawAmount(ofstream &TransactionDb);
    void OpenAccount();
    void ShowAccount();
    int SearchAccount(int);

    
};
void Bank::OpenAccount()
{
  string AccountFile = "AccountFiles.txt";
  ofstream CustomerDb(AccountFile);
  
    cout << "Enter your Full Name: ";
    cin.ignore();
    cin.getline(Name_, 50);
    CustomerDb<<Name_<<"\t";
    cout<< "Enter your Full address:  ";
    
    cin.getline(address_,99);
    CustomerDb<<address_<<"\t";
    cout << "Account Type (Saving/current) :";
    cin.getline(accountType_,50);
    CustomerDb<<accountType_<<"\t";
    cout << "Enter Account Number: ";
    cin >> accountNumber_;
    CustomerDb<<accountNumber_<<"\t";
    cout << "Enter Balance: ";
    cin >> balanceAmount_;
    CustomerDb<<balanceAmount_<<"\t";
    CustomerDb<<"\n";
    
    

}


void Bank::ShowAccount()
{
   string AccountFile = "AccountFiles.txt";
    ifstream readCustomerDb(AccountFile);


   while(readCustomerDb)
    {
      readCustomerDb>>Name_;
      readCustomerDb>>address_;
      readCustomerDb>>accountType_;
      readCustomerDb>>balanceAmount_;

      cout << "Name: " << Name_ << endl;
      cout << "Account Type: " << accountType_ << endl;
      cout << "Balance: " << balanceAmount_ << endl;
      cout << "Address: "<<address_<<endl; 
    }
    readCustomerDb.close();
}

void Bank::DepositAmount()
{

    float amt;
    cout << "Enter amount you want to deposit: ";
    cin >> amt;

    balanceAmount_ = balanceAmount_ + amt;
    cout << "\nAmount successfully deposited.\n";
}


void Bank::WithdrawAmount(ofstream & BankTransactionDb)
{
    float amt;
    cout << "Enter Amount you want to withdraw: ";
    cin >> amt;
    BankTransactionDb<<amt;

    if (amt <= balanceAmount_)
    {
        balanceAmount_ = balanceAmount_ - amt;
        cout << "\nAmount successfully withdrawn.\n";
    }
    else
    {
        cout << "\nYour balance is not sufficient for this request.\n";
        cout << "Please add money before proceeding." << endl;
    }
}


int Bank::SearchAccount(int a)
{
    if (accountNumber_ == a)
        return 1;
    return 0;
}

int main()
{
  
    int size;

    string BankTransaction = "BankTransaction.txt";
    ofstream BankTransactionDb(BankTransaction);
cout << "\nHow many bank accounts you want to create:\n";
    cin >> size;

    
    Bank b[100];

    
    for (int i = 0; i < size; i++)
    {
        cout << "\nEnter details of account :" << i + 1 << ":\n"
             << endl;
        b[i].OpenAccount();
        cout << "\nYour Account created successfully.\n";
        
    }
    
    int found = 0, choice, i;
    long accNum;

    do
    {
       cout << "\n===========================";
        cout << "\n  Welcome to SBI Bank ";
        cout << "\n===========================\n\n";
  
        cout<<"Choose  to perform:"<< endl;
        cout << "1:Deposit amount\n2:Withdraw amount\n3:Check Balance\n4:Open new account\n5:All Bank account holders\n6:Account added at the end\n7:Exit" << endl;

        // user input
        cout << "\nPlease input your choice";
        cin >> choice;

        switch (choice)
        {
            case 1:
                
                cout << "Enter your VALID account number ";
                cin >> accNum;

                for (i = 0; i < size; i++)
                {
                    found = b[i].SearchAccount(accNum);
                    if (found)
                    {
                        b[i].DepositAmount();
                        break;
                    }
                }
                if (!found)
                    cout << "ERROR: Account Not Found!!" << endl;

                break;

            case 2:
      
                cout << "Enter your account number: ";
                cin >> accNum;

                for (i = 0; i < size; i++)
                {
                    found = b[i].SearchAccount(accNum);
                    if (found)
                    { 
                        BankTransactionDb<<accNum<<'\t';
                        b[i].WithdrawAmount(BankTransactionDb);
                        break;
                    }
                }
                if (!found)
                    cout << "ERROR: Account Not Found!!" << endl;

                break;

            case 3:
            
                cout << "Enter your account number: ";
                cin >> accNum;

                for (i = 0; i < size; i++)
                {
                    found = b[i].SearchAccount(accNum);
                    if (found)
                    {
                        cout << endl;
                        b[i].ShowAccount();
                        break;
                    }
                }
                if (!found)
                    cout << "ERROR: Account Not Found!!" << endl;

                break;

            case 4:
            
                b[size++].OpenAccount();
                cout << "\nAccount created successfully.\n";

                break;
            case 5:
                cout<<"\nThe list of bank account holders:\n";
                  
                    cout<<"\n";
                    b[i].ShowAccount();
                    cout<<"\n";
                  
                  break;
            case 6:
                cout<<"\nLast Account Added:\n";
                b[size-1].ShowAccount();
                cout<<'\n';
                break;

            case 7:
                
                cout << "\nThank you for using this bank service\n"<< endl;

                break;

            default:
                cout << "Error: Please type the correct number" << endl;
        }
    } while (choice != 7);
  BankTransactionDb.close();

    return 0;
}