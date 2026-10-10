// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Impl@BattlePromptDialog@StrategicInGameUI@@QAE@PAXPAVRva0057C394@@PAVLivingWorldBattle@@000@Z,
// retail 0x005E9E41..0x005E9EEC (171 bytes, EH, ret 0x18). The battle
// prompt dialog's implementation constructor (the Impl of the rowed
// OnClipLoaded 0x005E9D78 in StrategicInGameUIBattlePromptDialog.cpp): stores
// its owner, the movie provider, the battle and three inputs at +0..+0x14,
// clears the clip at +0x18 and a word at +0x1C, then asks the provider to
// load "StrategicBattlePrompt.swf" with OnClipLoaded as the loaded
// callback (a delegate reference released afterwards). The movie loading
// idiom follows Rva005F54DADtor.cpp.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *pointer;
};

class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);

struct DelegateDesc
{
	template <class T, class M> DelegateDesc(T *object, M method)
		: m_object(reinterpret_cast<AptDelegateTarget *>(object))
		, m_method(reinterpret_cast<AptDelegateMethod>(method))
	{
	}

	AptDelegateTarget *m_object;
	AptDelegateMethod m_method;
};

template <class T, class M> __forceinline DelegateDesc MakeDelegate(T *object, M method)
{
	DelegateDesc desc(object, method);
	return desc;
}

class Rva00579E47 : public TreeHintRef00217D4C
{
public:
	Rva00579E47(const DelegateDesc &desc);
	__forceinline ~Rva00579E47()
	{
		if (pointer) ReleaseTreeHintRef00217D4C(pointer);
	}
};

class Rva0057C2CC
{
public:
	void rva0057C2CC();
};

class Rva0057C394 : public Rva0057C2CC
{
public:
	void rva0057C394(const AsciiString &name, const TreeHintRef00217D4C &callback);
};

class LivingWorldBattle;
class Rva005E9625;

// The owned clip holder at +0x18 (rowed clear 0x005E9E27).
class Rva005E9E27
{
public:
	__forceinline Rva005E9E27() : m_ptr(0) {}
	~Rva005E9E27() { clear(); }
	void clear();
private:
	Rva005E9625 *m_ptr;
};

namespace StrategicInGameUI { class BattlePromptDialog { public: class Impl; }; }
class StrategicInGameUI::BattlePromptDialog::Impl
{
public:
	Impl(void *owner, Rva0057C394 *frame, LivingWorldBattle *battle, void *first, void *second, void *third);
	void OnClipLoaded(int, const AsciiString &);
private:
	void *m_owner;
	Rva0057C394 *m_frame;
	LivingWorldBattle *m_battle;
	void *m_first;
	void *m_second;
	void *m_third;
	Rva005E9E27 m_clip;
	int m_1c;
};

StrategicInGameUI::BattlePromptDialog::Impl::Impl(void *owner, Rva0057C394 *frame, LivingWorldBattle *battle, void *first, void *second, void *third)
	: m_owner(owner), m_frame(frame), m_battle(battle), m_first(first), m_second(second), m_third(third), m_1c(0)
{
	Rva00579E47 delegate(MakeDelegate(this, &Impl::OnClipLoaded));
	m_frame->rva0057C394(AsciiString("StrategicBattlePrompt.swf"), delegate);
}
