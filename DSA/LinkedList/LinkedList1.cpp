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
            Node* temp;
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
                    std::cerr<<"Position out of bounds!";
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


    
};

int main(){
    return 0;
}