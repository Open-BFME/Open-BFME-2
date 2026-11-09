// cl: /MD /EHsc /DNDEBUG
//
// 0x00072B55 (29B), unreferenced in retail: the out-of-line constructor of
// the 0x10-byte counted method object W3DShroud's constructor (0x00073320)
// builds inline and stores at +0x40. Retail bytes: count 1 at +4, a null at
// +8 (the novtable base), then the vtable 0x00BC6568 and the owner pointer
// at +0x0C; ret 4. The view is W3DShroudCtor.cpp's (slot 0 destroy, slot 1
// the scalar deleting destructor 0x00072FC5), split like Rva00072AEDDtor.cpp:
// the count belongs to the base and the counted reference (with its own
// null-initialising constructor) to the intermediate class, which is what
// keeps retail's +4-before-+8 store order. Names are address-derived.

class W3DShroud;

#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
inline RefCountClass::~RefCountClass() {}
class Rva00073320Ref
{
public:
	Rva00073320Ref() : m_ptr(0) {}
	~Rva00073320Ref();
	void *m_ptr;
};

// The counted reference at +8 belongs to the intermediate class
// (Rva00072AEDDtor.cpp's Rva0072AED), so it is initialised after the count.
class __declspec(novtable) Rva0072AED : public RefCountClass
{
public:
	virtual ~Rva0072AED();
	Rva00073320Ref m_ref;
};

class Rva00072FE1 : public Rva0072AED
{
public:
	Rva00072FE1(W3DShroud *owner);
	virtual ~Rva00072FE1();
	W3DShroud *m_owner;
};

Rva00072FE1::Rva00072FE1(W3DShroud *owner) : m_owner(owner)
{
}
