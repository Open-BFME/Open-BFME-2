// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Animatable3DObjClass::Release at 0x001A4AA0.
//
// Zero Hour's switch plus one release Zero Hour does not have: after dropping
// the single or double animation references, BFME also drops its reference on
// the hierarchy tree, which it counts like the animations.  The case values are
// one higher than Zero Hour's (the bytes test 2 and 3).  Release_Ref inlines to
// --NumRefs / Delete_This through vtable slot 0.
//
// The shared bfme2htree shim models HTreeClass without the reference count, so
// animobj.cpp cannot express the tree release; this unit carries a reduced model
// instead, as Open-BFME-1 did, laid out by BFME 2's offsets (the tree at +0xFC,
// the motion mode at +0x100, the animations from +0x104), four bytes below BFME
// 1's.  /G7 is the unit's tell.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
		{
			Delete_This();
		}
	}

protected:
	virtual void Delete_This(void);

	int NumRefs;
};

class HAnimClass : public RefCountClass {};
class HTreeClass : public RefCountClass {};

enum
{
	SINGLE_ANIM = 2,
	DOUBLE_ANIM = 3
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
protected:
	void Release(void);

	// covers the vtable pointer and the render-object base
	unsigned char m_unreconstructed_00[0xFC];
	HTreeClass *HTree;
	int CurMotionMode;

	union
	{
		struct
		{
			HAnimClass *Motion;
		} ModeAnim;

		struct
		{
			HAnimClass *Motion0;
			HAnimClass *Motion1;
		} ModeInterp;
	};
};

void Animatable3DObjClass::Release(void)
{
	switch (CurMotionMode)
	{
		case SINGLE_ANIM:
			if (ModeAnim.Motion != 0)
			{
				ModeAnim.Motion->Release_Ref();
				ModeAnim.Motion = 0;
			}
			break;

		case DOUBLE_ANIM:
			if (ModeInterp.Motion0 != 0)
			{
				ModeInterp.Motion0->Release_Ref();
				ModeInterp.Motion0 = 0;
			}

			if (ModeInterp.Motion1 != 0)
			{
				ModeInterp.Motion1->Release_Ref();
				ModeInterp.Motion1 = 0;
			}
			break;

		default:
			break;
	}

	if (HTree != 0)
	{
		HTree->Release_Ref();
		HTree = 0;
	}
}
