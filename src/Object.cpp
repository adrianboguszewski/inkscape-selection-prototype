#include "Object.h"

Object::Object(std::string name) : name(name), parent(NULL) { }

Object::~Object() {
    // only for this prototype
    children.clear_and_dispose(delete_disposer());
    release_signal.emit(this);
}

const std::string& Object::getName() const {
    return name;
}

Object *Object::getParent()  {
    return parent;
}

bool Object::isDescendantOf(Object *o) {
    Object* p = parent;
    while(p != NULL) {
        if (p == o) {
            return true;
        }
        p = p->parent;
    }
    return false;
}

void Object::addChild(Object* o) {
    o->parent = this;
    children.push_back(*o);
}

void Object::connectRelease(sigc::slot<void, Object*> slot) {
    release_connection = release_signal.connect(slot);
}

void Object::disconnectRelease() {
    release_connection.disconnect();
}
