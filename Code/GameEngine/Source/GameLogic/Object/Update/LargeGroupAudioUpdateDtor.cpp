// cl: /MD /EHsc /DNDEBUG
//
// ??1LargeGroupAudioUpdate@@UAE@XZ, retail 0x004AB8DC, 46 bytes.
// Target evidence: the audited scalar deleting dtor 0x004ABB1B calls this
// body; slot 4 -> 0x004AB897 uses class-name string "LargeGroupAudioUpdate".
// Body: five compiler vptr restores (+0 +0x0C +0x10 +0x20 +0x24), then the
// +0x24 base's own inline dtor re-stores its vptr 0x00BFB698, then a tail
// jmp to the UpdateModule-family dtor 0x0024A797 (UpdateModule). The +0x20
// and +0x24 bases are structural stand-ins (types unrecovered).

// Base view matching Common/Rva0024A797DeletingDtor.cpp.
class Rva0049B47C
{
public:
	virtual ~Rva0049B47C() throw();

private:
	char m_pad04[8];
};

#include "../../../../Include/Common/MiBase1.h"

class PrimaryP4AB8DC : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP4AB8DC() {}
};

class Rva0024A797_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class LargeGroupAudioUpdate_B20
{
public:
	virtual void f20();
};

class LargeGroupAudioUpdate_B24
{
public:
	virtual void f24();
	~LargeGroupAudioUpdate_B24() {}
};

class LargeGroupAudioUpdate : public UpdateModule, public LargeGroupAudioUpdate_B20,
	public LargeGroupAudioUpdate_B24
{
public:
	virtual ~LargeGroupAudioUpdate();
public:
	// retail slot 4: the rowed ?getModuleNameKey@LargeGroupAudioUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
public:
	// BehaviorModuleInterface table 0x00C54900 (+0x0C) slot 36: retail 0x004543A9, the +0x0C
	// receiver converted to the +0x20 interface (the null-preserving cast retail folds).
	virtual void *slot36();
};

void *LargeGroupAudioUpdate::slot36()
{
	return static_cast<LargeGroupAudioUpdate_B20 *>(this);
}

LargeGroupAudioUpdate::~LargeGroupAudioUpdate()
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f20@LargeGroupAudioUpdate_B20@@UAEXXZ=?rva004ABA71@LargeGroupAudioUpdate@@UAEXXZ")
#pragma comment(linker, "/alternatename:?f24@LargeGroupAudioUpdate_B24@@UAEXXZ=__purecall")
#pragma comment(linker, "/alternatename:?f2@Rva0024A797_B2@@UAEXXZ=?update@LargeGroupAudioUpdate@@UAE?AW4UpdateSleepTime@@XZ")
