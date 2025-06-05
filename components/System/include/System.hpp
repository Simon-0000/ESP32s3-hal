#pragma once
#include "Component.hpp"

class System{
public:
    template<typename T>
    static uniqueId_t getUniqueId() {
        static uniqueId_t objectId = nextValue();
        return objectId;
    }

private:
    static uniqueId_t nextValue(){
        return ++count8;//TODO log error when reaching close to 255
    }
    static inline uniqueId_t count8 = 0;
};

