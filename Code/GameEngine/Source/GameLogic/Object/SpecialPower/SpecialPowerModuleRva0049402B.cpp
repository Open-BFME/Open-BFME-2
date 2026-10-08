// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX
//
// ?rva0049402B@SpecialPowerModule@@QAEXPAUBfmeWideResult@@@Z @0x0049402B 428B.
// Original name unknown. Sole caller: triggerSpecialPower (0x004941F3) at
// 0x0049456F, passing the partition range query it built, with ecx = the
// primary SpecialPowerModule this (+4 module data, +8 object). Shape from the
// WorldBuilder debug body (0x011E8C20, 872B, unnamed; callgraph lead): for a
// type-0x85 template on a KindOf 300 object, the object's SpecialDisguiseUpdate
// (NAMEKEY "SpecialDisguiseUpdate", rowed findModule 0x0028B6D6) gets
// 0x004B05F5(false). The expiry frame is the current frame plus the named
// attribute modifier's duration (rowed rva00214713/getDuration), or 999999
// when the duration is not positive, and stays 0 when the data's +0x34
// BitFlags<11> (rowed any 0x0023C58B) is empty. Each queried object that is
// not KindOf 47, not the source unless data+0x20, passes the data+0x5E/+0x5F
// player-flag filters and (unless data+0x60) shares the source's controlling
// player, goes to primary virtual slot 13 (0x00493EA7) with that frame and the
// mask. Field offsets are target evidence; field meanings are inferred.
#include "ascii_string.h"
#include "../../../Common/PartitionRangeQueryCallView.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum KindOfType { KINDOF_47 = 47, KINDOF_300 = 300 };

template <int N>
class BitFlags
{
public:
	bool any() const;
	unsigned int m_words[(N + 31) / 32];
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class AttributeModifierStore
{
public:
	int rva00214713(int key);
	void *getDuration(int index);
};
extern AttributeModifierStore *TheAttributeModifierStore;

class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva0049402BFrameView { char pad[0x40]; unsigned frame; };

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x10];
};

class SpecialPowerTemplate : public Overridable
{
public:
	char m_pad10[0x1C - 0x10];
	int m_type;
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(KindOfType t) const
	{
		return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0;
	}
	char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

class Rva0049402BPlayerFlags { public: char m_pad[0x1BC]; bool m_flag; };

class Player
{
public:
	bool rva0049402BFlag() const { return m_34 ? m_34->m_flag : false; }
	char m_pad[0x34];
	Rva0049402BPlayerFlags *m_34;
};

class Module;
class SpecialPowerModule;

class Object
{
	friend class SpecialPowerModule;
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	bool isKindOf(KindOfType t) const;
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
private:
	void *m_vptr;
	const ThingTemplate *m_template;
};

class SpecialDisguiseUpdate
{
public:
	void rva004B05F5(bool keep);
};

class ModuleData
{
public:
	virtual ~ModuleData();
};

class SpecialPowerModuleData : public ModuleData
{
public:
	int m_unknown4;
	const SpecialPowerTemplate *m_specialPowerTemplate;
	char m_pad0C[0x18 - 0x0C];
	AsciiString m_attributeModifierName;
	char m_pad1C[0x20 - 0x1C];
	bool m_includeSelf;
	char m_pad21[0x34 - 0x21];
	BitFlags<11> m_mask;
	char m_pad38[0x5E - 0x38];
	bool m_skipFlaggedPlayers;
	bool m_onlyFlaggedPlayers;
	bool m_anyPlayer;
};

class SpecialPowerModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual void rva00493EA7(Object *obj, int frame, const BitFlags<11> *mask);
	void rva0049402B(BfmeWideResult *iter);
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

void SpecialPowerModule::rva0049402B(BfmeWideResult *iter)
{
	const SpecialPowerModuleData *modData = (const SpecialPowerModuleData *)m_moduleData;
	Object *source = m_object;
	if (((const SpecialPowerTemplate *)modData->m_specialPowerTemplate->friend_getFinalOverride())->m_type == 0x85
		&& source->isKindOf(KINDOF_300))
	{
		static NameKeyType key = TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
		SpecialDisguiseUpdate *disguise = (SpecialDisguiseUpdate *)source->findModule(key);
		if (disguise)
			disguise->rva004B05F5(false);
	}

	unsigned frame = 0;
	if (modData->m_mask.any())
	{
		frame = ((Rva0049402BFrameView *)TheGameLogic)->frame;
		if (!((const StringBase<char> *)&modData->m_attributeModifierName)->isEmpty())
		{
			int duration = (int)TheAttributeModifierStore->getDuration(
				TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(modData->m_attributeModifierName.str())));
			if (duration > 0)
				frame += duration;
			else
				frame += 999999;
		}
	}

	Object *obj;
	while ((obj = iter->next()) != 0)
	{
		if (obj->getTemplate()->isKindOf(KINDOF_47))
			continue;
		if (!modData->m_includeSelf && obj == source)
			continue;
		if (modData->m_skipFlaggedPlayers && obj->getControllingPlayer()->rva0049402BFlag())
			continue;
		if (modData->m_onlyFlaggedPlayers && !obj->getControllingPlayer()->rva0049402BFlag())
			continue;
		if (!modData->m_anyPlayer && obj->getControllingPlayer() != source->getControllingPlayer())
			continue;
		rva00493EA7(obj, frame, &modData->m_mask);
	}
}
