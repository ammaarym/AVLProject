//#define CATCH_CONFIG_MAIN
//#include <catch2/catch_test_macros.hpp>
//#include <iostream>
//#include <algorithm>
//#include "../src/header.h"
//#include <sstream>
//
//using namespace std;
///*
//	To check output (At the Project1 directory):
//		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
//*/
//
//
//TEST_CASE("Insertion into AVL Tree", "[flag]") {
//    AVLTree tree;
//
//    // Test single insertion
//    tree.insertHelper(12345678, "Alice");
//    REQUIRE(tree.root->id == 12345678);
//    REQUIRE(tree.root->name == "Alice");
//
//    // Test insertion causing a rotation
//    tree.insertHelper(12345677, "Bob");
//    tree.insertHelper(12345676, "Charlie");
//    REQUIRE(tree.root->id == 12345677);
//    REQUIRE(tree.root->name == "Bob");
//    REQUIRE(tree.root->left->id == 12345676);
//    REQUIRE(tree.root->right->id == 12345678);
//}
//
//// Success: All 4 Rotations
//TEST_CASE("Rotation Cases", "[flag]") {
//    AVLTree tree;
//
//    SECTION("Right Rotation (LL)") {
//        tree.insertHelper(30, "C");
//        tree.insertHelper(20, "B");
//        tree.insertHelper(10, "A");
//        REQUIRE(tree.root->name == "B");
//    }
//
//    SECTION("Left Rotation (RR)") {
//        tree.insertHelper(10, "A");
//        tree.insertHelper(20, "B");
//        tree.insertHelper(30, "C");
//        REQUIRE(tree.root->name == "B");
//    }
//
//    SECTION("Left-Right Rotation (LR)") {
//        tree.insertHelper(30, "C");
//        tree.insertHelper(10, "A");
//        tree.insertHelper(20, "B");
//        REQUIRE(tree.root->name == "B");
//    }
//
//    SECTION("Right-Left Rotation (RL)") {
//        tree.insertHelper(10, "A");
//        tree.insertHelper(30, "C");
//        tree.insertHelper(20, "B");
//        REQUIRE(tree.root->name == "B");
//    }
//}
//
//// Success: Deletion of Different Cases
//TEST_CASE("Deletion Cases", "[AVLTree]") {
//    AVLTree tree;
//
//    SECTION("Delete node with no children") {
//        tree.insertHelper(20, "B");
//        tree.removeHelper(20);
//        REQUIRE(tree.root == nullptr);
//    }
//
//    SECTION("Delete node with one child") {
//        tree.insertHelper(30, "C");
//        tree.insertHelper(20, "B");
//        tree.removeHelper(30);
//        REQUIRE(tree.root->name == "B");
//    }
//
//    SECTION("Delete node with two children") {
//        tree.insertHelper(30, "C");
//        tree.insertHelper(20, "B");
//        tree.insertHelper(40, "D");
//        tree.removeHelper(30);
//        REQUIRE(tree.root->name == "D" );
//    }
//    SECTION("Delete node with two children") {
//        tree.insertHelper(30, "C");
//        tree.insertHelper(20, "B");
//        tree.insertHelper(40, "D");
//        tree.removeHelper(30);
//        REQUIRE(tree.root->name == "D");
//    }
//}
//
//// doesn't work
////TEST_CASE("AVLTree Insert Large", "[flag]") {
////    AVLTree tree;
////    std::vector<int> expectedOutput, actualOutput;
////
////    for(int i = 0; i < 100000; i++) {
////        int randomInput = rand();
////        if (count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0) {
////            expectedOutput.push_back(randomInput);
////            tree.insertHelper(randomInput, "RandomNode" + std::to_string(randomInput));
////        }
////    }
////
////
////    REQUIRE(expectedOutput.size() == actualOutput.size());
////    sort(expectedOutput.begin(), expectedOutput.end());
////    REQUIRE(expectedOutput == actualOutput);
////}
//
//// testing incorrect commands
////TEST_CASE("Incorrect Commands", "[AVLTree]") {
////    AVLTree tree;
////
////    // Redirect cout output to a stringstream for capturing
////    std::stringstream ss;
//////    auto old_buf = std::cout.rdbuf(ss.rdbuf());
////
////    SECTION("Invalid name with digits") {
////        tree.insertHelper(45679999, "A11y");
////        REQUIRE(ss.str() == "unsuccessful");
////        ss.str(""); // Clear the stringstream for the next test
////    }
////
////    SECTION("Invalid ID too long") {
////        tree.insertHelper(456799999, "Ally");
////        REQUIRE(ss.str() == "unsuccessful\n");
////        ss.str("");
////    }
////
////    SECTION("Invalid ID too short") {
////        tree.insertHelper(457, "Ally");
////        REQUIRE(ss.str() == "unsuccessful\n");
////        ss.str("");
////    }
////
////    SECTION("Invalid name with special characters") {
////        tree.insertHelper(45679999, "Al#y");
////        REQUIRE(ss.str() == "unsuccessful\n");
////        ss.str("");
////    }
////
////    SECTION("Negative ID") {
////        tree.insertHelper(-4579999, "Ally");
////        REQUIRE(ss.str() == "unsuccessful\n");
////    }
//
//     // Reset cout buffer
////    std::cout.rdbuf(old_buf);
////}
//
//
