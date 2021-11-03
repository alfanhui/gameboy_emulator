#include "Test.h"

int Test::factorial(int number) {
    return number <= 1 ? number : factorial(number - 1) * number;
}