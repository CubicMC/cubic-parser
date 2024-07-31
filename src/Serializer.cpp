#include <string_view>

#include <cubic-parsing/options.h>
#include <cubic-parsing/serializer.hpp>

namespace cubic::parsing {

void Serializer::write_string(const std::string_view &string)
{
    write_raw(static_cast<uint32_t>(string.size()));
    write_data(reinterpret_cast<const uint8_t *>(string.data()), string.size());
}

} // namespace cubic::parsing
