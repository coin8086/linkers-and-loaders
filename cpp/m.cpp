#include "a.h"

A a("Bob");

int main() {
  a.tip();
  a.speak("Hi!");

  A a2("Dave");
  a2.tip();
  a2.speak("Oh!");
  return 0;
}
