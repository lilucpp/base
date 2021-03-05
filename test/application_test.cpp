#include "../src/Colors.h"
#include "../src/Application.h"

int main() {
    using namespace peanut;
    ColorPrintln(Color::PURPLE, "application path=%s", GetApplicationPath().c_str());
    ColorPrintln(Color::GREEN, "application dir=%s", GetApplicationDir().c_str());

    return 0;
}
