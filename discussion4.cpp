// Doubly Linked List, Rule of Three, TaskList Methods
// No Worksheet

class TaskList{
private:
  struct Node{
    string task;
    Node* prev;
    Node* next;
  };
  Node* head;
  Node* tail; 
  int size;
public: 
  bool empty();
  int size();
  void addBack(const string& task);
  bool removeFront();
  bool get(int pos, string& task);
  void clear();
  void printAll();
}
