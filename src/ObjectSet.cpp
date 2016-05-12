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
    return container.get<hashed>().find(object->name) != container.get<hashed>().end();
}

void ObjectSet::clear() {
    container.clear();
}

int ObjectSet::size() {
    return container.size();
}

void ObjectSet::remove(Object* object) {
    object->disconnectRelease();
    container.get<hashed>().erase(object->name);
    if (anyParentIsInSet(object)) {
        if (object->parent != NULL) {
            remove(object->parent);
            for (auto it = object->parent->children.begin(); it != object->parent->children.end(); ++it) {
                if (&*it != object) {
                    add(&*it);
                }
            }
        }
    }
}

void ObjectSet::print() {
    for (multi_index_container::iterator it = container.begin(); it != container.end(); ++it) {
        std::cout << (*it)->name << " ";
    }
    std::cout << std::endl;
}

bool ObjectSet::anyParentIsInSet(Object *object) {
    Object* o = object;
    while (o != NULL) {
        if (contains(o)) {
            return true;
        }
        o = o->parent;
    }
    return false;
}

void ObjectSet::removeChildrenFromSet(Object *object) {
    for (auto it = object->children.begin(); it != object->children.end(); ++it) {
        Object* o = &*it;
        if (contains(o)) {
            remove(o);
            continue;
        }

        removeChildrenFromSet(o);
    }
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
