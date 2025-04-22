#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

// Define the structure for a node in the linked list
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// LinkedList class encapsulates the head pointer and various operations
class LinkedList {
private:
    Node* head;
public:
    // Constructor initializes an empty list
    LinkedList() : head(nullptr) {}

    // Destructor to free allocated memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    // Function to add an element at the beginning of the list
    void addFirst(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // Function to append an element at the end of the list
    void append(int data) {
        Node* newNode = new Node(data);
        
        if (head == nullptr) {
            head = newNode;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        
        current->next = newNode;
    }

    // Function to insert an element at a specific position (0-indexed)
    void insert(int data, int pos) {
        if (pos == 0 || head == nullptr) {
            addFirst(data);
            return;
        }
        
        Node* newNode = new Node(data);
        Node* current = head;
        int currentPos = 0;
        
        while (current->next != nullptr && currentPos < pos - 1) {
            current = current->next;
            currentPos++;
        }
        
        newNode->next = current->next;
        current->next = newNode;
    }

    // Function to delete the first occurrence of a node with the given value
    void deleteNode(int data) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->next->data != data) {
            current = current->next;
        }
        
        if (current->next == nullptr) {
            cout << "Value " << data << " not found in the list." << endl;
            return;
        }
        
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    // Function to search for an element in the list.
    // Returns a pointer to the node if found, otherwise returns nullptr.
    Node* search(int data) {
        Node* current = head;
        
        while (current != nullptr) {
            if (current->data == data) {
                return current;
            }
            current = current->next;
        }
        
        return nullptr;
    }

    // Function to display the linked list
    void display() {
        Node* current = head;
        cout << "Linked List: ";
        while (current != nullptr) {
            // Uncomment the line below to display the data
            // Here we assume the data have one element of type int and one element of pointer type
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

    // Function to remove and return the first element of the list
    int pop() {
        if (head == nullptr) {
            throw runtime_error("List is empty. Cannot pop.");
        }
        
        int poppedData = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        
        return poppedData;
    }
};

int main(){

    // Open the input file "input.txt"
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error opening input.txt" << "\n";
        return 1;
    }

    // Redirect cin to use the file stream, but keep cout as standard output.
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    LinkedList list;
    
    // Process T commands from input
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "addFirst") {
            int x;
            cin >> x;
            list.addFirst(x);
        } else if (command == "append") {
            int x;
            cin >> x;
            list.append(x);
        } else if (command == "insert") {
            int x, pos;
            cin >> x >> pos;
            list.insert(x, pos);
        } else if (command == "delete") {
            int x;
            cin >> x;
            list.deleteNode(x);
        } else if (command == "pop") {
            try {
                int popped = list.pop();
                cout << "Popped: " << popped << "\n";
            } catch (const runtime_error &e) {
                cout << e.what() << "\n";
            }
        } else if (command == "search") {
            int x;
            cin >> x;
            Node* found = list.search(x);
            cout << (found ? "Found" : "Not Found") << "\n";
        } else if (command == "display") {
            list.display();
        }
    }
    return 0;
}
