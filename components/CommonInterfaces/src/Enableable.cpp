#include "Enableable.hpp"
#include "esp_log.h"

EnableableSmart::EnableableSmart() : isEnabled_(std::make_shared<bool>(false)) {}
EnableableSmart::EnableableSmart(std::shared_ptr<bool> isEnabled) : isEnabled_(isEnabled){}
EnableableSmart::EnableableSmart(const EnableableSmart* other) : isEnabled_(other->isEnabled_){}

esp_err_t EnableableSmart::start() {
    esp_err_t err = ESP_ERR_INVALID_STATE;

    if(*isEnabled_ == false){
        err = enableOnce();//the order is important
        *isEnabled_ = true;
        Bindable::syncChildren(System::getUniqueId<EnableableSmart>());

    }
    if(!childrenAreEnabled_)
    {
        childrenAreEnabled_ = true;
    }

    return err;
}

esp_err_t EnableableSmart::stop() {
    esp_err_t err = ESP_ERR_INVALID_STATE;

    if(*isEnabled_){
        err = disableOnce();
        *isEnabled_ = false;
        Bindable::syncChildren(System::getUniqueId<EnableableSmart>());
    }
    return err;
}

esp_err_t EnableableSmart::toggle() {
    if(*isEnabled_)
        return stop();
    else
        return start();
}

bool EnableableSmart::isEnabled() const{
    return *isEnabled_;
}

void EnableableSmart::syncSelf(uint8_t eventId) {
    if(parent_ && eventId == System::getUniqueId<EnableableSmart>()){
        if(static_cast<EnableableSmart*>(parent_)->isEnabled())
            start();
        else
            stop();
    }
}
