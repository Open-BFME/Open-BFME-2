// cl: /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Animatable3DObjClass::Set_Animation, the blend overload, at 0x001A4D10.
//
// Takes references on both motions, releases whatever was playing, and stores
// the double-animation state: both motions before either frame, and the blend
// percentage straight after the second frame (BFME dropped the two PrevFrame
// floats Zero Hour keeps there).  This is Open-BFME-1's body; BFME 2's render-
// object base is four bytes smaller, so every field below sits four bytes lower
// than in BFME 1.  Release is the out-of-line call at 0x001A4AA0.  Retail moves
// the floats through SSE registers: the unit is /G7 /arch:SSE.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Add_Ref( void ) { NumRefs++; }

protected:
	virtual ~RefCountClass();	// vtable pointer at +0x00
	int NumRefs;				// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimClass : public RefCountClass
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
public:
	enum { NONE = 0, BASE_POSE, SINGLE_ANIM, DOUBLE_ANIM, MULTIPLE_ANIM };

	virtual void Set_Animation( HAnimClass *motion0, float frame0, HAnimClass *motion1, float frame1, float percentage );

	void Set_Hierarchy_Valid( bool onoff ) const { IsTreeValid = onoff; }

protected:
	void Release( void );

	char m_head[0xf0];			// the render-object base after the vtable pointer at +0x00

	mutable bool IsTreeValid;	// +0xf4
	char m_pad[3];
	void *HTree;				// +0xf8
	void *m_bfmeFC;				// +0xfc
	int CurMotionMode;			// +0x100

	struct
	{
		HAnimClass *Motion0;	// +0x104
		HAnimClass *Motion1;	// +0x108
		float Frame0;			// +0x10c
		float Frame1;			// +0x110
		float Percentage;		// +0x114
	} ModeInterp;
};

void Animatable3DObjClass::Set_Animation( HAnimClass *motion0, float frame0, HAnimClass *motion1, float frame1, float percentage )
{
	if( motion0 )
	{
		motion0->Add_Ref();
	}

	if( motion1 )
	{
		motion1->Add_Ref();
	}

	Release();

	CurMotionMode = DOUBLE_ANIM;
	ModeInterp.Motion0 = motion0;
	ModeInterp.Frame0 = frame0;
	ModeInterp.Motion1 = motion1;
	ModeInterp.Frame1 = frame1;
	ModeInterp.Percentage = percentage;

	Set_Hierarchy_Valid( false );
}
