#include "Bindable.hpp"

// esp_err_t Bindable::linkChild(Bindable* child) {

//     if(this == child )//TODO add error here instead of return
//         return ESP_ERR_INVALID_ARG;
//     else if(children_.contains(child) || createsCircularity(child))
//         return ESP_FAIL;

//     if(child->parent_)
//         child->parent_->children_.erase(child);

//     children_.insert(child);
//     child->parent_ = this;
//     return ESP_OK;
// }

// void Bindable::syncChildren(){
//     for(auto& child: children_)
//         child->sync();
// }

// void Bindable::sync() {  
//     syncSelf();
//     syncChildren();
// }

// bool Bindable::createsCircularity(Bindable* child){
//     for(auto& c : child->children_)
//         if(c->parent_ == child)
//             return false;
//         else if(c == child || c->createsCircularity(child))
//             return true;
//     return false;
// }




void Bindable::syncChildren(){
    for(auto& child: children_)
        child->sync();
}

void Bindable::sync() {  
    syncSelf();
    syncChildren();
}

bool Bindable::isInChildrenTree(Bindable* other) {
    for (auto& child : children_) {
        if(other == child)
            return true;
        else if (child->isInChildrenTree(other))
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
        parent_->children_.erase(this);

    parent->children_.insert(this);
    parent_ = parent;
    return ESP_OK;
}