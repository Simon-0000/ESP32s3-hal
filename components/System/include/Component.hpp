// #pragma once
// #include "System.hpp"

// // template<typename T>
// // class Identifiable {
// // public:
// //     // Identifiable(){
// //     //     if(!id_)
// //     //         id_ = ++SystemCounter::count8;
// //     // }
// //     // virtual ~Identifiable() = default;
// //     // static uniqueId_t getId() {
// //     //     return id_;
// //     // }    
// //     // virtual bool isIdEqualTo(const uniqueId_t otherId) const {
// //     //     return getId() == otherId;
// //     // }

// //     // template<typename U>
// //     // bool isA() const {
// //     //     return isIdEqualTo(U::getId()); 
// //     // }
// // private:
// //     static inline uniqueId_t id_ = 0;     
// // };


// template<typename T>
// class Component {
// public:
//     Component(){
//         if(!id_)
//             id_ = System::nextValue();
//     }
//     virtual ~Component() = default;

//     static uniqueId_t getId() {
//         return id_;
//     }    

//     template<ComponentType U>
//     bool isA() const {
//         return isIdEqualTo(U::getId()); 
//     }

//     virtual bool isIdEqualTo(const uniqueId_t otherId) const {
//         return getId() == otherId;
//     }

//     template<ComponentType U>
//     U* tryCastTo() {
//         if (isA<U>()) {
//             return static_cast<U*>(this);
//         }
//         return nullptr;
//     }
// private:
//     static inline uniqueId_t id_ = 0;     

// };



// //TO PICK UP FROM HERE WHEN U DONE FIXING THIS, ALSO ADD PARENT FOR THE CHILDREN WHO DECIDE TO USE THEM (WITH CASTING)