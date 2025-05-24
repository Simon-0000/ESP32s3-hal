#pragma once
#include "esp_err.h"
#include "System.hpp"
#include <vector>

class Bindable: public Component{
    GENERATED_COMPONENT_BODY(Bindable);
public:
    virtual ~Bindable() = default;
    void syncChildren();
    virtual void syncSelf() = 0;
    virtual esp_err_t linkTo(Bindable* parent);

    protected:
    Bindable* parent_ = nullptr;
    std::vector<Bindable*> children_ = {};
private:
    bool isInChildrenTree(Bindable* other);
};
    