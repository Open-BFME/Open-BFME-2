// cl: /DNDEBUG /MD /EHsc
//
// ??1ModelConditionAudioLoopClientBehavior@@UAE@XZ, retail 0x004CC0FE, 95 bytes.
// ModelConditionAudioLoopClientBehavior dtor: restores the three MI vptrs
// (+0 0xC5F458 plus +0x0C 0xC5F450 plus +0x10 0xC5F44C, DIR32), calls the
// rowed ?clear@Rva004CBF9A@@QAEXXZ (0x004CBF9A, audio remove slot 0x6c plus
// holder clear tail) on this, releases the +0x18 holder via rowed
// ?Release_Ref@OpaqueRefCounted@@QAEXXZ (0x00050ED3) when non-null, restores
// the intermediate primary 0xBEFE48 (Rva00252B68 vtable, DIR32) and calls
// the opaque fold-point base at 0x0049B47C via the Rva0049B47C pin (packet
// annotates the WindModuleInfo row at the same fold address). Layout from
// the rowed ctor 0x004CBECA via rowed Rva00252B68 base 0x00252B68 (size 0x0C)
// plus derived +0x0C/+0x10 secondary slots plus +0x14 handle plus +0x18
// holder (factory 0x00252D62 news 0x1C). Caller is the slot-0 ??_G at
// 0x004CC179; retail slot 4 -> 0x004CBF13 uses class-name string
// "ModelConditionAudioLoopClientBehavior". Shape follows CastleMemberBehaviorDtor
// (three-vptr restore plus audio plus intermediate restore plus Rva0049B47C base call).

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva004CBF9A
{
public:
	void clear();
};

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

// Shared intermediate: Rva0049B47C (padded to 0xC) with a user empty
// destructor. It is load-bearing: it makes the derived restore the
// intermediate primary vptr (+0) itself before tail-calling the pinned fold
// base, which is the single final store retail shows (cf.
// CastleMemberBehaviorDtor PrimaryP, Rva0049B47CThreeVptrDerived).
// Named Rva004CC0FEPrimary (not PrimaryP): PrimaryP is an invented name that
// Rva0049B47CThreeVptrDerived.cpp also uses for a different MI layout
// (Rva0049B47C plus MiBase1); same mangled ??1PrimaryP would clash as a
// differing COMDAT, so this single-base intermediate keeps its own name.
class Rva004CC0FEPrimary : public Rva0049B47C
{
public:
	~Rva004CC0FEPrimary() {}
};

class Secondary0C
{
public:
	virtual void secondary0CAnchor() = 0;
};

class Secondary10
{
public:
	virtual void secondary10Anchor() = 0;
};

class Holder18
{
public:
	~Holder18()
	{
		if (m_ptr != 0)
			m_ptr->Release_Ref();
	}

private:
	OpaqueRefCounted *m_ptr;
};

class ModelConditionAudioLoopClientBehavior : public Rva004CC0FEPrimary, public Secondary0C, public Secondary10
{
public:
	virtual ~ModelConditionAudioLoopClientBehavior();

private:
	int m_14;
	Holder18 m_holder18;
};

ModelConditionAudioLoopClientBehavior::~ModelConditionAudioLoopClientBehavior()
{
	((Rva004CBF9A *)this)->clear();
}
