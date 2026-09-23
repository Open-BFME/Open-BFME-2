// cl: /G7 /DNDEBUG /MD /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
//
// ShareBufferClass<unsigned> copy constructor at target RVA 0x0015B000.
//
// BFME's ShareBufferClass carries an Alignment member beside Zero Hour's Count:
// zero means a plain new[] with Array aliasing RawBuffer, anything else means a
// raw char buffer over-allocated by Alignment with Array rounded up inside it.
// The matched aligned Vector2 donor is adapted only where target evidence
// identifies the element type. /G7 writes add reg,1 and add reg,-1 where /G6
// writes inc and dec.

void *operator new[](unsigned int size);
inline void *operator new(unsigned int, void *place) { return place; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/sharebuf.h,
// with BFME's RawBuffer/Alignment pair around Zero Hour's Array and Count.
template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &);

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

template ShareBufferClass<unsigned>::ShareBufferClass(
	const ShareBufferClass<unsigned> &);

// Color cloning15B840 calls this175-byte constructor. Its vtableBCE330
// agrees with the unsigned-buffer constructor used by Get_Color_Array D1FBD.
