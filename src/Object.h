#ifndef INKSCAPE_PROTOTYPE_OBJECT_H
#define INKSCAPE_PROTOTYPE_OBJECT_H

#include <string>
#include <sigc++/signal.h>
#include <sigc++/connection.h>
#include <boost/intrusive/list.hpp>

// this causes some warning, but it's only for this prototype
struct Object;
struct delete_disposer
{
    void operator()(Object *delete_this) {
        delete delete_this;
    }
};

typedef boost::intrusive::list_member_hook<boost::intrusive::link_mode<boost::intrusive::auto_unlink>> list_hook;

struct Object {
    std::string name;
    list_hook child_hook;
    boost::intrusive::list<Object, boost::intrusive::constant_time_size<false>,
    boost::intrusive::member_hook<
            Object,
            list_hook,
            &Object::child_hook
    >> children;
    Object* parent;
    sigc::signal<void, Object*> release_signal;
    sigc::connection release_connection;
    Object(const std::string &name) : name(name), parent(NULL){ }
    virtual ~Object() {
        // only for this prototype
        children.clear_and_dispose(delete_disposer());
        release_signal.emit(this);
    }
    void connectRelease(sigc::slot<void, Object*> slot) {
        release_connection = release_signal.connect(slot);
    }
    void disconnectRelease() {
        release_connection.disconnect();
    }
    bool operator==(Object o) {
        return name == o.name;
    }
    bool operator!=(Object o) {
        return name != o.name;
    }
    void addChild(Object* o);
    bool isDescendantOf(Object* o);
};

#endif //INKSCAPE_PROTOTYPE_OBJECT_H
