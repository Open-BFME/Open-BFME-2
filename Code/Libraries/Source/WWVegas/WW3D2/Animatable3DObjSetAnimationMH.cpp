// cl: /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Animatable3DObjClass::Set_Animation( HAnimClass *, float, int ) at 0x001A4BF0.
//
// BFME's rewrite of Zero Hour's single-animation setter: it keeps a clamped copy
// of the requested frame, leaves Frame alone for a backwards loop and picks the
// direction by comparing against the frame already reached, and no longer looks
// up embedded-sound bones.  The clamp is spelled with macros because retail
// re-evaluates the inner minimum, calling Get_Num_Frames each time.  This is
// Open-BFME-1's body; BFME 2's render-object base is four bytes smaller, so every
// field below sits four bytes lower than in BFME 1, and BFME 2's HAnimClass has
// one more virtual ahead of Get_Num_Frames.  Release is the out-of-line call at
// 0x001A4AA0.  Retail does the float work in SSE: the unit is /G7 /arch:SSE.
#define BFME_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define BFME_MAX(a,b) (((a) > (b)) ? (a) : (b))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Add_Ref( void ) { NumRefs++; }

protected:
	virtual ~RefCountClass();	// vtable pointer at +0x00
	int NumRefs;				// +0x04
};

// Only slot 5 is proven: retail calls dword ptr [eax+0x14].  The slot before it
// has no recovered identity in BFME 2 and keeps an offset-derived name.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimClass : public RefCountClass
{
public:
	virtual const char *Get_Name( void ) const;		// slot 1
	virtual const char *Get_HName( void ) const;	// slot 2
	virtual const char *Get_Key( void );			// slot 3
	virtual void _M_slot_10( void );				// slot 4
	virtual int Get_Num_Frames( void );				// slot 5
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static unsigned int Get_Sync_Time( void ) { return SyncTime; }

private:
	static unsigned int SyncTime;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
public:
	enum { NONE = 0, BASE_POSE, SINGLE_ANIM, DOUBLE_ANIM, MULTIPLE_ANIM };
	enum
	{
		ANIM_MODE_MANUAL = 0,
		ANIM_MODE_LOOP,
		ANIM_MODE_ONCE,
		ANIM_MODE_LOOP_PINGPONG,
		ANIM_MODE_LOOP_BACKWARDS,
		ANIM_MODE_ONCE_BACKWARDS,
	};

	virtual void Set_Animation( HAnimClass *motion, float frame, int mode );

	void Set_Hierarchy_Valid( bool onoff ) const { IsTreeValid = onoff; }

protected:
	void Release( void );

	char m_head[0xf0];				// the render-object base after the vtable pointer at +0x00

	mutable bool IsTreeValid;		// +0xf4
	char m_pad[3];
	void *HTree;					// +0xf8
	void *m_bfmeFC;					// +0xfc
	int CurMotionMode;				// +0x100

	struct
	{
		HAnimClass *Motion;			// +0x104
		float Frame;				// +0x108
		float PrevFrame;			// +0x10c
		int AnimMode;				// +0x110
		mutable int LastSyncTime;	// +0x114
		float animDirection;		// +0x118
		float frameRateMultiplier;	// +0x11c
	} ModeAnim;
};

void Animatable3DObjClass::Set_Animation( HAnimClass *motion, float frame, int mode )
{
	if( motion != 0 )
	{
		// Add_Ref before the release, in case it is the animation already playing.
		motion->Add_Ref();
		Release();

		CurMotionMode = SINGLE_ANIM;
		ModeAnim.Motion = motion;

		ModeAnim.PrevFrame = BFME_MAX( BFME_MIN( (float)(ModeAnim.Motion->Get_Num_Frames() - 1), frame ), 0.0f );

		if( mode == ANIM_MODE_LOOP_BACKWARDS )
		{
			// Frame is left alone: the direction says which way to walk away
			// from wherever the object already was.
			if( ModeAnim.PrevFrame >= ModeAnim.Frame )
			{
				ModeAnim.animDirection = 1.0f;
			}
			else
			{
				ModeAnim.animDirection = -1.0f;
			}
		}
		else
		{
			ModeAnim.Frame = frame;

			if( mode < ANIM_MODE_ONCE_BACKWARDS )
			{
				ModeAnim.animDirection = 1.0f;
			}
			else
			{
				ModeAnim.animDirection = -1.0f;
			}
		}

		ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();
		ModeAnim.frameRateMultiplier = 1.0f;
		ModeAnim.AnimMode = mode;
	}
	else
	{
		Release();
		CurMotionMode = BASE_POSE;
	}

	Set_Hierarchy_Valid( false );
}
