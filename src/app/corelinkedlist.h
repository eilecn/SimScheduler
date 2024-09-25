#ifndef CORELINKEDLIST_H
#define CORELINKEDLIST_H

#include "core.h"

class CoreLinkedList
{
public:
    CoreLinkedList();
    ~CoreLinkedList();
    void Add(Core* new_core);

private:
 Core* head;

};

#endif
