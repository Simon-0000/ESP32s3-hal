#pragma once

class Chainable{
public:
    ~Chainable() = default;
    void linkChild(Chainable* child){
        if(child_)
            child_->linkChild(child);
        else
            child_ = child;
    }

    void bindChildrens(){
        if(child_)
            child_->bind(this);
    }

    virtual void bindLocally(Chainable* parent) = 0;
private:

    void bind(Chainable* parent){
        bindLocally(parent);
        bindChildrens();
    }
    Chainable* child_ = nullptr;

};