#include <cubic-parser/options.h>
#include <cubic-parser/serializer.hpp>
#include <string_view>

namespace cubic::parser {

void Serializer::write_string(const std::string_view &string)
{
    write_raw(static_cast<uint32_t>(string.size()));
    write_data(reinterpret_cast<const uint8_t *>(string.data()), string.size());
}

} // namespace cubic::parser
