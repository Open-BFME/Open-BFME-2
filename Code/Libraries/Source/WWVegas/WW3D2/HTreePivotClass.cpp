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
// constructor stores.  Both assign member by member: retail's operator= copies
// every float with its own move, where a compiler-generated block assignment
// would move each block as a unit.
struct BfmePivotRotation
{
	BfmePivotRotation() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}
	BfmePivotRotation &operator=(const BfmePivotRotation &that) { X = that.X; Y = that.Y; Z = that.Z; W = that.W; return *this; }
	float X, Y, Z, W;
};

struct BfmePivotTranslation
{
	BfmePivotTranslation() : X(0.0f), Y(0.0f), Z(0.0f) {}
	BfmePivotTranslation &operator=(const BfmePivotTranslation &that) { X = that.X; Y = that.Y; Z = that.Z; return *this; }
	float X, Y, Z;
};

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);
#pragma intrinsic(memcpy)

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

PivotClass &PivotClass::operator=(const PivotClass &that)
{
	if (this != &that) {
		memcpy(Name, that.Name, sizeof(Name));
		Parent = that.Parent;
		m_bfme14 = that.m_bfme14;
		m_bfme24 = that.m_bfme24;
		m_bfme30 = that.m_bfme30;
		m_bfme40 = that.m_bfme40;
		Index = that.Index;
		IsVisible = that.IsVisible;
		m_bfme54 = that.m_bfme54;
	}
	return *this;
}
