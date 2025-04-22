#include <iostream>
#include <fstream>
using namespace std;

// Define the structure for a node in the circular linked list
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class CircularQueue {
private:
    Node* tail;
    int count;
    const int MAX_SIZE = 8;

public:
    // Constructor initializes an empty queue
    CircularQueue() : tail(nullptr), count(0) {}

    // Destructor to free allocated memory
    ~CircularQueue() {
        if (tail == nullptr) return;
        
        Node* current = tail->next;
        while (current != tail) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete tail;
        tail = nullptr;
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return tail == nullptr;
    }

    // Function to check if the queue is full
    bool isFull() {
        // Max capacity = 8 elements
        return count >= MAX_SIZE;
    }

    // Function to add an element to the end of the queue (enqueue)
    void enqueue(int data) {
        // If the queue is full
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue " << data << "." << endl;
            return;
        }
        
        Node* newNode = new Node(data);
        
        // If queue is empty
        if (isEmpty()) {
            tail = newNode;
            tail->next = tail; // Point to itself
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
        
        count++;
        // Output the information about the enqueued element
        cout << "Enqueued: " << data << " (size: " << count << ")" << endl;
    }

    // Function to remove an element from the front of the queue (dequeue)
    int dequeue() {
        // If the queue is empty
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }
        
        Node* head = tail->next;
        int value = head->data;
        
        // If there's only one element
        if (head == tail) {
            delete head;
            tail = nullptr;
        } else {
            tail->next = head->next;
            delete head;
        }
        
        count--;
        // Output the information about the dequeued element
        cout << "Dequeued: " << value << " (size: " << count << ")" << endl;
        return value;
    }

    // Function to get the front element of the queue (peek)
    int peek() {
        // If the queue is empty
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        
        return tail->next->data;
    }

    // Function to display the queue elements
    void display() {
        // If the queue is empty
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        
        Node* current = tail->next;
        cout << "Queue: ";
        do {
            cout << current->data;
            current = current->next;
            if (current != tail->next) {
                cout << " -> ";
            }
        } while (current != tail->next);
        cout << endl;
    }
};

int main() {
    // Open the input file "input_part3.txt"
    ifstream infile("input_part3.txt");
    if (!infile) {
        cerr << "Error opening input_part3.txt" << "\n";
        return 1;
    }
    
    // Redirect standard input to read from the file
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    CircularQueue cq;
    
    // Process T commands from input_part3.txt
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "enqueue") {
            int x;
            cin >> x;
            cq.enqueue(x);
        } else if (command == "dequeue") {
            cq.dequeue();
        } else if (command == "peek") {
            int front = cq.peek();
            if(front != -1)
                cout << "Front element: " << front << "\n";
        } else if (command == "display") {
            cq.display();
        } else {
            cout << "Unknown command: " << command << "\n";
        }
    }
    
    return 0;
}
