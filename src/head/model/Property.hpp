#include "../cpphead.hpp"

template<typename T>
class Property {
public:
    using ValueType = T;
    using GetterType = std::function<T(ValueType&)>;
    using SetterType = std::function<void(ValueType&, T)>;
private:
    ValueType value;
    GetterType getter;
    SetterType setter;
public:
    Property(
        ValueType initValue,
        GetterType getterFunc,
        SetterType setterFunc
    ) : value(initValue), getter(getterFunc), setter(setterFunc) {}

    operator T () {
        return this->getter(value);
    }

    T& operator* () {
        return this->operator T();
    }

    Property& operator=(T newValue) {
        this->setter(this->value, newValue);
        return *this;
    }
};