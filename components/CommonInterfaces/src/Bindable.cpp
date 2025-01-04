#include "Bindable.hpp"

esp_err_t Bindable::linkChild(Bindable* child) {

    if(this == child )//TODO add error here instead of return
        return ESP_ERR_INVALID_ARG;
    else if(children_.contains(child) || createsCircularity(child))
        return ESP_FAIL;

    if(child->parent_)
        child->parent_->children_.erase(child);

    children_.insert(child);
    child->parent_ = this;
    return ESP_OK;
}

void Bindable::syncChildren(){
    for(auto& child: children_)
        child->sync();
}

void Bindable::sync() {  
    syncSelf();
    syncChildren();
}

bool Bindable::createsCircularity(Bindable* child){
    for(auto& c : child->children_)
        if(c->parent_ == child)
            return false;
        else if(c == child || c->createsCircularity(child))
            return true;
    return false;
}
