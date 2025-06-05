#include "Bindable.hpp"

void Bindable::syncChildren(uint8_t eventId){
    for (int i = 0; i < children_.size(); ++i) {
        children_[i]->syncSelf(eventId);
        children_[i]->syncChildren(eventId);

    }
}

bool Bindable::isInChildrenTree(Bindable* other) {
    for (int i = 0; i < children_.size(); ++i) {
        if(other == children_[i])
            return true;
        else if (children_[i]->isInChildrenTree(other))
            return true;
    }
    return false;
}

esp_err_t Bindable::linkTo(Bindable* parent) {
    if(this == parent )//TODO add warning logs here as well
        return ESP_ERR_INVALID_ARG;
    else if(parent_ == parent || isInChildrenTree(parent))
        return ESP_FAIL;

    if(parent_)
        std::erase(parent_->children_,this);
    parent->children_.push_back(this);
    parent_ = parent;
    return ESP_OK;
}