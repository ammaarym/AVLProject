#include <iostream>
#include <regex>
#include "header.h"

using namespace std;

/* Note:
    1. You will have to comment main() when unit testing your code because catch uses its own main().
    2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

// Regex to capture content between quotations (typically a name)
regex name("[^\"]*[\"]([a-zA-Z\\s]*)[\"].*");
// Regex thats not greedy and captures everything bw first and last quotation mark
//regex name("\"(.*?)\"\\s+(\\d+)");
// Regex to capture idStr
regex number("[^\\d]*([\\d]*).*");
// Regex to extract a name and ID together from a given string
//regex otherPattern("\"([^\"]*)\"\\s+(\\d+)");

int main() {
    // Create a new AVL tree instance
    AVLTree avlTree;
    // Fetch the number of commands/operations to be performed
    int num;
    cin >> num;
    cin.ignore();  // Clear the input buffer after fetching the number

    // Process each command
    for (int i = 0; i < num; i++) {
        // Fetch the entire line containing the command
        string line;
        getline(cin, line);
        istringstream in(line);  // Convert line into a stream for easy extraction
        string command;
        in >> command;  // Extract the actual command keyword

        // Handle "insert" command
        if (command == "insert") {
            smatch matches;
            string nameVal;

            // Extract the name from the input line using the regex
            if (regex_search(line, matches, name)){
                nameVal = matches[1];
            }
            else {
                cout << "unsuccessful" << endl;
                continue;
            }
            string idStr;

            if (regex_search(line, matches, number)){
                idStr = matches[1];
            }
            else {
                cout << "unsuccessful" << endl;
                continue;
            }

            // Validate that the ID is made up of numeric characters only
            // christian
            // checks for special characters
            bool looper = false;
            for (char c : idStr){
                if(!isdigit(c)){
                    cout << "unsuccessful" << endl;
                    looper = true;
                    break;
                }
            }

            if (looper){
                continue;
            }

            // christian
            // check for 8-digit ids
            // string id_str = to_string(id);
            if (idStr.length() != 8) {
                cout << "unsuccessful" << endl;
                continue;
            }

            int idNum = stoi(idStr);  // Convert the ID string to an integer

            // Attempt to insert into the AVL tree
            avlTree.insertHelper(idNum, nameVal);
        }
            // Handle "removeInorder" command
        else if (command == "removeInorder") {
            string nStr;
            in >> nStr;

            // Validate that 'n' is numeric
            for (char c : nStr){
                if(!isdigit(c)){
                    cout << "unsuccessful" << endl;
                }
            }

            int n = stoi(nStr);
            avlTree.removeInorderHelper(n);
        }
            // Handle "remove" command
        else if (command == "remove") {
            string idStr;
            in >> idStr;

            // Validate that the ID is numeric
            for (char c : idStr){
                if(!isdigit(c)){
                    cout << "unsuccessful" << endl;
                }
            }

            int idNum = stoi(idStr);
            avlTree.removeHelper(idNum);
        }
            // Handle "search" command
        else if (command == "search") {
            string next;
            in >> next;

            // Check if the search term matches a name pattern
            if (regex_match(next, name)) {
                next = regex_replace(next, regex("[^a-zA-Z]"), "");
                avlTree.searchNameHelper(next);
            }
                // Check if the search term matches an ID pattern
            else if (regex_match(next, regex("^[0-9]+$")) && next.size() == 8){
                int searchiD = stoi(next);
                avlTree.searchiDHelper(searchiD);
            }
            else {
                cout << "unsuccessful";
            }
        }
            // Handle printing commands
        else if (command == "printInorder") {
            avlTree.printInOrder();
        }
        else if (command == "printPreorder") {
            avlTree.printPreOrder();
        }
        else if (command == "printPostorder") {
            avlTree.printPostOrder();
        }
            // Handle the command to print the level count of the AVL tree
        else if (command == "printLevelCount") {
            avlTree.printLCHelper();
        }
    }
    return 0;
}