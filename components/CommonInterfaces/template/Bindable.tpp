#include "Bindable.hpp"

template<typename ...ChildrenTypes>
esp_err_t BindableSmart<ChildrenTypes...>::linkChild(Bindable* child) {
    const bool isLinkable = ((dynamic_cast<ChildrenTypes*>(child) != nullptr) || ...);
    return isLinkable? Bindable::linkChild(child) : ESP_ERR_INVALID_ARG;
}
