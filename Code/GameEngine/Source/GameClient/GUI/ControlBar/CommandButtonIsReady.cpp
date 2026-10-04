// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// CommandButton::isReady(const Object *), retail 0x0035B069 (135 bytes),
// pinned. Zero Hour's body (GameClient/GUI/ControlBar/ControlBar.cpp) with
// BFME 2's additions read from the target: a null source is never ready, and
// command type 0x17 (+0x14) is ready when the source has the button's
// upgrade (+0x24, if any) and its +0x458 frame has been reached. Otherwise
// ZH's checks: the special power module for +0x44 (the rowed lookup
// 0x0028BB9E, reached through its address-named view) at 100% (vslot 2,
// fld1/fucomip), or an upgrade the source is affected by (pinned 0x002940B9,
// address-named view) and does not yet have (rowed 0x00290D2B).
typedef bool Bool;
typedef float Real;

class UpgradeTemplate;
class SpecialPowerTemplate;

class SpecialPowerModuleInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual Real getPercentReady() const = 0; // vslot 2
};

class BfmeSubBEC
{
public:
	void *rva0028BB9E(void *specialPower); // Object::getSpecialPowerModule
};

class BfmeArg985
{
public:
	char bfmeHas985C(int upgrade); // Object::affectedByUpgrade
};

class GameLogic
{
public:
	unsigned getFrame() const { return m_frame; }
private:
	char m_pad[0x40];
	unsigned m_frame;
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const; // Object::hasUpgrade
	Bool bfmeReadyFrameReached() const { Bool ready = m_readyFrame <= TheGameLogic->getFrame(); return ready; }
private:
	char m_pad[0x458];
	unsigned m_readyFrame; // +0x458
};

// Object::getSpecialPowerModule and Object::affectedByUpgrade through the
// address-named views their rows carry (kept file-local so this unit emits
// no copy of the shared inline names).
static inline SpecialPowerModuleInterface *getSpecialPowerModule(const Object *obj, const SpecialPowerTemplate *sp)
{
	return (SpecialPowerModuleInterface *)((BfmeSubBEC *)obj)->rva0028BB9E((void *)sp);
}
static inline Bool affectedByUpgrade(const Object *obj, const UpgradeTemplate *upgrade)
{
	return ((BfmeArg985 *)obj)->bfmeHas985C((int)upgrade) != 0;
}

class CommandButton
{
public:
	Bool isReady(const Object *sourceObj) const;
private:
	char m_pad00[0x14];
	int m_commandType;                         // +0x14
	char m_pad18[0x24 - 0x18];
	const UpgradeTemplate *m_upgradeTemplate;  // +0x24
	char m_pad28[0x44 - 0x28];
	const SpecialPowerTemplate *m_specialPower; // +0x44
};

Bool CommandButton::isReady(const Object *sourceObj) const
{
	if( !sourceObj )
		return false;

	if( m_commandType == 0x17 )
	{
		if( m_upgradeTemplate && !sourceObj->rva00290D2B( m_upgradeTemplate ) )
			return false;
		return sourceObj->bfmeReadyFrameReached();
	}

	SpecialPowerModuleInterface *mod = getSpecialPowerModule( sourceObj, m_specialPower );
	if( mod && mod->getPercentReady() == 1.0f )
		return true;

	if (m_upgradeTemplate && affectedByUpgrade(sourceObj, m_upgradeTemplate) && !sourceObj->rva00290D2B(m_upgradeTemplate))
		return true;

	return false;
}
