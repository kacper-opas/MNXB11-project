
#include "Example.h"

double square(double input) { return input * input; }

void square_vector_elements(std::vector<double>& data) {
  // A Range-based for loop that modifies the elements (using a reference)
  for (auto& element : data) {
    // Equivalent to writing element = element * element;
    element *= element;
    // Could use the square function and assignment
    // element = square(element);
  }
}

void print_elements(const std::vector<double>& data) {
  for (auto element : data) {
    std::cout << element << std::endl;
  }
}

// Remember: Outside of the class declaration we need to prefix the name of the
// member function with the name of the class and two : to tell the compiler
// that we are referencing the function with that name inside of the class

// const is part of the signature so it has to be here as well
//
// override is not part of the signature and shouldn't be included here
void Example::print() const {
  std::cout << "I am being printed from the derived class!" << std::endl;

  std::cout << "I have some data in the form of member variables that  we can "
               "print as well:";
  std::cout << "This is the contents of the some_data member variable "
            << some_data << std::endl;
  std::cout << "This is the contents of the some_data member variable but "
               "accessed via the get_data member function "
            << get_data() << std::endl;
}

// Initializes the some_data member variable to be the two strings concatenated.
Example::Example(const std::string& a_string,
                 const std::string& a_second_string)
    : some_data{a_string + a_second_string} {}

Example::~Example() { std::cout << "The object is being destroyed!" << std::endl; }
