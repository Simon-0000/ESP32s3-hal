#pragma once
#include "esp_err.h"
#include <vector>

class Bindable{
public:
    virtual ~Bindable() = default;
    void syncChildren(uint8_t eventId);
    virtual void syncSelf(uint8_t eventId) = 0;
    virtual esp_err_t linkTo(Bindable* parent);
protected:
    Bindable* parent_ = nullptr;
    std::vector<Bindable*> children_ = {};
private:
    bool isInChildrenTree(Bindable* other);
};
    