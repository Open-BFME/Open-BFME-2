// cl: /DNDEBUG /MD
// ??0Rva00332F5B@@QAE@ABVWeaponTemplateSetHead@@0@Z @0x00332F5B 38B
// retail 0x00332F5B 38 bytes: name key at +0 plus two WeaponTemplateSetHead at +4 and +0x50
// LuaScriptEngineParseModelConditionEvent sets +0 with EventFlagEntry::setKeyFromName.
// Reuse the scripted-event key view and its rowed zero constructor at 0x00326BE6;
// that folded address alone does not identify a string. Payload copy: 0x00045455.
// neighbours prev 0x00332F29 stlport vector and next 0x00333027 Disp8 getters

struct Rva00336BE4Key
{
	unsigned key;
	Rva00336BE4Key();
};

class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
private:
	char m_data[76];
};

class Rva00332F5B
{
public:
	Rva00332F5B(const WeaponTemplateSetHead &a, const WeaponTemplateSetHead &excluded);
	bool equals(const Rva00332F5B &other) const;
private:
	Rva00336BE4Key m_key;
	WeaponTemplateSetHead m_a;
	WeaponTemplateSetHead m_b;
};

Rva00332F5B::Rva00332F5B(const WeaponTemplateSetHead &weaponTemplateSetHead, const WeaponTemplateSetHead &excluded) : m_key(), m_a(weaponTemplateSetHead), m_b(excluded)
{
}

bool __cdecl Rva00045473Equal(const void *a, const void *b);

// Returns bool: the result is the && chain's 1/0 in EAX (xor eax,eax; inc eax),
// and the WorldBuilder debug twin 0xC00C20 returns mov al,[local].
__declspec(noinline) inline bool Rva00332F5B::equals(const Rva00332F5B &other) const
{
	return m_key.key == other.m_key.key && Rva00045473Equal(&m_a, &other.m_a) && Rva00045473Equal(&m_b, &other.m_b);
}
// Select-any: LuaScriptEngineParseModelConditionEvent.cpp compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva00332F81 absent-from-retail
void bfmeAnchorRva00332F81(const Rva00332F5B *record) { record->equals(*record); }
