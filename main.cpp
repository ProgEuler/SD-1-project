#include <iostream>
using namespace std;

char name[20];
int dip_amt, amt = 10000, acc_no;

void menu();
void welcome();
void deposit();
void withdraw();
void check_balance();


int main(){
    welcome();
    menu();
}
void menu(){
    int choice;
    cout<<"1. Check Balance"<<endl;
    cout<<"2. Deposit"<<endl;
    cout<<"3. Withdraw"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    switch(choice){
        case 1:
            cout<<"Your balance is: "<<amt<<endl;
            break;
        case 2:
            cout<<"Enter the amount you want to deposit: ";
            cin>>dip_amt;
            amt += dip_amt;
            cout<<"Amount deposited successfully"<<endl;
            break;
        case 3:
            cout<<"Enter the amount you want to withdraw: ";
            cin>>dip_amt;
            if(dip_amt > amt){
                cout<<"Insufficient balance"<<endl;
            }
            else{
                amt -= dip_amt;
                cout<<"Amount withdrawn successfully"<<endl;
            }
            break;
        case 4:
            cout<<"Thank you for using our service"<<endl;
            break;
        default:
            cout<<"Invalid choice"<<endl;
    }
}

void welcome(){
    cout<<"\n\n\n"<<endl;
    cout<<"\t\t\t\t==== WELCOME TO NUBPay ====" << endl;
    cout<<"\t\t\t A Organized Payment system for NUB Students " << endl;
    cout<<"\n\n\n"<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------" << endl;
    cout<<"\t\t\t\t\t\t\t\t DEVELOPED BY Saruf, Jakaria, Shihab, Nur" << endl;


    cout<<"\n\n\n"<<endl;
    cout<<"Enter your name: ";
    cin>>name;
    cout<<"Enter your account number: ";
    cin>>acc_no;
    cout<<"Enter the amount you want to deposit: ";
    cin>>dip_amt;
    amt += dip_amt;
    cout<<"Amount deposited successfully"<<endl;
}
void deposit(){
    cout<<"Enter the amount you want to deposit: ";
    cin>>dip_amt;
    amt += dip_amt;
    cout<<"Amount deposited successfully"<<endl;
}
void withdraw(){
    cout<<"Enter the amount you want to withdraw: ";
    cin>>dip_amt;
    if(dip_amt > amt){
        cout<<"Insufficient balance"<<endl;
    }
    else{
        amt -= dip_amt;
        cout<<"Amount withdrawn successfully"<<endl;
    }
}
void check_balance(){
    cout<<"Your balance is: "<<amt<<endl;
}
