#pragma once

#include <iostream>

using namespace std;

class A {
  private:
    string _name;

  public:
    A(string name) : _name(name) {}

    void tip() {
      cout << _name << endl;
    }

    void speak(string words);
};

