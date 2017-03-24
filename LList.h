#ifndef __LLIST_H
#define __LLIST_H

template<class Elem>
class Link
{
public:
    Elem element;
    Link *next;
    Link(const Elem& elemval, Link *nextval = NULL)
    {
        element = elemval; next = nextval;
    }
    Link(Link *nextval = NULL) { next = nextval; }
};

template<class Elem>
class LList
{
public:
    Link<Elem>* head;
    LList()
    {
        head = new Link<Elem>();
    }

    void removeall()
    {
        Link<Elem> *fence;
        while(head!=NULL)
        {
            fence = head;
            head = head->next;
            delete fence;
        }
    }

    ~LList() { removeall(); }
};

#endif // __LLIST_H
