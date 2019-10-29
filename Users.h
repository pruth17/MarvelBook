#ifndef USERS_H_
#define USERS_H_

#include <string>
#include <ostream>
using namespace std;
#include "List.h"
#include"BST.h"

class Users
{
private:
    int ido;
    string firstname;
    string lastname;
    string city;
    string login;
    string password;
    BST<int> *friends;
    List<string> *interests;
    int rank;
    
    
public:
    
    /**Constructors*/
    Users();
    Users(const Users &users); // this is a copy constructer
    Users(string fn, string ln, string c, string log, string pw,int id, BST<int> *f, List<string> *i, int rank);
    
    
    /**Access Functions*/
    string get_first_name();
    int get_rank();
    string get_last_name();
    string get_city();
    List<string> get_listofinterest();
    string get_login();
    BST<int> get_listoffriends();
    string get_password();
    int get_id();
    
    
    
    /**Manipulation Procedures*/
    void set_first_name(string fn);
    void set_rank(int rank);
    void set_last_name(string ln);
    void set_city(string c);
    void set_listofinterest(string i);
    void set_login(string log);
    void set_listoffriend(string f);
    void set_password(string pw);
    void set_id(int id);
    void sort(List<int> d);
    
    
    /**Additional Functions*/
    
    friend ostream& operator<<(ostream& os, const Users& user);
    
    
    bool operator==(const Users& user);
   
    
    bool operator<(const Users& user);
   
    
    bool operator>(const Users& user);
   
    void add_bst(Users user);
    void add_interest(string interest);
    bool searchBst(Users user);
    void remove_bst(Users user);
    
};



#endif /* USERS_H_ */



