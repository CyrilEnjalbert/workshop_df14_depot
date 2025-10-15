#include <iostream>

int main() {
#ifdef PLATFORM_WINDOWS
    std::cout << "Build: Windows\n";
#else
    std::cout << "Build: Linux/Unix\n";
#endif
    std::cout << "Hello from MyWorkshopProject\n";
    return 0;
}
