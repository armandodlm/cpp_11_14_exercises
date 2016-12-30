#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <memory>

class ListNode
{
public:
    ListNode() = default;
    ~ListNode() = default;
    
    void insert(int value);
    void remove(int value);
    ListNode *find(int value);

private:
    int m_value;
    std::unique_ptr<ListNode> m_next;
};


#endif
