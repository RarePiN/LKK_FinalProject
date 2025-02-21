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
}

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

                int choose(int c) {            // UI for choosing options    c: Count of total options 
                        int chosen = 0;
                        return chosen;
                }

                void textInput() {        // UI for text inputs
                        
                        return;
                }

                void test() {
                        clr();
                        cout << "////////////// TESTING //////////////" << endl;
                        
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
