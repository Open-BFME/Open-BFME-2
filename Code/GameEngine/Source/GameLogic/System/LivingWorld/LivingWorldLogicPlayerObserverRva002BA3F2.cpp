// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
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
// and a new 0x28-byte message (constructor 0x004FBC4D, refcount at +4) is
// queued through the inlined 0x002B9A85 push onto the +0x154 vector of
// 0x002B9062 references.  The method name is not recovered.
//
// The temporary of the view vslot 0x64 result shares [ebp-0x14] with seconds
// only when the defeated branch follows an early return: its title and text
// then live in the function scope and keep the temporary out of the free
// player home [ebp+8].  Retail keeps the new object in esi across the
// inlined vector push_back so the real STLport vector is in the unit.  The
// message constructor at 0x004FBC4D is called as
// ??0Rva004FBCBE@@QAE@ABVUnicodeString@@0H@Z (it returns the object) and
// the 0.6f at 0x007FDF64 is the file-local g_00BFDF64.
// Constructor4FBC4D now has a whole113-byte provider on the same neutral
// owner as destructor4FBCBE and12-byte8634E4 vtable. This declaration
// retains only the caller-observed refcount4 and total28-byte extent.

#include "ascii_string.h"
#include "unicode_string.h"
#include "Coord3D.h"
#include "Coord2D.h"

typedef float Real;

#include "../../../../Include/GameClient/GameText.h"

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
class LivingWorld; extern LivingWorld *TheLivingWorld;

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

// The region (+0x3C word, +0x48 map position) and army views of slot 1;
// both names come from rowed UnicodeString getters.
class Rva0020E89C
{
public:
	UnicodeString rva0020E89C();
	unsigned char m_pad00[0x3c];
	void *m_3c;				// +0x3C
	unsigned char m_pad40[0x48 - 0x40];
	Coord2D m_position;			// +0x48
};
class Rva003F1241
{
public:
	UnicodeString rva003F1241();
};
class Vector3;
#include "../../../../Include/Common/Rva002BF4F3.h"
#include "../../../../Include/GameLogic/LivingWorldRegionManager.h"

// The rowed 0x004FBC02 position setter (position +0x18, flag +0x24).
struct Rva004FBC02Src;
class Rva004FBC02 { public: void rva004FBC02(const Rva004FBC02Src *position); };

class Rva004FBCBE
{
public:
	Rva004FBCBE(const UnicodeString &title, const UnicodeString &text, int arg);

	virtual ~Rva004FBCBE();
 virtual void slot04();
 virtual void slot08();
 int m_refCount;				// +0x04
	unsigned char m_pad08[0x14 - 0x08];
	void *m_14;				// +0x14
	unsigned char m_pad18[0x28 - 0x18];
};
// The 0x48-byte region message (vtable 0x00C63B34): ctor 0x004FF28E builds
// the 0x28-byte base from the two strings, then keeps the region at +0x28
// and copies the army word at +0x2C.
class Rva004FF2C0 : public Rva004FBCBE
{
public:
	Rva004FF2C0(Rva0020E89C *region, Rva003F1241 *army, const UnicodeString &title, const UnicodeString &text, int arg);
	unsigned char m_pad28[0x48 - 0x28];
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct Rva002B9062Element
{
	Rva004FBCBE *m_object;

	Rva002B9062Element(Rva004FBCBE *object) : m_object(object)
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
	Rva004FBCBE *operator->() const { return m_object; }
};

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
namespace _STL { template<> void vector<Rva002B9062Element>::_M_clear(); }

extern const Real g_00BFDF64;	// 0.6f, file-local rdata used only here
const Real g_00BFDF64 = 0.6f;	// retail .rdata VA 0x00BFDF64 (bound by address: max takes const Real &)

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
	virtual void rva002BA654(const Rva002E0687 *player, Rva0020E89C *region, Rva003F1241 *army) = 0;
};

