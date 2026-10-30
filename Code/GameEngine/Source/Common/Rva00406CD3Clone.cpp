// stlport46
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_STLP_USE_STATIC_LIB
#include <memory>

// Native 0x00406CD3 (75 B, EH frame): vtable slot of Rva00406BB0 that returns
// ownership of a twelve-byte copy made through the rowed copy ctor 0x00406BB0.
// Target evidence: new 12, copy ctor call, result stored through the hidden
// slot [ebp+8], a zeroed flag word at [ebp-0x10] and EH state 1 for the raw
// allocation. Structural inference: the flagged result state retail's funclet
// tests (tail-jump to the null-guarded virtual slot 0 call 0x002E3A80) is a
// named STLport auto_ptr local whose pointee has a virtual destructor; the
// direct "return auto_ptr(new T(*this))" spelling and a non-virtual pointee
// both lose it (see Rva00567FBCClone.cpp for the one-state sibling).
class Rva00406BB0
{
public:
	Rva00406BB0(const Rva00406BB0 &other);
	virtual ~Rva00406BB0();
	virtual _STL::auto_ptr<Rva00406BB0> rva00406CD3();
private:
	void *m_04;
	int m_08;
};

_STL::auto_ptr<Rva00406BB0> Rva00406BB0::rva00406CD3()
{
	_STL::auto_ptr<Rva00406BB0> result(new Rva00406BB0(*this));
	return result;
}
