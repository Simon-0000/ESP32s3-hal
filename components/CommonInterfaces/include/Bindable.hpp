#pragma once
#include "esp_err.h"
#include "System.hpp"
#include <vector>

class Bindable: public Component2{
public:
    virtual ~Bindable() = default;
    void syncChildren();
    virtual void syncSelf() = 0;
    virtual esp_err_t linkTo(Bindable* parent);
    bool isIdEqualTo(const uniqueId_t otherId) const override{
        return System::saveAndGetId<Bindable>() == otherId;
    }
protected:
    virtual void onNewParentLink() {};
    template<typename T>
    bool isParentTypeValid(){return dynamic_cast<T>(parent_);}
    
    Bindable* parent_ = nullptr;
    std::vector<Bindable*> children_ = {};
    
private:
    bool isInChildrenTree(Bindable* other);
};
    