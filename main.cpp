#include <iostream>
#include <regex>
#include <algorithm>
#include "header.h"

using namespace std;

/* Note:
    1. You will have to comment main() when unit testing your code because catch uses its own main().
    2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

// old regex that gets what between the quotations
regex name("[^\"]*[\"]([a-zA-Z\\s]*)[\"].*");
// Separate regex for capturing name and ID
regex otherPattern("\"([^\"]*)\"\\s+(\\d+)");

int main() {
    // create instance of AVL tree
    AVLTree avlTree;
    // original insertions for local testing
//    avlTree.insertHelper(10, "Joe");
//    avlTree.insertHelper(12, "Huzaifa");
//    avlTree.insertHelper(17, "Lemantha");
//    avlTree.insertHelper(11, "Rory");
//    avlTree.insertHelper(15, "Mary");
//    avlTree.insertHelper(40, "Lola");
//    avlTree.insertHelper(48, "Joe");
//    avlTree.insertHelper(30, "Lauren");
//    avlTree.insertHelper(36, "Tyrone");


    // left right root
    // get num
    int num;
    cin >> num;
    // convert to int
    cin.ignore();
    // for loop through first num (ex. for loop from 0 to 8)
    for (int i = 0; i < num; i++)  {
        // gets input, parses it
        string line;
        getline(cin, line);
        istringstream in(line);
        string command;
        in >> command;

        // command if statements
        if (command == "insert") {
            // *OLD VERSION*
            //use regex to get name from the line
            smatch matches;
            string nameVal;
            if (regex_search(line, matches, name)){
                nameVal = matches[1];
            }
            // cout << "nameVal: " << nameVal << endl;
            string idStr;
            // take int id as next
            in >> idStr;
            in >> idStr;
            // cout << "idStr: " << idStr << endl;
            for (char c : idStr){
                if(!isdigit(c)){
                     cout << "unsuccessful.main.insert" << endl;
                 }
            }
            int idNum = stoi(idStr);

            // validation done in insertHelper func
            avlTree.insertHelper(idNum, nameVal);
        }
        else if (command == "removeInorder") {
            string nStr;
            // take int id as next
            in >> nStr;
            for (char c : nStr){
                if(!isdigit(c)){
                    cout << "unsuccessful.main.removeInOrder" << endl;
                }
            }
            int n = stoi(nStr);
            avlTree.removeInorderHelper(n);
        }
        else if (command == "remove") {
            string idStr;
            // take int id as next
            in >> idStr;
            for (char c : idStr){
                if(!isdigit(c)){
                    cout << "unsuccessful.main.remove" << endl;
                }
            }
            int idNum = stoi(idStr);
            avlTree.removeHelper(idNum);
        }
        else if (command == "search") {
            // show
            // store next thing into string
            string next;
            in >> next;
            // way 1: tutor 2
//            if (regex_match(next, regex("^[A-Za-z ]+$"))) {
//                avlTree.searchNameHelper(next);
//            }
//            else {
//                cout << "unsuccessful.main.searchName" << endl;
//            }
//
//            if (next.size() != 8) {
//                cout << "unsuccessful.main.searchiD.size";
//            }
//            else if (!regex_match(next, regex("^[0-9]+$"))) {
//                cout << "unsuccessful.main.searchID";
//            }
//            else {
//                int searchiD = stoi(next);
//                avlTree.searchiDHelper(searchiD);
//            }
            //  new
            if (regex_match(next, regex("^[A-Za-z ]+$"))) {
                avlTree.searchNameHelper(next);
            }
            else if (regex_match(next, regex("^[0-9]+$")) && next.size() == 8){
                int searchiD = stoi(next);
                avlTree.searchiDHelper(searchiD);
            }
            else {
                cout << "unsuccessful.main.id&name";

            }


            // way 2: tutor 7 regex
            // have two cases: one where next is int and one where next is name
            // 1. next is int (search by id)
            // differentiate by checking if next term has quotation
            // issue: im taking in commands as one whole line

            // easy way: use regex expression to check if theres a valid name in full line
            // regex will return something inside quotations
                // if there isnt itll return false
                // if false, its a num
                // if it returns true, it must be a name
            // read up on regex
        }
        else if (command == "printInorder") {
            avlTree.printInOrder();
        }
        else if (command == "printPreorder") {
            avlTree.printPreOrder();
        }
        else if (command == "printPostorder") {
            avlTree.printPostOrder();
        }
        else if (command == "printLevelCount") {
            avlTree.printLCHelper();
        }
    }
    return 0;
}