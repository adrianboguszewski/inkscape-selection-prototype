#include "ObjectSet.h"

bool ObjectSet::add(Object* object) {
    if (anyParentIsInSet(object)) {
        return false;
    }
    removeChildrenFromSet(object);

    object->connectRelease(sigc::mem_fun(*this, &ObjectSet::remove));
    container.push_back(object);
    return true;
}

bool ObjectSet::contains(Object* object) {
    return container.get<hashed>().find(object->getName()) != container.get<hashed>().end();
}

void ObjectSet::clear() {
    container.clear();
}

int ObjectSet::size() {
    return container.size();
}

void ObjectSet::remove(Object* object) {
    object->disconnectRelease();
    container.get<hashed>().erase(object->getName());
    if (anyParentIsInSet(object)) {
        if (object->getParent() != NULL) {
            remove(object->getParent());
            for (auto it = object->getParent()->getChildren().begin(); it != object->getParent()->getChildren().end(); ++it) {
                if (&*it != object) {
                    add(&*it);
                }
            }
        }
    }
}

void ObjectSet::print() {
    for (multi_index_container::iterator it = container.begin(); it != container.end(); ++it) {
        std::cout << (*it)->getName() << " ";
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
    for (auto it = object->getChildren().begin(); it != object->getChildren().end(); ++it) {
        Object* o = &*it;
        if (contains(o)) {
            remove(o);
            continue;
        }

        removeChildrenFromSet(o);
    }
}
