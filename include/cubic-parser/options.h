#pragma once

// Os detection
#if defined(_WIN32) || defined(_WIN64)
#define CUBIC_PARSER_OS_WINDOWS
#elif defined(__unix__) && defined(__linux__)
#define CUBIC_PARSER_OS_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
#define CUBIC_PARSER_OS_MACOS
#else
#error "Unsupported operating system"
#endif

// Export and import macros
#if defined(CUBIC_PARSER_OS_WINDOWS)
#define CUBIC_PARSER_EXPORT __declspec(dllexport)
#define CUBIC_PARSER_IMPORT __declspec(dllimport)
#else
#define CUBIC_PARSER_EXPORT __attribute__((visibility("default")))
#define CUBIC_PARSER_IMPORT __attribute__((visibility("default")))
#endif

#if defined(CUBIC_PARSER_BUILD)
#define CUBIC_PARSER_API CUBIC_PARSER_EXPORT
#else
#define CUBIC_PARSER_API CUBIC_PARSER_IMPORT
#endif
