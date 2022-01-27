//In this program i have implemented "Linked List" to perform Various Task.


#include<iostream>  //This header file provides basic I/O operations for program
#include<stdlib.h> //This header file includes functions involving memory allocation, process control,
                   // conversion and others.
#include<string.h> //This header file includes string functions.
using namespace std;

/* This is the structure which provides a template for node of Linked List. It shows a representation of
    a food item in menu. It contains different attributes of node such as it's food name, quantity, price,
    data, pointer to next node and pointer to previous node. Here in order to perform various task of admin 
    as well as customer using one single structure, I have created one single struct. Catering to purpose of
    menu item as well as customer's order.
*/
struct node{
    string foodName;
    int quantity;
    float price;
    int data;
    struct node *next;
};

//global struct pointers which are used throughout the program to create linked list and maintain it.
struct node *headc = NULL, *newnode, *tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

//This function prints the options available for admin to choose 
void adminMenu(){
    cout<<"\n\t\t\t\t\t\t\t1. View total sales\n";
    cout<<"\t\t\t\t\t\t\t2. Add new items in the order menu\n";
    cout<<"\t\t\t\t\t\t\t3. Delete items from the order menu\n";
    cout<<"\t\t\t\t\t\t\t4. Display order menu\n";
    cout<<"\t\t\t\t\t\t\t5. Back to Main Menu\n\n";
    cout<<"\t\t\t\t\t\t\t   Enter Your Choice --->";
}

//This function prints the options available for customer to choose.
void customerMenu(){
    cout<<"\n\t\t\t\t\t\t\t1. Place your order\n";
    cout<<"\t\t\t\t\t\t\t2. View your ordered items\n";
    cout<<"\t\t\t\t\t\t\t3. Delete an item from order\n";
    cout<<"\t\t\t\t\t\t\t4. Display final bill\n";
    cout<<"\t\t\t\t\t\t\t5. Back to Main Menu\n\n";
    cout<<"\t\t\t\t\t\t\t   Enter Your Choice --->";
}

//This function creates a node for admin's Linked List
node* createAdmin( node *head, int data, string foodName, float price){
    node *newnode = new node();

    newnode->data = data;
    newnode->price = price;
    newnode->quantity = 0;
    newnode->foodName = foodName;
    newnode->next = NULL;

    node *temp = head;

    if(temp==NULL) heada = taila =newnode;
    else{
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newnode;
        taila = newnode;
    }
    return heada;
}

