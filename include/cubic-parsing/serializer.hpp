#pragma once

#include <cassert>
#include <cstdint>
#include <map>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <cubic-parsing/options.h>

namespace cubic::parsing {

class CUBIC_PARSING_API Serializer {
public:
    virtual ~Serializer() = default;

    virtual auto write_data(const uint8_t *data, size_t size) -> bool = 0;

    template<typename T>
    void write_raw(const T &value);

    template<typename T>
    void write(const T &value);

    template<typename T>
    void write_object(const T &object);

    void write_string(const std::string_view &string);

    template<typename Key, typename Value>
    void write_map(const std::map<Key, Value> &map, bool write_size = true);

    template<typename Key, typename Value>
    void write_map(const std::unordered_map<Key, Value> &map, bool write_size = true);

    template<typename T>
    void write_array(const std::vector<T> &array, bool write_size = true);

    template<typename T>
    void write_array(const T *array, uint32_t size);
};

template<typename T>
void Serializer::write_raw(const T &value)
{
    [[maybe_unused]]
    bool success
        = this->write_data(reinterpret_cast<const uint8_t *>(&value), sizeof(T));
    assert(success);
}

template<typename T>
void Serializer::write_object(const T &object)
{
    T::serialize(this, object);
}

template<typename T>
void Serializer::write(const T &value)
{
    if constexpr (std::is_trivial<T>::value)
        write_raw(value);
    else
        write_object(value);
}

template<typename Key, typename Value>
void Serializer::write_map(const std::map<Key, Value> &map, bool write_size)
{
    if (write_size)
        write_raw(static_cast<int32_t>(map.size()));

    for (const auto &[key, value] : map) {
        if constexpr (std::is_trivial<Key>::value)
            write_raw<Key>(key);
        else
            write_object<Key>(key);

        if constexpr (std::is_trivial<Value>::value)
            write_raw<Value>(value);
        else
            write_object<Value>(value);
    }
}

template<typename Key, typename Value>
void Serializer::write_map(const std::unordered_map<Key, Value> &map, bool write_size)
{
    if (write_size)
        write_raw(static_cast<int32_t>(map.size()));

    for (const auto &[key, value] : map) {
        if constexpr (std::is_trivial<Key>::value)
            write_raw<Key>(key);
        else
            write_object<Key>(key);

        if constexpr (std::is_trivial<Value>::value)
            write_raw<Value>(value);
        else
            write_object<Value>(value);
    }
}

template<typename T>
void Serializer::write_array(const std::vector<T> &array, bool write_size)
{
    if (write_size)
        write_raw<uint32_t>(static_cast<uint32_t>(array.size()));

    for (const auto &value : array) {
        if constexpr (std::is_trivial<T>::value)
            write_raw<T>(value);
        else
            write_object<T>(value);
    }
}

template<typename T>
void Serializer::write_array(const T *array, uint32_t size)
{
    [[maybe_unused]]
    bool success
        = write_data(reinterpret_cast<const uint8_t *>(array), size * sizeof(T));
    assert(success);
}

template void Serializer::write_raw<uint8_t>(const uint8_t &value);
template void Serializer::write_raw<uint16_t>(const uint16_t &value);
template void Serializer::write_raw<uint32_t>(const uint32_t &value);
template void Serializer::write_raw<uint64_t>(const uint64_t &value);
template void Serializer::write_raw<int8_t>(const int8_t &value);
template void Serializer::write_raw<int16_t>(const int16_t &value);
template void Serializer::write_raw<int32_t>(const int32_t &value);
template void Serializer::write_raw<int64_t>(const int64_t &value);
template void Serializer::write_raw<float>(const float &value);
template void Serializer::write_raw<double>(const double &value);

} // namespace cubic::parsing
