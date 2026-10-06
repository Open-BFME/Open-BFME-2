// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005DB3B3@Rva005DB3B3@@QAEXH@Z @0x005DB3B3 351B
// Unlock Apt connection-player name/num setter via GameSpy slot + GameInfo slot.
// Evidence: callers 0x005DB61E 0x005DB639 in 0x005DB5F2 (thiscall 1 int arg ret 4);
// strings "APT:ConnectionPlayerName_%d" "APT:ConnectionPlayerNum_%d" literals;
// rowed getSlot 0x003FF29F isHuman 0x003FF0F1 format 0x00038150/0x006CB5D0
// releaseBuffer 0x00036E70/0x00036410 pinned bfmeSetText 0x00225301;
// globals TheGameSpyInfo 0x00A02320 TheRva00222A8BTarget 0x009FE4CC
// g_00BC26DC g_00C76704; GameSlot m_name at +0x30 via 0x003FFF62 precedent;
// neighbours 0x005DB335 same cl; unblocks 0x005DB5F2.
#include "ascii_string.h"
#include "unicode_string.h"

class GameInfo;
class GameSlot;

class GameSpyInfoInterface
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual void _M_slot_7c();
	virtual void _M_slot_80();
	virtual void _M_slot_84();
	virtual void _M_slot_88();
	virtual void _M_slot_8c();
	virtual void _M_slot_90();
	virtual void _M_slot_94();
	virtual void _M_slot_98();
	virtual void _M_slot_9c();
	virtual void _M_slot_a0();
	virtual void _M_slot_a4();
	virtual void _M_slot_a8();
	virtual void _M_slot_ac();
	virtual void _M_slot_b0();
	virtual void _M_slot_b4();
	virtual void _M_slot_b8();
	virtual void _M_slot_bc();
	virtual void _M_slot_c0();
	virtual void _M_slot_c4();
	virtual void _M_slot_c8();
	virtual void _M_slot_cc();
	virtual void _M_slot_d0();
	virtual GameInfo *_M_slot_d4();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class GameInfo
{
public:
	GameSlot *getSlot(int slotNum);
};

class GameSlot
{
public:
	bool isHuman() const;
	char m_pad[0x30];
	UnicodeString m_name;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const unsigned short g_00BC26DC[] = { 0 };
extern const unsigned short g_00C76704[] = { '%', 'd', '.', 0 };

class Rva005DB3B3
{
public:
	void rva005DB3B3(int idx);
};

void Rva005DB3B3::rva005DB3B3(int idx)
{
	if (!TheGameSpyInfo)
		return;
	GameInfo *info = TheGameSpyInfo->_M_slot_d4();
	if (!info)
		return;
	GameSlot *slot = info->getSlot(idx);
	if (!slot)
		return;
	AsciiString key;
	key.format("APT:ConnectionPlayerName_%d", idx);
	UnicodeString tmp(slot->m_name);
	if (slot->isHuman())
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, slot->m_name, false);
	else
	{
		UnicodeString def(g_00BC26DC);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, def, false);
	}
	key.format("APT:ConnectionPlayerNum_%d", idx);
	if (slot->isHuman())
	{
		tmp.format(g_00C76704, idx + 1);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, tmp, false);
	}
	else
	{
		UnicodeString def2(g_00BC26DC);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, def2, false);
	}
}
