#pragma once
#include "Task.hpp"

class TestTask : public Task<>{
public:
    void run() override;
    void onInit() override;
    void onStop() override;
    void onSuspend() override;
    void onResume() override;
};