#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctype.h>

#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Users.h"
#include "BST.h"
#include "List.h"
#include "Hash_name.h"
#include "Hash_interest.h"
#include "FileIO.h"


using namespace std;

void printMenu(Users& currentUser)
{
    
    cout << endl;
    
    cout << "1. View My Friends " << endl;
    cout << "2. Search by name" << endl;
    cout << "3. Search by interest" << endl;
    cout << "4. Get Friend Recommendtion" << endl;
    cout << "5. Quit" << endl;
    cout<< "6. View my profile "<<endl;
    cout << endl;
    cout << "Enter your choice: ";
}

void interactWithUser(Users&currentUser,List<Users>&allUser,HashTable_I<Users>& HI,HashTable_N<Users>& HN, Graph &G)
{
    
    string choice;
    bool quit = false;
    while (! quit)
    {
        printMenu(currentUser);
        
        cin >> choice;
        while (!isdigit(choice[0]))
        {
            cout << "\n\nPlease enter numbers not letters\n" << endl;
            printMenu(currentUser);
            cin >> choice;
        }
        int num = stoi(choice);
        while (!(0 < num) || !(num < 7))
        {
            cout << "\n\nInvalid input.\n" << endl;
            printMenu(currentUser);
            cin >> num;
        }
        if (num == 5)
        {
            ofstream out;
            out.open("User2.txt");
            break;
        }
        
        
        if(num ==1)
        {
            int choi1;
            cout << "1. View all friends" << endl;
            cout << "2. View a friend's profile " << endl;
            cout << "3. Remove a friend" << endl;
            cin >> choi1;
            while (cin.fail() || choi1 > 3 || choi1 < 1)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << endl;
                cout << " Please enter correct input" << endl;
                cout << "1. View all friends" << endl;
                cout << "2. View a friend's profile " << endl;
                cout << "3. Remove a friend" << endl << endl;
                
                cin >> choi1;
                
            }
            cin.ignore();
            List<int> asf = G.seeFriends(currentUser.get_id());
            
            if(choi1 == 1)
            {
                while(!asf.isEmpty())
                {
                    int x = asf.getFirst();
                    asf.removeFirst();
                    allUser.startIterator();
                    for(int i=1;i<x;i++)
                    {
                        allUser.advanceIterator();
                    }
                    Users viewFriend = allUser.getIterator();
                    
                    
                    cout <<viewFriend.get_id() << " " <<   viewFriend.get_first_name() << " " << viewFriend.get_last_name() << endl;
                }
            }
            else if (choi1 == 2)
            {
                cout << "Enter the ID of your friend: ";
                int ch;
                cin >> ch;
                allUser.startIterator();
                for(int l=0;l<ch;l++)
                {
                    allUser.advanceIterator();
                }
                Users viewFriend1 = allUser.getIterator();
                cout << "First Name: " << viewFriend1.get_first_name() << endl;
                cout << "Last Name: " << viewFriend1.get_last_name() << endl;
                cout << "City: " << viewFriend1.get_city() << endl;
            }
            else if(choi1==3)
            {
                cout << "Enter the ID you want to remove: ";
                int r;
                cin >> r;
                G.removeFriend(currentUser.get_id(), r);
                allUser.startIterator();
                for (int k=1; k<r; k++)
                {
                    allUser.advanceIterator();
                }
                Users UserRemove = allUser.getIterator();
                cout << UserRemove.get_first_name() << " removed!" << endl;
            }
        }
        else if (num == 2)
        {
            string fn, ln;
            cout << "Enter the first name of the User: ";
            cin >> fn;
            cout << "Enter the last name of the User: ";
            cin >> ln;
            transform(fn.begin(), fn.end(), fn.begin(), ::tolower);
            transform(ln.begin(), ln.end(), ln.begin(), ::tolower);
            
            int index = HN.hash(fn + ln);
            
            if (HN.countBucket(index) == 0)
            {
                cout << fn << " is not a User of Marvel Book" << endl;
            }
            else
            {
                List<Users> usersWithName;
                cout << endl << " This's a list of users whose name is " << fn
                << " " << ln << endl << endl;
                List<Users>& bucket = (List<Users>&)HN.getBucket(index);
                bucket.startIterator();
                int count = 1;
                while (! bucket.offend())
                {
                    Users user = (Users)bucket.getIterator();
                    // check actual lowercase names are correct to avoid hash collisions
                    string user_fn = user.get_first_name();
                    string user_ln = user.get_last_name();
                    transform(user_fn.begin(), user_fn.end(), user_fn.begin(), ::tolower);
                    transform(user_ln.begin(), user_ln.end(), user_ln.begin(), ::tolower);
                    
                    
                    if (fn == user_fn && ln == user_ln)
                    {
                        cout << count << "." << endl << user << endl;
                        usersWithName.insertLast(user);
                        count ++;
                    }
                    bucket.advanceIterator();
                }
                if (! usersWithName.isEmpty())
                {
                    char choice;
                    
                    cout << "Would you like to add a user from the searched list? Enter Y or N: ";
                    
                    cin >> choice;
                    if (choice == 'Y' || choice == 'y')
                    {
                        cout << endl << "Choose number of user listed to add: ";
                        int numU;
                        
                        cin >> numU;
                        int index = 0;
                        Users userToAdd;
                        usersWithName.startIterator();
                        while (index < numU && ! usersWithName.offend())
                        {
                            Users user = usersWithName.getIterator();
                            if (index == numU - 1)
                            {
                                userToAdd = user;
                                break;
                            }
                            usersWithName.advanceIterator();
                        }
                        
                        cout << "The user to be added is: " << endl << endl << userToAdd << endl;
                        // add user to currentUsers' friends
                        G.addEdge1(currentUser.get_id(), userToAdd.get_id());
                        G.printGraph(cout);
                        currentUser.add_bst(userToAdd);
                        
                        cout << endl << "OK, " << userToAdd.get_first_name()
                        << " added to your friends, " << currentUser.get_first_name()
                        << "." << endl;
                    }
                    else
                    {
                        cout << endl << "OK" << endl;
                    }
                }
            }
            
        }
        else if(num==3)
        { // search by interest
            const int interest_count = 18;
            string possibleInterests[interest_count] =
            {
                "Technology",
                "Money",
                "Fighting Evil",
                "Working out",
                "Old movies",
                "Studies",
                "Food",
                "Combat",
                "Biology",
                "Street fighting",
                "Hammer",
                "Stealing",
                "Tricks",
                "Physics",
                "Photography",
                "Pranks",
                "Killing",
                "Fashion Design"
            };
            
            cout << "*** All Possible Marvel Book Interests ***" << endl;
            for (int i = 0; i < interest_count; i++)
            {
                cout << "  " << i + 1 << ". " << possibleInterests[i] << endl;
            }
            cout << "******************************************" << endl;
            
            int num;
            cout << "Please choose an interest to search for (1 -- " << interest_count << "): ";
            cin >> num;
            while (cin.fail() || num <= 0 || num > 18)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input.  Please enter a number (1 -- " << interest_count << "): ";
                cin >> num;
            }
            string searchInterest = possibleInterests[num - 1];
            cout << "OK, searching for users with " << searchInterest << " as an interest." << endl;
            int inde = HI.hash(searchInterest);
            if (HI.countBucket(inde) == 0)
            {
                cout << "No User matched" << endl << endl;
            }
            else
            {
                cout << endl
                << "This is a list of users with interest as searched"
                << endl << endl;
                
                List<Users>& bucket = HI.getBucket(inde);
                List<Users> usersWithInterest;
                int count = 1;
                bucket.startIterator();
                while (! bucket.offend())
                {
                    Users        user            = bucket.getIterator();
                    bool         userHasInterest = false;
                    List<string> userInterests   = user.get_listofinterest();
                    userInterests.startIterator();
                    while (! userInterests.offend())
                    {
                        string userInterest = userInterests.getIterator();
                        if (userInterest == searchInterest)
                        {
                            userHasInterest = true;
                            break;
                        }
                        userInterests.advanceIterator();
                    }
                    if (userHasInterest)
                    {
                        cout << count << "." << endl;
                        cout << user << endl;
                        usersWithInterest.insertLast(user);
                        count ++;
                    }
                    bucket.advanceIterator();
                }
                
                if (! usersWithInterest.isEmpty())
                {
                    char choice;
                    cout << endl
                    << "Would you like to add a user from the searched list? Enter Y or N : ";
                    
                    cin >> choice;
                    if (choice == 'Y' || choice == 'y')
                    {
                        cout << endl << "Chose number of user listed to add: ";
                        int numU;
                        cin >> numU;
                        
                        Users userToAdd;
                        bool foundUser = false;
                        int count = 1;
                        usersWithInterest.startIterator();
                        while (! usersWithInterest.offend())
                        {
                            Users user = usersWithInterest.getIterator();
                            if (count == numU) {
                                userToAdd = user;
                                foundUser = true;
                                break;
                            }
                            count ++;
                            usersWithInterest.advanceIterator();
                        }
                        if (! foundUser)
                        {
                            cout << "Could not find user" << endl;
                        }
                        else
                        {
                            cout << "The user to be added is: " << endl;
                            cout << userToAdd << endl;
                            // add user to currentUsers' friends
                            currentUser.add_bst(userToAdd);
                            G.addEdge(currentUser.get_id(), userToAdd.get_id());
                            G.printGraph(cout);
                            
                            
                            cout << endl << "OK, " << userToAdd.get_first_name()
                            << " added to your friends, " << currentUser.get_first_name()
                            << "." << endl;
                        }
                    }
                }
            }
            
        }
        else if(num == 4)
        {
             List<int> Table[15];
            cout << "Friend recommendation: " << endl;
            List<int> rec = G.BFS(currentUser.get_id());
            rec.startIterator();
             //int p=0;
            while(!rec.offend())
            {
                int x = rec.getIterator();
                allUser.startIterator();
                for(int i =1; i < x; i++)
                {
                    allUser.advanceIterator();
                }
                Users recUser = allUser.getIterator();
                List<string> k = recUser.get_listofinterest();
                k.printList(cout);
               List<string> l = currentUser.get_listofinterest();
                l.printList(cout);
                l.startIterator();
                
                
            }
            cout << "Your reccomendation" << endl;
            for(int i = 0;i<15;i++)
            {
                Table[i].startIterator();
                while(!Table[i].offend())
                {
                    int w= Table[i].getIterator();
                    allUser.startIterator();
                                         for(int i =1; i < w; i++)
                                         {
                                             allUser.advanceIterator();
                                        }
                                    Users recUser1 = allUser.getIterator();
               
                    cout << recUser1.get_first_name() << " " << recUser1.get_last_name() << " and ID is " << recUser1.get_id() << endl;
                                    cout << "Would u like to add (y/n): ";
                                   string re;
                                   cin >> re;
                                   if (re == "Y" || re == "y")
                                   {
                                       G.addEdge1(currentUser.get_id(), recUser1.get_id());
                                       cout << recUser1.get_first_name() << " added!" << endl;
                                   }
                    
                    
                    Table[i].advanceIterator();
                }
            }
         
        }
        
        
        
        else if (num == 5)
        {
            quit = true;
            break;
        }
        
        else if (num==6)
        {
            cout<<endl<<"This's your profile:"<<endl<<currentUser;
            
        }
    }
    cout << "Bye " << currentUser.get_first_name() << "!" << endl;
}
int main()
{
   
  
    HashTable_I<Users>* HI  = new HashTable_I<Users>();
    HashTable_N<Users>* HN  = new HashTable_N<Users>();
    List<Users>*  allUser   = new List<Users>();
    Graph G(15);
    
    FileIO::readFromFile(allUser, HI, HN, G);
    G.printGraph(cout);
    int id;
    string login, pass;
    
    allUser->startIterator();
    cout << "Enter your ID: ";
    cin >> id;
    while (cin.fail() || id >15||id<=0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << endl;
        cout << " Please enter correct id" << endl;
        
        cin >> id;
        
    }
    
    for(int i =1; i < id; i++)
    {
        allUser->advanceIterator();
    }
    Users currentUser = allUser->getIterator(); // assume current user is first for testing for now.
    do
    {
        cout << "Enter you password: ";
        cin >> pass;
    }
    while(pass != currentUser.get_password());
    if(pass == currentUser.get_password() )
    {
        cout <<endl<< "Welcome to MarvelBook, " << currentUser.get_first_name() << "!" << endl<<endl;
        
        
        
        interactWithUser(currentUser, *allUser, *HI, *HN, G);
    }
    else
    {
        cout << " Password didn't match " << endl;
    }
    
    
    return 0;
}



