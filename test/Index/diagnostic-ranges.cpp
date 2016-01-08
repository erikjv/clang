// RUN: c-index-test -test-load-source all %s > /dev/null 2> %t.err
// RUN: FileCheck < %t.err -check-prefix=CHECK-RANGE %s

struct Foo {
  someIdentifierLeadingToAnInvalidRange;
};

template <typename T>
struct Bar {
  Bar(const T&) {}
};
  
void f()
{
  for (Bar<__typeof__(v.x)> container(v.x); true; )
    return;
}

// CHECK-RANGE: diagnostic-ranges.cpp:5:3: error: C++ requires a type specifier for all declarations
// CHECK-RANGE: diagnostic-ranges.cpp:15:39: error: use of undeclared identifier 'v'
// CHECK-RANGE: diagnostic-ranges.cpp:5:3:{5:3-5:40}: error: C++ requires a type specifier for all declarations
// CHECK-RANGE: diagnostic-ranges.cpp:15:23:{15:23-15:24}: error: use of undeclared identifier 'v'

