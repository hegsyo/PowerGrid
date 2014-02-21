#include "animablenode.h"

#include "animable.h"

namespace api {
namespace bridge {

IMPL_JACE_CONSTRUCTORS(AnimableNode)
IMPL_RSCLASS_GET(AnimableNode)

IMPL_OBJECT_METHOD(AnimableNode, getAnimable, Animable)
IMPL_OBJECT_METHOD(AnimableNode, getNext, AnimableNode)

}
}
