// cl: /O1 /DNDEBUG /MD
//
// ??1TransitionDamageFX@@MAE@XZ, retail 0x004BA47C, 76 bytes. TransitionDamageFX
// dtor over the rowed DamageModule base. The TU-local DamageModule models the
// donor multiple inheritance (primary 0x0C plus two pure interface words, 0x14
// total) so the derived vtable group lands at ([esi], +0x0C, +0x10) matching
// the ctor at 0x4BA3EA which installs 0xC59AEC/0xC59A30/0xC59A20. The member at
// +0xD4 is TensileFormationUpdateMember (3-pointer layout) whose QAE dtor is
// pinned at 0x4BA35A; the base call goes to the opaque three-vptr base at
// 0x4B96CC (rowed as Rva004B96CC, twin pin for DamageModule to be added on
// landing). Vtable immediates are DIR32. The deleting dtor at 0x4BA7C4 (slot 0
// of 0x00859AEC) calls this body, proving the class. BFME1 donor has explicit
// empty dtor, so explicit here to get vptr stores (implicit would omit them,
// cf. the placed 56B body at 0x490E7B).

class Thing;
class ModuleData;

class DamageModuleBase
{
public:
	virtual ~DamageModuleBase();

protected:
	const ModuleData *m_moduleData;
	void *m_object;
};

class DamageModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class DamageModuleInterface2
{
public:
	virtual void slot2() = 0;
};

class DamageModule : public DamageModuleBase,
		     public DamageModuleInterface1,
		     public DamageModuleInterface2
{
public:
	virtual ~DamageModule();
};

class TensileFormationUpdateMember
{
public:
	~TensileFormationUpdateMember();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class TransitionDamageFX : public DamageModule
{
protected:
	virtual ~TransitionDamageFX();

private:
	int m_clear[0x30]; // +0x14
	TensileFormationUpdateMember m_fxIds; // +0xD4
};

TransitionDamageFX::~TransitionDamageFX()
{
}
