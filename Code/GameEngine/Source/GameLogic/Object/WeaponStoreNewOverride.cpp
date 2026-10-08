// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?newOverride@WeaponStore@@QAEPAVWeaponTemplate@@PAV2@@Z, retail 0x002CE063
// (159 bytes).
// Identity (target): WorldBuilder's debug Weapon.cpp:1996
// WeaponStore::newOverride calls operator new, the WeaponTemplate
// constructor (0x002CD169) and copy assignment (0x002CD67C), then the
// template vector's erase and push_back, as retail does.
// Donor (BFME 1 / Zero Hour WeaponStore::newOverride): a new template copied
// from the given one, chained to it as its next template (+0x04). BFME 2
// deltas (target): no override of an override (flag +0x160, set on the new
// one), and the store's template vector (+0x0C) swaps the entry with the
// same name key (+0x0C) for the new template. The 0x180-byte allocation
// and its constructor stand for newInstance(WeaponTemplate).
#include <vector>
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct FieldParse;
// Retail Weapon FieldParse table; its original linker symbol is unestablished.
extern const FieldParse g_00C00B48[];
enum INILoadType;
// Target-only INI view: the retail parser reads its load type at +0x08.
// This declaration does not assert the size or the other fields of INI.
class INI
{
public:
    const char *getNextToken(const char *seps = 0);
    void initFromINI(void *object, const FieldParse *fields);
    INILoadType getLoadType() const { return m_loadType; }
private:
    unsigned char m_pad00[8];
    INILoadType m_loadType;
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class WeaponTemplate
{
    friend class WeaponStore;
public:
	WeaponTemplate();
	WeaponTemplate &operator=(const WeaponTemplate &that);

	NameKeyType getNameKey() const { return m_nameKey; }
	bool isOverride() const { return m_isOverride; }
	void friend_setNextTemplate(WeaponTemplate *next) { m_nextTemplate = next; }
	void friend_setIsOverride() { m_isOverride = true; }

private:
	unsigned char m_pad000[0x04];
	WeaponTemplate *m_nextTemplate; // +0x04
	AsciiString m_name; // +0x08
	NameKeyType m_nameKey; // +0x0C
	unsigned char m_pad010[0x160 - 0x10];
	bool m_isOverride; // +0x160
    unsigned char m_pad161[0x174 - 0x161];
    mutable int m_retired; // +0x174
    unsigned char m_pad178[0x180 - 0x178];
};

typedef _STL::vector<WeaponTemplate *, _STL::allocator<WeaponTemplate *> > WeaponTemplateVector;

class WeaponStore
{
public:
	WeaponTemplate *newOverride(WeaponTemplate *weaponTemplate);
    void rva002CDB0E(const WeaponTemplate *weaponTemplate);
    static void parseWeaponTemplateDefinition(INI *ini);

protected:
    WeaponTemplate *findWeaponTemplatePrivate(NameKeyType key) const;
    WeaponTemplate *newWeaponTemplate(const AsciiString &name);

private:
	unsigned char m_pad00[0x0C];
	WeaponTemplateVector m_weaponTemplateVector; // +0x0C
    _STL::vector<const WeaponTemplate *> m_retiredTemplates; // +0x18
};

WeaponTemplate *WeaponStore::newOverride(WeaponTemplate *weaponTemplate)
{
	if (weaponTemplate == 0)
		return 0;
	if (weaponTemplate->isOverride())
		return 0;

	WeaponTemplate *wt = new WeaponTemplate;
	*wt = *weaponTemplate;
	wt->friend_setNextTemplate(weaponTemplate);
	wt->friend_setIsOverride();

	NameKeyType key = wt->getNameKey();
	for (WeaponTemplateVector::iterator it = m_weaponTemplateVector.begin(); it != m_weaponTemplateVector.end(); ++it)
	{
		if ((*it)->getNameKey() == key)
		{
			m_weaponTemplateVector.erase(it);
			break;
		}
	}
	m_weaponTemplateVector.push_back(wt);
	return wt;
}

// Target: retail 0x002CADBE is the complete 60-byte key search; the mapped
// WorldBuilder Weapon.cpp body indexes the vector at +0x0C and compares the
// template key at +0x0C. WeaponStore callers establish the receiver and role.
// Name, protected access and mutable return follow Zero Hour Weapon.h/source.
// Keep the genuine STLport size/index operations: a hand-written pointer range
// hoists the count and differs from retail's loop-bottom recomputation.
WeaponTemplate *WeaponStore::findWeaponTemplatePrivate(NameKeyType key) const
{
    for (int i = 0; i < m_weaponTemplateVector.size(); ++i)
        if (m_weaponTemplateVector[i]->getNameKey() == key)
            return m_weaponTemplateVector[i];
    return 0;
}

// Retail 0x002CD5FC: complete 128-byte creator. The mapped WB Weapon.cpp body
// proves the 0x180 allocation, constructor, name at +0x08, key at +0x0C and
// vector at store+0x0C. Both retail parser call sites pass their live string by
// reference; they emit no by-value string copy or cleanup. Zero Hour supplies
// the creator's purpose and member sequence; these layouts and ABI are target
// facts. Donor reviewed: reference/open-bfme-1 at ba7ddda7e8f26116
// (Zero Hour Weapon.cpp/Weapon.h). isEmpty uses retail's shared StringBase thunk.
WeaponTemplate *WeaponStore::newWeaponTemplate(const AsciiString &name)
{
    if (((const StringBase<char> *)&name)->isEmpty())
        return 0;
    WeaponTemplate *wt = new WeaponTemplate;
    wt->m_name = name;
    wt->m_nameKey = TheNameKeyGenerator->nameToKey(name);
    m_weaponTemplateVector.push_back(wt);
    return wt;
}

// Complete 69-byte helper formerly assigned to Weapon/ModuleData. Target WB
// parser bb475a and retail 0x002CE160 pass TheWeaponStore and the selected
// WeaponTemplate. The helper moves that template from the +0x0C active vector
// to +0x18 and sets its +0x174 flag, which the parser clears on its replacement.
// Receiver, argument and fields are target facts; the original method name is
// still unknown, so retain the RVA spelling rather than invent a semantic name.
void WeaponStore::rva002CDB0E(const WeaponTemplate *arg)
{
    if (!arg)
        return;
    WeaponTemplate **finish = m_weaponTemplateVector.end();
    for (WeaponTemplate **it = m_weaponTemplateVector.begin(); it != finish; ++it)
    {
        if (arg == *it)
        {
            arg->m_retired = 1;
            m_weaponTemplateVector.erase(it);
            m_retiredTemplates.push_back(arg);
            return;
        }
    }
}

extern WeaponStore *TheWeaponStore;
// Target identity: the INI Weapon block, mapped WB Weapon.cpp:2151 and its
// complete 170-byte retail handler agree on lookup/create/override dispatch.
// BFME 2 also handles numeric load type 5 by moving the old template aside;
// its original enum label is not established here. The parser retains its
// store receiver across the lookup because the exact helper is visible above.
// 0x00C00B48 is retail's descriptor input: independently decoded as 124
// 16-byte FieldParse records followed by an all-zero terminator at 0x00C01308.
// This function owns no descriptor data; the existing table is its input.
void WeaponStore::parseWeaponTemplateDefinition(INI *ini)
{
    AsciiString name;
    name.set(ini->getNextToken());
    WeaponTemplate *weapon = TheWeaponStore->findWeaponTemplatePrivate(TheNameKeyGenerator->nameToKey(name));
    if (weapon)
    {
        if (ini->getLoadType() == 2)
            weapon = TheWeaponStore->newOverride(weapon);
        else if (ini->getLoadType() == 5)
        {
            TheWeaponStore->rva002CDB0E(weapon);
            weapon = TheWeaponStore->newWeaponTemplate(name);
            weapon->m_retired = 0;
        }
        else
            return;
    }
    else
        weapon = TheWeaponStore->newWeaponTemplate(name);
    ini->initFromINI(weapon, g_00C00B48);
}
