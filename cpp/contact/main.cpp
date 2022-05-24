#include<bits/stdc++.h>
#include<sstream>

using namespace std;

const int ADMIN = 0, OTHER_APP = 1, GUEST = 2;

class ContractInfo{
    string name;
    string phoneNumber;
    string email;
    string address;
    string dob;

    public:
    //static int NAME = 0, PHONE_NUMBER = 1, EMAIL = 2, ADDRESS = 3, DOB = 4;

    ContractInfo(string line){
        stringstream ss(line);

        ss >> name;
        ss >> phoneNumber;
        ss >> email;
        ss >> address;
        ss >> dob;
    }

    friend ostream& operator<<(ostream &os, ContractInfo cinfo){
        os << cinfo.name << "\t"
            << cinfo.phoneNumber << "\t"
            << cinfo.email << "\t"
            << cinfo.address << "\t"
            << cinfo.dob;
        return os;
    }

    
    bool operator==(const ContractInfo& o){
        return name == o.name && phoneNumber == o.phoneNumber && email == o.email
                && address == o.address && dob == o.dob;
    }

    static ContractInfo makeContract(){
        cout << "Enter Contract info in format : \nname\tphoneNumber\temail\taddress\tdob\n";

        string line;
        cin >> line;
        ContractInfo c(line);

        return c;
    }
};

class Database{
    vector<ContractInfo> database;

    public:
    Database() =default;
    Database(istream &is){
        string s;

        while(getline(is, s)){
            ContractInfo temp(s);
            database.push_back(temp);
        }
    }

    bool addContract(ContractInfo cinfo){
        database.push_back(cinfo);

        return true;
    }

    bool deleteContract(ContractInfo cinfo){
        auto it = find(database.begin(), database.end(), cinfo);

        if(it != database.end()){
            database.erase(it);
            return true;
        }
        else{
            return false;
        }
    };

    bool modifyContract(ContractInfo old, ContractInfo ne){
        deleteContract(old);
        addContract(ne);

        return true;
    }

    friend ostream& operator<<(ostream &os, Database db){
        for(auto itr : db.database){
            os << itr << endl;
        }

        return os;
    }
};

struct Account{
    string username;
    string password;

    Account() = default;

    Account(string u, string p) : username(u), password(p){

    }

    bool authenticate(const Account &ac){
        return username == ac.username && password == ac.password;
    }

    bool operator==(const Account &ac){
        return authenticate(ac);
    }

    
    static Account getAccountInfo(){
        Account acc;
        cout << "Enter Username : ";
        cin >> acc.username;
        cout << "Enter Password : ";
        cin >> acc.password;

        return acc;
    }
};

class ContractInfoApp{
    Database database;
    vector<Account> admin, otherApp, guest;

    int curLoginType = 3;

    bool isAdmin(){return curLoginType == ADMIN;}
    bool isOtherApp(){return curLoginType == OTHER_APP;}
    bool isGuest(){return curLoginType == GUEST;}

    bool deleteHelper(vector<Account> accounts, Account toCheck){
        auto it = find(accounts.begin(), accounts.end(), toCheck);

        if(it != accounts.end()){
            accounts.erase(it);
            return true;
        }
        else{
            return false;
        }
    }

    bool loginHelper(vector<Account> accounts, Account toCheck){
        
        auto it = find(accounts.begin(), accounts.end(), toCheck);
        if(it != accounts.end()){
            return true;
        }

        return false;
    }
    
    public:
    ContractInfoApp(istream &is) 
        : database(is)
    {
        admin.emplace_back("admin", "@dmin@U$T");
    }

    bool login(Account credential, int accountType){
        if(accountType == ADMIN && loginHelper(admin, credential)){
            curLoginType = ADMIN;
            return true;
        }
        else if(accountType == OTHER_APP && loginHelper(otherApp, credential)){
            curLoginType = OTHER_APP;
            return true;
        }
        else if(accountType == GUEST && loginHelper(guest, credential)){
            curLoginType = GUEST;
            return true;
        }
        else{
            return false;
        }
    }

    bool createGuestAccount(Account acc){
        if(isAdmin()){
            guest.push_back(acc);
            return true;
        }

        return false;
    }

    bool createOtherApp(Account acc){
        if(isAdmin()){
            otherApp.push_back(acc);
            return true;
        }

        return false;
    }

    bool deleteGuestAccount(Account acc){
        return deleteHelper(guest, acc);
    }

    bool deleteOtherApp(Account acc){
        return deleteHelper(otherApp, acc);
    }

    Database getDatabase(){
        return database;
    }

    friend ostream& operator<<(ostream &os, ContractInfoApp app){
        os << app.database;
        return os;
    }
};

