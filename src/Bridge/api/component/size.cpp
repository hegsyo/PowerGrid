#include "size.h"

using entity::Component;
using jace::JField;
using java::lang::Object;

namespace api {
namespace component {

Size::Size(Object ref, JField<JInt> width, JField<JInt> height, QObject* parent):
    Component(ref, parent), x(width), y(height) {}

int Size::getWidth() {
    Object o = getReference();
    return x.get(o);
}

int Size::getHeight(){
    Object o = getReference();
    return y.get(o);
}

} // namespace component
} // namespace api
