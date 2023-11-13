#ifndef LIST_H //include guards
#define LIST_H

using namespace std; //namespace we are using

template <typename T> //for the structure

class DblLinkedList{ //making the class for the double linked list

    private:
        //all private members
        
        struct ListNode{    //the structure for each list node
            T value;
            ListNode *next; //pointer foreward and backward to make a double linked list
            ListNode *prev;
        };
        
        ListNode *head; //these are the beginning and end of the linked list
        ListNode *tail;

        /*
            purpose: displays the values of each node in the linked list
        */
        void printList(ListNode * displayNode){ //takes the start node

            while(displayNode->next != NULL){ //while we aren't at the end of the list
                cout << *(displayNode->value) << endl; // display the value of the node we are at
                displayNode = displayNode->next; //then move to the next node
            }
        }

        /*
            purpose: recursive function that breaks down the linked list we have a builds up a new sorted linked list
                     it then sends the head of the new sorted linked list back to public mergesort
        */
        typename DblLinkedList<T>::ListNode* mergesort(ListNode * head, ListNode * tail){ //called by public mergesort

            ListNode* nodeOne; //for the split functions
            ListNode * nodeTwo;

            ListNode* sortedHead; //for merge, this is the beginning of the sorted list we make

            nodeOne = head;
            nodeTwo = tail;

            if(nodeOne == NULL || nodeOne->next == NULL){
                return nodeOne; //base case to exit out of mergesort, when there are only one or zero nodes to sort
            }

            nodeTwo = split(nodeOne, nodeTwo); //splitting the list 

            nodeOne = mergesort(nodeOne, nodeTwo->prev); //splitting list nodes by using nodeOne, splits everything to the left

            nodeTwo = mergesort(nodeTwo, tail); //splitting list nodes by using nodeTwo, splits everything to the right

            sortedHead = merge(nodeOne, nodeTwo); //sortedHead is the head of the sorted list being merged

            return sortedHead; //when done we return the head of the new sorted list

        }
        
        /*
            purpose: merges each node we split up by population into a sorted list
        */
        typename DblLinkedList<T>::ListNode* merge(ListNode *nodeOne, ListNode *nodeTwo){
            if(nodeOne == NULL){

                return nodeTwo; //returning the node that still has value

            }else if(nodeTwo == NULL){

                return nodeOne; //returning the node that still has value 

            }else{

                if(*(nodeOne->value) > *(nodeTwo->value)){ //comparing nodes to find the largest value

                    nodeOne->next = merge(nodeOne->next, nodeTwo); //we want the next pointer to be lower than node one
                    nodeOne->prev = NULL; //nodeone is the head
                    nodeOne->next->prev = nodeOne;  //remake the link so the list goes both ways
                    return nodeOne; //we assign node one to the right place

                }else{

                    nodeTwo->next = merge(nodeOne, nodeTwo->next); //we get the next node smaller than nodeTwo
                    nodeTwo->prev = NULL; //nodetwo is the head
                    nodeTwo->next->prev = nodeTwo; //remake the links so the list goes both ways
                    return nodeTwo; //assign nodetwo to the right place

                }
            }
        }


        /*
            purpose: splits the linked list into  multiple smaller "linked lists" until each list has one or no nodes
                     which we then use merge to build into one sorted linked list
        */
        typename DblLinkedList<T>::ListNode* split(ListNode * nodeFirst, ListNode * nodeLast){
            ListNode * foreNode; //navigates the list going foreward
            ListNode * backNode; //navigates the list going backwards
            ListNode * midNode; //middle node position we use to split
            
            foreNode = nodeFirst; //assign the foreward and backward nodes to proper values being sent in
            backNode = nodeLast;

            if(nodeFirst == NULL){
                return NULL; // if we have no list to traverse 
            }
            while(foreNode->next != backNode->prev && foreNode->next != backNode){ 
                //runs until either forenode and backnode point to same node or if forenode is pointing at backnode.

                foreNode = foreNode->next; //moves each pointer accordingly
                backNode = backNode->prev;
            }
            midNode = foreNode->next; //then we assign midnode to the middle node
            foreNode->next = NULL; //and sever the list
         return midNode;
        }

