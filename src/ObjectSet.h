#ifndef INKSCAPE_PROTOTYPE_OBJECTSET_H
#define INKSCAPE_PROTOTYPE_OBJECTSET_H

#include "Object.h"
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

struct hashed{};

typedef boost::multi_index_container<
        Object*,
        boost::multi_index::indexed_by<
                boost::multi_index::sequenced<>,
                boost::multi_index::hashed_unique<
                        boost::multi_index::tag<hashed>,
                        boost::multi_index::const_mem_fun<Object, const std::string&, &Object::getName>>
        >> multi_index_container;

class ObjectSet {
public:
    bool add(Object* object);
    void clear();
    bool contains(Object* object);
    int size();
    void remove(Object* object);
    void print();

private:
    bool anyParentIsInSet(Object* object);
    void removeChildrenFromSet(Object *object);
    multi_index_container container;
};


#endif //INKSCAPE_PROTOTYPE_OBJECTSET_H
