#pragma once
#include "esp_err.h"
#include <unordered_set>

template<typename... ChildrenTypes>
class BindableSmart;

class Bindable{
public:
    virtual ~Bindable() = default;
    virtual void syncSelf() = 0;
    void sync();
    void syncChildren();
    virtual esp_err_t linkChild(Bindable* child);
protected:
    bool createsCircularity(Bindable* child);
    Bindable* parent_ = nullptr;
    std::unordered_set<Bindable*> children_ = {};

private:
    template<typename...>
    friend class BindableSmart;
};


template<typename ...ChildrenTypes>
class BindableSmart : public Bindable{
public:
    virtual ~BindableSmart() = default;
    esp_err_t linkChild(Bindable* child) override;
};

#include "../template/Bindable.tpp"
    