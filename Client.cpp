#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

// Coloured Text For Terminal.
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

struct User{
        string id;
        string psw;
        char type;
};

class Client{

        private:
                // ===========================[Values]=============================
                User CurrentUser;        // Current User Info
                bool LoggedIn;    // Log In Status

                void init() {     // Initialize the client.
                        CurrentUser.id = "Nil";
                        CurrentUser.psw = "Nil";
                        CurrentUser.type = '/';
                        LoggedIn = false;
                        return;
                }

                // ==========================[Functions]===========================

                void clr() {                 // Clear the terminal screen
                        system("cls");
                        return;
                }

                void logo() {
                        cout << "[" << YELLOW << "GU" << CYAN << "HK" << MAGENTA << " Student Portal" << RESET << "]" << endl;
                        return;
                }

                char keyPress() {
        		char key = _getch(); // Get the key pressed
                        return key;
                }

                bool isWord(char c) {
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
                            (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' ||
                             c == '*' || c == '(' || c == ')' || c == '_' || c == '+' || c == '-' || c == '=' || c == '.' || c == ',' || c == '<' || c == '>' || c == '?' || c == ':' ||
                             c == '"' || c == ';')) {
                            return true;
                        } else {
                            return false;
                        }
                }

                bool validCheck(char c) {    // Check if input is valid
                        if (c >= 48 and c <= 57) return true;
                        if (c >= 65 and c <= 90) return true;
                        if (c >= 97 and c <= 122) return true;
                        if (c >= 33 and c <= 47) return true;
                        if (c >= 58 and c <= 64) return true;
                        if (c >= 91 and c <= 96) return true;
                        if (c >= 123 and c <= 126) return true;

                        return false;
                }

                int optionMenu(int c, string q, vector<string> options) {       // UI for choosing options    c: Count of total options

                        int chosen = 0;
                        char key;
                        string l;

                        clr();
                        logo();

                        cout << endl << "    " << q << endl << endl;

                        for (int i = 0; i < c; i++) {
                                l = "";

                                if (chosen == i) l += "    > ";
                                else l += "      ";
                                
                                l += options[i];

                                if (chosen == i) l += " < ";
                                else l += "   ";

                                if (chosen == i) cout << GREEN << l << RESET << endl;
                                else cout << l << endl;
                        }

                        cout << endl << "(Use arrow keys to navigate, Enter to confirm, Esc to quit.)" << endl;

                        while (true) {
                                
                                if (_kbhit()) {

                                        key = _getch();

                                        if (key == 72) {                // Up Arrow is pressed
                                                if (chosen > 0) chosen--;
                                        } else if (key == 80) {         // Down Arrow is pressed
                                                if (chosen < (c - 1)) chosen++;
                                        } else if (key == 13) {         // Enter is pressed
                                                break;
                                        } else if (key == 27) {         // Escape is pressed
                                                chosen = -1;
                                                break;
                                        }

                                        clr();
                                        logo();
                                        cout << endl << "    " << q << endl << endl;

                                        for (int i = 0; i < c; i++) {
                                                l = "";

                                                if (chosen == i) l += "    > ";
                                                else l += "      ";
                                                                
                                                l += options[i];

                                                if (chosen == i) l += " < ";
                                                else l += "   ";

                                                if (chosen == i) cout << GREEN << l << RESET << endl;
                                                else cout << l << endl;
                                        }

                                        cout << endl << "(Use arrow keys to navigate, Enter to confirm, Esc to quit.)" << endl;

                                }
                                
                        }

                        return chosen; // Return the option chosen
                }

                void textInput(string message, int c, vector<string> f, vector<string> t, vector<string> & r) {        // UI for text inputs    c: number of fields   f: field names  t: field types l: field string
                        
                        vector<string> l;
                        for (int z = 0; z < c; z++) {
                                l.push_back("");
                        }

                        bool check = false;
                        for (int i = 0; i < t.size(); i++) {
                                if (t[i] == "1") check = true;
                        }

                        for (int i = 0; i < c; i++) {
                                
                                int mode = 0;
                                string temp;

                                char key;
                                while (true) {     // Loop until enter is pressed

                                        clr();
                                        logo();
                                        cout << endl;
                                        cout << "       " << message << endl << endl;

                                        // PREVIOUS FIELDS
                                        for (int j = 0; j < i; j++) {
                                                if (t[j] == "1" and mode == 0) {
                                                        temp = "";
                                                        for (int z = 0; z < l[j].length(); z++) temp += '*';
                                                }
                                                else temp = l[j];
                                                cout << f[j] << ": " << temp << endl;
                                        }

                                        // CURRENT FIELD
                                        if (t[i] == "1" and mode == 0) {
                                                temp = "";
                                                for (int z = 0; z < l[i].length(); z++) temp += '*';
                                        }
                                        else temp = l[i];
                                        cout << GREEN << f[i] << RESET << ": " << temp << "|" << endl;

                                        // Later FIELDS
                                        for (int j = i + 1; j < c; j++) {
                                                if (t[j] == "1" and mode == 0) {
                                                        temp = "";
                                                        for (int z = 0; z < l[j].length(); z++) temp += '*';
                                                }
                                                else temp = l[j];
                                                cout << f[j] << ": " << temp << endl;
                                        }

                                        if (check and mode == 0) cout << endl << endl << YELLOW << "(Press / to reveal password.)" << RESET << endl;
                                        if (check and mode == 1) cout << endl << endl << YELLOW << "(Press / to hide password.)" << RESET << endl;

                                        key = keyPress();

                                        if (key == 27) return;   // ESC is pressed
                                        if (key == 13) break;   // Enter is pressed

                                        if (isWord(key) and validCheck(key) and key != 8 and key != 72) {
                                                l[i].push_back(key);
                                        }
                                        if (key == 8) {
                                                if (l[i].length() > 0) {
                                                        l[i].pop_back();
                                                }
                                        }
                                        if (key == '/') {          // / pressed REVEAL PASSWORD
                                                if (mode == 0) mode = 1;
                                                else mode = 0;
                                        }

                                }

                        }

                        for (int i = 0; i < c; i ++) {
                                r.push_back(l[i]);
                        }

                        return;
                }

                void logInAttempt(string acc, string pas) {
                        return;
                }

                void logIn() {
                        while (LoggedIn == false) {
                                int n = optionMenu(4, "Welcome to GUHK Student Portal!", {"Log In","Register","Guest Mode","Quit"});
                                User temp;
                                vector<string> l;
                                if (n == 0) {
                                        textInput("Log In",2,{"ID / Email","Password"},{"0","1"},l);
                                } else if (n == 1) {
                                        textInput("Register",3,{"Account ID","Email","Password"},{"0","0","1"},l);
                                } else if (n == 2) {
                                        LoggedIn = true;
                                        temp.id = "GUEST";
                                        temp.psw = "GUEST";
                                        temp.type = 0;
                                }
                                if (n == 3) return;
                        }

                        return;
                }

                void test() {
                        clr();
                        cout << "////////////// TESTING //////////////" << endl;
                        cout << optionMenu(5, "Test Question", {"Option A","Option B","Option C","Option D","Option E"});

                        vector<string> l;
                        textInput("Test Message",3,{"Account","Password","Confirm"},{"0","1","0"},l);

                        for (int i = 0 ; i < l.size(); i++) cout << l[i] << endl;
                        return;
                }

        public:

                void start() {
                        init();
                        logIn();

                        return;
                }

};

int main() {
        Client Client;
        Client.start();
        return 0;
}
