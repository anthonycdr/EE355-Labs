Name: Anthony Chandra  
Email:ac68801@usc.edu

Part 1: Singly Linked List
This section implements a singly linked list with basic operations, including:

- addFirst(): This adds a node to the beginning of the list
- append(): This adds a node to the end of the list
- insert(): This will insert or add a node at the specified position
- deleteNode(): This will delete the first node containing the specified value
- search(): This will search for a node that has that specific value
- pop(): Removes the first node's value

Part 2: Doubly Linked List
This section builds a doubly linked list, which supports efficient operations at both ends using head and tail pointers. Supported operations include:

- addFirst(): This adds a node to the beginning of the list
- append(): This adds a node to the end of the list
- insert(): This will insert or add a node at the specified position
  (this top 3 is basically the same with singly linked lists)
- deleteAtIndex(): Removes the node at the specified index
- search(): This will search for a node that has that specific value
- isCircularTwoPointer(): Detects cycles using the two-pointer method

Part 2 (Extra): Cycle Detection

The function is explained this way:
- A slow pointer moves one node at a time
- A fast pointer moves two nodes at a time
- If a cycle exists, the two pointers will eventually meet
- If there is no cycle, the fast pointer reaches the end of the list

Part 3: Circular Queue
This section implements a circular queue using a circular linked list. Operations include:

- enqueue(): This will add an element to the rear
- dequeue(): This will remove and return the front element
- peek(): this will return the front element without removing it
- isEmpty(): Checks if the queue is empty
- isFull(): Checks if the queue is basically full or not
- display(): Displays all elements in the queue


