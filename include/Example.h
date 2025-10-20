// Include guards to prevent issues from including a header file multiple times
#ifndef REMEMBER_INCLUDE_GUARDS_H
#define REMEMBER_INCLUDE_GUARDS_H

#include <iostream>
#include <vector>
// This file has examples of how to do a lot of the things you've seen in the
// course with a class or function. Most classes that you will write won't make
// use of every single feature of the language

// A regular function returning a double called square taking a double as
// parameter. Declared in the header but defined in the source file (.cxx)
//
// Declaration:
// return-value function-name (function-parameters...);
//
// Definition:
// return-value function-name (function-parameters...) { function-body...}
//
double square(double input);

// A function returning void taking a vector of doubles by reference that
// squares each of the elements. Since the parameter is a reference,
// modifications that happen in the function body will affect the variable that
// was passed in!
void square_vector_elements(std::vector<double>& data);

// A function returning void taking a vector of doubles by const reference that
// prints the elements. Since the parameter is a const reference, we can't
// accidentally modify the variable we are passing in but we don't have to make
// an independent copy of it.
void print_elements(const std::vector<double>& data);

// A base class with a virtual function that a derived class could override
class ExampleBase {
  // Anything that is declared below this is accessible from outside the class
  // itself. In other words, if you have an object of type ExampleBase called
  // object you can access the print member function as follows
  //
  // ExampleBase obj {};
  // obj.print();
  //
  // Since print is virtual, this will also work for any type that derives
  // from it
 public:
  // A virtual function with void as return value called print taking no
  // parameters. Both declared and defined in the header file.
  //
  // Since a member function called "print" probably shouldn't change the
  // object, mark it as const
  //
  // If you have a function that is longer than this, it probably shouldn't be
  // defined in the header file.
  virtual void print() const {
    std::cout << "I'm being called from the base class!" << std::endl;
  }

};  // Don't forget the semicolon at the end!

// A new type called Example that derives from the ExampleBase class. If you
// don't need to inherit from something (which is the usual case), skip the part
// between Example and the {}, i.e.
//
//  class Example {
//  // Contents go here
//  };
//
class Example : public ExampleBase {
 private:
  // Things that are in the private section can only be accessed from within the
  // member functions of the class.

  // A string member variable. Can be accessed as if it was a local variable in
  // any member function of the Example class.
  std::string some_data;

 public:
  // A default constructor which will be used whenever we create an object of
  // type Example without any parameters, e.g.
  //
  // Example object; // Default constructor gets called here!
  //
  // Any function with the same name as the class is a constructor of some kind.
  // Note that constructors do not have a return value.
  //
  // If you don't have anything special you need to do in your constructor but
  // you want to make sure that you still have a default one, you can use
  // =default.
  Example() = default;

  // A different constructor taking a single parameter. Marked explicit to
  // disable implicit conversions (almost never what we want!)
  //
  // Note the special syntax for constructors used to initialize member
  // variables in between the parameters and the function body.
  //
  // Small constructors are often defined directly in the header file but most
  // of the time you want to put the definition in your source file.
  //
  // This constructor will be called automatically when we create an object like
  // this
  //
  // Example object{"this will be the a parameter variable"};
  explicit Example(std::string a_parameter)
      // This will initialize the some_data member variable by copying the
      // contents of the a_parameter variable
      : some_data{a_parameter} {
    std::cout << "Calling the explicit single argument constructor!"
              << std::endl;
  }

  // A declaration of a constructor taking two parameters. The definition can be
  // found in the source file.
  //
  // We don't need to mark it as explicit, that's only needed for single
  // argument constructors!
  //
  // This constructor will be called automatically whenever we create an object
  // like this
  //
  // Example object {"a string", " a second string"};

  Example(const std::string& a_string, const std::string& a_second_string);
  // Overriding the print function in the base class. Declared in the
  // header but defined in the source file!

  // A destructor for the example type. This gets called automatically for us by
  // the compiler whenever an object of this type is destroyed (typically when
  // it goes out of scope).
  //
  // Since we have virtual functions, we mark the destructor as virtual.
  // See
  // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c127-a-class-with-a-virtual-function-should-have-a-virtual-or-protected-destructor
  virtual ~Example();

  void print() const override;
  // The override keyword tells the compiler that we want this to override an
  // existing virtual function. If we make a mistake, the compiler will tell
  // us!
  //
  // The following commented out code would not compile because the signature
  // is missing the const keyword
  // void print() override {}

  // A member function giving the current value of the some_data member
  // variable

  std::string get_data() const { return some_data; }

};  // Don't forget the semicolon at the end!

#endif /* REMEMBER_INCLUDE_GUARDS_H */