//This function creates a node for customer's Linked List
node* createCustomer(node *head, int data, int quantity){
    node *newnode = new node();

    node *temp1 = heada;
    int flag = 0;
    while(temp1!=NULL){
        if(temp1->data==data){
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }
    if(flag==1){
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode->quantity = quantity;
        newnode->foodName = temp1->foodName;
        newnode->next = NULL;
        node *temp = head;

        if(temp==NULL) headc = tailc = newnode;
        else{
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = newnode;
            tailc = newnode;
        }
    }else {
        cout<<"\n\t\t\t\t\t\t\tSorry, This item is not present in the menu!\n";
    }
    return headc;
}

void displayList(node *head){
    node *temp1 = head;
    if(temp1==NULL){
        cout<<"\n\t\t\t\t\t\t\t\tList is empty!!\n\n";
    }else{
        cout<<"\n";
        while(temp1!=NULL){
            if(temp1->quantity==0) cout<<"\t\t\t\t\t\t\t||"<<temp1->data<<"||\t"<<temp1->foodName<<"\t\t"<<temp1->price<<"\n";
            else cout<<"\t\t\t\t\t\t\t||"<<temp1->data<<"||\t"<<temp1->foodName<<"\t\t"<<temp1->quantity<<"|\t\t"<<temp1->price<<"\n";
            temp1 = temp1->next;
        }
        cout<<"\n";
    }
}

//This function maintains the total value of sales done by maintaining another Linked List which
//keeps a track of total sales made to each customer represented by each node
node* totalSales(int data, int quantity){
    node *newnode = new node();
    int flag = 0;
    node *temp1 = heada;
    while(temp1->data!=data){
        temp1 = temp1->next;
    }
    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode->quantity = quantity;
    newnode->foodName = temp1->foodName;
    newnode->next = NULL;

    node *temp = head_s;
    if(temp==NULL) head_s = newnode;
    else{
        while(temp->next!=NULL){
            if(temp->data==data){
                flag = 1;
                break;
            }
            temp = temp->next;
        }
        if(flag==1){
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }else{
            temp->next = newnode;
        }
    }
    return head_s;
}

//This function performs task of calculating total sales for each customer
void calculateTotalSales(){
    node *temp = headc;
    while(temp!=NULL){
        head_s = totalSales(temp->data, temp->quantity);
        temp = temp->next;
    }
}

//This function performs the task of deleting the data from Linked List whose respective 
//head pointer is passed.
//Here, data to be deleted is passed as a parameter.

node *deleteData(int data, node *head, node *tail){
    if(head==NULL){
        cout<<"\n\t\t\t\t\t\t\tList is empty\n";
    }else{
        node *temp;
        if(data==head->data){
            temp = head;
            head = head->next;
            free(temp);
        }else if(data==tail->data){
            temp = tail;
            tail->next = NULL;
            free(temp);
        }else{
            temp = head;
            node *temp1 = temp;
            while(data!=temp->data){
                temp1 = temp;
                temp = temp->next;
            }
            temp1->next = temp->next;
            free(temp);
        }
    }
    return head;
}

//This function performs the task of deleting food item from admin's Linked List.
int deleteAdmin(){
    cout<<"\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin>>num;

    node *temp = heada;
    while(temp!=NULL){
        if(temp->data==num){
            heada = deleteData(num, heada, taila);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

//This function performs the task of deleting food from customer's Linked List i.e. customer's 
//ordered food item
int deleteCustomer(){
    cout<<"\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin>>num;
    node *temp = headc;
    while(temp!=NULL){
        if(temp->data==num){
            headc = deleteData(num, headc, tailc);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

//This function displays the total bill of food items ordered by customer.
void displayBill(){
    displayList(headc);
    node *temp = headc;
    float total_price = 0;
    while(temp!=NULL){
        total_price +=(temp->price);
        temp = temp->next;
    }
    cout<<"\t\t\t\t\t\t\tTotal price: "<<total_price<<"\n";
}

//This function performs the task of deleting entire Linked List.
node *deleteList(node *head){
    if(head==NULL){
        return NULL;
    }else{
        node *n, *temp = head;
        while(temp!=NULL){
            n = temp->next;
            free(temp);
            temp = n;
        }
        head = NULL;
    }
    return head;
}

//This function opens up the admin section and provides it's interface 
//and functionalities
void admin(){
    cout<<"\n\t\t\t\t\t   .......................................................\n";
    cout<<"\t\t\t\t\t\t\t       ADMIN SECTION\n";
    cout<<"\t\t\t\t\t   .......................................................\n";
    while(1){
        adminMenu();

        int opt;
        cin>>opt;
        
        if(opt==5) break;

        //switch-case block which executes according to the option selected by the user.
        switch(opt){
            case 1:
                {            
                    displayList(head_s);
                    break;
                }
            case 2:
                {
                    cout<<"\n\t\t\t\t\t\t\tEnter serial no. of the food item: ";
                    int num;
                    int flag = 0;
                    char name[50];
                    float price;
                    cin>>num;
                    node *temp = heada;
                    while(temp!=NULL){
                        if(temp->data==num){
                            cout<<"\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n";
                            flag = 1;
                            break;
                        }
                        temp = temp->next;
                    }
                    if(flag==1){
                        break;
                    }
                    cout<<"\t\t\t\t\t\t\tEnter food item name: ";
                    cin>>name;
                    cout<<"\t\t\t\t\t\t\tEnter price: ";
                    cin>>price;
                    heada = createAdmin(heada, num, name, price);
                    cout<<"\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n";
                    break;
                }
            case 3:
                {
                    if(deleteAdmin()){
                        cout<<"\n\t\t\t\t\t\t### Updated list of food items menu ###\n";
                        displayList(heada);
                    }else{
                        cout<<"\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n\n";
                    }
                    break;
                }
            case 4:
                {
                    cout<<"\n\t\t\t\t\t\t\t   ### Order menu ###\n";
                    displayList(heada);
                    break;
                }
            default:
                cout<<"\n\t\t\t\t\t\tWrong Input !! Please choose valid option\n";
                break;
        }
    }  
}

//This function opens up the customer section and provides it's interface and functionalities
void customer(){
    int flag=0, j=1;
    char ch;
    cout<<"\n\t\t\t\t\t  ...................................................\n";
    cout<<"\t\t\t\t\t\t\t     CUSTOMER SECTION\n";
    cout<<"\t\t\t\t\t  ...................................................\n";
    while(1){
        customerMenu(); //prints customer functionalities list
        int opt;
        cin>>opt;

        if(opt==5) break;
        switch(opt){
            case 1:
                {
                    displayList(heada);
                    cout<<"\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ";
                    int n;
                    cin>>n;
                    cout<<"\t\t\t\t\t\tEnter quantity: ";
                    int quantity;
                    cin>>quantity;
                    headc = createCustomer(headc, n, quantity);
                    break;
                }
            case 2:
                {
                    cout<<"\n\t\t\t\t\t\t\t  ### List of ordered items  ###\n";
                    displayList(headc);
                    break;
                }
            case 3:
                {
                    if(deleteCustomer()){
                        cout<<"\n\t\t\t\t\t\t### Updated list of your ordered food items  ###\n";
                        displayList(headc);
                    }else{
                        cout<<"\n\t\t\t\t\t\tFood item with ggiven serial number doesn't exist!!\n";
                    }
                    break;
                }
            case 4:
                {
                    calculateTotalSales();
                    cout<<"\n\t\t\t\t\t\t\t  ### Final Bill ###\n";
                    displayBill();
                    headc = deleteList(headc);
                    cout<<"\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
                    fflush(stdin);
                    ch = fgetc(stdin);
                    flag = 1;
                    break;
                }
            default: 
                cout<<"\n\t\t\t\t\t\tWrong Input !! Please choose valid option\n";
                break;
        }
        if(flag==1) break;
    }
}

//This function prints the welcome interface and opens the main menu where you can select the option where you want to go.
void mainMenu(){
    cout<<"\n                                  ..........................................................................\n";
    cout<<"                                                      WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n";
    cout<<"                                  ..........................................................................\n\n\n";
    cout<<"\t\t\t\t\t\t\t1. ADMIN SECTION--> \n";
    cout<<"\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n";
    cout<<"\t\t\t\t\t\t\t3. Exit--> \n\n";
    cout<<"\t\t\t\t\t\t\tEnter Your Choice -->";
}

//From here the actual program execution begins
int main(){
    //Here we have initialized admin's Linked List i.e. Food Menu with 5 items
    heada = createAdmin(heada, 1, "Hot and Sour Soup", 100);
    heada = createAdmin(heada, 2, "Manchow Soup", 200);
    heada = createAdmin(heada, 3, "Manchurian Noodles", 150);
    heada = createAdmin(heada, 4, "Fried Rice", 180);
    heada = createAdmin(heada, 5, "Hakka Noodles", 80);

    while(1){
        mainMenu();
        int choice;
        cin>>choice; //choice of user

        if(choice==3){
            cout<<"\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n";
            break;
        }

        //switch-case block which executes according to the option selected by user
        switch(choice){
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;
            default: 
                cout<<"\n\t\t\t\t\t\tWrong Input !! Please choose valid option\n";
                break;
        }
    }
}