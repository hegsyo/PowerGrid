#ifndef API_BRIDGE_COMBATINFONODE_H
#define API_BRIDGE_COMBATINFONODE_H

#include "MethodHelper.h"
#include "linkedlistnode.h"


namespace RS {

class LinkedList;

class CombatInfoNode : public LinkedListNode {
public:
    RS_OBJECT(CombatInfoNode)

    JACE_PROXY_API LinkedList getData();
private:
    DECLARE_FRIENDS
};

} // namespace bridge

#endif // API_BRIDGE_COMBATINFONODE_H
