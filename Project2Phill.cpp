//Phillip Kimbrel
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
// the creation of course structure for information
struct Course
{
    string number;
    string title;
    vector<string> prerequisites;
};
// Creation of node structure for BST
struct Node{
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};
// BST class creation with search sort and insert functions 
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course) {
        if (course.number < node->course.number) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            } else {
                addNode(node->left, course);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            } else {
                addNode(node->right, course);
            }
        }
    }
Node* searchNode(Node* node, string courseNumber) {
        if (node == nullptr || node->course.number == courseNumber) {
            return node;
        }
        if (courseNumber < node->course.number) {
            return searchNode(node->left, courseNumber);
        } else {
            return searchNode(node->right, courseNumber);
        }
    }
void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.number << ": " << node->course.title << endl;
            inOrder(node->right);
        }
    }
public:
    BinarySearchTree() {
        root = nullptr;
    }
    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        } else {
            addNode(root, course);
        }
    }
    Course* Search(string courseNumber) {
        Node* result = searchNode(root, courseNumber);
        if (result != nullptr) {
            return &result->course;
        }
        return nullptr;
    }
    void PrintInOrder() {
        inOrder(root);
    }
};
// loading data from file putting it into bst
void loadFromFile(string filename, BinarySearchTree& bst) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<string> fields;
        string field;
        stringstream ss(line);
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        
}
Course course;
        course.number = fields[0];
        course.title = fields[1];
        for (size_t i = 2; i < fields.size(); ++i) {
            course.prerequisites.push_back(fields[i]);
        }
        bst.Insert(course);
    }
    file.close();
}

void printCourseInfo(BinarySearchTree& bst, string courseNumber) {
    Course* course = bst.Search(courseNumber);
    if (course != nullptr) {
        cout << "Course Number: " << course->number << endl;
        cout << "Course Title: " << course->title << endl;
        cout << "Prerequisites: ";
        for (const string& prereq : course->prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    } else {
        cout << "Course not found." << endl;
    }
}
// Main menu for load print and search functions
int main() {
    BinarySearchTree bst;
    int choice = 0;

    while (choice !=9)
    {
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course Information" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            loadFromFile("CS 300 ABCU_Advising_Program_Input.csv", bst);
            cout << "Data loaded successfully." << endl;
        } else if (choice == 2) {
            cout << "\nCourse List:" << endl;
            bst.PrintInOrder();
        } else if (choice == 3) {
            string courseNumber;
            cout << "Enter course number: ";
            cin >> courseNumber;
            printCourseInfo(bst, courseNumber);
        } else if (choice == 9) {
            cout << "Exiting Goodbye!" << endl;
        } else if (choice != 9) {
            cout << "Invalid choice." << endl;
        }
    }
        return 0;
}