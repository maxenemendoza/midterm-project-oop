#include <iostream>
#include <string>
#include <cctype> // for to upper
#include <limits> // for numeric limits
#include <iomanip> // for table
using namespace std;

struct Item { // stores item details
    string itemID;
    string itemName;
    int itemQuantity;
    double itemPrice;
    string itemCategory;
};

class Base {
    public:
    // abstraction
    virtual void addItem() = 0;
    virtual void updateItem() = 0; // quantity, price
    virtual void removeItem() = 0;
    virtual void displayItem() = 0; // clothing, electronics, entertainment
    virtual void displayAllItem() = 0;
    virtual void searchItem() = 0;
    virtual void sortItem() = 0; // quantity, price, ascending, descending
    virtual void displayLowStock() = 0;
};

class Inventory : public Base {
    private:
    string categoryChoice;

    static const int itemMax = 100; // max items per category
    int itemCount; 

    // arrays to store items
    Item clothingItem [itemMax]; 
    Item electronicsItem [itemMax]; 
    Item entertainmentItem [itemMax]; 
    Item allItem [itemMax]; 

    // counts items per category
    int clothingCount;
    int electronicsCount;
    int entertainmentCount;

    public:
    // set counters to 0
    Inventory(): itemCount(0), clothingCount(0), electronicsCount(0), entertainmentCount(0) {} // default constructor 

    void addItem() override { // abstraction
        system("cls");
        cout << "ADD ITEM" << endl << endl;

        // check if there is room for new items
        if (itemCount >= itemMax){
            cout << "Inventory is full!" << endl;
            system("pause");
            return;
        }

        // display if inventory is not full
        cout << "Item Category" << endl << endl;
        cout << "Category 1: Clothing" << endl;
        cout << "Category 2: Electronics" << endl;
        cout << "Category 3: Entertainment" << endl << endl;
        cout << "Note: Type the category name." << endl;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        cout << "Enter choice: ";
        getline (cin, categoryChoice);

        if (categoryChoice.empty()) { // check for empty string input
            cout << endl; 
            cout << "Category cannot be empty!" << endl;
            system("pause");
            return;
        }

        for (char &c : categoryChoice) {
            c = toupper(c); // convert input to uppercase 
        }
        
        // check for valid input for category
        if (categoryChoice != "CLOTHING" && categoryChoice != "ELECTRONICS" && categoryChoice != "ENTERTAINMENT"){
            cout << endl;
            cout << "Category " << categoryChoice << " does not exist!" << endl;
            system("pause");
            return;
        }

        Item newItem; // structName objectName
        system("cls");
        cout << "ADD NEW ITEM TO " << categoryChoice << " CATEGORY" << endl << endl;
        cout << "Item Details: " << endl;

        bool validateItemID = false;
        while (!validateItemID){
            cout << "Enter Item ID: ";
            getline (cin, newItem.itemID);

            if (newItem.itemID.empty()) { // check for empty string input
                cout << "Item ID cannot be empty!" << endl << endl;
            } 
            else { // ensure no item ID dupes
                bool duplicateID = false;
                for (int i=0; i<itemCount; i++){
                    if (allItem[i].itemID == newItem.itemID){
                        cout << "Item ID already exists! Please enter a new Item ID." << endl << endl;
                        duplicateID = true;
                        break;
                    }
                }
                if (!duplicateID){
                    validateItemID = true;
                }
            }
        } 

        bool validateItemName = false;
        while (!validateItemName){
            cout << "Enter Item Name: ";
            getline (cin, newItem.itemName);

            if (newItem.itemName.empty()) { // check for empty string input
                cout << "Item Name cannot be empty!" << endl << endl;
            } 
            else {
                validateItemName = true;
            }
        } 

        bool validateItemQuantity = false;
        while (!validateItemQuantity){
            cout << "Enter Item Quantity: ";
            cin >> newItem.itemQuantity;

            if (cin.fail() || newItem.itemQuantity <= 0) {  // validate for numeric input
                cin.clear(); // clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Please enter a valid positive number for Item Quantity." << endl << endl; 
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                validateItemQuantity = true;
            }
        } 

        bool validateItemPrice = false;
        while (!validateItemPrice){
            cout << "Enter Item Price: ";
            cin >> newItem.itemPrice;

            if (cin.fail() || newItem.itemPrice <= 0) {  // validate for numeric input
                cin.clear(); // clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Please enter a valid positive number for Item Price." << endl << endl;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
                validateItemPrice = true;
            }
        } 
        
        if (categoryChoice == "CLOTHING"){
            if (clothingCount < itemMax){
                newItem.itemCategory = "CLOTHING"; // set category that item belongs to
                clothingItem[clothingCount++] = newItem; // add to clothing category/array
                allItem[itemCount++] = newItem; // add to overall item count/array

                cout << endl;
                cout << "Item added successfully to CLOTHING inventory!" << endl;
                system("pause");
            } 
            else {
                cout << endl;
                cout << "CLOTHING inventory is full!" << endl;
                system("pause");
            }
        }
        else if (categoryChoice == "ELECTRONICS"){
            if (electronicsCount < itemMax){
                newItem.itemCategory = "ELECTRONICS"; // set category that item belongs to
                electronicsItem[electronicsCount++] = newItem; // add to electronics category/array
                allItem[itemCount++] = newItem; // add to overall item count/array
                
                cout << endl;
                cout << "Item added successfully to ELECTRONICS inventory!" << endl;
                system("pause");
            }
            else {
                cout << endl;
                cout << "ELECTRONICS inventory is full!" << endl;
                system("pause");
            }
        }
        else if (categoryChoice == "ENTERTAINMENT"){
            if (entertainmentCount < itemMax){
                newItem.itemCategory = "ENTERTAINMENT"; // set category that item belongs to
                entertainmentItem[entertainmentCount++] = newItem; // add to entertainment category/array
                allItem[itemCount++] = newItem; // add to overall item count/array

                cout << endl;
                cout << "Item added successfully to ENTERTAINMENT inventory!" << endl;
                system("pause");
            }
            else {
                cout << endl;
                cout << "ENTERTAINMENT inventory is full!" << endl;
                system("pause");
            }
        }
    }

