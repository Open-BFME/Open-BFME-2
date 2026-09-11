// cl: /G7 /DNDEBUG /MD /EHsc
//
// HTreeClass's copy constructor at 0x001662A0.
//
// BFME 2 rewrote Zero Hour's: the pivot count and scale factor come straight
// from the source in the initialiser list, the member at +0x1C (a 12-byte
// object with its own copy constructor at 0x00166110 and a destructor, hence
// the unwind slot that keeps `this` on the stack) is copy-constructed, the three
// words after it are cleared, and the name is copied inline.  The pivots are
// 0x58-byte records built through the vector constructor iterator and copied
// one by one through PivotClass::operator=, each Parent re-pointed into the new
// array through the source parent's Index.
//
// htree.cpp's bfme2htree shim models +0x1C as a plain array and PivotClass with
// Zero Hour's layout, so this unit carries a reduced model of its own, as
// Open-BFME-1 did for BFME 1's version.  Unrecovered types keep address-derived
// names.  /G7 is the unit's tell.

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);
#pragma intrinsic(memcpy)

// Without this declaration MSVC routes `new T[n]` to the scalar ??2@YAPAXI@Z
// (0x0002FDA0); retail allocates the pivots through the array form ??_U@YAPAXI@Z
// at 0x0002FDE0.
void *__cdecl operator new[](unsigned int size);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
struct PivotClass
{
public:
	PivotClass();
	PivotClass &operator=(const PivotClass &);

	char Name[16];
	PivotClass *Parent;					// +0x10
	unsigned char m_bfme14[0x4C - 0x14];
	int Index;							// +0x4C
	unsigned char m_bfme50[0x58 - 0x50];
};

// The +0x1C member; only its copy constructor (0x00166110) and the fact that it
// has a destructor are proven.
class BfmeRva00166110
{
public:
	BfmeRva00166110(const BfmeRva00166110 &);
	~BfmeRva00166110();

private:
	unsigned int m_bfmeWords[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
class HTreeClass
{
public:
	HTreeClass(const HTreeClass &);

private:
	char Name[16];
	int NumPivots;						// +0x10
	PivotClass *Pivot;					// +0x14
	float ScaleFactor;					// +0x18
	BfmeRva00166110 OwnedSequence1C;	// +0x1C
	unsigned int Unknown28;
	unsigned int Unknown2C;
	unsigned int Unknown30;
};

HTreeClass::HTreeClass(const HTreeClass & src) :
	NumPivots(src.NumPivots),
	Pivot(0),
	ScaleFactor(src.ScaleFactor),
	OwnedSequence1C(src.OwnedSequence1C),
	Unknown28(0),
	Unknown2C(0),
	Unknown30(0)
{
	memcpy(&Name,&src.Name,sizeof(Name));

	if (NumPivots > 0) {
		Pivot = new PivotClass[NumPivots];
	}

	for (int pi = 0; pi < NumPivots; pi++) {
		Pivot[pi] = src.Pivot[pi];

		if (src.Pivot[pi].Parent != 0) {
			Pivot[pi].Parent = &(Pivot[src.Pivot[pi].Parent->Index]);
		} else {
			Pivot[pi].Parent = 0;
		}
	}
}
