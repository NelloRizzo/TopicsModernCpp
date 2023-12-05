#include <iostream>
#include <string>

template<typename T>
struct Container { 
    using value_type = T; 
    T value;
};

template<typename ContainerT>
void info(const ContainerT& c)
{
    typename ContainerT::value_type T{};
    std::cout << "ContainerT is `" << typeid(decltype(c)).name() << "`\n"
        "value_type is `" << typeid(T).name() << "` and value is: " << c.value << "\n";
}

int main()
{
    Container<int> ci{ 1234 }; info(ci);
    Container<std::string> cs{ "abcde" }; info(cs);
}