    void updateItem() override {
        string searchItemID;
        system("cls");
        cout << "UPDATE ITEM" << endl << endl;

        cout << "Enter Item ID: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
        getline (cin, searchItemID);

        bool itemFound = false; 

        // find item in array for all items regardless of category
        for (int i=0; i<itemCount; i++){
            if (allItem[i].itemID == searchItemID){
                itemFound = true;

                cout << "Details for Item " << searchItemID << ": " << endl << endl;
                cout << "Item ID: " << allItem[i].itemID << endl;
                cout << "Item Name: " << allItem[i].itemName << endl;
                cout << "Item Quantity: " << allItem[i].itemQuantity << endl;
                cout << "Item Price: " << allItem[i].itemPrice << endl << endl;

                int updateChoice;
                cout << "What do you want to update?" << endl;
                cout << "1 - Quantity" << endl;
                cout << "2 - Price" << endl << endl;

                cout << "Enter choice: ";
                cin >> updateChoice;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

                if (updateChoice == 1){ // update quantity
                    system("cls");
                    cout << "UPDATE ITEM " << searchItemID << " BY QUANTITY" << endl << endl;
                    int oldQuantity = allItem[i].itemQuantity;

                    cout << "Enter new Item Quantity: ";
                    cin >> allItem[i].itemQuantity;

                    while (cin.fail() || allItem[i].itemQuantity <= 0) {  // validate for numeric input
                        cin.clear(); // clear error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                        cout << "Please enter a valid positive number for Item Quantity: ";
                        cin >> allItem[i].itemQuantity;
                    }
                    cout << endl;
                    cout << "Quantity of Item " << allItem[i].itemName 
                     << " is updated from " << oldQuantity 
                     << " to " << allItem[i].itemQuantity << endl;
                }
                else if (updateChoice == 2){ // update price
                    system("cls");
                    cout << "UPDATE ITEM " << searchItemID << " BY PRICE" << endl << endl;
                    int oldPrice = allItem[i].itemPrice;

                    cout << "Enter new Item Price: ";
                    cin >> allItem[i].itemPrice;

                    while (cin.fail() || allItem[i].itemPrice <= 0) {  // validate for numeric input
                        cin.clear(); // clear error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                        cout << "Please enter a valid positive number for Item Price: ";
                        cin >> allItem[i].itemPrice;
                    }
                    cout << endl;
                    cout << "Price of Item " << allItem[i].itemName 
                     << " is updated from " << oldPrice 
                     << " to " << allItem[i].itemPrice << endl;
                }
                else {
                    cout << endl;
                    cout << "Invalid input! Please select either 1 or 2 only." << endl;
                }
                break;
            }
        }
        if (!itemFound) {
                cout << endl;
                cout << "Item not found!" << endl;
        }
        cout << endl;
        system("pause");
    }

