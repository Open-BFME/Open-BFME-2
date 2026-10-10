// ??0Rva00527378Payload@@QAE@PAXHABVAsciiString@@00@Z
// partial score=0.9885202318 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva00527378Payload@@QAE@PAXHABVAsciiString@@00@Z @0x00527378 1007B:
// BFME2's hero select panel (InGameHeroSelectInterface::Impl) constructor,
// 0x1E0 bytes, run by 0x00527767 with the owner then the level and name and
// the owner's +0xC0/+0xF8 members. Target evidence: vptr 0x00C67F0C (the
// rowed ~Rva0052634F at 0x0052634F walks the same members); unwind state 0
// runs the base dtor 0x00524F5A (pinned ??1Gen_uwm_00524f5a); the name copy
// at +0x0C; the hero data pointer at +0x10 registers this panel (rowed
// append 0x005A0B4C); the command map list at +0x14 (fold ctor 0x001F81BF
// and dtor 0x0052413E); the over-button handler lists at +0x20 (rowed ctor
// 0x00524415 and dtor 0x00524436); the +0x38 list (fold ctor 0x001F81BF and
// dtor 0x005242D7); sixteen 0x18-byte hero slots at +0x48 (empty ctor
// 0x0047A6A9 through the vector constructor iterator) then each reset to
// the end of the hero button list (rowed slot init 0x00524F35 and rowed
// fill 0x0052506F); the two hot-key records at +0x1C8/+0x1D0. It binds
// "_level%d." plus the name plus "_OnBttnHeroSelect" (WorldBuilder's
// Impl::OnButtonPressed 0x00527122) and "_OnBttnSelectAllHeroes"
// (0x0052633A) as commands; each "%s/Hero%d/" path below the name's slash
// path (rowed AptUtils::DotPath2SlashPath 0x00412E76) as an over-button
// handler with its slot index (rowed binder 0x00525916); and the
// "/SelectAllHeroesBttn/" path with the rowed 0x005257F6. It then applies
// the faction (rowed 0x005255E2) and registers the
// NonCommand_SelectNearestBuilder hot key (rowed findCommandButton
// 0x0031BE3C and its hot key string 0x0035B1E9; pinned HotKeyManager
// 0x00358CCD and addHotKey 0x00359302) with a new action (vtable
// 0x00C67E70) holding this panel; the handle goes to +0x1D0 and the flag at
// +0x1D9 is set. WorldBuilder's twin 0x013BE190 is unnamed; the row keeps
// the pinned address name.

#include "ascii_string.h"

// Narrow concat nodes (RegistryAsciiPath.cpp).
class Rva000B3F84Pair
{
public:
 Rva000B3F84Pair() {} Rva000B3F84Pair *init(const char*);
	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString();

	Rva000B3F84Pair m_text;
};

struct AsciiStringPlusText : AsciiStringRef
{
	operator AsciiString();

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right){Rva000B3F84Pair text;text.init(right);AsciiStringPlusStringText result;static_cast<AsciiStringPlusString&>(result)=left;result.m_text=text;return result;}
AsciiStringPlusText operator+(const AsciiString &left, const char *right);

namespace AptUtils
{
	AsciiString DotPath2SlashPath(const char *path);
}

// The Apt delegates: an (object, method) pair, or (object, slot index) for
// the hero button handlers.
class __single_inheritance DelegateTarget;
typedef void (DelegateTarget::*DelegateMethod)(const char *);

struct DelegateDesc
{
	DelegateDesc(void *object, DelegateMethod method) : m_object(object), m_method(method) {}
	DelegateDesc(void *object, void(__stdcall *function)(int)) : m_object(object), m_function(function) {}
	DelegateDesc(void *object, int index) : m_object(object), m_index(index) {}

	void *m_object;
	union
	{
		DelegateMethod m_method;
		void(__stdcall *m_function)(int);
		int m_index;
	};
};

// The hero button handlers bind their slot index through 0x00525916.
struct HeroIndexDesc : DelegateDesc
{
	HeroIndexDesc(void *object, int index) : DelegateDesc(object, index) {}
};

class Rva00525916
{
public:
	Rva00525916 &rva00525916(const DelegateDesc *desc);
};

