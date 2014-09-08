#include "mapper.h"
#include "world.h"
#include "component.h"

namespace entity {

Mapper::Mode Mapper::getMode(Component *c) {
    if (!c) {
        return Undefined;
    }
    HashableComponent* hc = qobject_cast<HashableComponent*>(c);
    if (hc) {
        return HashMode;
    } else {
        return TreeMode;
    }
}

Mapper::Mapper(QString type, bool init, World* parent, Mode m) :
        QObject(parent), mode(m), type(type) {
    if (parent == NULL) {
        parent = World::instance();
        setParent(parent);
    }
    // Connect to the specified World.
    if (init) {
        parent->initMapper(this);
    }
}

bool Mapper::contains(Entity* e) const{
    Component* cmp = e->get(type);
    if (cmp) {
        switch(getMode(cmp)) {
        case TreeMode:
            return *(map.find(cmp)) == e;
        case HashMode:
            return *(hashMap.find(qobject_cast<HashableComponent*>(cmp))) == e;
        default:
            return false;
        }
    } else {
        // if the entity doesn't have the expected Component type,
        // it cannot be in this Mapper
        return false;
    }
}

Entity* Mapper::getEntity(Component* key) const {
    if (key->metaObject()->className() != type) {
        return NULL;
    }
    switch (getMode(key)) {
    case TreeMode:
        return map.value(key, NULL);
    case HashMode:
        return hashMap.value(qobject_cast<HashableComponent*>(key), NULL);
    default:
        return NULL;
    }
}

QString Mapper::getMappedType() const {
    return type;
}

void Mapper::remove(Entity* e, Component* cmp){
    if (e != NULL && getEntity(cmp) == e) {
        switch(getMode(cmp)) {
        case TreeMode:
            map.remove(cmp);
            break;
        case HashMode:
            hashMap.remove(qobject_cast<HashableComponent*>(cmp));
            break;
        case Undefined:
            return;
        }
    }
}

void Mapper::add(Entity* e, Component* cmp){
    if (cmp->metaObject()->className() == type) {
        switch(getMode(cmp)) {
        case TreeMode:
            map.insert(cmp, e);
            break;
        case HashMode:
            hashMap.insert(qobject_cast<HashableComponent*>(cmp), e);
            break;
        case Undefined:
            return;
        }
    }
}

} // namespace entity