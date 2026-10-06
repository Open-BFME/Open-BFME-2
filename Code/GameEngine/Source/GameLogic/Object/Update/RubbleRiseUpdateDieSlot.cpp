// cl: /DNDEBUG /MD
//
// ?rva004A4D98@RubbleRiseUpdate@@UAEXPBVDamageInfo@@@Z, retail 0x004A4D98, 38
// bytes: slot 0 of the vtable 0x00C52858 that RubbleRiseUpdate's ctors
// (0x004A4C2D, 0x004A4D03) install at +0x20, the die-module slot: when the
// module data's DieMuxData (at +8, rowed isDieApplicable 0x004CE588) applies to
// the owner and the damage, the matched primary member 0x004A4D70 runs (the
// Object read before the module data, as retail orders the loads).
// Compiled with the +0x20 subobject this. Names by address.
class Object;
class DamageInfo;

class DieMuxData
{
public:
	bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;
};

struct RubbleRiseUpdateModuleData
{
	unsigned char m_pad00[8];
	DieMuxData m_dieMuxData; // +0x08
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	const RubbleRiseUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
private:
	unsigned char m_pad0C[0x20 - 0x0C];
};

class DieModuleInterface
{
public:
	virtual void rva004A4D98(const DamageInfo *damageInfo) = 0;
};

class RubbleRiseUpdate : public UpdateModule, public DieModuleInterface
{
public:
	virtual void rva004A4D98(const DamageInfo *damageInfo);
	void rva004A4D70();
};

void RubbleRiseUpdate::rva004A4D98(const DamageInfo *damageInfo)
{
	Object *obj = m_object;
	const RubbleRiseUpdateModuleData *d = m_moduleData;
	if (!d->m_dieMuxData.isDieApplicable(obj, damageInfo))
		return;
	rva004A4D70();
}
