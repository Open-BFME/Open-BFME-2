// stlport46
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_STLP_USE_STATIC_LIB
#include <memory>

// Native 0x004E74A0 (64 B, EH frame) is slot 1 of the Rva004E7392 vtable
// 0x00BFD010 (slot 0 is the virtual destructor). Target evidence: a twelve
// byte new, the rowed copy ctor 0x004E7392 (base copy 0x004E72C0, vtable and
// two fields only), the result stored through the hidden slot [ebp+8], a zeroed
// flag word at [ebp-0x10] and a single FuncInfo state whose funclet tail-jumps
// to the null-guarded virtual slot 0 call 0x002E3A80. Structural inference:
// that state is the result of a named STLport auto_ptr local over the base
// (virtual destructor); the copy ctor is declared nonthrowing, which removes
// the allocation cleanup state exactly as in the sibling Rva00567FBCClone.cpp.
// The const qualifier and the base spelling are not proven by target evidence.
struct Rva004E72C0 {Rva004E72C0(const Rva004E72C0&);virtual ~Rva004E72C0();};
struct Rva004E7392:public Rva004E72C0 {
 Rva004E7392(const Rva004E7392&) throw();
 virtual _STL::auto_ptr<Rva004E72C0> rva004E74A0()const;
private:unsigned int first,second;
};
_STL::auto_ptr<Rva004E72C0> Rva004E7392::rva004E74A0()const {
 _STL::auto_ptr<Rva004E72C0> result(new Rva004E7392(*this)); return result;
}
