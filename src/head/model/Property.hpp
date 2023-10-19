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
        T initValue,
        GetterType getterFunc,
        SetterType setterFunc
    ) : value(initValue), getter(getterFunc), setter(setterFunc) {}

    Property(
        GetterType getterFunc,
        SetterType setterFunc
    ) : getter(getterFunc), setter(setterFunc) {}

    operator T () {
        return getter(value);
    }

    Property& operator=(T newValue) {
        setter(this->value, newValue);
        return *this;
    }
};