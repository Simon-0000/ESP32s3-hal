# CommonInterfaces Overview
This component defines different types of interfaces used by other components in the HAL

# Bindable - Interface Functional Overview
Makes it possible for objects to bind to each other to form a parent/child relationship and allow them to synchronize their state. Each bindable objects points to an its children through an unordered_set. Each child has a reference to its parent. Rebinding a child to an new parent will restructure the old/new links in order to make them coherent. Note that circular loops may happen if unproperly used ([linkChild](#void-linkchildbindable-child)
 doesnt check for it).

In order to implement Bindable, you'll need to [inherit from Bindable and override the syncSelf function](#make-a-class-bindable)
.

</ul>



## Bindable - Application Example

### Basic Initialization and Usage

```
//init the objects
... bindableObjA;
... bindableObjB;


bindableObjA.linkChild(bindableObjB);// A->B
bindableObjB.sync();    //will call syncSelf on bindableObjB 
bindableObjA.sync();    //will call syncSelf on bindableObjA and then on bindableObjB
```

### Make a Class Bindable

```

//CMakeLists.txt:
idf_component_register(.
                    REQUIRES CommonInterfaces)


//MyComponent.hpp
#include "Bindable.hpp"
class MyComponent : public Bindable{
public:
    ...
    void syncSelf() override;
};

```

### Updating Children After Changing State

```
//init the objects
... bindableParentA;
... bindableB;
... bindableC;


bindableParentA.linkChild(bindableB);// A->B
bindableParentA.linkChild(bindableC);// A->C


...//code that updates the state of the parent
bindableParentA.syncChildren();// Sync our children because the parent has a new state.
                               // Will call syncSelf on bindableB, bindableC
```

### Relinking to a New Parent

```
    ... bindableParentA;//init the objects
    ... bindableParentB;
    ... bindableC;
    

    bindableParentA.linkChild(bindableC);// A->C, B

    bindableParentA.sync();//will call syncSelf on bindableParentA, bindableC
    bindableParentB.sync();//will call syncSelf on bindableParentB

    ...

    //linking to a new parent
    bindableParentB.linkChild(bindableC);// B->C, A

    bindableParentA.sync();//will call syncSelf on bindableParentA
    bindableParentB.sync();//will call syncSelf on bindableParentB, bindableC

```




## Bindable - API Reference
### Header File
```
#include "Bindable.hpp"
```
### Public Functions
#### ```void linkChild(Bindable* child)```
<span>Links a child and its own children to a new parent. Also unlinks itself and its children from the old parent (if it had one)</span>

<b>Parameters:</b>
<ul> 
<li>child -- Pointer to a Bindable object that needs to be linked</li>
</ul>

<b>Returns:</b>
<ul> 
<li>ESP_OK -- linked successfully</li>
<li>ESP_ERR_INVALID_ARG -- We are trying to link an object to itself</li>
<li>ESP_FAIL -- The object was already linked</li>

</ul>

#### ```void sync()```
<span>Syncs the object and its children</span>

#### ```void syncChildren()```
<span>Syncs the children of an object</span>


#### ```void syncSelf() = 0```
<span>Function that is overrided by classes in order to implement this interface. This allows each object to define a logic to follow when syncing to a parent</span>

### Protected Attributes

#### ```Bindable* parent_ ```
<span>Pointer to the parent of the object, nullptr if there are none. Can be used in syncSelf to interact with the parent</span>



# Enableable Functional overview
Makes it possible for objects to be enabled or disabled. EnableableSmart implements Enableable and Bindable and allows the object to keep track of its state which makes it possible to alert others if it changed state. EnableableSmart overrides syncSelf to allow itself to follow its parent enabled/disabled state.  

In order to implement Enableable, you'll need to [inherit from Enableable and override the start and stop functions](#make-a-class-enableable).

In order to implement EnableableSmart, you'll need to [inherit from EnableableSmart, override the enableOnce and disableOnce functions, choose 1 of 3 ways of providing its state variable and if you override syncSelf, it is recommended to call EnableableSmart's version of it inside that function](#make-a-class-enableablesmart).

</ul>



## Bindable - Application Example

### Basic Initialization and Usage of Enableable

```
//init the object
... enableableObj;


enableableObj.start();
...
enableableObj.stop();
```

### Basic Initialization and Usage of EnableableSmart

```
//init the object
... enableableSmartA;
... enableableSmartB;
... enableableSmartC(&enableableSmartA);//share the same state as enableableSmartA
... enableableSmartD;

enableableSmartA.linkChild(enableableSmartB);// A->B
enableableSmartC.linkChild(enableableSmartD);// C->D

...

enableableSmartA.start();// will call enableOnce() on enableableSmartA and enableableSmartB
enableableSmartC.start();// will call enableOnce() on enableableSmartD
...

enableableSmartC.stop();// will call disableOnce() on enableableSmartC and enableableSmartD
enableableSmartA.stop();// will call disableOnce() on enableableSmartB


enableableSmartA.stop();// wont do anything because its already stopped
enableableSmartC.stop();// wont do anything because its already stopped

```

### Make a Class Enableable

```

//CMakeLists.txt:
idf_component_register(.
                    REQUIRES CommonInterfaces)


//MyComponent.hpp
#include "Enableable.hpp"
class MyComponent : public Enableable{
public:
    ...
    esp_err_t start() override;
    esp_err_t stop() override;
};
```

### Make a Class EnableableSmart

```

//CMakeLists.txt:
idf_component_register(.
                    REQUIRES CommonInterfaces)


//MyComponent.hpp
#include "Enableable.hpp"
class MyComponent : public EnableableSmart{
public:
    MyComponent() {}// implicit call to the Enableable default constructor
                    // which creates a shared_ptr to contain the state

    //MyComponent() : Enableable(isEnabled_) {}// SECOND METHOD used to create the shared_ptr outside
                        // the class, which allows us to control the lifetime and reach of that state

    MyComponent(MyComponent& other) : EnableableSmart(&other) {}// THIRD METHOD used to share the state of an other EnableableSmart object
                                                                // (CAREFUL, this will not make them share a parent-child link, only the state so enabling 
                                                                // one wont enable the other, only prevent the other one from calling enableOnce to itself 
                                                                // after(because it thinks its already enabled)) (ex use case: Motor using a TimerPWM)

    void syncSelf() override // OPTIONAL
    {
        EnableableSmart::syncSelf();
        ...
    }
protected:
    esp_err_t enableOnce() override;
    esp_err_t disableOnce() override;
private:
    static inline std::shared_ptr<bool> isEnabled_ = make_shared<bool>(false);//example of a state
                        // used by the second constructor. This variable shares the enabled state accross
                        // all instance of this class

};
```



## Enableable - API Reference
### Header File
```
#include "Enableable.hpp"
```

### Public Functions


#### ```esp_err_t start()```
<span>Starts/Enables the object</span>

<b>Returns:</b>
<ul> 
<li>ESP_OK -- started successfully</li>
<li>Other error codes -- Failed to start. Depends on the overridden function. </li>
</ul>

#### ```esp_err_t stop()```
<span>Stops/Disables the object</span>

<b>Returns:</b>
<ul> 
<li>ESP_OK -- stopped successfully</li>
<li>Other error codes -- Failed to stop. Depends on the overridden function. </li>
</ul>

## EnableableSmart - API Reference
### Header File
```
#include "Enableable.hpp"
```

### Public Functions

#### ```EnableableSmart()```
<span>creates a new state variable (shared_ptr) in order to use it in the functions</span>

#### ```EnableableSmart(std::shared_ptr<bool> isEnabled)```
<span>Use the given shared_ptr as the state variable for the class functions</span>

<b>Parameters:</b>
<ul> 
<li>isEnabled -- shared_ptr from an external source that is will be used as the state variable</li>
</ul>

#### ```EnableableSmart(const EnableableSmart* other)```
<span>Use the state variable of the given EnableableSmart in order to use that variable in the functions</span>

<b>Parameters:</b>
<ul> 
<li>other -- pointer to a EnableableSmart that will provide its state variable which will be referenced in the new EnableableSmart instance</li>
</ul>

#### ```esp_err_t start()```
<span>Starts/Enables the object and its children if they were not previously enabled</span>

<b>Returns:</b>
<ul> 
<li>ESP_OK -- started successfully</li>
<li>ESP_ERR_INVALID_STATE -- was already started, so it cannot start again</li>
<li>Other error codes -- Failed to start. Depends on the overridden function. </li>
</ul>


#### ```esp_err_t stop()```
<span>Stops/Disables the object and its children if they were not previously disabled</span>


<b>Returns:</b>
<ul> 
<li>ESP_OK -- stopped successfully</li>
<li>ESP_ERR_INVALID_STATE -- was already stopped, so it cannot stop again</li>
<li>Other error codes -- Failed to stop. Depends on the overridden function. </li>
</ul>

#### ```esp_err_t toggle()```
<span>Toggle the object and its children between their start/stop state </span>


<b>Returns:</b>
<ul> 
<li>ESP_OK -- toggled successfully</li>
<li>Other error codes -- Failed to toggle to the other state. Depends on the overridden function( [disableOnce](#esp_err_t-disableOnce) ) </li>
</ul>

#### ```bool isEnabled()```
<span>Gives the value of the current enabled state</span>


<b>Returns:</b>
<ul> 
<li>true -- object is enabled</li>
<li>false -- object is disabled</li>
</ul>

#### ```void syncSelf()```
<span>Function from  the Bindable interface that is overriden in order to sync an object's enabled/disabled state according to its parent's state (Enabling a parent will enable its children and theirs....).</span>


### Protected Functions

#### ```esp_err_t enableOnce() = 0```
<span>Function that is overrided by classes in order to implement this interface. This function should contain the code that is needed to enable the object</span>

<b>Returns:</b>
<ul> 
<li>ESP_OK -- enabled successfully</li>
<li>Other error codes -- Failed to enable. Depends on the overridden function. </li>
</ul>

#### ```esp_err_t disableOnce() = 0```
<span>Function that is overrided by classes in order to implement this interface. This function should contain the code that is needed to disable the object</span>

<b>Returns:</b>
<ul> 
<li>ESP_OK -- disabled successfully</li>
<li>Other error codes -- Failed to disable. Depends on the overridden function. </li>
</ul>



## Authors 
Simon Asmar
<br>MachinePM, Organization
## License
This project is not to be shared unless you have received the approbation of its contributors.
