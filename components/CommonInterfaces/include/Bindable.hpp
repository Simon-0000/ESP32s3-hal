#pragma once
#include "esp_err.h"
#include <vector>

class Syncable{
public:
    virtual ~Syncable() = default;
    void syncChildren(uint8_t eventId);
    virtual void syncSelf(uint8_t eventId) = 0;
    virtual esp_err_t linkTo(Syncable* parent);
protected:
    Syncable* parent_ = nullptr;
    std::vector<Syncable*> children_ = {};
private:
    bool isInChildrenTree(Syncable* other);
};
    