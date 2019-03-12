#include <iostream>

enum { PRIME, noPRIME };

class Prime
{
    public:
        Prime(int prime_numb): myPrime(prime_numb){}
        ~Prime(){}

        void Show(){ std::cout << " " << myPrime; }
        int Prime_Test(const Prime &);

    private:
        int myPrime;
};

int Prime::Prime_Test(const Prime & newNumb)
{
    if(!(newNumb.myPrime % myPrime))
        return noPRIME;
    else
        return PRIME;
}

class Node
{
    public:
        Node(){}
        virtual ~Node(){}

        virtual void Show() = 0;
        virtual Node * Insert(Prime*) = 0;

    private:
};

class InternalNode: public Node
{
    public:
        InternalNode(Prime *, Node *);
        virtual ~InternalNode()
        {
            delete myNext;
            delete myPrime;
        }

        virtual void Show()
        {
            myPrime->Show();
            myNext->Show();
        }
        virtual Node * Insert(Prime *);

        static int howManyPrime;

    private:
        Node * myNext;
        Prime * myPrime;
};

InternalNode::InternalNode(Prime * newNumb, Node * Next):
myNext(Next),
myPrime(newNumb)
{
    InternalNode::howManyPrime++;
}

Node * InternalNode::Insert(Prime * other_numb)
{
    int result = myPrime->Prime_Test(*other_numb);

    if(result == PRIME)
    {
        myNext = myNext->Insert(other_numb);
        return this;
    }   
    else
        return this;
}

class TailNode: public Node
{
    public:
        TailNode(){}
        virtual ~TailNode(){}

        virtual void Show(){}
        virtual Node * Insert(Prime* );

    private:
};

Node * TailNode::Insert(Prime * numb)
{
    InternalNode * numbNode = new InternalNode(numb, this);
    return numbNode;
}

class HeadNode: public Node
{
    public:
        HeadNode();
        virtual ~HeadNode(){ delete myNext; }

        virtual void Show(){ myNext->Show(); }
        virtual Node * Insert(Prime*);

    private:
        Node * myNext;
};

HeadNode::HeadNode()
{
    myNext = new TailNode;
}

Node * HeadNode::Insert(Prime* numb)
{
    myNext = myNext->Insert(numb);
    return this;
}

class LinkedList
{
    public:
        LinkedList();
        ~LinkedList(){ delete myHead; }

        void ShowAll(){ myHead->Show(); }
        void Insert(Prime*);
    private:
        HeadNode * myHead;
};

LinkedList::LinkedList()
{
    myHead = new HeadNode;
}

void LinkedList::Insert(Prime* numb)
{
    myHead->Insert(numb);
}

int InternalNode::howManyPrime = 0;

int main()
{
    int choice;
    int biggest_numb, last_prim;
    int numb_counter;

    Prime* prime_number;

    LinkedList primeNumbers;

    do
    {
        std::cout << "\nIf you are interested in prime numbers that occur up to a certain number, press 1 \nif the first prime number 'x' is of interest, then press 2.\n";
        std::cin >> choice;

    } while(!((choice == 1) || (choice == 2)));

    switch(choice)
    {
        case 1:
        {
            std::cout << "\tWhat is the given number: \n";
            std::cin >> biggest_numb;


            InternalNode::howManyPrime = 0;

           for(numb_counter=2 ; numb_counter<=(biggest_numb+1) ; numb_counter++)
            {
                prime_number = new Prime(numb_counter);
                primeNumbers.Insert(prime_number);
            }
            delete prime_number;

            std::cout << std::endl << InternalNode::howManyPrime;
            std::cout << " there are a number of prime numbers up to the specified number.\n";
            primeNumbers.ShowAll();

            break;
        }
        case 2:
        {
            std::cout << "\tHow many primes you want?: \n";
            std::cin >> last_prim;

            numb_counter = 2;
            while(InternalNode::howManyPrime < (last_prim))
            {
                prime_number = new Prime(numb_counter);
                primeNumbers.Insert(prime_number);

                ++numb_counter;
            }
            delete prime_number;


            std::cout << std::endl << InternalNode::howManyPrime;
            std::cout << " there are a number of prime numbers up to the specified number.\n";
            primeNumbers.ShowAll();

            break;
        }
    }

    return 0;
}
