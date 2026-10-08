// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
//
// StrategicHUD::DynamicAutoResolveMovieClip::Impl (WorldBuilder
// StrategicHUDDynamicAutoResolveMovieClip.cpp names Impl::Impl). Target
// facts: the ctor at 0x005FC20E (ret 0x18) stores owner, level and copies of
// the name and the region name; sets "APT:<_level%u.><name>_RegionName" from
// the region name; binds seven "<_level%u.><name>_On..." command maps (retail
// strings) with the machinery of the HUD::Impl ctor
// (Common/Rva0042DB21Method.cpp); then tells the clip SetNumAllies /
// SetNumEnemies. The callbacks forward to the owner, whose vtable 0x0087A064
// holds a dtor and seven pure slots: slot 1 on open, 2 when closed (state 2
// -> 3), 3 on the skip button (state 1), 4/6 when an ally/enemy panel loads
// (its "index" 0..4, level and leaf "name" read from the Apt path through
// the rowed 0x004128F0 / 0x004128BB / 0x00412845), 5/7 when one unloads
// (the leading digit of the path). The panel handlers take the owner slot as
// a member pointer (the folded vcall thunks 0x005CB26A..0x005CB279). Owner
// slot names follow the bound callbacks (inference).
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <class T> class AptRef
{
public:
	AptRef(const DelegateDesc *desc) { rva00579E47(desc); }
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
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
	char m_pad[0xC];
};

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src); // 0x000B3F84

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
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}


// "APT:" + prefix + name + text: the text-plus-string node is the rowed
// 0x002226E5 (System/RegistryAsciiPath.cpp); the two widening concats are
// emitted out of line here and ICF-folded at 0x005F17C6 and 0x005D2F96
// (pinned, these definitions are the fold proofs); the materializer is the
// pinned 0x005F1D47 (WorldBuilder StringCompose::Concat<...>, three levels).
struct Rva002226E5TextPlusString
{
	Rva002226E5TextPlusString() {}

	Rva000B3F84Pair m_left;
	AsciiStringRef m_right;
};
Rva002226E5TextPlusString __cdecl operator+(const char *left, const AsciiString &right); // 0x002226E5

struct AptTextPlusStringPlusString : Rva002226E5TextPlusString
{
	AsciiStringRef m_third;
};

struct AptTextPlusStringPlusStringText : AptTextPlusStringPlusString
{
	operator AsciiString(); // 0x005F1D47

	Rva000B3F84Pair m_text;
};

// ?operator+(Rva002226E5TextPlusString, AsciiString) present-unmatched (inline, emitted out of line; ICF-folded at 0x005F17C6; pinned)
inline AptTextPlusStringPlusString operator+(const Rva002226E5TextPlusString &left, const AsciiString &right)
{
	AptTextPlusStringPlusString r;
	static_cast<Rva002226E5TextPlusString &>(r) = left;
	r.m_third.m_string = &right;
	return r;
}

// ?operator+(AptTextPlusStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x005D2F96; pinned)
inline AptTextPlusStringPlusStringText operator+(const AptTextPlusStringPlusString &left, const char *right)
{
	Rva000B3F84Pair p;
	p.init(right);
	AptTextPlusStringPlusStringText r;
	static_cast<AptTextPlusStringPlusString &>(r) = left;
	r.m_text = p;
	return r;
}

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool flag); // 0x00225301
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void *target, void *level, const char *prefix, const char *function, int *value);

// BfmePathLeafAfterMarker.cpp's path helpers and the pinned Apt parameter
// reader 0x004128F0.
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);
bool __cdecl Rva004128F0GetParam(const char *path, const char *key, AsciiString &value);

// TheAudio (0x009FE6E8) viewed by slot: addAudioEvent +0x64.
class Rva005FBED8AudioView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
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
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
};
class AudioManager;
extern AudioManager *TheAudio;

// TheLivingWorldLogic (0x009FEF10): the auto-resolve sound source at +0x98,
// whose +0x40 block holds the event reference at +0x3C and whose +0x14 is
// copied into the event's +0x70.
struct Rva005FBED8SoundBlock
{
	char m_pad[0x3C];
	OpaqueRefElement4 m_ref; // +0x3C
};

struct Rva005FBED8Sound
{
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x40 - 0x18];
	Rva005FBED8SoundBlock *m_40;
};

struct Rva005FBED8LivingWorld
{
	char m_pad[0x98];
	Rva005FBED8Sound *m_sound; // +0x98
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

namespace StrategicHUD {
class DynamicAutoResolveMovieClip
{
public:
	class Impl;

	DynamicAutoResolveMovieClip(int level, const AsciiString &name, const UnicodeString &regionName, int numAllies, int numEnemies);
	virtual ~DynamicAutoResolveMovieClip();
	virtual void notifyOpen() = 0;
	virtual void notifyClosed() = 0;
	virtual void notifySkipButtonClicked() = 0;
	virtual void notifyAllyPanelLoaded(int index, int level, const AsciiString &name) = 0;
	virtual void notifyAllyPanelUnloaded(int index) = 0;
	virtual void notifyEnemyPanelLoaded(int index, int level, const AsciiString &name) = 0;
	virtual void notifyEnemyPanelUnloaded(int index) = 0;

private:
	Impl *m_impl; // +0x04 (owning; released by the rowed 0x005FC1CA)
};
}

class StrategicHUD::DynamicAutoResolveMovieClip::Impl
{
public:
	typedef void (DynamicAutoResolveMovieClip::*PanelLoaded)(int index, int level, const AsciiString &name);
	typedef void (DynamicAutoResolveMovieClip::*PanelUnloaded)(int index);