/*#include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include <ctype.h>
 
 #include <algorithm>
 #include <string>
 #include <iostream>
 #include <iomanip>
 #include <fstream>
 #include <sstream>
 
 #include "Users.h"
 #include "BST.h"
 #include "List.h"
 #include "Hash_name.h"
 #include "Hash_interest.h"
 #include "FileIO.h"
 
 using namespace std;
 
 void printMenu(Users& currentUser) {
 
 cout << endl;
 cout<<"Menu"<<endl;
 cout << "1. List all Users" << endl;
 cout << "2. Search by name" << endl;
 cout << "3. Search by interest" << endl;
 cout << "4. Quit" << endl;
 cout << endl;
 cout << "Enter your choice:";
 }
 
 void interactWithUser(Users&              currentUser,
 List<Users>&        allUser,
 HashTable_I<Users>& HI,
 HashTable_N<Users>& HN) {
 
 string choice;
 bool quit = false;
 while (! quit) {
 printMenu(currentUser);
 
 cin >> choice;
 while (!isdigit(choice[0])) {
 cout << "\n\nPlease enter numbers not letters\n" << endl;
 printMenu(currentUser);
 cin >> choice;
 }
 int num = stoi(choice);
 while (!(0 < num) || !(num < 6)) {
 cout << "\n\nInvalid input.\n" << endl;
 printMenu(currentUser);
 cin >> num;
 }
 if (num == 4) {
 ofstream out;
 out.open("User2.txt");
 //bst.inOrderPrint(cout);
 break;
 }
 
 switch (num) {
 case 1: { // Print all users
 cout << "\nUser List:" << endl << endl;
 //bst.inOrderPrint(cout);
 allUser.printList(std::cout);
 break;
 }
 case 2: { // search by name
 string fn, ln;
 cout << "Enter the first name of the User: ";
 cin >> fn;
 cout << "Enter the last name of the User: ";
 cin >> ln;
 transform(fn.begin(), fn.end(), fn.begin(), ::tolower);
 transform(ln.begin(), ln.end(), ln.begin(), ::tolower);
 
 int index = HN.hash(fn + ln);
 
 if (HN.countBucket(index) == 0) {
 cout << fn << " is not a User of Marvel Book" << endl;
 } else {
 List<Users> usersWithName;
 cout << endl << " This's a list of users whose name is " << fn
 << " " << ln << endl << endl;
 List<Users>& bucket = (List<Users>&)HN.getBucket(index);
 bucket.startIterator();
 int count = 1;
 while (! bucket.offend()) {
 Users user = (Users)bucket.getIterator();
 // check actual lowercase names are correct to avoid hash collisions
 string user_fn = user.get_first_name();
 string user_ln = user.get_last_name();
 transform(user_fn.begin(), user_fn.end(), user_fn.begin(), ::tolower);
 transform(user_ln.begin(), user_ln.end(), user_ln.begin(), ::tolower);
 //cout << "fn = '" << fn << "'" << endl;
 //cout << "ln = '" << ln << "'" << endl;
 //cout << "user_fn = '" << user_fn << "'" << endl;
 //cout << "user_ln = '" << user_ln << "'" << endl;
 
 if (fn == user_fn && ln == user_ln) {
 cout << count << "." << endl << user << endl;
 usersWithName.insertLast(user);
 count ++;
 }
 bucket.advanceIterator();
 }
 if (! usersWithName.isEmpty()) {
 char choice;
 
 cout << "Would you like to add a user from the searched list? Enter Y or N: ";
 
 cin >> choice;
 if (choice == 'Y' || choice == 'y') {
 cout << endl << "Choose number of user listed to add: ";
 int numU;
 
 cin >> numU;
 int index = 0;
 Users userToAdd;
 usersWithName.startIterator();
 while (index < numU && ! usersWithName.offend()) {
 Users user = usersWithName.getIterator();
 if (index == numU - 1) {
 userToAdd = user;
 break;
 }
 usersWithName.advanceIterator();
 }
 
 cout << "The user to be added is: " << endl << endl << userToAdd << endl;
 // add user to currentUsers' friends
 currentUser.add_bst(userToAdd);
 cout << endl << "OK, " << userToAdd.get_first_name()
 << " added to your friends, " << currentUser.get_first_name()
 << "." << endl;
 } else {
 cout << endl << "OK" << endl;
 }
 }
 }
 break;
 }
 case 3: { // search by interest
 const int interest_count = 18;
 string possibleInterests[interest_count] = {
 "Technology",
 "Money",
 "Fighting Evil",
 "Working out",
 "Old movies",
 "Studies",
 "Food",
 "Combat",
 "Biology",
 "Street fighting",
 "Hammer",
 "Stealing",
 "Tricks",
 "Physics",
 "Photography",
 "Pranks",
 "Killing",
 "Fashion Design"
 };
 
 cout << "*** All Possible Marvel Book Interests ***" << endl;
 for (int i = 0; i < interest_count; i++) {
 cout << "  " << i + 1 << ". " << possibleInterests[i] << endl;
 }
 cout << "******************************************" << endl;
 
 int num;
 cout <<endl<< "Please choose an interest to search for (1 -- " << interest_count << "): ";
 cin >> num;
 while (num <= 0 || num > interest_count) {
 cout << "Invalid input.  Please enter a number (1 -- " << interest_count << "): ";
 cin >> num;
 }
 string searchInterest = possibleInterests[num - 1];
 int inde = HI.hash(searchInterest);
 if (HI.countBucket(inde) == 0) {
 cout << "No User matched!" << endl << endl;
 } else {
 cout<< endl   << "This is a list of users with "<<searchInterest<<  " as an interest:" << endl;
 cout << endl << endl;
 
 List<Users>& bucket = HI.getBucket(inde);
 List<Users> usersWithInterest;
 int count = 1;
 bucket.startIterator();
 while (! bucket.offend()) {
 Users        user            = bucket.getIterator();
 bool         userHasInterest = false;
 List<string> userInterests   = user.get_listofinterest();
 userInterests.startIterator();
 while (! userInterests.offend()) {
 string userInterest = userInterests.getIterator();
 if (userInterest == searchInterest) {
 userHasInterest = true;
 break;
 }
 userInterests.advanceIterator();
 }
 if (userHasInterest) {
 cout << count << "." << endl;
 cout << user << endl;
 usersWithInterest.insertLast(user);
 count ++;
 }
 bucket.advanceIterator();
 }
 
 if (! usersWithInterest.isEmpty()) {
 char choice;
 cout << endl
 << "Would you like to add a user from the searched list? Enter Y or N : ";
 
 cin >> choice;
 if (choice == 'Y' || choice == 'y') {
 cout << endl << "Chose number of user listed to add: ";
 int numU;
 cin >> numU;
 
 //HI->UserToAdd(index,numU);//user to be added
 
 //to test UserToAdd
 Users userToAdd;
 bool foundUser = false;
 int count = 1;
 usersWithInterest.startIterator();
 while (! usersWithInterest.offend()) {
 Users user = usersWithInterest.getIterator();
 if (count == numU) {
 userToAdd = user;
 foundUser = true;
 break;
 }
 count ++;
 usersWithInterest.advanceIterator();
 }
 if (! foundUser) {
 cout << "Could not find user" << endl;
 } else {
 cout << "The user to be added is: " << endl<<endl;
 cout <<"First name: "<< userToAdd.get_first_name() << endl;
 cout <<"Last name: "<< userToAdd.get_last_name() << endl;
 cout <<"ID: "<< userToAdd.get_login() << endl;
 
 // add user to currentUsers' friends
 currentUser.add_bst(userToAdd);
 cout << endl<< userToAdd.get_first_name()
 << "is added to your friend list, " << currentUser.get_first_name()
 << "." << endl;
 }
 }
 }
 }
 break; // switch
 }
 case 4:
 quit = true;
 break;
 }
 }
 cout << "Bye " << currentUser.get_first_name() << "!" << endl;
 }
 
 Users usingapp(List<Users>* allUser, string id)
 {
 allUser->startIterator();
 for(int i=0;i<allUser->getLength();i++)
 
 {    if (allUser->getIterator().get_login()==id)
 {
 return allUser->getIterator();
 }
 else if (allUser->getIterator().get_login()==id+"\t")
 {
 return allUser->getIterator();
 }
 else if (allUser->getIterator().get_login()==id+"\a")
 {
 return allUser->getIterator();
 }
 else if (allUser->getIterator().get_login()==id+" ")
 {
 return allUser->getIterator();
 }
 else
 {
 allUser->advanceIterator();
 }
 
 }
 }
 
 
 int main() {
 
 cout<<"Please enter your login ID: ";
 string id;
 cin>>id;
 cout<<endl<<"Please enter your password: ";
 string pass;
 cin>>pass;
 
 HashTable_I<Users>* HI      = new HashTable_I<Users>();
 HashTable_N<Users>* HN      = new HashTable_N<Users>();
 List<Users>*        allUser = new List<Users>();
 
 
 FileIO::readFromFile(allUser, HI, HN);
 
 Users currentUser=usingapp(allUser,id);
 
 cout<<endl;
 
 cout << "Welcome to MarvelBook, " << currentUser.get_first_name() << "!" << endl<<endl;
 
 cout<<"This's your profile:"<<endl<<currentUser;//can be used for choice 1 of main Menu
 
 interactWithUser(currentUser, *allUser, *HI, *HN);
 
 return 0;
 }
 
 
 */



