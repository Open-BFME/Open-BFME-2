// cl: /DNDEBUG /MD /Ob2 /EHsc
//
// ShareBufferClass<unsigned>::ShareBufferClass, retail 0x00D1DE2 (110 bytes),
// and its sibling destructor group in the same object: the scalar deleting
// destructor at 0x00D1E6C (28 bytes) and the destructor at 0x00D1E88
// (26 bytes, the vtable store 0xBCE330 identifies the instantiation).
// Out-of-line dependency of MeshMatDescClass::Get_Color_Array (retail calls
// it with the fresh 0x18-byte block, VertexCount and the
// "MeshMatDescClass::ColorArray" message). BFME1 sweep sharebuf.h 3-arg
// shape (Count/Alignment init-list, RawBuffer in-arm, Array sunk to the
// join); msg is dead in retail, kept only for the signature. Both arms
// allocate through an explicit operator new[] call (retail routes them to
// vector-new 0x2FDE0): a plain array-new of a trivial element type would
// emit scalar operator new instead. RawBuffer/Array/Count/Alignment sit at
// +0x08/+0x0C/+0x10/+0x14 behind the vtable (retail installs 0xBCE330).
// RefCountClass resets NumRefs to 1 on copy. This unit builds at /O1: at
// /O2 the compiler picks the frameless SEH prologue, while retail opens
// with the ebp-frame __EH_prolog sequence; the /O1 cleanup form (pop ecx,
// not add esp,4) is what retail's kept deleting destructor shows.

#include <new>

#include "../WWLib/RefCountData.h"
inline RefCountClass::~RefCountClass() {}

// The canonical class view declares the destructor out of line. This unit
// emits the instantiation retail keeps: the CPU's vptr stores around the
// buffer free, no EH frame (the free cannot throw) and no null test.
template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment = 0);
	~ShareBufferClass();

protected:
	Type *RawBuffer; // +0x08
	Type *Array; // +0x0C
	int Count; // +0x10
	int Alignment; // +0x14
};

// The unsigned specialization uses raw allocation; the Vector2 generic
// constructor must run the element constructor for every array slot.
template <>
ShareBufferClass<unsigned>::ShareBufferClass(int count, const char *msg, int alignment) :
	Count(count),
	Alignment(alignment)
{
	(void)msg;
	if (Alignment == 0)
	{
		RawBuffer = (unsigned *)operator new[](Count * sizeof(unsigned));
		Array = RawBuffer;
	}
	else
	{
		RawBuffer = (unsigned *)operator new[](Count * sizeof(unsigned) + Alignment);
		Array = (unsigned *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(Alignment - 1));
	}
}

template <> inline
ShareBufferClass<unsigned>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

