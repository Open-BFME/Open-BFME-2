// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /arch:SSE
// stlport
//
// FindInGameNotificationType, retail 0x0022216E (59B), from the WorldBuilder
// lead (InGameNotificationType.cpp; its "result != NULL" and name assertions
// at lines 291..292 are compiled out of retail). Retail makes sure the store
// singleton exists (0x002220DC, holder g_00DFE4C4), looks the name up in the
// store's AsciiString-keyed map at +0x28 with find (WorldBuilder's debug build
// uses operator[]) and returns the found entry's InGameNotificationType base
// (entry +8), or NULL.
//
// The store and entry types are not established and keep address-derived
// names.

#include "ascii_string.h"
#include "unicode_string.h"
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

struct FontDesc
{
	AsciiString name;
	int size;
	bool bold;
};

class Image;
class GameFont;
class GameMessageList;

class GameMessage
{
public:
	void friend_setList(GameMessageList *list);
};

class Gen_00489270
{
public:
	__declspec(noinline) void m(int val);
private:
	char m_unknown00[0x10];
	int m_word10;
};
// Target 5F69CE stores the argument word at +10. Notification builder
// 2219D1 uses it for color; the inherited receiver spelling remains provisional.
void Gen_00489270::m(int val) { m_word10 = val; }

struct Rva0040FB15WideStringCopyForward
{
	void set(const StringBase<unsigned short> &that);
};

struct OpaqueRefElement4
{
	void *referent;
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva002D9D7CRef : public OpaqueRefElement4
{
	~Rva002D9D7CRef() { if (referent) ((OpaqueRefCounted *)referent)->Release_Ref(); }
};

struct Rva0040FB2E
{
	OpaqueRefElement4 &rva0040FB2E(const OpaqueRefElement4 &other);
};

class Rva0040FB1A
{
public:
	Rva0040FB1A();
	int m_00;
	int m_04;
	const Image *m_08;
	int m_0C;
	int m_10;
};

class Rva002217EA : public Rva0040FB1A
{
public:
	Rva002217EA() {}
	Rva002217EA(const Rva002217EA &other);
	~Rva002217EA();
	__declspec(noinline) void rva0010670B(const Image *image);
};

// Target 10670B and the independently recovered builder establish the
// image pointer at +8. This retires the anonymous GameMessage alias row.
void Rva002217EA::rva0010670B(const Image *image) { m_08 = image; }

class InGameNotificationType
{
public:
	AsciiString m_textKey;
	AsciiString m_audioKey;
	AsciiString m_imageKey;
	FontDesc m_font;
	int m_color;

	Rva002217EA rva00221ABB() const;
};

struct Rva0022216EEntryHead
{
	unsigned char m_data[8];
};

struct Rva0022216EEntry : public Rva0022216EEntryHead, public InGameNotificationType
{
};

struct InGameNotificationTypeStore
{
	unsigned char m_pad00[0x0C];
	InGameNotificationType m_defaultType;
	_STL::map<AsciiString, Rva0022216EEntry *> m_types;
};

struct AptScale
{
	float x;
	float y;
};

class AptPlayer
{
public:
	virtual void _slot0() = 0;
	virtual void _slot1() = 0;
	virtual void _slot2() = 0;
	virtual void _slot3() = 0;
	virtual void _slot4() = 0;
	virtual void _slot5() = 0;
	virtual void _slot6() = 0;
	virtual void _slot7() = 0;
	virtual void _slot8() = 0;
	virtual void _slot9() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual AptScale *v15() = 0;
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class AudioManager
{
public:
	virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
	virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9();
	virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
	virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24();
	virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29();
	virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34();
	virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44();
	virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49();
	virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53(); virtual void a54();
	virtual void a55(); virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59();
	virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63(); virtual void a64();
	virtual void a65(); virtual void a66(); virtual void a67(); virtual void a68(); virtual void a69();
	virtual void a70(); virtual void a71(); virtual void a72(); virtual void a73(); virtual void a74();
	virtual Rva002D9D7CRef a75(const AsciiString *name);
};
extern AudioManager *TheAudio;

class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, float size, bool bold);
};
extern FontLibrary *TheFontLibrary;

