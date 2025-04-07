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
                User User;        // Current User Info
                bool LoggedIn;    // Log In Status

                void init() {     // Initialize the client.
                        User.id = "Nil";
                        User.psw = "Nil";
                        User.type = '/';
                        LoggedIn = false;
                        return;
                }

                // ==========================[Functions]===========================

                void clr() {                 // Clear the terminal screen
                        system("cls");
                        return;
                }

                char keyPress() {
        		char key = _getch(); // Get the key pressed
                        return key;
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

                void textInput(int c, vector<string> f, vector<string> t, vector<string> & r) {        // UI for text inputs    c: number of fields   f: field names  t: field types l: field string
                        
                        vector<string> l;
                        for (int z = 0; z < c; z++) {
                                l.push_back("");
                        }

                        for (int i = 0; i < c; i++) {
                                
                                int mode = 0;
                                string temp;

                                char key;
                                while (true) {     // Loop until enter is pressed

                                        clr();

                                        // PREVIOUS FIELDS
                                        for (int j = 0; j < i; j++) {
                                                if (t[j] == "1") {
                                                        temp = "";
                                                        for (int z = 0; z < l[j].length(); z++) temp += '*';
                                                }
                                                else temp = l[j];
                                                cout << f[j] << ": " << temp << endl;
                                        }

                                        // CURRENT FIELD
                                        if (t[i] == "1") {
                                                temp = "";
                                                for (int z = 0; z < l[i].length(); z++) temp += '*';
                                        }
                                        else temp = l[i];
                                        cout << GREEN << f[i] << RESET << ": " << temp << "|" << endl;

                                        // Later FIELDS
                                        for (int j = i + 1; j < c; j++) {
                                                if (t[j] == "1") {
                                                        temp = "";
                                                        for (int z = 0; z < l[j].length(); z++) temp += '*';
                                                }
                                                else temp = l[j];
                                                cout << f[j] << ": " << temp << endl;
                                        }

                                        key = keyPress();

                                        if (key == 27) return;   // ESC is pressed
                                        if (key == 13) break;   // Enter is pressed

                                        if (validCheck(key) and key != 8 and key != 13 and key != 27) {
                                                l[i].push_back(key);
                                        }
                                        if (key == 8) {
                                                if (l[i].length() > 0) {
                                                        l[i].pop_back();
                                                }
                                        }

                                }

                        }

                        for (int i = 0; i < c; i ++) {
                                r.push_back(l[i]);
                        }

                        return;
                }

                void test() {
                        clr();
                        cout << "////////////// TESTING //////////////" << endl;
                        cout << optionMenu(5, "Test Question", {"Option A","Option B","Option C","Option D","Option E"});

                        vector<string> l;
                        textInput(3,{"Account","Password","Confirm"},{"0","1","0"},l);

                        for (int i = 0 ; i < l.size(); i++) cout << l[i] << endl;
                        return;
                }

        public:

                void start() {
                        init();
                        test();
                        return;
                }

};

int main() {
        Client Client;
        Client.start();
        return 0;
}
