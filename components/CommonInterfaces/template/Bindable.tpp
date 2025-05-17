#include "Bindable.hpp"

template<typename ...ParentTypes>
esp_err_t TypedBindable<ParentTypes...>::linkTo(Bindable* child) {
    const bool isLinkable = ((dynamic_cast<ParentTypes*>(child) != nullptr) || ...);
    return isLinkable? Bindable::linkTo(child) : ESP_ERR_INVALID_ARG;
}
template<typename ...ParentTypes>
bool TypedBindable<ParentTypes...>::isLinkable(Bindable* child){
    return ((dynamic_cast<ParentTypes*>(child) != nullptr) || ...);
} 
