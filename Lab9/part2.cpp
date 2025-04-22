#include <iostream>
#include <fstream>
using namespace std;

// Define the structure for a node in the doubly linked list
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
public:
    // Constructor initializes an empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor to free allocated memory
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    // Function to add an element at the beginning of the list
    void addFirst(int data) {
        Node* newNode = new Node(data);
        
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }
        
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // Function to append an element at the end of the list
    void append(int data) {
        Node* newNode = new Node(data);
        
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }
        
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // Function to insert an element at a specific position (0-indexed)
    void insert(int data, int pos) {
        if (pos == 0) {
            addFirst(data);
            return;
        }
        
        Node* newNode = new Node(data);
        Node* current = head;
        int currentPos = 0;
        
        while (current != nullptr && currentPos < pos) {
            current = current->next;
            currentPos++;
        }
        
        // If we reached the end, append at the end
        if (current == nullptr) {
            append(data);
            return;
        }
        
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }

    // Function to delete the node at a specific index (0-indexed)
    void deleteAtIndex(int index) {
        // if the index is Invalid or the list is empty
        if (index < 0 || head == nullptr) {
            cout << "Invalid index or empty list." << endl;
            return;
        }
        
        // If deleting the head node
        if (index == 0) {
            Node* temp = head;
            
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
            
            delete temp;
            return;
        }
        
        // Traverse to the node at the given index
        Node* current = head;
        int currentIndex = 0;
        
        while (current != nullptr && currentIndex < index) {
            current = current->next;
            currentIndex++;
        }
        
        // If the index is out of bounds
        if (current == nullptr) {
            cout << "Index out of bounds." << endl;
            return;
        }
        
        // If deleting the tail node
        if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            delete current;
            return;
        }
        
        // Deleting a node in the middle
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
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

    // Function to check whether the doubly linked list is circular using two pointers.
    // The list is considered circular if there is a cycle in the next pointers.
    bool isCircularTwoPointer() {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        
        Node* slow = head;
        Node* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                return true;
            }
        }
        
        return false;
    }

    // Function to display the doubly linked list
    void display() {
        Node* current = head;
        cout << "Doubly Linked List: ";
        while (current != nullptr) {
            // Uncomment the line below to display the data
            // Here we assume the data have one element of type int and one element of pointer type
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    // Open input.txt file for reading
    std::ifstream infile("input_part2.txt");
    if (!infile) {
        std::cerr << "Error opening input.txt" << "\n";
        return 1;
    }
    
    // Redirect cin to read from input.txt
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    DoublyLinkedList dll;
    
    // Process T commands from the input file
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "addFirst") {
            int x;
            cin >> x;
            dll.addFirst(x);
        } else if (command == "append") {
            int x;
            cin >> x;
            dll.append(x);
        } else if (command == "insert") {
            int x, pos;
            cin >> x >> pos;
            dll.insert(x, pos);
        } else if (command == "deleteAtIndex") {
            int idx;
            cin >> idx;
            dll.deleteAtIndex(idx);
        } else if (command == "search") {
            int x;
            cin >> x;
            Node* found = dll.search(x);
            cout << (found ? "Found" : "Not Found") << "\n";
        } else if (command == "display") {
            dll.display();
        } else if (command == "isCircular") {
            cout << "Is the list circular (two-pointer check)? " 
                 << (dll.isCircularTwoPointer() ? "Yes" : "No") << "\n";
        }
    }
    return 0;
}
