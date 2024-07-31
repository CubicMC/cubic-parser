#pragma once

#include <cassert>
#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <cubic-parsing/options.h>

namespace cubic::parsing {

class CUBIC_PARSING_API Parser {
public:
    virtual ~Parser() = default;

    virtual auto read_data(uint8_t *data, size_t size) -> bool = 0;

    template<typename T>
    void read_raw(T &value);

    template<typename T>
    void read(T &value);

    template<typename T>
    void read_object(T &object);

    void read_string(std::string &string);

    template<typename Key, typename Value>
    void read_map(std::map<Key, Value> &map, uint32_t size = 0);

    template<typename Key, typename Value>
    void read_map(std::unordered_map<Key, Value> &map, uint32_t size = 0);

    template<typename T>
    void read_array(std::vector<T> &array, uint32_t size = 0);

    template<typename T>
    void read_array(T *array, uint32_t size);
};

template<typename T>
void Parser::read_raw(T &value)
{
    [[maybe_unused]]
    bool success
        = this->read_data(reinterpret_cast<uint8_t *>(&value), sizeof(T));
    assert(success);
}

template<typename T>
void Parser::read_object(T &object)
{
    T::parse(this, object);
}

template<typename T>
void Parser::read(T &value)
{
    if constexpr (std::is_trivial<T>::value)
        read_raw(value);
    else
        read_object(value);
}

template<typename Key, typename Value>
void Parser::read_map(std::map<Key, Value> &map, uint32_t size)
{
    if (size == 0)
        read_raw<uint32_t>(size);

    for (uint32_t i = 0; i < size; i++) {
        Key key;
        if constexpr (std::is_trivial<Key>::value)
            read_raw<Key>(key);
        else
            read_object<Key>(key);

        if constexpr (std::is_trivial<Value>::value)
            read_raw<Value>(map[key]);
        else
            read_object<Value>(map[key]);
    }
}

template<typename Key, typename Value>
void Parser::read_map(std::unordered_map<Key, Value> &map, uint32_t size)
{
    if (size == 0)
        read_raw<uint32_t>(size);

    for (uint32_t i = 0; i < size; i++) {
        Key key;
        if constexpr (std::is_trivial<Key>::value)
            read_raw<Key>(key);
        else
            read_object<Key>(key);

        if constexpr (std::is_trivial<Value>::value)
            read_raw<Value>(map[key]);
        else
            read_object<Value>(map[key]);
    }
}

template<typename T>
void Parser::read_array(std::vector<T> &array, uint32_t size)
{
    if (size == 0)
        read_raw<uint32_t>(size);

    for (uint32_t i = 0; i < size; i++) {
        T value;
        if constexpr (std::is_trivial<T>::value)
            read_raw<T>(value);
        else
            read_object<T>(value);

        array.emplace_back(std::move(value));
    }
}

template<typename T>
void Parser::read_array(T *array, uint32_t size)
{
    if (size != 0)
        assert(array != nullptr);

    for (uint32_t i = 0; i < size; i++) {
        if constexpr (std::is_trivial<T>::value)
            read_raw<T>(array[i]);
        else
            read_object<T>(array[i]);
    }
}

template void Parser::read_raw<uint8_t>(uint8_t &value);
template void Parser::read_raw<uint16_t>(uint16_t &value);
template void Parser::read_raw<uint32_t>(uint32_t &value);
template void Parser::read_raw<uint64_t>(uint64_t &value);
template void Parser::read_raw<int8_t>(int8_t &value);
template void Parser::read_raw<int16_t>(int16_t &value);
template void Parser::read_raw<int32_t>(int32_t &value);
template void Parser::read_raw<int64_t>(int64_t &value);
template void Parser::read_raw<float>(float &value);
template void Parser::read_raw<double>(double &value);

} // namespace cubic::parsing
