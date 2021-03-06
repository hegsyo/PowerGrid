#ifndef API_BRIDGE_HARDREFERENCE_H
#define API_BRIDGE_HARDREFERENCE_H

#include "MethodHelper.h"
#include "reference.h"


namespace RS {

class HardReference : public Reference {
public:
    RS_OBJECT(HardReference)

    JACE_PROXY_API Object getHardReference();
private:
    DECLARE_FRIENDS
};

} // namespace bridge

#endif // API_BRIDGE_HARDREFERENCE_H
