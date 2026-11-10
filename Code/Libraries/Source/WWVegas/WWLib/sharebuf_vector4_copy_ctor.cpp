// cl: /DNDEBUG /MD /EHsc
//
// ShareBufferClass<Vector4> copy constructor. Twin of the landed Vector2
// and Vector3 bodies.

#include <new>

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// auto_inline(off) keeps the iterator out of line: without it the copy
// constructor's Vector4 array inlines it and loses retail's call to ??_H.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma auto_inline(off)
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#pragma auto_inline(on)

#include "../WWMath/Vector4Data.h"

// Retail's RefCountClass inline copies (scalar deleting dtor 0x00072899) are
// the size form: compile this class for size, as hlod.cpp does.
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

template ShareBufferClass<Vector4>::ShareBufferClass(
	const ShareBufferClass<Vector4> &);
