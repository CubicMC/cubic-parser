#include <cstdint>

#include <cubic-parser/options.h>
#include <cubic-parser/parser.hpp>

namespace cubic::parser {

void Parser::read_string(std::string &string)
{
    uint32_t size = 0;
    this->read_raw(size);
    string.resize(size);
    this->read_data(reinterpret_cast<uint8_t *>(string.data()), size);
}

} // namespace cubic::parser
