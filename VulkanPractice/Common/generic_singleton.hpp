#pragma once
#ifndef generic_singleton_hpp
#define generic_singleton_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>

namespace common{
    
    template <class T>
    class GenericSingleton{
        public:
            static T* get_instance();
        protected:
            static T* m_instance;
            static bool instantiated;
            GenericSingleton(){
                if(instantiated){
                    std::string message = "Trying to create multiple instance of singleton of type";
                    message += typeid(T).name();
                    message += "/n Try using \"get_instance()\" instead of constructor";
                    throw std::runtime_error(message);
                }
                else{
                    std::cout << "new instance of singleton of type: " << typeid(*m_instance).name() << " created" << std::endl;
                    instantiated = true;
                }
            };
    };

    template <class T>
    T* GenericSingleton<T>::m_instance = nullptr;

    template<class T>
    bool GenericSingleton<T>::instantiated = false;

    template <class T>
    T* GenericSingleton<T>::get_instance(){
        if(m_instance != nullptr){
            return m_instance;
        }
        m_instance = new T();
        return m_instance;
    }
}

#endif
