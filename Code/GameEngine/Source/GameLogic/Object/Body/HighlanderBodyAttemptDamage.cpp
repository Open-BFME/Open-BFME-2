// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// HighlanderBody::attemptDamage, retail 0x004C082B (67 bytes): slot 0 of the
// class's body-module interface table at VA 0x00C5B390, placed directly
// after HighlanderBody's constructor, pool key and destructors. As Zero
// Hour's HighlanderBody does, it clamps every damage except one type to
// leave at least one hit point -- amount = min(amount, getHealth() - 1) --
// and then forwards to ActiveBody::attemptDamage (0x004BFE07, pinned).
// Target facts: the exempt type is 8 at DamageInfo +0x10 and the amount is
// the float at +0x20; getHealth is slot 4 (+0x10) of the interface, one
// later than in ZH. getHealth is read once, so the clamp is a by-reference
// a < b ? a : b template rather than ZH's min macro. Retail compares with
// fcompi, which MSVC 7.1 emits only under /arch:SSE.
class DamageInfo
{
public:
	unsigned char m_pad00[0x10];
	int m_damageType;		// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	float m_amount;			// +0x20
};
class ModuleData;
class Object;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo) = 0;
	virtual void i01() = 0;
	virtual void i02() = 0;
	virtual void i03() = 0;
	virtual float getHealth() const = 0;
};
class BodyModule : public ModuleBase, public BehaviorModuleInterface, public BodyModuleInterface
{
};
class ActiveBody : public BodyModule
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};
class HighlanderBody : public ActiveBody
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};

template <class T> inline const T &bfmeMin(const T &a, const T &b) { return a < b ? a : b; }

void HighlanderBody::attemptDamage(DamageInfo *damageInfo)
{
	// 8 is the damage type ZH spells DAMAGE_UNRESISTABLE.
	if (damageInfo->m_damageType != 8)
		damageInfo->m_amount = bfmeMin(damageInfo->m_amount, getHealth() - 1.0f);
	ActiveBody::attemptDamage(damageInfo);
}
