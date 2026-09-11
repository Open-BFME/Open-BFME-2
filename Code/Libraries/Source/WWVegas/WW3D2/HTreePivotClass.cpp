// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// PivotClass, BFME 2's 0x58-byte hierarchy pivot.
//
// The layout is read from the constructor at 0x00197830 and the member-wise
// assignment at 0x00197950: the name, the parent, two blocks each holding an
// identity rotation (0,0,0,1) and a zero translation, the index, the
// visibility flag and a float that starts at 1.0.  The constructor clears the
// name last, the way Zero Hour's PivotClass constructor does.  Only the
// offsets and initial values are proven; the block and float names are not
// recovered.  HTreeClass's copy constructor (0x001662A0) builds these through
// the vector constructor iterator and copies them with operator=.

// An identity rotation (0,0,0,1) and a zero translation, by the values the
// constructor stores.
struct BfmePivotRotation
{
	BfmePivotRotation() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}
	float X, Y, Z, W;
};

struct BfmePivotTranslation
{
	BfmePivotTranslation() : X(0.0f), Y(0.0f), Z(0.0f) {}
	float X, Y, Z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
struct PivotClass
{
public:
	PivotClass();
	PivotClass &operator=(const PivotClass &that);

	char Name[16];
	PivotClass *Parent;					// +0x10
	BfmePivotRotation m_bfme14;			// +0x14
	BfmePivotTranslation m_bfme24;		// +0x24
	BfmePivotRotation m_bfme30;			// +0x30
	BfmePivotTranslation m_bfme40;		// +0x40
	int Index;							// +0x4C
	bool IsVisible;						// +0x50
	float m_bfme54;						// +0x54
};

PivotClass::PivotClass() :
	Parent(0),
	Index(0),
	IsVisible(true),
	m_bfme54(1.0f)
{
	Name[0] = 0;
}
