#include "itemnode.h"


namespace RS {

IMPL_JACE_CONSTRUCTORS_SUPERTYPE(ItemNode, Node)
IMPL_RSCLASS_GET(ItemNode)

IMPL_PRIMITIVE_METHOD(ItemNode, getID, JInt)
IMPL_PRIMITIVE_METHOD(ItemNode, getStackSize, JInt)

} // namespace bridge
