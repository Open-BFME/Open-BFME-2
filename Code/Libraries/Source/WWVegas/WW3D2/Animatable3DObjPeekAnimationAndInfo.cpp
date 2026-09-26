// cl: /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeanimobj /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Peek_Animation_And_Info@Animatable3DObjClass@@UAEPAVHAnimClass@@AAMAAH10@Z, RVA 0x001A53E0, 94B. Virtual slot 130 (offset 0x208) of vtable 0x007D6D10 (class of ??0Animatable3DObjClass@@QAE@PBD@Z in animobj.cpp). Evidence: vtable slot 130 next to slot 129 Set_Animation_Frame_Rate_Multiplier at 0x001A5440; donor BFME1 animobj.cpp Peek_Animation_And_Info; retail checks CurMotionMode==2 SINGLE_ANIM and fills frame numFrames mode mult; HAnim Get_Num_Frames at slot 5 (+0x14) via TU-local _M_slot_10 shim per Animatable3DObjSetAnimationMH.cpp.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Add_Ref(void) { NumRefs++; }

protected:
	virtual ~RefCountClass();
	int NumRefs;
};

// Only slot 5 is proven: retail calls dword ptr [edx+0x14]. The slot before it
// keeps the offset-derived name from Animatable3DObjSetAnimationMH.cpp.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimClass : public RefCountClass
{
public:
	virtual const char *Get_Name(void) const;
	virtual const char *Get_HName(void) const;
	virtual const char *Get_Key(void);
	virtual void _M_slot_10(void);
	virtual int Get_Num_Frames(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
public:
	enum { NONE = 0, BASE_POSE, SINGLE_ANIM, DOUBLE_ANIM, MULTIPLE_ANIM };

	virtual HAnimClass *Peek_Animation_And_Info(float &frame, int &numFrames, int &mode, float &mult);

	void Set_Hierarchy_Valid(bool onoff) const { IsTreeValid = onoff; }

protected:
	char m_head[0xf0];

	mutable bool IsTreeValid;
	char m_pad[3];
	void *HTree;
	void *m_bfmeFC;
	int CurMotionMode;

	struct
	{
		HAnimClass *Motion;
		float Frame;
		float PrevFrame;
		int AnimMode;
		mutable int LastSyncTime;
		float animDirection;
		float frameRateMultiplier;
	} ModeAnim;
};

HAnimClass *Animatable3DObjClass::Peek_Animation_And_Info(float &frame, int &numFrames, int &mode, float &mult)
{
	if (CurMotionMode == SINGLE_ANIM) {
		frame = ModeAnim.Frame;
		numFrames = ModeAnim.Motion ? ModeAnim.Motion->Get_Num_Frames() : 0;
		mode = ModeAnim.AnimMode;
		mult = ModeAnim.frameRateMultiplier;
		return ModeAnim.Motion;
	} else {
		return 0;
	}
}
