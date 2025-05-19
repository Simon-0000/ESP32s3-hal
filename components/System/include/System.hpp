#include <cstdint>
#include <concepts>

typedef uint8_t uniqueId_t;

template<typename T>
concept IsComponent = requires(const T& t, uniqueId_t id) {
    { t.isIdEqualTo(id) } -> std::convertible_to<bool>;
};


class System{
public:
    static uniqueId_t nextValue(){
        return ++count8;//TODO log error when reaching close to 255
    }
    template<typename T>
    static uniqueId_t saveAndGetId() {
        static uniqueId_t componentId = nextValue();
        return componentId;
    }
    
    template<IsComponent U, IsComponent T>
    static U* tryCastTo(T *src){
        if (src->isIdEqualTo(saveAndGetId<U>())) {
            return static_cast<U*>(src);
        }
        return nullptr;
    }

private:
    static inline uniqueId_t count8 = 0;
};


class Component2 {
public:
    virtual bool isIdEqualTo(const uniqueId_t otherId) const = 0;
};
