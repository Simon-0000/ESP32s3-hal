#pragma once
#include "Component.hpp"

class System{
public:
    static uniqueId_t nextValue(){
        return ++count8;//TODO log error when reaching close to 255
    }
    template<typename T>
    static uniqueId_t saveAndGetId() {
        static uniqueId_t componentId = nextValue();
        return componentId;
    }
    
    template<IsComponent U, IsComponent T>
    static U* tryCastTo(T *src){
        if (src->isIdEqualTo(saveAndGetId<U>())) {
            return static_cast<U*>(src);
        }
        return nullptr;
    }

private:
    static inline uniqueId_t count8 = 0;
};