    void removeItem() override {
        string searchItemID;
        system("cls");
        cout << "REMOVE ITEM" << endl << endl;

        cout << "Enter Item ID: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
        getline (cin, searchItemID);
        cout << endl;

        bool itemFound = false;

        for (int i=0; i<itemCount; i++){
            if (allItem[i].itemID == searchItemID){
                itemFound = true;

                cout << "Details for Item " << searchItemID << ": " << endl << endl;
                cout << "Item ID: " << allItem[i].itemID << endl;
                cout << "Item Name: " << allItem[i].itemName << endl;
                cout << "Item Quantity: " << allItem[i].itemQuantity << endl;
                cout << "Item Price: " << allItem[i].itemPrice << endl << endl;

                string removedItemName = allItem[i].itemName; // store in temp var before shift

                // remove from category array
                if (allItem[i].itemCategory == "CLOTHING"){
                    for (int k=0; k<clothingCount; k++){
                        if (clothingItem[k].itemID == searchItemID){
                            // shift items left in clothing category
                            for (int m=k; m<clothingCount-1; m++) {
                                clothingItem[m] = clothingItem[m+1];
                            }
                            clothingCount--;
                            cout << "Item " << removedItemName << " has been removed from the CLOTHING inventory." << endl;
                            break;
                        }
                    }
                }
                else if (allItem[i].itemCategory == "ELECTRONICS"){
                    for (int k=0; k<electronicsCount; k++){
                        if (electronicsItem[k].itemID == searchItemID){
                            // shift items left in electronics category
                            for (int m=k; m<electronicsCount-1; m++) {
                                electronicsItem[m] = electronicsItem[m+1];
                            }
                            electronicsCount--;
                            cout << "Item " << removedItemName << " has also been removed from the ELECTRONICS inventory." << endl;
                            break;
                        }
                    }
                }
                else if (allItem[i].itemCategory == "ENTERTAINMENT"){
                    for (int k=0; k<entertainmentCount; k++){
                        if (entertainmentItem[k].itemID == searchItemID){
                            // shift items left in entertainment category
                            for (int m=k; m<entertainmentCount-1; m++) {
                                entertainmentItem[m] = entertainmentItem[m+1];
                            }
                            entertainmentCount--;
                            cout << "Item " << removedItemName << " has been removed from the ENTERTAINMENT inventory." << endl;
                            break;
                        }
                    }
                }
                // remove from overall array
                for (int j=i; j<itemCount-1; j++) { // shift items to remove found item
                    allItem[j] = allItem[j+1]; // shift items left
                }

                itemCount--;
                cout << "Item " << removedItemName << " has also been removed from the OVERALL inventory." << endl;
                break;
            }
        }
        if (!itemFound){
            cout << "Item not found!" << endl;
        }
        cout << endl;
        system("pause");
    }

