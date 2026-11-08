// cl: /DNDEBUG /MD /EHsc
//
// ShareBufferClass<Vector3> copy constructor. Twin of the landed Vector2
// body in sharebuf_vector2_copy_ctor.cpp.

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body instead of the /O2 one, which loses at link time.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
#pragma auto_inline(off)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma auto_inline(on)
#pragma optimize("", on)

#include <new>

#include "../WWMath/Vector3Data.h"

// Retail's out-of-line RefCountClass deleting-dtor copy is the /O1 form
// (pop ecx after the delete call); compile just the base class for size so
// this unit's COMDAT matches the first copy in link order (hlod.cpp).
#pragma optimize("s", on)
#include "RefCountData.h"
inline RefCountClass::~RefCountClass() {}
#pragma optimize("", on)

template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &);
	virtual ~ShareBufferClass();

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;
};

template <class Type>
ShareBufferClass<Type>::ShareBufferClass(const ShareBufferClass<Type> &that) :
	Count(that.Count)
{
	Alignment = that.Alignment;
	if (Alignment == 0) {
		RawBuffer = new Type[Count];
		Array = RawBuffer;
	} else {
		RawBuffer = (Type *)new char[Count * sizeof(Type) + Alignment];
		Array = (Type *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}
	for (int index = 0; index < Count; ++index) {
		Array[index] = that.Array[index];
	}
}

template ShareBufferClass<Vector3>::ShareBufferClass(
	const ShareBufferClass<Vector3> &);