    public:

    /*
        creates the linked list
    */
    DblLinkedList(){ //constructor, making the list/setting head and tail to null

        head = NULL;
        tail = NULL;
    }

    /*
        destructs the list
    */
    ~DblLinkedList(){ //destructor

        ListNode* tempNode;
        tempNode = head->next; //making a temporary node to traverse list

        while(tempNode->next != NULL){ //while there are still nodes in the list

            delete head; //we delete head and assign heads new node to tempnode
            head = tempNode;
            tempNode = tempNode->next; //then we move tempnode up 
        }
    }

    /*
        prints out the values of each node in the list by calling the private printList function
    */
    void printList(){

        ListNode * displayNode; //getting the display node to throw into printlist (private function)
        displayNode = head; //setting display node

        printList(displayNode); //calling private printlist
    }

    /*
        purpose: appends a node to the end of the double linked list
    */
    void appendNode(T neoValue){ //appending a node to end of list

        ListNode * neoNode;
        neoNode = new ListNode; //making a new node and assigning the value to said node
        neoNode->value = neoValue;
        neoNode->next = NULL;
        neoNode->prev = NULL; //setting next/prev to null

        if(!head){ //if there is no list

            head = neoNode; //head and tail become the new node
            tail = neoNode;

        }else{ //if there is a list

            tail->next = neoNode; //tail points to the new node
            neoNode->prev = tail; //node now points to where tail is as tail is behind it
            tail = neoNode; //tail becomes the new node
        }
    }

    /*
        purpose: calls the private mergesort function and finds the end of the new sorted list 
    */
    void mergesort(){
        ListNode * newHead; //variable used to keep the start of the sorted list

        newHead = mergesort(head, tail); //assigning the newhead to the sorted list

        ListNode * temp = newHead; //variable used for finding the end of the list

        while(temp->next != NULL){
            temp = temp->next; //while loop for traversing the new sorted list until we reach the end
        }
        tail = temp; //when we reach the end we assign tail to the end node of the sorted list

    }


    //NOTE: EACH VARIANT OF SELECTION SORT DOES NOT WORK, PROCEED AT YOUR OWN RISK
    /*
        this selectionsort used two different variables to keep track of both the element we are starting with and the element we are comparing
        it used c++ built in swap function, so i didn't write one for this sort
    */