    void displayItem() override { 
    string searchItemCategory;
    system("cls");
    cout << "DISPLAY ITEM BY CATEGORY" << endl << endl;

    cout << "Enter Item Category: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
    getline (cin, searchItemCategory);

    // convert input category to uppercase
    for (char &c : searchItemCategory) {
        c = toupper(c);
    }

    bool itemFoundInCategory = false;

    // loop thru allItem[] to display items from searched category
    for (int i = 0; i < itemCount; i++) {
        if (allItem[i].itemCategory == searchItemCategory) {
            if (!itemFoundInCategory){ 
                cout << endl;
                cout << "Items in " << searchItemCategory << " Category: " << endl << endl;
                cout << setw(20) << left << "ID"
                     << setw(20) << left << "Name"
                     << setw(20) << left << "Quantity"
                     << setw(20) << left << "Price" << endl;
            }

            cout << setw(20) << left << allItem[i].itemID
                 << setw(20) << left << allItem[i].itemName
                 << setw(20) << left << allItem[i].itemQuantity
                 << setw(20) << left << allItem[i].itemPrice << endl;
            itemFoundInCategory = true;
        }
    }

    if (!itemFoundInCategory) {
        cout << endl;
        cout << "No items found in " << searchItemCategory << " category!" << endl;
    }
    cout << endl;
    system("pause");
}

    void displayAllItem() override { 
        system("cls");
        cout << "DISPLAY ALL ITEMS" << endl << endl;

        cout << setw(20) << left << "ID"
             << setw(20) << left << "Name"
             << setw(20) << left << "Quantity"
             << setw(20) << left << "Price"
             << setw(20) << left << "Category" << endl;
        
        for (int i=0; i<itemCount; i++){
            cout << setw(20) << left << allItem[i].itemID
                 << setw(20) << left << allItem[i].itemName
                 << setw(20) << left << allItem[i].itemQuantity
                 << setw(20) << left << allItem[i].itemPrice
                 << setw(20) << left << allItem[i].itemCategory << endl;
        }
        cout << endl;
        system("pause");
    }

    void searchItem() override {
        string searchItemID;
        system("cls");
        cout << "SEARCH ITEM" << endl << endl;

        cout << "Enter Item ID: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
        getline (cin, searchItemID);

        bool itemFound = false;

        for (int i=0; i<itemCount; i++){
            if (allItem[i].itemID == searchItemID){
                if (!itemFound){
                    cout << endl;
                    cout << setw(20) << left << "ID"
                         << setw(20) << left << "Name"
                         << setw(20) << left << "Quantity"
                         << setw(20) << left << "Price"
                         << setw(20) << left << "Category" << endl;
                }
                cout << setw(20) << left << allItem[i].itemID
                     << setw(20) << left << allItem[i].itemName
                     << setw(20) << left << allItem[i].itemQuantity
                     << setw(20) << left << allItem[i].itemPrice
                     << setw(20) << left << allItem[i].itemCategory << endl;

                itemFound = true;
                break;
            }
        }
        if (!itemFound) {
                cout << endl;
                cout << "Item not found!" << endl;
            }
        cout << endl;
        system("pause");
    }

    void sortItem() override {
        int sortChoice;
        int sortOrderChoice;
        system("cls");
        cout << "SORT ITEMS" << endl << endl;
        cout << "How would you like to sort your items?" << endl;
        cout << "1 - Sort by Quantity" << endl;
        cout << "2 - Sort by Price" << endl << endl;

        cout << "Enter choice: ";
        cin >> sortChoice;

        if (sortChoice == 1){
            system("cls");
            cout << "SORT BY QUANTITY" << endl << endl;
            cout << "How would you like to sort your items?" << endl;
            cout << "1 - Ascending" << endl;
            cout << "2 - Descending" << endl << endl;

            cout << "Enter choice: ";
            cin >> sortOrderChoice;

            bool itemSwapped = false;

            // bubble sort (quantity)
            system("cls");
            for (int i=0; i<itemCount; i++){
                itemSwapped = false;
                for (int j=0; j<itemCount-1; j++){
                    if ((sortOrderChoice == 1 && allItem[j].itemQuantity > allItem[j+1].itemQuantity) || 
                        (sortOrderChoice == 2 && allItem[j+1].itemQuantity > allItem[j].itemQuantity)){
                            Item temp = allItem[j];
                            allItem[j] = allItem[j+1];
                            allItem[j+1] = temp;
                            itemSwapped = true;
                        }
                }
                if (!itemSwapped){
                    break;
                }
            }
        }
        else if (sortChoice == 2){
            system("cls");
            cout << "SORT BY PRICE" << endl << endl;
            cout << "How would you like to sort your items?" << endl;
            cout << "1 - Ascending" << endl;
            cout << "2 - Descending" << endl << endl;

            cout << "Enter choice: ";
            cin >> sortOrderChoice;

            bool itemSwapped = false;

            // bubble sort (price)
            for (int i=0; i<itemCount; i++){
                itemSwapped = false;
                for (int j=0; j<itemCount-1; j++){
                    if ((sortOrderChoice == 1 && allItem[j].itemPrice > allItem[j+1].itemPrice) || 
                        (sortOrderChoice == 2 && allItem[j+1].itemPrice > allItem[j].itemPrice)){
                            Item temp = allItem[j];
                            allItem[j] = allItem[j+1];
                            allItem[j+1] = temp;
                            itemSwapped = true;
                        }
                }
                if (!itemSwapped){
                    break;
                }
            }
        }
        else {
            cout << "Invalid input!" << endl;
            return; 
        }

        cout << setw(20) << left << "ID"
             << setw(20) << left << "Name"
             << setw(20) << left << "Quantity"
             << setw(20) << left << "Price"
             << setw(20) << left << "Category" << endl;
        
        for (int i=0; i<itemCount; i++){
            cout << setw(20) << left << allItem[i].itemID
                 << setw(20) << left << allItem[i].itemName
                 << setw(20) << left << allItem[i].itemQuantity
                 << setw(20) << left << allItem[i].itemPrice
                 << setw(20) << left << allItem[i].itemCategory << endl; 
        }
        cout << endl;
        system("pause");
    }

