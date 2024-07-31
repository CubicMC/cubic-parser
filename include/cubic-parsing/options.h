#pragma once

// Os detection
#if defined(_WIN32) || defined(_WIN64)
#define CUBIC_PARSING_OS_WINDOWS
#elif defined(__unix__) && defined(__linux__)
#define CUBIC_PARSING_OS_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
#define CUBIC_PARSING_OS_MACOS
#else
#error "Unsupported operating system"
#endif

// Export and import macros
#if defined(CUBIC_PARSING_OS_WINDOWS)
#define CUBIC_PARSING_EXPORT __declspec(dllexport)
#define CUBIC_PARSING_IMPORT __declspec(dllimport)
#else
#define CUBIC_PARSING_EXPORT __attribute__((visibility("default")))
#define CUBIC_PARSING_IMPORT __attribute__((visibility("default")))
#endif

#if defined(CUBIC_PARSING_BUILD)
#define CUBIC_PARSING_API CUBIC_PARSING_EXPORT
#else
#define CUBIC_PARSING_API CUBIC_PARSING_IMPORT
#endif
