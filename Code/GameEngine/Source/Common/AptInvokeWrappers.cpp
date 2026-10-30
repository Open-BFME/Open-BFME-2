// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// Typed Apt callback wrappers: convert the argument to an AsciiString with
// the rowed formatters (Rva0022288EGet for unsigned, Rva002228E8Get for float)
// and return the rowed Rva00222A8BTarget::invoke result for a one-argument
// call. They are template-style siblings over one shape; names are
// address-derived.
//
// ?Rva002162CFInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABI@Z @0x002162CF 99B  unsigned
// ?Rva0021642FInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABM@Z @0x0021642F 103B float
// and two siblings below (int; unsigned+two strings). The unsigned+int
// wrapper is owned by BannerUIUpdate.cpp, whose caller needs its body visible.
#include "ascii_string.h"

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

// StringBase<char>::str() (TheNullChr for an empty string) of a temporary.
static inline const char *Rva002162CFStr(const AsciiString &asciiString)
{
	return ((const StringBase<char> *)&asciiString)->str();
}

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

AsciiString __cdecl Rva0022288EGet(unsigned int value);
AsciiString __cdecl Rva002228E8Get(float value);

int __cdecl Rva002162CFInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &arg)
{
	return target->invoke(owner, name, 1, Rva002162CFStr(Rva0022288EGet(arg)), 0, 0, 0, 0);
}

int __cdecl Rva0021642FInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const float &arg)
{
	return target->invoke(owner, name, 1, Rva002162CFStr(Rva002228E8Get(arg)), 0, 0, 0, 0);
}

AsciiString __cdecl Rva00222834Get(int value);

// ?Rva00216496Invoke@@YAHPAVRva00222A8BTarget@@PAXPBDABIABVAsciiString@@4@Z @0x00216496 129B
// three arguments, an unsigned then two strings.
int __cdecl Rva00216496Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &a, const AsciiString &asciiString, const AsciiString &c)
{
	return target->invoke(owner, name, 3, Rva002162CFStr(Rva0022288EGet(a)), (void *)Rva002162CFStr(asciiString), (void *)Rva002162CFStr(c), 0, 0);
}

// ?Rva002D4531Invoke@@YAHPAVRva00222A8BTarget@@PAXPBDABH@Z @0x002D4531 99B
// one int argument through the rowed Rva00222834Get.
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &arg)
{
	return target->invoke(owner, name, 1, Rva002162CFStr(Rva00222834Get(arg)), 0, 0, 0, 0);
}

// ?rva00522A91@AptSkirmish@@QAEXXZ @0x00522A91 107B: close the profile popup.
// In state 2 (unless the flag at +0x6C2 is set) and in state 4 it sends
// CloseProfilePopup to the panel's Apt owner (+0x274). It then calls the
// state's follow-up, 0x00521B56 or 0x005229D3 (both pinned), with 0.
class AptSkirmish
{
public:
	void rva00522A91();
	void rva00521841();
	int rva00523178(int msg, unsigned int key, unsigned int state);
	// Follow-ups on the same panel, rowed in AptSkirmishCallbacks.cpp:
	// 0x00521770, 0x00521B56, 0x005229D3.
	void OnProfilePopupCancel(const char *unused);
	void OnAddProfileAccept(const char *unused);
	void OnChangeProfile(const char *unused);
private:
	char m_pad000[0x274];
	void *m_owner;				// +0x274
	char m_pad278[0x440];
	int m_state;				// +0x6B8
	char m_pad6BC[6];
	bool m_busy;				// +0x6C2
};

int AptSkirmish::rva00523178(int msg, unsigned int key, unsigned int state)
{
	if (msg != 0x15)
		return 0;
	switch ((unsigned char)key)
	{
	case 1:
		if (state & 1)
			rva00521841();
		break;
	case 0x1C:
		if (state & 2)
			rva00522A91();
		break;
	default:
		return 0;
	}
	return 1;
}

void AptSkirmish::rva00522A91()
{
	switch (m_state)
	{
	case 2:
		if (!m_busy)
		{
			((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_owner, "CloseProfilePopup", 0, 0, 0, 0, 0, 0);
			OnAddProfileAccept(0);
		}
		break;
	case 4:
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_owner, "CloseProfilePopup", 0, 0, 0, 0, 0, 0);
		OnChangeProfile(0);
		break;
	}
}

// ?rva00521841@AptSkirmish@@QAEXXZ @0x00521841 110B: the same panel's back
// action. States 2-4 close the profile popup and run 0x00521770 (pinned)
// with 0, and states 8-9 send CloseStats. Any other state tail-calls the
// rowed Rva00521643Enable.
void __cdecl Rva00521643Enable();

void AptSkirmish::rva00521841()
{
	switch (m_state)
	{
	case 2:
	case 3:
	case 4:
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_owner, "CloseProfilePopup", 0, 0, 0, 0, 0, 0);
		OnProfilePopupCancel(0);
		break;
	case 8:
	case 9:
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_owner, "CloseStats", 0, 0, 0, 0, 0, 0);
		break;
	default:
		Rva00521643Enable();
		break;
	}
}

static inline const char *Rva005252CDPass(const char *text)
{
	return text;
}

// ?Rva005252CDInvoke@@YAHPAVRva00222A8BTarget@@PAXPBD2ABHABQBD@Z @0x005252CD
// 107B: a two-argument call through the level-scoped rva00222B19 (level,
// prefix, name), an int via the rowed Rva00222834Get and a string held by
// reference.
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *target, void *level, const char *prefix, const char *name, const int &a, const char *const &text)
{
	return target->rva00222B19(level, prefix, name, 2, Rva002162CFStr(Rva00222834Get(a)), (void *)Rva005252CDPass(text), 0, 0, 0);
}

// ?Rva007410ECInvoke@@YAHPAVRva00222A8BTarget@@PAXPBD2ABI@Z @0x007410EC 102B:
// the level-scoped call with one unsigned argument.
int __cdecl Rva007410ECInvoke(Rva00222A8BTarget *target, void *level, const char *prefix, const char *name, const unsigned int &a)
{
	return target->rva00222B19(level, prefix, name, 1, Rva002162CFStr(Rva0022288EGet(a)), 0, 0, 0, 0);
}

// ?Rva002D3409Invoke@@YAHPAVRva00222A8BTarget@@PAXPBDABQBD@Z @0x002D3409 33B:
// the one-string member: the string held by reference passes straight through.
int __cdecl Rva002D3409Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const char *const &text)
{
	return target->invoke(owner, name, 1, Rva005252CDPass(text), 0, 0, 0, 0);
}
