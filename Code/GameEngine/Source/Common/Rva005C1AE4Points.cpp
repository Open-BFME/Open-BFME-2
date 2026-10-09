// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// ?rva005C1AE4@Rva005C1A36@@QAEHH@Z @0x005C1AE4 73B
// Slot 2 of Rva005C1A36's vtable 0x008743DC: the Points value for a faction
// index. Builds a by-value AsciiString from the faction table 0x009BE9B0,
// fetches the UserPreferences from the object held at +0x2C through its
// slot 2 (0x08), and calls the rowed Points getter 0x005358C3.
// Retail keeps the argument temporary live (state 0) across the slot-2 call
// and disarms it only before the final call. A direct `m_held->v2()->...`
// disarms before the slot-2 call (the banked 0.90 attempt); an inline
// accessor gives retail's order. Retail also keeps that accessor out of line
// at 0x005C1A85 (8B, `mov ecx,[ecx+0x2c]; mov eax,[ecx]; jmp [eax+8]`, no
// references).
#include "ascii_string.h"
#include "unicode_string.h"


class UserPreferences
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12)
#undef V
	// Slot 13 takes the current user name (0x005C1ABA).
	virtual void v13(const UnicodeString &name);

	int rva005358C3(AsciiString arg);
};

class Holder
{
public:
	virtual void v0();
	virtual void v1(void *owner);
	virtual UserPreferences *v2();
};

class Rva005C1A36
{
public:
	virtual void v0();
	virtual void v1();
	virtual int v2(int idx);
	int rva005C1AE4(int idx);
	void rva005C1ABA(const UnicodeString &name);
	// Unrowed 0x005DD48C (353 bytes), pinned by address.
	void rva005DD48C();
	UserPreferences *prefs() { return m_held->v2(); }
private:
	char m_pad[0x28];
	Holder *m_held;
};

static const char *kFactions[] = { "Men", "Elves", "Dwarves", "Isengard", "Mordor", "Wild" };

int Rva005C1A36::rva005C1AE4(int idx)
{
	return prefs()->rva005358C3(AsciiString(kFactions[idx]));
}

// ?rva005C1ABA@Rva005C1A36@@QAEXABVUnicodeString@@@Z @0x005C1ABA 42B
// (pinned so far as Rva005C1ABA): the skirmish screen's +0x668 member takes
// the new current user name: the held object's preferences get it (slot
// 13), the holder is told (slot 1, with this) and 0x005DD48C refreshes.
void Rva005C1A36::rva005C1ABA(const UnicodeString &name)
{
	m_held->v2()->v13(name);
	m_held->v1(this);
	rva005DD48C();
}

// Native5C1B2D..5C1BDE, complete177B cdecl hidden UnicodeString return.
// WB1592B10 and SIDE: key prove faction-label lookup with wide dash fallback.
// Canonical strings reproduce hidden-return construction flag and four EH
// lifetime states; fetch uses witnessed virtual slot38. Original name unknown.
class GameTextInterface {public:
#define V(n) virtual void s##n();
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
#undef V
virtual UnicodeString fetch(const AsciiString&,bool*);
};
extern GameTextInterface *TheGameText;
UnicodeString Rva005C1B2D(const AsciiString &faction){
 UnicodeString result((const unsigned short*)L"-");
 if(!((const StringBase<char>*)&faction)->isEmpty()){
  AsciiString label("SIDE:");label+=faction;
  result=TheGameText->fetch(label,0);
 }
 return result;
}
