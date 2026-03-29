#include<iostream>

class LinkedList{
private:
    struct Node{
        int value;
        struct Node* link;
    };
    Node* head;
public:

    LinkedList(){
        head = nullptr;
    }

    void insertAtHead(int value){
        Node* n = new Node();
        n->value = value;
        n->link = head;
        head = n;
    }

    void insertAtTail(int value){
        Node* novel = new Node();
        novel->link = nullptr;
        novel->value = value;

        if (head == nullptr)
        {
            head = novel;
        }else
        {
            Node* temp = head;
            while (temp->link!=nullptr)
            {
                temp = temp->link;
            }
            temp->link = novel;
        }
    }

    void insertAtPosition(int value, int position){
        Node* novel = new Node();
        novel->value = value;
        novel->link = nullptr;
        if (position==0)
        {
            novel->link = head;
            head = novel;
            return;
        }
        Node* temp1 = head;
        if(head != nullptr){
            for (int i = 0; i < position-1; i++)
            {
                if (temp1->link!=nullptr)
                {
                    temp1=temp1->link;
                }else
                {
                    std::cerr<<"Position out of bounds!\n";
                    return;
                }
                
                
            }
            novel->link = temp1->link;
            temp1->link = novel;
        }
    }

    void deleteAtHead(){
        if(head ==  nullptr){
            return;
        }else
        {
            Node* temp = head;
            head = head->link;
            delete temp;
        }
    }

    void deleteAtTail(){
        if (head==nullptr)
        {
            std::cerr << "Invalid Operation!";
            return;
        }
        
        Node* temp = head;
        if(head->link==nullptr){
            delete temp;
            head = nullptr;
            return;
        }
        Node* temp2 = nullptr;
        while (temp->link!=nullptr)
        {
            temp2 = temp;
            temp = temp->link; 
        }
        delete temp;
        temp2->link = nullptr;
                
    }

    void deleteAtPosition(int position){
        if (head==nullptr)
        {
            std::cerr << "Empty List!\nInvalid operation!";
            return;
        }

        if(position==0){
            if (head->link!=nullptr)
            {
                Node* tem = head->link;
                delete head;
                head = tem;
                return;
            }else{
                delete head;
                head = nullptr;
                return;
            }
            
        }

        if(head->link!=nullptr){
            Node* temp = head;
            for (int i = 0; i < position-1; i++)//This loop will get the pointer to node before the position
            {
                if (temp->link!=nullptr)
                {
                    temp = temp->link;
                }else{
                    std::cerr << "Position out of bounds!";
                    return;
                }
            }
            if (temp->link!=nullptr)
            {
                Node* temp1 = temp->link;//This will get the pointer of the element to delete and with it will come the link to next
                temp->link = temp1->link;
                delete temp1;
            
            }else
            {
                std::cerr << "Position out of bound";
                return;
            }
            
        }else
        {
            std::cerr << "Invalid Position!";
            return;
        }
    }
    
    void printList(){
        Node* temp = head;
        int position = 0;
        while (temp!=nullptr)
        {
            std::cout <<"Position: "<< position++<< "Value: "<<temp->value <<"\n";
            temp = temp->link;
        }
        std::cout << "\n";
    }

    int search(int value){
        int position = 0;
        Node* temp = head;
        while (temp!=nullptr)
        {
            if (temp->value!=value)
            {
                position++;
                temp=temp->link;
            }else
            {
                return position;
            }
                
            
        }
        return -1;
    }
    
    int length(){
        Node* temp = head;
        int counter = 0;
        while (temp!=nullptr)
        {
            counter++;
            temp = temp->link;
        }
        return counter;
    }

    bool hasCycle(){
        if(head==nullptr){
            return false;
        }else if(head->link == nullptr){
            return false;
        }

        Node* temp = head;
        Node* temp1 = head;
        while (temp!=nullptr && temp1!=nullptr)
        {
            temp = temp->link;
            if(temp1->link!=nullptr){
                temp1 = (temp1->link)->link;
            }else{
                return false;
            }
            if(temp==temp1){
                return true;
            }
        }
        return false;
    }

    // void reverse(){
    //     if(head==nullptr){return;}
    //     else if(head->link==nullptr){return;}

    //     Node* prev = nullptr;
    //     Node* current = head;
    //     Node* next = head->link;
    //     while (current!=nullptr)
    //     {
    //         if(next!=nullptr){ 
    //             current->link=prev;
    //             prev = current;
    //             current = next;
    //             next = next->link;
    //         }else
    //         {
    //             current->link=prev;
    //             prev = current;
    //             current=next;
    //         }
    //     }
    //     if(prev!=nullptr&& current==nullptr){
    //         head = prev;
    //     }
        
    // }
    void reverse(){
        if(head==nullptr || head->link==nullptr){return;}

        Node* prev = nullptr;
        Node* current = head;
        while (current!=nullptr)
        {
            Node* next = current->link;
            current->link=prev;
            prev = current;
            current =next;
        }
        head = prev;
        
    }

    ~LinkedList(){
        if (head==nullptr)
        {
            return;
        }
        Node* temp = head;
        while (temp!=nullptr)
        {
            Node* temp2 = temp->link;
            delete temp;
            temp = temp2;
        }
    }
};

