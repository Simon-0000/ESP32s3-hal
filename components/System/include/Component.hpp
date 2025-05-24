#pragma once

#include <concepts>
#include <cstdint>

typedef uint8_t uniqueId_t;


class Component {
public:
    virtual bool isIdEqualTo(const uniqueId_t otherId) const = 0;
};

template<typename T>
concept IsComponent = requires(const T& t, uniqueId_t id) {
    { t.isIdEqualTo(id) } -> std::convertible_to<bool>;
};



//MACROS to create the repetitive component logic
#define GENERATED_COMPONENT_BODY_1(Class) \
public: \
    bool isIdEqualTo(const uniqueId_t otherId) const override { \
        return System::saveAndGetId<Class>() == otherId; \
} \
private:

#define GENERATED_COMPONENT_BODY_2(Class, BASEA) \
public: \
    bool isIdEqualTo(const uniqueId_t otherId) const override { \
        return System::saveAndGetId<Class>() == otherId || BASEA::isIdEqualTo(otherId); \
} \
private:

#define GENERATED_COMPONENT_BODY_3(Class, BASEA, BASEB) \
public: \
    bool isIdEqualTo(const uniqueId_t otherId) const override { \
        return System::saveAndGetId<Class>() == otherId || BASEA::isIdEqualTo(otherId) || BASEB::isIdEqualTo(otherId); \
} \
private:

#define GENERATED_COMPONENT_BODY_4(Class, BASEA, BASEB, BASEC) \
public: \
    bool isIdEqualTo(const uniqueId_t otherId) const override { \
        return System::saveAndGetId<Class>() == otherId || BASEA::isIdEqualTo(otherId) || BASEB::isIdEqualTo(otherId) || BASEC::isIdEqualTo(otherId); \
} \
private:

#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME
#define GENERATED_COMPONENT_BODY(...) \
    GET_MACRO(__VA_ARGS__, GENERATED_COMPONENT_BODY_4, GENERATED_COMPONENT_BODY_3, GENERATED_COMPONENT_BODY_2, GENERATED_COMPONENT_BODY_1)(__VA_ARGS__)