class Rva00579E47
{
public:
	Rva00579E47() {}
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);

private:
	void *m_ptr;
};

template <class T> class AptRef : public Rva00579E47
{
public:
	__forceinline AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}
	AptRef(DelegateDesc desc) : Rva00579E47(desc) {}
	__forceinline AptRef(const HeroIndexDesc *desc) { ((Rva00525916 *)this)->rva00525916(desc); }
};

class AptCommandMap;
class AptOverButtonHandler;

class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, &desc);
	}

private:
	unsigned char m_names[0xC];
};

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(int level, const AsciiString &name, AptRef<AptOverButtonHandler> handler);

	__forceinline void AddOverButtonHandlerDelegate(const int &level, const AsciiString &name, DelegateDesc desc)
	{
		AddOverButtonHandler(level, name, &desc);
	}
};

class Rva00524415
{
public:
	Rva00524415();

private:
	unsigned char m_lists[0x18];
};

class Rva00524436 : public Rva00524415
{
public:
	~Rva00524436();
};

class Rva005242D7
{
public:
	Rva005242D7();
	~Rva005242D7();

private:
	unsigned char m_names[0xC];
};

// STLport list<HeroButtonInfo> view (InGameHeroSelectInterface.cpp).
struct HeroButtonNode;

struct HeroButtonIterator
{
	HeroButtonIterator(HeroButtonNode *node) : m_node(node) {}
	HeroButtonIterator(const HeroButtonIterator &other) : m_node(other.m_node) {}

	HeroButtonNode *m_node;
};

struct HeroButtonList
{
	HeroButtonIterator end() const { return m_header; }

	HeroButtonNode *m_header;
};

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

struct HeroSelectData
{
	unsigned char m_pad00[0x10];
	HeroButtonList m_heroButtons; // +0x10
};

// One hero button slot (0x18 bytes).
class Rva00524F35
{
public:
	Rva00524F35() {}
	Rva00524F35 &rva00524F35(int node);

private:
	int m_node;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_14;
	unsigned char m_15;
	unsigned char m_16;
};

typedef Rva00524F35 &(Rva00524F35::*SlotInit)(HeroButtonIterator);

struct BfmeStringRecord000B9534;

namespace _STL
{
	template <class _ForwardIter, class _Tp> void fill(_ForwardIter first, _ForwardIter last, const _Tp &value);
}

// A hot-key registration handle.
struct Rva00359302Result
{
	Rva00359302Result() : m_node(0) {}
	Rva00359302Result(void *node, bool alternate) : m_node(node), m_alt(alternate) {}

	void *m_node;
	bool m_alt;
};

struct TargetRef00217D4C;
struct TreeHintRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct HotKeyActionBase
{
	HotKeyActionBase() : m_refCount(0) {}
	virtual ~HotKeyActionBase();

	int m_refCount; // +0x04
};

// The select-nearest-builder hot key action (vtable 0x00C67E70).
struct SelectNearestBuilderAction : HotKeyActionBase
{
	SelectNearestBuilderAction(void *panel) : m_panel(panel) {}
	virtual ~SelectNearestBuilderAction();

	void *m_panel; // +0x08
};

class Rva005F8F96
{
public:
	Rva005F8F96(HotKeyActionBase *action) : m_ptr(action)
	{
		if (action)
			++action->m_refCount;
	}
	~Rva005F8F96()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

	HotKeyActionBase *m_ptr;
};

class HotKeyManager
{
public:
	AsciiString rva00358CCD(const AsciiString &name);
	Rva00359302Result addHotKey(const TreeHintRef00217D4C &action, const AsciiString &key, bool flag);
};

class Rva00E01E28Owner;
extern HotKeyManager *TheHotKeyManager;