    /*void selectionSort(){
        //listnode for minimum value
        //listnode for swap
        //listnode to traverse that equals head and increase in first for loop
        //head and tail
        ListNode * minNode;
        ListNode * indexNode;
        ListNode * startNode;
        ListNode * elementNode;

        elementNode = head;

        cout <<"a";

        //loop to go through each element
        //set minimum value equal to starting node
        while(indexNode!=NULL){
            
            minNode = indexNode;
            startNode = indexNode;
            
            cout << "index node before loop (incremental)" << *(indexNode->value) << endl;
            while(indexNode!=NULL){
                if(*(indexNode->value) < *(minNode->value)){
                    minNode = indexNode;
                    //cout << "minNode reassign " <<endl;
                }
                indexNode = indexNode->next;
                //cout << " index moved up " << endl;
            }


            swap(startNode, minNode);

            elementNode = elementNode->next;
            indexNode = elementNode;
            //cout << "index node set to next element " << endl;
        }

        //nested loop to take element we are starting with and comparing it to each one after
        //if node travelling greater than min val, store it and keep going
        //then call swap
        //then start again
        
    }

    void selectionSort(){
        //listnode for minimum value
        //listnode for swap
        //listnode to traverse that equals head and increase in first for loop
        //head and tail
        ListNode * minNode;
        ListNode * indexNode;
        ListNode * startNode;

        indexNode = head;

        cout <<"a";

        //loop to go through each element
        //set minimum value equal to starting node
        while(indexNode!=NULL){
            minNode = indexNode;
            startNode = indexNode;
            //cout << "loop 1 " << *(startNode->value) << endl;
            cout << "index node before loop (incremental)" << *(indexNode->value) << endl;
            while(indexNode!=NULL){
                if(*(indexNode->value) < *(minNode->value)){
                    minNode = indexNode;
                    //cout << "minNode reassign " <<endl;
                }
                indexNode = indexNode->next;
                //cout << " index moved up " << endl;
            }
            //cout << "minnode " << *(minNode->value) << endl;
            //cout << "startnode" << *(startNode->value) << endl;
            cout << endl << "startnode before swap " << *(startNode->value) << endl;
            swap(startNode, minNode);

            //cout << "loop 2 " << *(startNode->value) << endl;
            indexNode = startNode->next;
            //cout << "index node set to next element " << endl;
        }

        //nested loop to take element we are starting with and comparing it to each one after
        //if node travelling greater than min val, store it and keep going
        //then call swap
        //then start again
        
    }

    void swap(ListNode * highNode, ListNode * lowNode){

        //make new nodes using respective values, delete old nodes and insert new ones
        //use node before->next instead of actual node, keep track of said nodes
        //point to new nodes after old node deletion? 


        ListNode * swapNode;
        swapNode = highNode;
        swapNode->next = highNode->next;
        swapNode->prev = highNode->prev;

        highNode = lowNode;
        highNode->next = lowNode->next;
        highNode->prev = lowNode->prev;

        lowNode = swapNode;
        lowNode->next = swapNode->next;
        lowNode->prev = swapNode->prev;

        cout << endl <<"swap start" << endl;
        //cout << "start at start " <<*(startNode->value) << endl;
        //cout << "low at start " << *(minNode->value) << endl;
        
    }*/

    /*void selectionSort(){
        //listnode for minimum value
        //listnode for swap
        //listnode to traverse that equals head and increase in first for loop
        //head and tail
        ListNode * minNode;
        ListNode * indexNode;
        ListNode * startNode;
        ListNode * startPrev;
        ListNode * minPrev;

        indexNode = head;

        cout <<"a";

        //loop to go through each element
        //set minimum value equal to starting node
        while(indexNode!=NULL){
            minNode = indexNode;
            startNode = indexNode;
            //cout << "loop 1 " << *(startNode->value) << endl;
            cout << "index node before loop (incremental)" << *(indexNode->value) << endl;
            while(indexNode!=NULL){
                if(*(indexNode->value) < *(minNode->value)){
                    startPrev = indexNode->prev;
                    minNode = indexNode;
                    minPrev = minNode->prev;
                    //cout << "minNode reassign " <<endl;
                }
                indexNode = indexNode->next;
                //cout << " index moved up " << endl;
            }
            //cout << "minnode " << *(minNode->value) << endl;
            //cout << "startnode" << *(startNode->value) << endl;
            cout << endl << "startnode before swap " << *(startNode->value) << endl;
            swap(startPrev, minPrev);

            //cout << "loop 2 " << *(startNode->value) << endl;
            indexNode = startNode->next;
            //cout << "index node set to next element " << endl;
        }

        //nested loop to take element we are starting with and comparing it to each one after
        //if node travelling greater than min val, store it and keep going
        //then call swap
        //then start again
        
    }

    void swap(ListNode * highPrev, ListNode * lowPrev){

        //make new nodes using respective values, delete old nodes and insert new ones
        //use node before->next instead of actual node, keep track of said nodes
        //point to new nodes after old node deletion? 
        
        ListNode * highNode = highPrev->next;
        ListNode * lowNode = lowPrev->next;

        //delete highPrev->next;
        //delete lowPrev->next;

        ListNode * swapNode = lowNode;


        highPrev->next = lowNode;
        lowNode->prev = highPrev;
        lowNode->next = highNode->next;

        lowPrev->next = highNode;
        highNode->prev = lowPrev;
        highNode->next = swapNode->next;

        cout << endl <<"swap start" << endl;
    }*/

    


};

#endif
