#include "ObjectSet.h"

bool ObjectSet::add(Object* object) {
    if (anyParentIsInSet(object)) {
        return false;
    }
    removeChildrenFromSet(object);

    _add(object);
    return true;
}

bool ObjectSet::contains(Object* object) {
    return container.get<hashed>().find(object) != container.get<hashed>().end();
}

void ObjectSet::clear() {
    container.clear();
}

int ObjectSet::size() {
    return container.size();
}

bool ObjectSet::remove(Object* object) {
    // object is the top of subtree
    if (contains(object)) {
        _remove(object);
        return true;
    }

    // any parent of object is in the set
    if (anyParentIsInSet(object)) {
        Object* o = object;
        while (o->getParent() != NULL) {
            for (auto &child: o->getParent()->getChildren()) {
                if (&child != o) {
                    _add(&child);
                }
            }
            if (contains(o->getParent())) {
                _remove(o->getParent());
                break;
            }
            o = o->getParent();
        }
        return true;
    }

    // no object nor any parent in the set
    return false;
}

void ObjectSet::print() {
    for (auto& object: container) {
        std::cout << object->getName() << " ";
    }
    std::cout << std::endl;
}

bool ObjectSet::anyParentIsInSet(Object *object) {
    Object* o = object;
    while (o != NULL) {
        if (contains(o)) {
            return true;
        }
        o = o->getParent();
    }

    return false;
}

void ObjectSet::removeChildrenFromSet(Object *object) {
    for (auto& child: object->getChildren()) {
        if (contains(&child)) {
            _remove(&child);
            // there is certainly no children of this child in the set
            continue;
        }

        removeChildrenFromSet(&child);
    }
}

void ObjectSet::_remove(Object *object) {
    releaseConnections[object].disconnect();
    releaseConnections.erase(object);
    container.get<hashed>().erase(object);
}

void ObjectSet::_add(Object *object) {
    releaseConnections[object] = object->connectRelease(sigc::mem_fun(*this, &ObjectSet::remove));
    container.push_back(object);
}