    void displayLowStock() override {
        system("cls");
        cout << "DISPLAY LOW STOCK ITEMS" << endl << endl;
            
        bool lowStockFound = false;

        for (int i=0; i<itemCount; i++){
            if (allItem[i].itemQuantity <= 5){
                if (!lowStockFound){
                    cout << "The following item/s are low in stock: " << endl << endl;
                    cout << setw(20) << left << "ID"
                         << setw(20) << left << "Name"
                         << setw(20) << left << "Quantity"
                         << setw(20) << left << "Price"
                         << setw(20) << left << "Category" << endl;
                }
                cout << setw(20) << left << allItem[i].itemID
                     << setw(20) << left << allItem[i].itemName
                     << setw(20) << left << allItem[i].itemQuantity
                     << setw(20) << left << allItem[i].itemPrice
                     << setw(20) << left << allItem[i].itemCategory << endl;

                lowStockFound = true;
            }
        }
        if (!lowStockFound){
            cout << "No low stock items found!" << endl;
        }
        cout << endl;
        system("pause");
    }
};

int main (){
    int menuChoice;
    Inventory inventory;

    do {
        system("cls");
        cout << "Inventory Management System" << endl << endl;
        cout << "MAIN MENU" << endl;
        cout << "1 - Add Item" << endl;
        cout << "2 - Update Item" << endl;
        cout << "3 - Remove Item" << endl;
        cout << "4 - Display Items By Category" << endl;
        cout << "5 - Display All Items" << endl;
        cout << "6 - Search Item" << endl;
        cout << "7 - Sort Items" << endl;
        cout << "8 - Display Low Stock Items" << endl;
        cout << "9 - Exit" << endl << endl;

        cout << "Enter choice: ";
        cin >> menuChoice;

        // ensures only accepting values from 1 to 9
        while (cin.fail() || menuChoice < 1 || menuChoice > 9) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
            cout << "Invalid input! Please enter a number between 1 and 9: ";
            cin >> menuChoice;
        }

        switch (menuChoice){
        case 1:
            inventory.addItem();
            break;

        case 2:
            inventory.updateItem();
            break;

        case 3:
            inventory.removeItem();
            break;
        
        case 4:
            inventory.displayItem();
            break;

        case 5:
            inventory.displayAllItem();
            break;

        case 6:
            inventory.searchItem();
            break;

        case 7:
            inventory.sortItem();
            break;

        case 8:
            inventory.displayLowStock();
            break;
        
        case 9:
            cout << "Thank you for using Inventory Management System!" << endl;
            break;
        
        default:
            cout << "Invalid input! Please enter a valid input." << endl;
        }
    } while (menuChoice != 9);
    return 0;
}