class DoublyLinkedList{
private:
    struct Node
    {
        int value;
        Node* previous;
        Node* next;
    };
    Node* head;
    Node* tail;
public:

    DoublyLinkedList(){
        head = nullptr;
        tail = nullptr;
    }

    void insertAtHead(int value){
        Node* createNode = new Node();
        createNode->value = value;
        createNode->previous = nullptr;
        if (head==nullptr)
        {
            head = createNode;
            createNode->next=nullptr;
            tail = createNode;
            return;
        }
        head->previous = createNode;
        createNode->next = head;
        head = createNode;
    }

    void insertAtTail(int value){
        Node* novel = new Node();
        novel->value = value;
        novel->next=nullptr;
        if(head == nullptr)
        {
            novel->previous = nullptr;
            head = novel;
            tail = novel;
            return;
        }else{
            novel->previous = tail;
            tail->next = novel;//This is added after identifying bug! This line was not in the first draft of the code!
            tail = novel;
            return;
        }
    }

    void insertAtPosition(int value, int position){
        Node* novel = new Node();
        novel->value = value;
        if(position == 0 && head == nullptr)
        {
            novel->next=nullptr;
            novel->previous = nullptr;
            head = novel;
            tail = novel;
            return;

        }else if (position==0)
        {
            novel->next = head;
            novel->previous = nullptr;
            head->previous = novel;
            head = novel;
            return;
        }
        
        

        Node* temp = head;
        for (int i = 0; i < position-1; i++)
        {
            if(temp->next!=nullptr)
            {
                temp = temp->next;
            }
            else
            {
                std::cout<<"Position out of bounds!\n";
                delete novel;
                return;
            }
        }
        if (temp->next==nullptr && temp == tail)
        {
            temp->next = novel;
            novel->previous = temp;
            novel->next = nullptr;
            tail = novel;
            return;
        }
        
        (temp->next)->previous = novel;
        novel->next = temp->next;
        novel->previous = temp;
        temp->next=novel;
    }

    void deleteAtHead(){
        if(head!=nullptr)
        {
            if(head->next==nullptr)
            {
                delete head;
                head = nullptr;
                tail=nullptr;
                return;
            }
            Node* temp = head;
            head = head->next;
            head->previous = nullptr;
            delete temp;
        }

    }

    void deleteAtTail()
    {
        if(head==nullptr){
            return;
        }else if(head==tail){
            delete head;
            head = nullptr;
            tail = nullptr;
        }else
        {
            Node* temp = tail;
            tail = tail->previous;
            tail->next = nullptr;
            delete temp;
        }
        
    }

    void deleteAtPosition(int position)
    {
        if(head==nullptr)
        {
            std::cout<<"Emty LinkedList.\nInvalid deletion operation!";
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position; i++)
        {
            if(temp->next!=nullptr)
            {
                temp = temp->next;
            }else
            {
                std::cout<<"Position out of bounds!\n";
                return;
            }
        }
        if(temp==head)
        {
            if (temp->next==nullptr)
            {
                head = nullptr;
                tail = nullptr;
                delete temp;
            }else
            {
            
                head = head->next;
                head->previous = nullptr;
                delete temp;
            }
        }else if(temp == tail)
        {
            tail = tail->previous;
            tail->next = nullptr;
            delete temp;
        }else
        {
            (temp->next)->previous=temp->previous;
            (temp->previous)->next = temp->next;
            delete temp;
        }
    }


    void printForward()
    {
        if(head==nullptr){
            std::cout<<"Empty linked list!";
            return;
        }

        Node* temp = head;
        int countIndx=0;

        while (temp!=nullptr)
        {
            std::cout<<"Element "<<countIndx<<": "<<temp->value<<"\n";
            countIndx++;
            temp=temp->next;
        }
        
    }

    void printBackward()
    {
        if (head==nullptr)
        {
            std::cout<<"Empty linked list!\n";
            return;
        }
        int counter = 0;
        Node* temp = head;
        while (temp!=nullptr)
        {
            counter++;
            temp = temp->next;
        }
        temp = tail;
        while(temp!=nullptr)
        {
            std::cout<<"Element "<<counter<< ": "<<temp->value<<"\n";
            counter--;
            temp=temp->previous;
        }
        
    }

    int search(int value)
    {
        int position = 0;
        Node* temp = head;

        while (temp!=nullptr)
        {
            if (temp->value==value)
            {
                return position;
            }else
            {
                position++;
                temp = temp->next;
            }
        }
        return -1;
    }

    void reversal()
    {
        Node* temp = head;
        while (temp!=nullptr)
        {
            Node* temp1 = temp->next;
            temp->next = temp->previous;
            temp->previous = temp1;
            temp = temp1;
        }
        
        temp = head;
        head = tail;
        tail = temp;

    }

    ~DoublyLinkedList()
    {
        if(head==nullptr)
        {
            return;
        }
        Node* temp = head;
        while (temp!= nullptr)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
        
    }
    

    
};

int main(){

    LinkedList l;
    l.insertAtHead(5);
    l.insertAtTail(6);
    l.insertAtTail(7);
    l.insertAtPosition(8,3);
    l.printList();

    return 0;
}