#ifndef COMPONENT_SPEED_H
#define COMPONENT_SPEED_H

#include "entity/component.h"

using entity::Component;

namespace component {

class Speed : public Component {
    Q_OBJECT
    Q_DISABLE_COPY(Speed)
private:
    double value;
public:
    explicit Speed(double speed, entity::Entity *parent = 0);
    double getCurrentSpeed() const { return value; }
};

} // namespace component

#endif // COMPONENT_SPEED_H