class LivingWorldLogic : public Rva002BA3F2Base00, public Rva002BA3F2Base10,
	public Rva002BA3F2Base14, public Rva002BA3F2PlayerObserver
{
public:
	virtual void rva002BA3F2(const Rva002E0687 *player);
	virtual void rva002BA654(const Rva002E0687 *player, Rva0020E89C *region, Rva003F1241 *army);

	Rva002104B6 *getRegions() { return m_regions; }
	void addMessage(const Rva002B9062Element &message)
	{
		m_messages.push_back(message);
	}

	unsigned char m_pad1C[0x98 - 0x1c];
	Rva002E071E *m_localPlayer;		// +0x98
	unsigned char m_pad9C[0xb0 - 0x9c];
	Rva002104B6 *m_regions;			// +0xB0
	unsigned char m_padB4[0xf4 - 0xb4];
	int m_fieldF4;				// +0xF4
	unsigned char m_padF8[0xfc - 0xf8];
	int m_fieldFC;				// +0xFC
	unsigned char m_pad100[0x154 - 0x100];
	_STL::vector<Rva002B9062Element> m_messages;	// +0x154
	unsigned char m_pad160[0x175 - 0x160];
	bool m_field175;			// +0x175
};

void LivingWorldLogic::rva002BA3F2(const Rva002E0687 *player)
{
	if (player->rva002E0687())
	{
		Real seconds = Rva002BA3F2Max::max(((Rva002D3627Host *)TheLivingWorld)->slot25(), g_00BFDF64);
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
			found = ((LivingWorldRegionManager *)getRegions())->GetRegionCenterPoint((Rva0020E89C *)region, (Coord2D *)center);
			if (found)
			{
				pos.x = center[0];
				pos.y = center[1];
			}
		}
		if (!found)
			((Rva002D3627Host *)TheLivingWorld)->slot28(&pos);
		int frames = ((Rva002D3627Host *)TheLivingWorld)->rva002BEDCA(&pos, seconds);
		((Rva002D3627Host *)TheLivingWorld)->slot39(&pos, 0.0f, seconds, frames);
		return;
	}
	if (m_field175)
		return;
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
	Rva002B9062Element message(new Rva004FBCBE(title, text, 0));
	addMessage(message);
}

// Slot 1 of the same observer vtable (0x00BFE2A8): native 0x002BA654..
// 0x002BA829 (471B, RET 0xC), WorldBuilder twin 0xD88320 (unnamed; the two
// LW:UnifiedRegion* labels give the statement order). Unless both the +0xFC
// word and the +0xF4 count are clear, a player the rowed 0x002E0687 test
// accepts gets a unified-region message: the title is formatted with the
// region name, the text with the region name and the army string, and the
// new 0x48-byte message (ctor 0x004FF28E) takes the region's +0x3C word and
// its +0x48 map position through the tactical transform 0x002BF5B0 before it
// is queued on the +0x154 vector. The method name is not recovered.
void LivingWorldLogic::rva002BA654(const Rva002E0687 *player, Rva0020E89C *region, Rva003F1241 *army)
{
	if (m_fieldFC == 0 && m_fieldF4 <= 0)
		return;
	if (!player->rva002E0687())
		return;
	UnicodeString title = TheGameText->fetch("LW:UnifiedRegionTitle");
	title.format(&title, region->rva0020E89C().str());
	UnicodeString text = TheGameText->fetch("LW:UnifiedRegionText");
	text.format(&text, region->rva0020E89C().str(), army->rva003F1241().str());
	Rva002B9062Element message(new Rva004FF2C0(region, army, title, text, 0));
	Coord2D xy;
	xy.x = region->m_position.x;
	xy.y = region->m_position.y;
	Coord3D position;
	position.x = xy.x;
	position.y = xy.y;
	position.z = 0.0f;
	((Rva002BF4F3 *)TheLivingWorld)->rva002BF5B0((const Vector3 *)&xy, (Vector3 *)&position);
	void *word = region->m_3c;
	message->m_14 = word;
	((Rva004FBC02 *)message.operator->())->rva004FBC02((const Rva004FBC02Src *)&position);
	addMessage(message);
}
