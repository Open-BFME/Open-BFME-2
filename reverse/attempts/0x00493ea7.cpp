// ?rva00493EA7@SpecialPowerModule@@UAEXPAVObject@@HPBV?$BitFlags@$0L@@@@Z
// partial score=0.99 date=2026-10-05
// ?rva00493EA7@SpecialPowerModule@@UAEXPAVObject@@HPBV?$BitFlags@$0L@@@@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// @0x00493EA7 388B
// model=space-bunny-alpha
// Evidence: vslot 13 of 23 special-power vtables; callers 0x004C38BF 0x004C7BD0; sibling dtor 0x00493DEF same flags.
// The banked attempt declared five callees with mangled names that do not exist in the ledger, so every
// one of those call sites was an UNRESOLVED REL32 and the comparison could never mask it:
//   bank ?findAttributeModifierPoolUpdate@Object@@QBEPBVAttributeModifierPoolUpdate@@XZ
//        -> real ?findAttributeModifierPoolUpdate@Object@@ABEPAVAttributeModifierPoolUpdate@@XZ (private const,
//           returns AttributeModifierPoolUpdate*)
//   bank ?rva00403415@AttributeModifierPoolUpdate@@QBEXPAH0@Z
//        -> real ?rva00403415@AttributeModifierPoolUpdate@@QAEXPAHH@Z (public, void(int* mask, int value))
//   bank ?rva0028EA91@Object@@QBE_NABVAsciiString@@H@Z
//        -> real ?rva0028EA91@Object@@QAE_NABVAsciiString@@H@Z (non-const)
//   bank ?getRelationship@Object@@QBEHPBV1@@Z
//        -> real ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z (returns Relationship&)
//   bank ?doFXObj@FXList@@SAXPBXPBVObject@@1@Z
//        -> real ?doFXObj@FXList@@SAXPBV1@PBVObject@@1@Z
#include "ascii_string.h"

template <int N> class BitFlags
{
public:
	bool any() const;
private:
	unsigned int m_bits[1];
};

class ExperienceTracker
{
public:
	bool rva0039ABFF() const;
	bool rva0039B4EC(int a, bool b, bool c);
};

class Player;
class AttributeModifierPoolUpdate;

enum Relationship { REL_NEUTRAL = 0, REL_ALLY = 1, REL_ENEMY = 2 };

class SpecialPowerModule;

class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva0028EA91(const AsciiString &s, int v);
	Relationship getRelationship(const Object *other) const;
private:
	// private: the A/B access pair is part of the mangled name, so these must
	// stay private to reproduce ?findAttributeModifierPoolUpdate@Object@@ABEPAV...
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
	friend class SpecialPowerModule;
	char m_pad00[0x04];
	void *m_04;
	char m_pad08[0x264 - 0x08];
	ExperienceTracker *m_264;
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad[0x34];
	void *m_34;
	char m_pad38[0x54 - 0x38];
	int m_playerIndex;
};

class PlayerTemplate
{
public:
	unsigned char m_1BC[1];
private:
	char m_pad[0x1BC];
public:
	unsigned char m_flag1BC;
};

class ModuleData
{
public:
	virtual ~ModuleData();
};

class SpecialPowerModuleData : public ModuleData
{
public:
	char m_pad04[0x18 - 0x04];
	AsciiString m_18;
	char m_pad1C[0x28 - 0x1C];
	void *m_28;
	char m_pad2C[0x42 - 0x2C];
	unsigned char m_42;
	char m_pad43[0x4C - 0x43];
	void *m_4C;
	char m_pad50[0x58 - 0x50];
	int m_58;
	unsigned char m_5C;
	unsigned char m_5D;
	unsigned char m_5E;
	unsigned char m_5F;
};

extern class GameLogic *TheGameLogic;
class GameLogic
{
public:
	char m_pad[0x40];
	int m_40;
};

extern const char g_bfmeEmptyF9[];

class AttributeModifierPoolUpdate
{
public:
	void rva00403415(int *mask, int value);
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class SpecialPowerModule
{
public:
	virtual ~SpecialPowerModule();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void rva00493EA7(Object *obj, int value, const BitFlags<11> *disabled);
protected:
	const SpecialPowerModuleData *m_moduleData;
	Object *m_object;
};

// ?rva00493EA7@SpecialPowerModule@@UAEXPAVObject@@HPBV?$BitFlags@$0L@@@@Z present-unmatched
void SpecialPowerModule::rva00493EA7(Object *obj, int value, const BitFlags<11> *disabled)
{
	const SpecialPowerModuleData *data = m_moduleData;
	ExperienceTracker *tracker = *(ExperienceTracker **)((char *)obj + 0x264);
	// Retail emits a do-while on the counter: one `test`/`jg` pair, entry and
	// back-edge both `jmp` to it, and the failed predicate clears the counter.
	if (tracker != 0) {
		int count = data->m_58;
		while (count > 0) {
			if (tracker->rva0039ABFF()) {
				tracker->rva0039B4EC(1, true, false);
				--count;
			} else {
				count = 0;
			}
		}
	}
	AsciiString *name = (AsciiString *)((char *)data + 0x18);
	if (name->isEmpty()) {
	} else {
		// Retail branches on the null data pointer first and adds 8 in the
		// fall-through, so the empty literal sits after the `add`.
		const char *text = *(const char **)name;
		if (text != 0)
			text += 8;
		else
			text = g_bfmeEmptyF9;
		AsciiString tmp(text);
		obj->rva0028EA91(tmp, -1);
	}
	if (value == 0)
		return;
	if (!disabled->any())
		return;
	// The pool is stored through a volatile-qualified pointer so the returned value
// is written straight into its stack slot (`mov [ebp+8],eax`); without it cl
// routes the result through ecx and emits an extra `mov ecx,eax`.
AttributeModifierPoolUpdate *const volatile pool = obj->findAttributeModifierPoolUpdate();
	bool flag = false;
	if (data->m_42 != 0) {
		if (data->m_5F != 0) {
			Player *player = obj->getControllingPlayer();
			int *t = *(int **)((char *)player + 0x34);
			if (t != 0) {
				unsigned char v = *((unsigned char *)t + 0x1BC);
				if (v != 0)
					flag = true;
			}
		}
		if (data->m_5E != 0) {
			Player *player = obj->getControllingPlayer();
			int *t = *(int **)((char *)player + 0x34);
			if (t != 0) {
				unsigned char v = *((unsigned char *)t + 0x1BC);
				if (v == 0)
					flag = true;
			}
		}
		if (data->m_5F == 0 && data->m_5E == 0) {
			Object *self = m_object;
			void *rel = *(void **)((char *)self + 8);
			if (obj->getRelationship((Object *)rel) == 2)
				flag = true;
		}
		if (flag) {
			int v = TheGameLogic->m_40;
			pool->rva00403415((int *)disabled, v);
		} else {
			pool->rva00403415((int *)disabled, value);
		}
	} else {
		pool->rva00403415((int *)disabled, value);
	}
	const FXList *fx = (const FXList *)data->m_4C;
	if (fx != 0)
		FXList::doFXObj(fx, obj, (const Object *)0);
	const FXList *fx2 = (const FXList *)data->m_28;
	if (fx2 != 0) {
		void *o4 = *(void **)((char *)obj + 4);
		if ((*((unsigned char *)o4 + 0x115) & 0x20) == 0)
			FXList::doFXObj(fx2, obj, (const Object *)0);
	}
}