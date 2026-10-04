// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1
// ?rva00318333@Rva00318333@@QAEXPAVObject@@_N@Z 0x00318333 247B evidence: controlling player checks via 0x28AFA9 flag 0x1BC then ThePlayerList mask at +0x24 via 0x2A7B91 then bfmeHas1026 at +0x1C then AsciiString at +0x20 via isEmpty then BitFlags at +0x58 via any then AttributeModifierPoolUpdate via 0x403415 callers 0x29384E 0x318731 0x31885C
class Player;
class Object
{
	friend class Rva00318333;
public:
	Player *getControllingPlayer() const;
	void rva0028EB42(const class AsciiString &s);
	bool rva0028EA91(const class AsciiString &s, int v);
private:
	class AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
public:
	char m_pad00[0x8C];
	Object *m_8C;
};
class AsciiString;
template<class T> class StringBase
{
public:
	bool isEmpty() const;
	void set(const T *);
	void set(const StringBase &);
};
class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;
class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
	int m_00;
};
template<int N> class BitFlags
{
public:
	bool any() const;
	unsigned int m_words[(N + 31) / 32];
};
class AttributeModifierPoolUpdate
{
public:
	void rva00403415(int *mask, int value);
};
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
	unsigned char m_1BC;
};
class Rva00318333
{
public:
	void rva00318333(Object *obj, bool flag);
	void rva00318719();
	void rva00318807(int m18, int *m1Csrc, void *shiftSrc, const StringBase<char> *m20src, int *m58src, int m2C);
private:
	char m_pad00[0x18];
	int m_18;
	BfmeTab1026 m_1C;
	StringBase<char> m_20;
	int m_24;
	char m_pad28[4];
	int m_2C;
	char m_pad30[0x28];
	BitFlags<11> m_58;
};
extern "C" void *__cdecl memset(void *dst, int c, unsigned int count);
class GameLogic
{
public:
	Object *getFirstObject();
};
extern GameLogic *TheGameLogic;
extern const char g_Rva0107301CEmptyString[];
void Rva00318333::rva00318333(Object *obj, bool flag)
{
	if (!obj)
		return;
	if (!m_18)
		return;
	if (m_18 == 2) {
		Player *p = obj->getControllingPlayer();
		if (p) {
			p = obj->getControllingPlayer();
			PlayerStats *st = p->m_34;
			unsigned char f = st ? st->m_1BC : 0;
			if (!f)
				return;
		}
	}
	if (m_18 == 3) {
		Player *p = obj->getControllingPlayer();
		if (p) {
			p = obj->getControllingPlayer();
			PlayerStats *st = p->m_34;
			unsigned char f = st ? st->m_1BC : 0;
			if (f)
				return;
		}
	}
	Player *pl = (Player *)m_24;
	if (m_24) {
		pl = ThePlayerList->getPlayerFromMask(m_24);
	}
	if (!m_1C.bfmeHas1026((int)obj, (int)pl))
		return;
	if (!m_20.isEmpty()) {
		if (flag) {
			obj->rva0028EB42((const AsciiString &)m_20);
		} else {
			obj->rva0028EA91((const AsciiString &)m_20, -1);
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
	m_20.set(g_Rva0107301CEmptyString);
	memset(&m_58, 0, 4);
	m_24 = 0;
	m_2C = 0;
}
void Rva00318333::rva00318807(int m18, int *m1Csrc, void *shiftSrc, const StringBase<char> *m20src, int *m58src, int m2C)
{
	rva00318719();
	m_18 = m18;
	m_1C.m_00 = *m1Csrc;
	m_20.set(*m20src);
	m_58.m_words[0] = (unsigned int)*m58src;
	int sh = *(int *)((char *)shiftSrc + 0x54);
	m_24 = 1 << sh;
	m_2C = m2C;
	Object *obj = TheGameLogic->getFirstObject();
	while (obj) {
		rva00318333(obj, false);
		obj = obj->m_8C;
	}
}
