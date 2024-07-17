#include<bits/stdc++.h>
using namespace std;

class Node1 {
  private:
  unsigned int account_no;
  int balance;
  Node1* next;

  Node1(unsigned int acc=0)
  {
    account_no=acc;
    balance=1000;
    next=nullptr;
  }
  public:
  int get_bal()
  {
    return balance;
  }

  friend class SLL;
};

class SLL{
  private:
  Node1* first=nullptr;
  Node1* last=nullptr;
  int len=0;

  public:
  void add_node(int acc){
    Node1* temp=first;
    Node1* new_node= new Node1(acc);

   if(first==nullptr)
   {
     first=new_node;
     len++;
     last=new_node;
   }
   else
   {
    while(temp->next!=nullptr)
      {
        temp=temp->next;
      }
    temp->next=new_node;
     len++;
     last=new_node;
   }  
  }

  Node1* get_node_to_acc(int acc)
  {
    Node1* temp=first;
    while(temp!=nullptr)
      {
        if(temp->account_no==acc)
        {
          return temp;
        }
      temp=temp->next;
      }
    return nullptr;
  }

  void transaction(Node1* temp,int x){
    temp->balance+=x;
  }

  int Max(){
    int max=first->balance;
    Node1* temp=first;
    while(temp!=nullptr)
      {
        if(temp->balance>max)
        {
          max=temp->balance;
        }
      temp=temp->next;
      }
   return max;
  }

  void G(int X){
    Node1* temp=first;
    int num=0;
    while(temp!=nullptr)
      {
        if(temp->balance>=X)
        {
          num++;
        }
      temp=temp->next;        
      }
    cout<<num<<endl;
  }

  void M(){
    Node1* temp=first;
    while(temp!=nullptr)
      {
        if(temp->balance==Max())
        {
          cout<<temp->account_no<<" ";
        }
      temp=temp->next;
      }
    cout<<endl;
  }

  void V(int X){
    Node1* temp=first;
    while(temp!=nullptr)
      {
        if(temp->account_no==X)
        {
          cout<<temp->balance<<endl;
          return;
        }
        temp=temp->next;
      }
  }

void printlist(){
  Node1* temp=first;
  while(temp!=nullptr)
    {
      cout<<temp->account_no<<" "<<temp->balance<<endl;;
      temp=temp->next;
    }
}

};

class Node {
private:
  unsigned int account_no;
  int x;
  char op;
  Node* next;
  Node* prev;

  Node(unsigned int account_no=0, int x=0, char op='\0')
  {
    this->x = x;
    this->op=op;
    this->account_no=account_no;
    this->prev = nullptr;
    this->next = nullptr;
  }
 
  friend class DLL;
};

class DLL {

private:
  Node* head=nullptr;
  Node* tail=nullptr;
  Node* cursor=nullptr;
  int length=0;

public:
  DLL()
  {
    head= new Node();
    tail=new Node();
    head->next = tail;
    tail->prev = head;
   cursor=head;
  }
   
  void add_node(unsigned int acc,char op,int x){
      Node* new_node =new Node(acc,x,op);

      (tail->prev)->next=new_node;
      new_node->prev=tail->prev;
      new_node->next=tail;
      tail->prev=new_node;
      length++;
    }

  void F(int X,SLL &list1){
    for(int i=0;i<X;i++)
      {
        if(cursor->next==tail) return;
        cursor=cursor->next;
        forward(cursor,list1);
      }
  }

  void forward(Node* temp,SLL &list1){
    int amount=temp->x;
    if(temp->op=='W')
    {
      amount=(-1)*temp->x;
    }
    list1.transaction(list1.get_node_to_acc(temp->account_no),amount);
  }

  void R(int X,SLL &list1){
    for(int i=0;i<X;i++)
      {
        if(cursor==head) return;
        backward(cursor,list1);
        cursor=cursor->prev;
      }
  }

  void backward(Node* temp,SLL &list1)
  {
    int amount=temp->x;
    if(temp->op=='D')
    {
      amount=temp->x*(-1);
    }
    list1.transaction(list1.get_node_to_acc(temp->account_no),amount);
  }    

  void C(SLL& list1){
    while(cursor->next!=tail)
      {
        cursor=cursor->next;
        forward(cursor,list1);
      }
  }

  void S(int y, SLL& list1){
    Node* temp=head->next;
    while(temp!=cursor->next)
    {
      if(temp->account_no==y)
      {
        cout<<temp->account_no<<" "<<temp->op<<" "<<temp->x<<endl;
      }
      temp=temp->next;
    }
  }

  void I(unsigned int acc,char op,int x,int k, SLL& list1){
    int count=0;
    Node*temp=head;
   
    if(0<=k&&k<=length)
    {
      for(int i=0;i<k;i++)
        {
          temp=temp->next;
          if(temp==cursor)
          {
            count=1;
          }
        }
      Node* new_node =new Node(acc,x,op);

      (temp->next)->prev=new_node;
      new_node->next=temp->next;
      new_node->prev=temp;
      temp->next=new_node;
      length++;
      if(count==0)
      {
        forward(new_node,list1);
      }
    }
  }
 
  void delete_node (Node* to_del){
   (to_del->prev)->next=to_del->next;
   (to_del->next)->prev=to_del->prev;
    length--;
  }

  void D(int M,int A,SLL &list1){
    if(M>0)
    {
      Node* temp=cursor->next;
      while(temp!=tail&&M!=0)
        {
          if(temp->account_no==A)
          {
            delete_node(temp);
             M--;
          }
          temp=temp->next;
         
        }
    }

    if(M<0)
    {
      Node* temp=cursor->prev;
      while(temp!=head&&M!=0)
        {
          if(temp->account_no==A)
          {
            // cout<<"hiiii"<<"\t";
            // cout<<temp->x<<"\t";
            backward(temp,list1);
            delete_node(temp);
             M++;
          }
          temp=temp->prev;
         
        }
      // cout<<endl;
    }
}

 void printlist(){
  Node* temp=head;
  while(temp!=nullptr)
    {
      cout<<temp->account_no<<" ";
      temp=temp->next;
    }
}

};

int main(){
  int C; cin>>C;
  SLL list1;
  for(int i=0;i<C;i++)
    {
      unsigned int acc; cin>>acc;
      list1.add_node(acc);
    }
 
  int N; cin>>N;
  DLL* list2= new DLL();
  for(int i=0;i<N;i++)
    {
      unsigned int a; char op; int x;
      cin>>a>>op>>x;
      list2->add_node(a,op,x);
    }
 
  // list1.printlist(); cout<<endl;
  // list2->printlist(); cout<<endl;
 
  char a;
  while(a!='E')
  {
    if(a=='F')
    {
      int X; cin>>X;
      list2->F(X,list1);
    }

    if(a=='R')
    {
      int Y; cin>>Y;
      list2->R(Y,list1);
    }

    if(a=='C')
    {
      list2->C(list1);
    }

     if(a=='S')
    {
      int Y; cin>>Y;
      list2->S(Y,list1);
    }

     if(a=='G')
    {
      int X; cin>>X;
      list1.G(X);
    }

    if(a=='V')
    {
      int X; cin>>X;
      list1.V(X);
    }

    if(a=='M')
    {
      list1.M();
    }

    if(a=='D')
    {
      int A,M; cin>>A>>M;
      list2->D(M,A,list1);
    }

    if(a=='I')
    {
      unsigned int acc; int x,k; char op;
      cin>>acc>>op>>x>>k;
      list2->I(acc,op,x,k,list1);
    }
    if(a=='P')
    {
       list1.printlist();
    }
    cin>>a;
  }
}