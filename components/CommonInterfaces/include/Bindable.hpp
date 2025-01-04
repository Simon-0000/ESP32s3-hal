#pragma once
#include "esp_err.h"
#include <unordered_set>

class Bindable{
public:
    ~Bindable() = default;
    esp_err_t linkChild(Bindable* child);
    void syncChildren();
    void sync();
    virtual void syncSelf() = 0;
protected:
    Bindable* parent_ = nullptr;
private:
    std::unordered_set<Bindable*> children_ = {};
    bool createsCircularity(Bindable* child);
};
