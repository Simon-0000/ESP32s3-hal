#pragma once
#include "esp_err.h"
#include <unordered_set>

template<typename... ParentTypes>
class TypedBindable;

class Bindable{
public:
    virtual ~Bindable() = default;
    virtual void syncSelf() = 0;
    void sync();
    void syncChildren();
    virtual esp_err_t linkTo(Bindable* parent);
protected:
    Bindable* parent_ = nullptr;
    std::unordered_set<Bindable*> children_ = {};
private:
    bool isInChildrenTree(Bindable* other);
    template<typename...>
    friend class TypedBindable;
};


template<typename ...ParentTypes>
class TypedBindable : public Bindable{
public:
    virtual ~TypedBindable() = default;
    esp_err_t linkTo(Bindable* parent) override;
protected:
    bool canSyncWithParent_ = false;
private:
    bool isLinkable(Bindable* child);
};

#include "../template/Bindable.tpp"
    