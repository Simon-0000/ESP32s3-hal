#include "Enableable.hpp"

EnableableSmart::EnableableSmart() : isEnabled_(std::make_shared<bool>(false)) {}
EnableableSmart::EnableableSmart(std::shared_ptr<bool> isEnabled) : isEnabled_(isEnabled){}
EnableableSmart::EnableableSmart(const EnableableSmart* other) : isEnabled_(other->isEnabled_){}

esp_err_t EnableableSmart::start() {
    esp_err_t err = ESP_ERR_INVALID_STATE;
    if(*isEnabled_ == false){
        *isEnabled_ = true;
        err = enableOnce();
    }
    if(!childrenAreEnabled_)
    {
        childrenAreEnabled_ = true;
        Bindable::syncChildren();
    }

    return err;
}

esp_err_t EnableableSmart::stop() {
    esp_err_t err = ESP_ERR_INVALID_STATE;

    if(*isEnabled_){
        *isEnabled_ = false;
        err = disableOnce();
    }

    if(childrenAreEnabled_)
    {
        childrenAreEnabled_ = false;
        Bindable::syncChildren();
    }
    return err;
}

esp_err_t EnableableSmart::toggle() {
    if(*isEnabled_)
        return stop();
    else
        return start();
}

inline bool EnableableSmart::isEnabled() const{
    return *isEnabled_;
}

void EnableableSmart::syncSelf() {
    if(parent_){
        if (EnableableSmart* enableableParent = System::tryCastTo<EnableableSmart>(parent_)) {
            if(enableableParent->isEnabled())
                start();
            else
                stop();
        }
    }
}
