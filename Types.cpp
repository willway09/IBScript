#include "Types.hpp"
const std::regex Types::stringRegex = std::regex("\\\".*\\\"");
const std::regex Types::intRegex = std::regex("^\\d+$");
const std::regex Types::languageElementRegex = std::regex("^[a-z][A-Za-z]*$");