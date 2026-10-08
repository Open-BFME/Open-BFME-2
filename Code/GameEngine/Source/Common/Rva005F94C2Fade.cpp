// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// 0x005F94C2 and 0x005F9567 are 165-byte standalone callbacks. Retail builds
// a temporary text pair from "FadeIn" / "FadeOut", appends "Page", materializes
// an AsciiString, fires the APT event, releases it, then stores state 2 / 4.
// The callback/class names remain address-derived; the target evidence proves
// the call sequence and field offsets, not the original class identity.
#include "ascii_string.h"

class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *text);
	const char *m_ptr;
	int m_len;
};

struct AsciiStringRefWithChar
{
	const AsciiString *m_string;
	char m_char;
};

struct AsciiStringCharPlusText : AsciiStringRefWithChar
{
	Rva000B3F84Pair m_right;
};

struct Rva005D2F96S16
{
	int m0, m1, m2, m3;
};

struct Rva005D2F96Base24
{
	int m0, m1, m2, m3, m4, m5;
};

struct Rva005D2F96S24 : Rva005D2F96Base24
{
};

Rva000B3F84Pair __cdecl Rva00108B93Make(const char *text);
AsciiStringCharPlusText __cdecl operator+(
	const AsciiStringRefWithChar &left, const char *right);
Rva005D2F96S24 __cdecl Rva005D2F96Build(
	const Rva005D2F96S16 &left, const char *right);
AsciiString __cdecl Rva002D56C3(const Rva005D2F96Base24 &node);
int __cdecl Rva0052519DFire(
	void *target, void *owner, const char *prefix, const char *event, int *result);
extern int g_00DFE4CC;

class Rva005F94C2
{
public:
	void rva005F94C2();
	void rva005F9567();

private:
	char m_pad00[8];
	void *m_owner;            // +0x08
	AsciiString m_prefix;     // +0x0C
	const char *m_eventText;  // +0x10
	int m_result;             // +0x14
	char m_pad18[0x10];
	int m_state;              // +0x28
};

void Rva005F94C2::rva005F94C2()
{
	Rva0052519DFire((void *)g_00DFE4CC, m_owner, m_prefix.str(),
		Rva002D56C3((Rva005D2F96Base24 &)Rva005D2F96Build(
			(const Rva005D2F96S16 &)operator+(
				(const AsciiStringRefWithChar &)Rva00108B93Make("FadeIn"),
				m_eventText),
			"Page")).str(), &m_result);
	m_state = 2;
}

void Rva005F94C2::rva005F9567()
{
	Rva0052519DFire((void *)g_00DFE4CC, m_owner, m_prefix.str(),
		Rva002D56C3((Rva005D2F96Base24 &)Rva005D2F96Build(
			(const Rva005D2F96S16 &)operator+(
				(const AsciiStringRefWithChar &)Rva00108B93Make("FadeOut"),
				m_eventText),
			"Page")).str(), &m_result);
	m_state = 4;
}
