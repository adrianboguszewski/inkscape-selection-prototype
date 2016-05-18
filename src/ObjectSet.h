#ifndef INKSCAPE_PROTOTYPE_OBJECTSET_H
#define INKSCAPE_PROTOTYPE_OBJECTSET_H

#include "Object.h"
#include <string>
#include <unordered_map>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <sigc++/connection.h>

struct hashed{};

typedef boost::multi_index_container<
        Object*,
        boost::multi_index::indexed_by<
                boost::multi_index::sequenced<>,
                boost::multi_index::hashed_unique<
                        boost::multi_index::tag<hashed>,
                        boost::multi_index::identity<Object*>>
        >> multi_index_container;

class ObjectSet {
public:
    ObjectSet() {};
    ~ObjectSet() {};
    bool add(Object* object);
    void clear();
    bool contains(Object* object);
    int size();
    bool remove(Object* object);
    void print();

private:
    bool anyParentIsInSet(Object* object);
    void removeChildrenFromSet(Object *object);
    void _remove(Object* object);
    void _add(Object* object);
    multi_index_container container;
    std::unordered_map<Object*, sigc::connection> releaseConnections;
};


#endif //INKSCAPE_PROTOTYPE_OBJECTSET_H
