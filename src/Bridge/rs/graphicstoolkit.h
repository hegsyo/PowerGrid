#ifndef API_BRIDGE_GRAPHICSTOOLKIT_H
#define API_BRIDGE_GRAPHICSTOOLKIT_H

#include "MethodHelper.h"
#include "java/lang/object.h"
using namespace java::lang;


namespace RS {

class GraphicsToolkit : public Object {
public:
    RS_OBJECT(GraphicsToolkit)

    JACE_PROXY_API JInt getIndex();
private:
    DECLARE_FRIENDS
};

} // namespace bridge

#endif // API_BRIDGE_GRAPHICSTOOLKIT_H
