#ifndef GRAPHICSTOOLKIT_H
#define GRAPHICSTOOLKIT_H

#include "jniobject.h"
#include "matrix4f.h"

namespace world{

class GraphicsToolkit : public jni::JNIObject {
private:
    Q_DISABLE_COPY(GraphicsToolkit)
    jint index;
    jfloat absolutex;
    jfloat multiplierx;
    jfloat absolutey;
    jfloat multipliery;
    Matrix4f* matrix4f;
public:
    GraphicsToolkit(jobject obj) : JNIObject(obj){}
    jint getIndex(bool useCache = true);
};

}

#endif // GRAPHICSTOOLKIT_H