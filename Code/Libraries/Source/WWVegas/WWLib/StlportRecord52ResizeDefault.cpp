// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

class Rva002B749C { public: Rva002B749C(); char storage[52]; };
struct Rva002BC47DElement : Rva002B749C { __forceinline Rva002BC47DElement() {}Rva002BC47DElement(const Rva002BC47DElement&);~Rva002BC47DElement();Rva002BC47DElement&operator=(const Rva002BC47DElement&);bool operator<(const Rva002BC47DElement&)const; bool operator==(const Rva002BC47DElement&)const; };

// Declaration-only call to the verified by-value resize owner. The inline
// derived view adapts that owner's opaque element name to the constructor
// owner already recovered at 0x002B749C; it adds no storage or behavior.
class Rva002BC8C9Vector {
public:
 void resize(unsigned n,Rva002BC47DElement value);
 void resize(unsigned n);
};

// Native 0x002BC935..0x002BC958 constructs its 52-byte argument
// directly with the existing 0x002B749C constructor and calls resize.
void Rva002BC8C9Vector::resize(unsigned n) { resize(n,Rva002BC47DElement()); }
