// ?rva002BA3F2@LivingWorldLogic@@UAEXPBVRva002E0687@@@Z
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// ?rva002BA3F2@LivingWorldLogic@@UAEXPBVRva002E0687@@@Z
// retail 0x002BA3F2..0x002BA654 (610 bytes), thiscall RET 4, EH frame.
//
// Slot 0 of LivingWorldLogic's player observer vtable 0x00BFE2A4, which the
// constructor (0x002B944F) and destructor (0x002B9684) store at +0x18; the
// body is entered with this at that base, so the logic's fields read at
// -0x18 (local player +0x98, region manager +0xB0, the message vector +0x154
// and the byte at +0x175).  WorldBuilder twin 0xD87EF0 (unnamed; the four
// LW:*Defeated* labels) gives the statement order.  For the player the
// rowed 0x002E0687 test accepts, the tactical view (g_00DFEF18) flies to the
// player's region center (region manager lookup 0x002104B6 then 0x0020EA58,
// or the view's own fallback at vslot 0x70) over max(view vslot 0x64 and
// 0.6) seconds, the frame count coming from rowed 0x002BEDCA.  Otherwise,
// unless the +0x175 byte is set, an ally or enemy "defeated" title and text
// are fetched from TheGameText (ally by the rowed 0x002E071E test against
// the local player), the text is formatted with the player's name (+0x1C)
// and a new 0x28-byte message (constructor 0x002B4FBC4D, refcount at +4) is
// queued through the inlined 0x002B9A85 push onto the +0x154 vector of
// 0x002B9062 references.  The method name is not recovered.
//
// NEAR (banked): 607 of 610 bytes; the only difference is the frame slot of
// the view vslot 0x64 result temporary bound to max's first reference
// (retail [ebp-0x14] shared with seconds; cl picks the free player home
// [ebp+8]).  Needs the constructor pin ??0Rva004FBC4D@@QAE@ABVUnicodeString@@0H@Z
// at 0x004FBC4D (the existing void-method pin cannot return the new object
// that retail keeps in esi) and a data name for the 0.6f at 0x007FDF64.
// Retail keeps the new object in esi across the inlined vector push_back,
// which needs the real STLport vector in the unit (its bodies visible).

#include "ascii_string.h"
#include "unicode_string.h"
#include "Coord3D.h"

typedef float Real;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class Rva002D3627Host
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual Real slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28(Coord3D *pos);
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39(const Coord3D *pos, Real a, Real seconds, int frames);

	int rva002BEDCA(const Coord3D *pos, Real seconds);
};
extern Rva002D3627Host *g_00DFEF18;

class Rva002E0687
{
public:
	bool rva002E0687() const;

	unsigned char m_pad00[0x1c];
	UnicodeString m_name;			// +0x1C
	unsigned char m_pad20[0x2c - 0x20];
	unsigned char m_key[4];			// +0x2C
};

class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;
};

class Rva002104B6
{
public:
	void *rva002104B6(void *key);
};

class Rva002B2702B0
{
public:
	bool rva0020EA58(void *region, float *center);
};

class Rva004FBC4D
{
public:
	Rva004FBC4D(const UnicodeString &title, const UnicodeString &text, int arg);

	void *m_vtbl;
	int m_refCount;				// +0x04
	unsigned char m_pad08[0x28 - 0x08];
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct Rva002B9062Element
{
	Rva004FBC4D *m_object;

	Rva002B9062Element(Rva004FBC4D *object) : m_object(object)
	{
		if (object)
			++object->m_refCount;
	}
	Rva002B9062Element(const Rva002B9062Element &that) : m_object(that.m_object)
	{
		if (m_object)
			++m_object->m_refCount;
	}
	~Rva002B9062Element()
	{
		if (m_object)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_object);
	}
};

#include <vector>

extern const Real g_00BFDF64;	// 0.6f, file-local rdata used only here

struct Rva002BA3F2Max
{
	static const Real &max(const Real &a, const Real &b)
	{
		return a < b ? b : a;
	}
};

class Rva002BA3F2Base00
{
public:
	virtual void slot00();

	unsigned char m_pad04[0x10 - 0x04];
};

class Rva002BA3F2Base10
{
public:
	virtual void slot00();
};

class Rva002BA3F2Base14
{
public:
	virtual void slot00();
};

class Rva002BA3F2PlayerObserver
{
public:
	virtual void rva002BA3F2(const Rva002E0687 *player) = 0;
};

class LivingWorldLogic : public Rva002BA3F2Base00, public Rva002BA3F2Base10,
	public Rva002BA3F2Base14, public Rva002BA3F2PlayerObserver
{
public:
	virtual void rva002BA3F2(const Rva002E0687 *player);

	Rva002104B6 *getRegions() { return m_regions; }
	void addMessage(const Rva002B9062Element &message)
	{
		m_messages.push_back(message);
	}

	unsigned char m_pad1C[0x98 - 0x1c];
	Rva002E071E *m_localPlayer;		// +0x98
	unsigned char m_pad9C[0xb0 - 0x9c];
	Rva002104B6 *m_regions;			// +0xB0
	unsigned char m_padB4[0x154 - 0xb4];
	_STL::vector<Rva002B9062Element> m_messages;	// +0x154
	unsigned char m_pad160[0x175 - 0x160];
	bool m_field175;			// +0x175
};

void LivingWorldLogic::rva002BA3F2(const Rva002E0687 *player)
{
	if (player->rva002E0687())
	{
		Real seconds = Rva002BA3F2Max::max(g_00DFEF18->slot25(), g_00BFDF64);
		Coord3D pos;
		pos.x = 0.0f;
		pos.y = 0.0f;
		pos.z = 0.0f;
		void *region = getRegions()->rva002104B6((void *)player->m_key);
		bool found = false;
		if (region)
		{
			float center[2];
			center[0] = 0.0f;
			center[1] = 0.0f;
			found = ((Rva002B2702B0 *)getRegions())->rva0020EA58(region, center);
			if (found)
			{
				pos.x = center[0];
				pos.y = center[1];
			}
		}
		if (!found)
			g_00DFEF18->slot28(&pos);
		int frames = g_00DFEF18->rva002BEDCA(&pos, seconds);
		g_00DFEF18->slot39(&pos, 0.0f, seconds, frames);
	}
	else if (!m_field175)
	{
		UnicodeString title;
		UnicodeString text;
		if (m_localPlayer->rva002E071E((const Rva002E071E *)player))
		{
			title = TheGameText->fetch("LW:AllyDefeatedTitle");
			text = TheGameText->fetch("LW:AllyDefeatedText");
			text.format(&text, player->m_name.str());
		}
		else
		{
			title = TheGameText->fetch("LW:EnemyDefeatedTitle");
			text = TheGameText->fetch("LW:EnemyDefeatedText");
			text.format(&text, player->m_name.str());
		}
		Rva002B9062Element message(new Rva004FBC4D(title, text, 0));
		addMessage(message);
	}
}
