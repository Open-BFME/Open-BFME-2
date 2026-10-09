// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// STLport4.5.3 default-fill resize supplies the operation. Native52076F
// constructs80B directly in the outgoing argument, then calls520703.
// The zero-storage derived view adapts the independently rowed constructor
// name to the fill argument's existing name; original type identity is unknown.
class Rva0051F87B {public:Rva0051F87B();char storage[80];};
struct Rva005205DAElement : Rva0051F87B {
 __forceinline Rva005205DAElement() {}
 Rva005205DAElement(const Rva005205DAElement&);
 ~Rva005205DAElement();
};
typedef char TimelineRecordExtent[sizeof(Rva005205DAElement)==80?1:-1];
class Rva00520703Vector {public:
 void resize(unsigned count,Rva005205DAElement value);
 void resize(unsigned count);
};
void Rva00520703Vector::resize(unsigned count) {resize(count,Rva005205DAElement());}
