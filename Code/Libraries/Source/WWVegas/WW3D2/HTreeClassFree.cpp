// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// HTreeClass::Free at 0x00166510.
//
// BFME 2's version of Zero Hour's Free: release the pivot array, reset the
// count and the scale factor, empty the +0x1C member, and drop the buffer held
// at +0x2C along with the words around it.
//
// The +0x1C member is emptied the way STLport's vector::erase(first, last)
// does it: copy the tail [last, finish) down to first through the random-
// access copy helper at 0x00161350 -- by-reference dispatch tag, null distance
// pointer, hence retail's extra pushed zero -- and make the result the new
// finish.  The element type and the helper have no recovered identity and keep
// address-derived names; the member is the same +0x1C object whose copy
// constructor HTreeClassCopyConstructor.cpp reaches at 0x00166110.

void __cdecl operator delete[](void *block);

struct BfmeRva00161350Tag {};
struct BfmeRva00161350Elem;

// The copy helper the +0x1C member's clear reaches: copy(first, last, result)
// with a by-reference dispatch tag, returning the new end.
BfmeRva00161350Elem *__cdecl bfmeRva00161350(BfmeRva00161350Elem *first, BfmeRva00161350Elem *last,
	BfmeRva00161350Elem *result, const BfmeRva00161350Tag &tag, int *distance);

// The +0x1C member: start, finish, end of storage.  Clear is STLport's
// erase(begin(), end()).
struct BfmeRva00166110
{
	void Clear()
	{
		BfmeRva00161350Elem *first = Start;
		BfmeRva00161350Elem *last = Finish;
		BfmeRva00161350Tag tag;
		BfmeRva00161350Elem *i = bfmeRva00161350(last, Finish, first, tag, (int *)0);
		Finish = i;
	}
	BfmeRva00161350Elem *Start;
	BfmeRva00161350Elem *Finish;
	BfmeRva00161350Elem *EndOfStorage;
};

struct PivotClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
class HTreeClass
{
public:
	void Free(void);

private:
	char Name[16];
	int NumPivots;						// +0x10
	PivotClass *Pivot;					// +0x14
	float ScaleFactor;					// +0x18
	BfmeRva00166110 OwnedSequence1C;	// +0x1C
	unsigned int Unknown28;				// +0x28
	void *Unknown2C;					// +0x2C
	unsigned int Unknown30;				// +0x30
};

void HTreeClass::Free(void)
{
	if (Pivot != 0) {
		delete [] (char *)Pivot;
		Pivot = 0;
	}
	NumPivots = 0;
	ScaleFactor = 1.0f;

	OwnedSequence1C.Clear();

	Unknown28 = 0;
	delete [] (char *)Unknown2C;
	Unknown2C = 0;
	Unknown30 = 0;
}