	Impl(DynamicAutoResolveMovieClip *owner, int level, const AsciiString &name, const UnicodeString &regionName, int numAllies, int numEnemies);
	void OnOpen(const char *path);
	void StopAudio(); // 0x005FBEBA (pinned)
	void OnClosed(const char *path);
	void OnSkipButtonClicked(const char *path);
	void OnAllyPanelLoaded(const char *path);
	void OnAllyPanelUnloaded(const char *path);
	void OnEnemyPanelLoaded(const char *path);
	void OnEnemyPanelUnloaded(const char *path);
	void OnPanelLoaded(const char *path, PanelLoaded notify);
	void OnPanelUnloaded(const char *path, PanelUnloaded notify);

private:
	DynamicAutoResolveMovieClip *m_owner; // +0x00
	int m_level; // +0x04
	AsciiString m_name; // +0x08
	UnicodeString m_regionName; // +0x0C
	AptCommandMapAdder m_commandMaps; // +0x10
	int m_state; // +0x1C (0 closed, 1 open, 2 closing, 3 closed again)
	int m_resultState; // +0x20
	int m_audioHandle; // +0x24
};

StrategicHUD::DynamicAutoResolveMovieClip::Impl::Impl(DynamicAutoResolveMovieClip *owner, int level, const AsciiString &name, const UnicodeString &regionName, int numAllies, int numEnemies)
	: m_owner(owner), m_level(level), m_name(name), m_regionName(regionName), m_state(0), m_resultState(0), m_audioHandle(1)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	g_bfmeAptWindowManager->bfmeSetText("APT:" + prefix + m_name + "_RegionName", m_regionName, false);
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnOpen", DelegateDesc(this, &Impl::OnOpen));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnClosed", DelegateDesc(this, &Impl::OnClosed));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnSkipButtonClicked", DelegateDesc(this, &Impl::OnSkipButtonClicked));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnAllyPanelLoaded", DelegateDesc(this, &Impl::OnAllyPanelLoaded));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnAllyPanelUnloaded", DelegateDesc(this, &Impl::OnAllyPanelUnloaded));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnEnemyPanelLoaded", DelegateDesc(this, &Impl::OnEnemyPanelLoaded));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnEnemyPanelUnloaded", DelegateDesc(this, &Impl::OnEnemyPanelUnloaded));
	Rva0052519DFire(g_bfmeAptWindowManager, (void *)m_level, m_name.str(), "SetNumAllies", &numAllies);
	Rva0052519DFire(g_bfmeAptWindowManager, (void *)m_level, m_name.str(), "SetNumEnemies", &numEnemies);
}

void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnClosed(const char *path)
{
	if (m_state == 2)
	{
		m_state = 3;
		m_owner->notifyClosed();
	}
}

void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnSkipButtonClicked(const char *path)
{
	if (m_state == 1)
		m_owner->notifySkipButtonClicked();
}

void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnAllyPanelLoaded(const char *path)
{
	OnPanelLoaded(path, &DynamicAutoResolveMovieClip::notifyAllyPanelLoaded);
}

void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnEnemyPanelLoaded(const char *path)
{
	OnPanelLoaded(path, &DynamicAutoResolveMovieClip::notifyEnemyPanelLoaded);
}

void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnAllyPanelUnloaded(const char *path)
{
	OnPanelUnloaded(path, &DynamicAutoResolveMovieClip::notifyAllyPanelUnloaded);
}

void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnEnemyPanelUnloaded(const char *path)
{
	OnPanelUnloaded(path, &DynamicAutoResolveMovieClip::notifyEnemyPanelUnloaded);
}

void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnPanelUnloaded(const char *path, PanelUnloaded notify)
{
	if (!path)
		return;
	if (!isdigit(*path))
		return;
	int index = atoi(path);
	if (index < 0 || index >= 5)
		return;
	(m_owner->*notify)(index);
}

// 0x005FC064: the "index" (0..4) and "name" parameters of the loaded panel's
// Apt path go to the owner slot with the name's level and leaf.
void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnPanelLoaded(const char *path, PanelLoaded notify)
{
	if (path == 0 || *path == 0)
		return;
	AsciiString indexText;
	if (!Rva004128F0GetParam(path, "index", indexText))
		return;
	int index = atoi(indexText.str());
	if (index < 0 || index >= 5)
		return;
	AsciiString panelPath;
	if (!Rva004128F0GetParam(path, "name", panelPath))
		return;
	AsciiString leaf(Rva00412845AfterLevel(panelPath.str()));
	(m_owner->*notify)(index, Rva004128BBGetLevel(panelPath.str()), leaf);
}

void StrategicHUD::DynamicAutoResolveMovieClip::Impl::OnOpen(const char *path)
{
	if (m_state == 0)
	{
		m_state = 1;
		m_owner->notifyOpen();
		StopAudio();
		if (TheAudio != 0 && TheLivingWorldLogic != 0)
		{
			Rva005FBED8Sound *sound = reinterpret_cast<Rva005FBED8LivingWorld *>(TheLivingWorldLogic)->m_sound;
			if (sound != 0)
			{
				BfmeAudioEventPrefix136 event(sound->m_40->m_ref, 1);
				event.m_int70 = sound->m_14;
				m_audioHandle = reinterpret_cast<Rva005FBED8AudioView *>(TheAudio)->addAudioEvent(&event);
			}
		}
	}
}

StrategicHUD::DynamicAutoResolveMovieClip::DynamicAutoResolveMovieClip(int level, const AsciiString &name, const UnicodeString &regionName, int numAllies, int numEnemies)
	: m_impl(new Impl(this, level, name, regionName, numAllies, numEnemies))
{
}
