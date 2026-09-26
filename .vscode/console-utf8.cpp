#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace {
struct Utf8Console {
    Utf8Console() {
        SetConsoleOutputCP(CP_UTF8);
    }
} utf8Console;
}
#endif
