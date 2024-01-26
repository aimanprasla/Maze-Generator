#pragma once
#include <iostream>
using namespace std;

struct Node
{
  Node* next;
  int row;
  int col;
};

class Queue
{
  private:
    Node* head;
    Node* tail;

  public:
    Queue()
    {
      head = nullptr;
      tail = nullptr;
    }
    void enqueue(int, int);
    void dequeue();
    void Print()
    {
      Node* temp = head;
      while(temp != nullptr)
        {
          cout << temp->row << " " << temp->col << endl;
          temp = temp->next;
        }
    }
    Node* top()
    {
      return head;
    }
    bool isEmpty()
    {
      return (head == nullptr);
    }
};
void Queue::enqueue(int row_, int col_)
{
  Node* temp = new Node;
  temp->row = row_;
  temp->col = col_;
  temp->next = nullptr;
  if(isEmpty())
  {
    head = temp;
    tail = temp;
  }
  else
  {
    tail->next = temp;
    tail = temp;
  }
}
void Queue::dequeue()
{
  if(head == tail)
  {
    Node* temp = head;
    head = head->next;
    tail = head;
    delete temp;
  }
  if(!isEmpty())
  {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
}