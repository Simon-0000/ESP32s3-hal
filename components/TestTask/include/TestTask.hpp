#pragma once
#include "Task.hpp"

class TestTask : public Task<>{
public:
    TestTask() : Task("test"){}
    void run() override;
    void onInit() override;
    void onStop() override;
    void onSuspend() override;
    void onResume() override;
};