class Owner{
    ContractInfoApp app;
    Database db;

    public:
    Owner(ContractInfoApp a) : app(a){
        db = app.getDatabase();
    }

    bool createGuestAccount(Account acc){
        return app.createGuestAccount(acc);
    }

    bool createOtherAppAccount(Account acc){
        return app.createOtherApp(acc);
    }

    bool deleteGuestAccount(Account acc){
        return app.deleteGuestAccount(acc);
    }

    bool deleteOtherAppAccount(Account acc){
        return app.deleteOtherApp(acc);
    }

    void print(){
        cout << "1. Create Guest Account\n"
             << "2. Delete Guest Account\n"
             << "3. Create Other App Account\n"
             << "4. Delete Other App Account\n"
             << "5. Create Record\n"
             << "6. Delete Record\n"
             << "7. Modify Record\n"
             << "8. Log Out\n";
        cout << "Input : ";
    }

    int getLogout(){
        return 8;
    }

    void process(int num){
        switch(num){
            case 1 :
                createGuestAccount(Account::getAccountInfo());
                break;
            case 2 :
                deleteGuestAccount(Account::getAccountInfo());
                break;
            case 3 :
                createOtherAppAccount(Account::getAccountInfo());
                break;
            case 4 :
                deleteOtherAppAccount(Account::getAccountInfo());
                break;
            case 5 :
                db.addContract(ContractInfo::makeContract());
                break;
            case 6:
                db.deleteContract(ContractInfo::makeContract());
                break;
            case 7:
                cout << " Old info first then new info\n";
                db.modifyContract(ContractInfo::makeContract(), ContractInfo::makeContract());
                break;
            default : 
                cout << "Invalid command\n";
        }
    }
};

class OtherApp{
    ContractInfoApp app;

    public:
    OtherApp(ContractInfoApp ap) : app(ap)
    {

    }

    void print(){
        cout << "1. View Database\n"
             << "2. Modify Record\n"
             << "3. Log Out\n";
        cout << "Input : ";
    }

    int getLogout(){
        return 3;
    }

    void process(int num){
        switch(num){
            case 1:
                cout << app.getDatabase() << endl;
                break;
            case 2:
                cout << " Old info first then new info\n";
                app.getDatabase().modifyContract(ContractInfo::makeContract(), ContractInfo::makeContract());
                break;
            default:
                cout << "invalid input";
        }
    }
};

class Guest{
    ContractInfoApp app;

    public :
    Guest(ContractInfoApp ap) : app(ap){

    }

    void print(){
        cout << "1. Modify Record\n"
             << "2. Log Out\n";
        cout << "Input : ";
    }

    int getLogout(){
        return 2;
    }

    void process(int num){
        switch(num){
            case 1:
                cout << app.getDatabase() << endl;
                break;
            default:
                cout << "invalid input";
        }
    }
};

ContractInfoApp readFromFile(string fileName);
int loginHelper(ContractInfoApp app){
    while(true){
        cout << "1. Owner\n"
            << "2. Other App\n"
            << "3. Guest\n"
            << "4. Quit\n";
        cout << "Account Type : ";

        int type;
        cin >> type;

        if(type < 1 || type > 4){
            cout << "Invalid input, input between 1-3\n";
        }
        else if(type == 4) return type;
        else{
            Account acc = Account::getAccountInfo();
            cout << acc.username << " " << acc.password << endl;
            if(app.login(acc, type-1))
                return type;
            else
                cout << "Invalid Credential\n";
        }
    }
}

int main(){
    ContractInfoApp app = readFromFile("contract.txt");

    cout << app << endl;
    int userType = loginHelper(app) - 1;
    
    while(true){
        if(userType == ADMIN){
            Owner owner(app);
            int input;

            while(true){
                owner.print();
                cin >> input;
                if(input != owner.getLogout())
                    owner.process(input);
                else
                    break;
            }

            userType = loginHelper(app) - 1;
        }

        else if(userType == OTHER_APP){
            OtherApp other(app);
            int input;

            while(true){
                other.print();
                cin >> input;
                if(input != other.getLogout())
                    other.process(input);
                else
                    break;
            }

            userType = loginHelper(app) - 1;
        }

        
        else if(userType == GUEST){
            Guest guest(app);
            int input;

            while(true){
                guest.print();
                cin >> input;
                if(input != guest.getLogout())
                    guest.process(input);
                else
                    break;
            }

            userType = loginHelper(app) - 1;
        }

        else{
            break;
        }
    }

    cout << "Thank You\n";
}



ContractInfoApp readFromFile(string fileName){
    ifstream inputFile;
    inputFile.open(fileName);

    ContractInfoApp app(inputFile);
    inputFile.close();

    return app;
}

