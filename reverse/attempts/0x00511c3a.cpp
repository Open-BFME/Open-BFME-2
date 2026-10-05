// ?Rva00511C3AInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABHAB_N@Z
// partial score=0.97 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Typed Apt callback wrappers: convert the argument to an AsciiString with
// the rowed formatters (Rva0022288EGet for unsigned, Rva002228E8Get for float)
// and return the rowed Rva00222A8BTarget::invoke result for a one-argument
// call. They are template-style siblings over one shape; names are
// address-derived.
//
// ?Rva002162CFInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABI@Z @0x002162CF 99B  unsigned
// ?Rva0021642FInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABM@Z @0x0021642F 103B float
// and three siblings below (int; unsigned+int; unsigned+two strings).
#include "ascii_string.h"

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

// StringBase<char>::str() (TheNullChr for an empty string) of a temporary.
static inline const char *Rva002162CFStr(const AsciiString &s)
{
	return ((const StringBase<char> *)&s)->str();
}

extern Rva00222A8BTarget *TheRva00222A8BTarget;

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

// ?Rva0021639AInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABIABH@Z @0x0021639A 149B
// two arguments, unsigned then int.
int __cdecl Rva0021639AInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &a, const int &b)
{
	return target->invoke(owner, name, 2, Rva002162CFStr(Rva0022288EGet(a)), (void *)Rva002162CFStr(Rva00222834Get(b)), 0, 0, 0);
}

// ?Rva00216496Invoke@@YAHPAVRva00222A8BTarget@@PAXPBDABIABVAsciiString@@4@Z @0x00216496 129B
// three arguments, an unsigned then two strings.
int __cdecl Rva00216496Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &a, const AsciiString &b, const AsciiString &c)
{
	return target->invoke(owner, name, 3, Rva002162CFStr(Rva0022288EGet(a)), (void *)Rva002162CFStr(b), (void *)Rva002162CFStr(c), 0, 0);
}

// ?Rva002D4531Invoke@@YAHPAVRva00222A8BTarget@@PAXPBDABH@Z @0x002D4531 99B
// one int argument through the rowed Rva00222834Get.
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &arg)
{
	return target->invoke(owner, name, 1, Rva002162CFStr(Rva00222834Get(arg)), 0, 0, 0, 0);
}

// ?rva00522A91@Rva00522A91@@QAEXXZ @0x00522A91 107B: close the profile popup.
// In state 2 (unless the flag at +0x6C2 is set) and in state 4 it sends
// CloseProfilePopup to the panel's Apt owner (+0x274). It then calls the
// state's follow-up, 0x00521B56 or 0x005229D3 (both pinned), with 0.
class Rva00522A91
{
public:
	void rva00522A91();
	void rva00521841();
	void rva00521770(int arg);
	void rva00521B56(int arg);
	void rva005229D3(int arg);
private:
	char m_pad000[0x274];
	void *m_owner;				// +0x274
	char m_pad278[0x440];
	int m_state;				// +0x6B8
	char m_pad6BC[6];
	bool m_busy;				// +0x6C2
};

void Rva00522A91::rva00522A91()
{
	switch (m_state)
	{
	case 2:
		if (!m_busy)
		{
			TheRva00222A8BTarget->invoke(m_owner, "CloseProfilePopup", 0, 0, 0, 0, 0, 0);
			rva00521B56(0);
		}
		break;
	case 4:
		TheRva00222A8BTarget->invoke(m_owner, "CloseProfilePopup", 0, 0, 0, 0, 0, 0);
		rva005229D3(0);
		break;
	}
}

// ?rva00521841@Rva00522A91@@QAEXXZ @0x00521841 110B: the same panel's back
// action. States 2-4 close the profile popup and run 0x00521770 (pinned)
// with 0, and states 8-9 send CloseStats. Any other state tail-calls the
// rowed Rva00521643Enable.
void __cdecl Rva00521643Enable();

void Rva00522A91::rva00521841()
{
	switch (m_state)
	{
	case 2:
	case 3:
	case 4:
		TheRva00222A8BTarget->invoke(m_owner, "CloseProfilePopup", 0, 0, 0, 0, 0, 0);
		rva00521770(0);
		break;
	case 8:
	case 9:
		TheRva00222A8BTarget->invoke(m_owner, "CloseStats", 0, 0, 0, 0, 0, 0);
		break;
	default:
		Rva00521643Enable();
		break;
	}
}

static inline const char *Rva005252CDPass(const char *s)
{
	return s;
}

// ?Rva005252CDInvoke@@YAHPAVRva00222A8BTarget@@PAXPBD2ABHABQBD@Z @0x005252CD
// 107B: a two-argument call through the level-scoped rva00222B19 (level,
// prefix, name), an int via the rowed Rva00222834Get and a string held by
// reference.
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *target, void *level, const char *prefix, const char *name, const int &a, const char *const &b)
{
	return target->rva00222B19(level, prefix, name, 2, Rva002162CFStr(Rva00222834Get(a)), (void *)Rva005252CDPass(b), 0, 0, 0);
}

// ?Rva007410ECInvoke@@YAHPAVRva00222A8BTarget@@PAXPBD2ABI@Z @0x007410EC 102B:
// the level-scoped call with one unsigned argument.
int __cdecl Rva007410ECInvoke(Rva00222A8BTarget *target, void *level, const char *prefix, const char *name, const unsigned int &a)
{
	return target->rva00222B19(level, prefix, name, 1, Rva002162CFStr(Rva0022288EGet(a)), 0, 0, 0, 0);
}

char **__cdecl Rva004E678BGet(char **out, bool flag);

static inline const char *Rva00511C3AFlag(const bool &b)
{
	char *text;
	return *Rva004E678BGet(&text, b);
}

int __cdecl Rva00511C3AInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &a, const bool &b)
{
	return target->invoke(owner, name, 2, Rva002162CFStr(Rva00222834Get(a)), (void *)Rva00511C3AFlag(b), 0, 0, 0);
}
