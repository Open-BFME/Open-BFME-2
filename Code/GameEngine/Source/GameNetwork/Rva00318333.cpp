// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva00318333@Rva00318333@@QAEXPAVObject@@_N@Z 0x00318333 247B evidence: controlling player checks via 0x28AFA9 flag 0x1BC then ThePlayerList mask at +0x24 via 0x2A7B91 then bfmeHas1026 at +0x1C then AsciiString at +0x20 via isEmpty then BitFlags at +0x58 via any then AttributeModifierPoolUpdate via 0x403415 callers 0x29384E 0x318731 0x31885C
class Player;
class Object
{
	friend class Rva00318333;
public:
	Player *getControllingPlayer() const;
	void removeAttributeModifierFromPool(const class AsciiString &s);
	bool addAttributeModifierToPool(const class AsciiString &s, int v);
private:
	class AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
public:
	char m_pad00[0x8C];
	Object *m_8C;
};
class AsciiString;
#include "../../Include/GameLogic/Module/AttributeModifierPoolUpdate.h"
#include "../../Include/Common/PlayerList.h"
// 0x00362437 is rowed as Rva2225E0Filter::accepts(Object *, Player *); the old
// ?bfmeHas1026@BfmeTab1026@@QAEDHH@Z pin names the same body.
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};
class BfmeTab1026 : public Rva2225E0Filter
{
public:
	int m_00;
};
#include "../../Include/Common/BitFlagsTemplate.h"
class Player
{
public:
	char m_pad[0x34];
	class PlayerStats *m_34;
};
class PlayerStats
{
public:
	char m_pad[0x1BC];
	unsigned char m_isEvil;
};
class Rva00318333
{
public:
	void rva00318333(Object *obj, bool flag);
	void rva00318719();
	void rva00318807(int m18, int *m1Csrc, void *shiftSrc, const StringBase<char> *m20src, int *m58src, int m2C);
	void rva00318768();
private:
	char m_pad00[0x18];
	int m_18;
	BfmeTab1026 m_1C;
	StringBase<char> m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_pad30[0x28];
	BitFlags<11> m_58;
};
#include "../../Include/Common/Rva003186EE.h"
#include <string.h>
#include "../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
void Rva00318333::rva00318333(Object *obj, bool flag)
{
	if (!obj)
		return;
	if (!m_18)
		return;
	if (m_18 == 2) {
		Player *player = obj->getControllingPlayer();
		if (player) {
			player = obj->getControllingPlayer();
			PlayerStats *st = player->m_34;
			unsigned char isEvil = st ? st->m_isEvil : 0;
			if (!isEvil)
				return;
		}
	}
	if (m_18 == 3) {
		Player *player = obj->getControllingPlayer();
		if (player) {
			player = obj->getControllingPlayer();
			PlayerStats *st = player->m_34;
			unsigned char isEvil = st ? st->m_isEvil : 0;
			if (isEvil)
				return;
		}
	}
	Player *pl = (Player *)m_24;
	if (m_24) {
		pl = ThePlayerList->getPlayerFromMask(m_24);
	}
	if (!m_1C.accepts(obj, pl))
		return;
	if (!m_20.isEmpty()) {
		if (flag) {
			obj->removeAttributeModifierFromPool((const AsciiString &)m_20);
		} else {
			obj->addAttributeModifierToPool((const AsciiString &)m_20, -1);
		}
	}
	if (!m_58.any())
		return;
	AttributeModifierPoolUpdate *pool = obj->findAttributeModifierPoolUpdate();
	if (!pool)
		return;
	if (flag) {
		((AttributeModifierPoolUpdate *)pool)->rva00403415((int *)&m_58, 0);
	} else {
		((AttributeModifierPoolUpdate *)pool)->rva00403415((int *)&m_58, 0x3B9AC9FF);
	}
}
void Rva00318333::rva00318719()
{
	Object *obj = TheGameLogic->getFirstObject();
	while (obj) {
		rva00318333(obj, true);
		obj = obj->m_8C;
	}
	m_18 = 0;
	m_20.set("");
	memset(&m_58, 0, 4);
	m_24 = 0;
	m_2C = 0;
}
void Rva00318333::rva00318807(int mode, int *m1Csrc, void *shiftSrc, const StringBase<char> *m20src, int *m58src, int duration)
{
	rva00318719();
	m_18 = mode;
	m_1C.m_00 = *m1Csrc;
	m_20.set(*m20src);
	m_58 = *(const BitFlags<11> *)m58src;
	int sh = *(int *)((char *)shiftSrc + 0x54);
	m_24 = 1 << sh;
	m_2C = duration;
	Object *obj = TheGameLogic->getFirstObject();
	while (obj) {
		rva00318333(obj, false);
		obj = obj->m_8C;
	}
}
void Rva00318333::rva00318768()
{
	int oldDuration = m_2C;
	int remainingDuration = oldDuration - 1;
	m_2C = remainingDuration;
	if (!oldDuration) {
	} else if (remainingDuration) {
	} else {
		rva00318719();
	}
	int oldCountdown = m_28;
	int remainingCountdown = oldCountdown - 1;
	m_28 = remainingCountdown;
	if (!oldCountdown) {
	} else if (remainingCountdown) {
	} else {
		((Rva003186EE *)this)->rva003186EE(0, 0, 0);
	}
}