class GameTextInterface
{
public:
	virtual void _slot0(); virtual void _slot1(); virtual void _slot2(); virtual void _slot3();
	virtual void _slot4(); virtual void _slot5(); virtual void _slot6(); virtual void _slot7();
	virtual void _slot8(); virtual void _slot9(); virtual void _slot10(); virtual void _slot11();
	virtual void _slot12(); virtual void _slot13();
	virtual UnicodeString fetchName(const AsciiString *name, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

static __declspec(noinline) Rva002217EA rva00221920(const InGameNotificationType *type)
{
	Rva002217EA localNotif;
	if (!type->m_textKey.isEmpty()) {
		reinterpret_cast<Rva0040FB15WideStringCopyForward *>(&localNotif)->set(TheGameText->fetchName(&type->m_textKey, 0));
	}
	if (!type->m_audioKey.isEmpty()) {
		reinterpret_cast<Rva0040FB2E *>(&localNotif)->rva0040FB2E(TheAudio->a75(&type->m_audioKey));
	}
	if (!type->m_imageKey.isEmpty()) {
		localNotif.rva0010670B(TheMappedImageCollection->findImageByName(type->m_imageKey));
	}
	AptScale *scale = reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->v15();
	float scaleFactor;
	if (scale->y > scale->x)
		scaleFactor = scale->x;
	else
		scaleFactor = scale->y;
	GameFont *font = TheFontLibrary->getFont(&type->m_font.name, (float)type->m_font.size * scaleFactor, type->m_font.bold);
	reinterpret_cast<GameMessage *>(&localNotif)->friend_setList(reinterpret_cast<GameMessageList *>(font));
	reinterpret_cast<Gen_00489270 *>(&localNotif)->m(type->m_color);
	return localNotif;
}

Rva002217EA InGameNotificationType::rva00221ABB() const
{
	return rva00221920(this);
}

class Rva00575674
{
public:
	void rva00575674(void *p);
	InGameNotificationTypeStore *m_ptr;
};
extern Rva00575674 g_00DFE4C4;

void Rva002220DCInit();

Rva002217EA rva0022213F()
{
	if (!g_00DFE4C4.m_ptr)
		Rva002220DCInit();
	return rva00221920(&g_00DFE4C4.m_ptr->m_defaultType);
}

InGameNotificationType *FindInGameNotificationType(const AsciiString &name)
{
	if (!g_00DFE4C4.m_ptr)
		Rva002220DCInit();
	_STL::map<AsciiString, Rva0022216EEntry *>::iterator it = g_00DFE4C4.m_ptr->m_types.find(name);
	if (it != g_00DFE4C4.m_ptr->m_types.end()) {
		Rva0022216EEntry *entry = (*it).second;
		return entry;
	}
	return 0;
}

// Retail 0x002221A9 (78B): visit every type in the store's map, in key order,
// through the visitor's first virtual (handed the entry's
// InGameNotificationType base, NULL-preserving), stopping at the first false.
// Visitor and function names are address-derived. The base conversion goes
// through an inline returning it, which keeps retail's branchless neg/sbb/and
// NULL adjust (an in-place conversion branches); the end node is read once.
static inline InGameNotificationType *rva002221A9Type(Rva0022216EEntry *entry)
{
	return entry;
}

class InGameNotificationTypeVisitor
{
public:
	virtual bool visit(InGameNotificationType *type) = 0;
};

void forEachInGameNotificationType(InGameNotificationTypeVisitor &visitor)
{
	if (!g_00DFE4C4.m_ptr)
		Rva002220DCInit();
	_STL::map<AsciiString, Rva0022216EEntry *> &types = g_00DFE4C4.m_ptr->m_types;
	_STL::map<AsciiString, Rva0022216EEntry *>::iterator end = types.end();
	for (_STL::map<AsciiString, Rva0022216EEntry *>::iterator it = types.begin(); it != end; ++it) {
		if (!visitor.visit(rva002221A9Type((*it).second)))
			break;
	}
}
