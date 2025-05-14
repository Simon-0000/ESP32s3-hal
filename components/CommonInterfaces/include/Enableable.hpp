#pragma once
#include <memory>
#include "esp_system.h"
#include "Bindable.hpp"
class Enableable {
public:
    ~Enableable() = default;
    virtual esp_err_t start() = 0;
    virtual esp_err_t stop() = 0;
};


class EnableableSmart : public Enableable, public BindableSmart<Bindable>{
public:
    EnableableSmart();
    EnableableSmart(std::shared_ptr<bool> isEnabled);
    EnableableSmart(const EnableableSmart* other);

    ~EnableableSmart() = default;
    esp_err_t start() override;
    esp_err_t stop() override;
    esp_err_t toggle();
    inline bool isEnabled() const;

    void syncSelf() override;

protected:
    virtual esp_err_t enableOnce() = 0;
    virtual esp_err_t disableOnce() = 0;
private:
    std::shared_ptr<bool> isEnabled_;//this is a pointer to allow multiple objects to be linked together when enabled
    bool childrenAreEnabled_ = false;
};