class CommandButton
{
public:
	const AsciiString &rva0035B1E9() const;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

extern ControlBar *TheControlBar;

void __stdcall rva005257F6(int unused);

class InGameHeroSelectInterface
{
public:
	class Impl
	{
	public:
		void OnButtonPressed(const char *params); // "_OnBttnHeroSelect"
		void rva0052633A(const char *params); // "_OnBttnSelectAllHeroes"
		void rva005255E2(const AsciiString *faction);
	};
};

class Gen_uwm_00524f5a
{
public:
	virtual void v00();
	~Gen_uwm_00524f5a();
};

class Rva00527378Payload : public Gen_uwm_00524f5a
{
public:
	Rva00527378Payload(void *owner, int level, const AsciiString &name, void *data, void *faction);
	virtual void v00();

private:
	void *m_owner; // +0x04
	int m_level; // +0x08
	AsciiString m_name; // +0x0C
	HeroSelectData *m_data; // +0x10
	AptCommandMapAdder m_commandMaps; // +0x14
	Rva00524436 m_overButtonHandlers; // +0x20
	Rva005242D7 m_list38; // +0x38
	bool m_44;
	bool m_45;
	Rva00524F35 m_slots[16]; // +0x48
	Rva00359302Result m_hotKey1C8; // +0x1C8
	Rva00359302Result m_hotKey1D0; // +0x1D0
	bool m_hasHotKey1C8; // +0x1D8
	bool m_hasHotKey1D0; // +0x1D9
	bool m_1DA;
	int m_1DC;
};

Rva00527378Payload::Rva00527378Payload(void *owner, int level, const AsciiString &name, void *data, void *faction)
	: m_owner(owner), m_level(level), m_name(name), m_data(*(HeroSelectData **)data),
	  m_44(false), m_45(false), m_hasHotKey1C8(false), m_hasHotKey1D0(false), m_1DA(false), m_1DC(0)
{
	((Rva005A0B4CList *)m_data)->append((Rva002BA8F1Listener *)this);
	AsciiString prefix;
	prefix.format("_level%d.", m_level);
	m_commandMaps.AddCommandMap(prefix + m_name + "_OnBttnHeroSelect", AptRef<AptCommandMap>(DelegateDesc(this, reinterpret_cast<DelegateMethod>(&InGameHeroSelectInterface::Impl::OnButtonPressed))));
	m_commandMaps.AddCommandMap(prefix + m_name + "_OnBttnSelectAllHeroes", AptRef<AptCommandMap>(DelegateDesc(this, reinterpret_cast<DelegateMethod>(&InGameHeroSelectInterface::Impl::rva0052633A))));
	{Rva00524F35 slot;
	SlotInit init = reinterpret_cast<SlotInit>(&Rva00524F35::rva00524F35);
	_STL::fill<BfmeStringRecord000B9534 *, BfmeStringRecord000B9534>((BfmeStringRecord000B9534 *)m_slots,
		(BfmeStringRecord000B9534 *)(m_slots + 16),
		(const BfmeStringRecord000B9534 &)(slot.*init)(m_data->m_heroButtons.end()));
	}
	for (int i = 0; i < 16; ++i)
	{
		AsciiString path;
		path.format("%s/Hero%d/", AptUtils::DotPath2SlashPath(m_name.str()).str(), i + 1);
		HeroIndexDesc desc(this, i);
		((AptOverButtonHandlerAdder *)&m_overButtonHandlers)->AddOverButtonHandler(m_level, path, &desc);
	}
	((AptOverButtonHandlerAdder *)&m_overButtonHandlers)->AddOverButtonHandler(m_level,
		AptUtils::DotPath2SlashPath(m_name.str()) + "/SelectAllHeroesBttn/",
		AptRef<AptOverButtonHandler>(DelegateDesc(this, rva005257F6)));
	((InGameHeroSelectInterface::Impl *)this)->rva005255E2((const AsciiString *)faction);
	if (TheHotKeyManager)
	{
		static const AsciiString s_selectNearestBuilder("NonCommand_SelectNearestBuilder");
		const CommandButton *button = TheControlBar->findCommandButton(s_selectNearestBuilder);
		if (button)
		{
			AsciiString hotKey = ((HotKeyManager *)TheHotKeyManager)->rva00358CCD(button->rva0035B1E9());
			if (!hotKey.isEmpty())
			{
				Rva005F8F96 action(new SelectNearestBuilderAction(this));
				m_hotKey1D0 = ((HotKeyManager *)TheHotKeyManager)->addHotKey(*(const TreeHintRef00217D4C *)&action, hotKey, true);
				m_hasHotKey1D0 = true;
			}
		}
	}
}
