// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0059B4FF@Rva0059B4FF@@QAE?AV?$StringBase@D@@XZ @0x0059B4FF 164B.
// Debug label "<name> (Lvl:<level>)" from the AI\TeamBuilder.cpp block
// (assert path at 0x00C70E3C; the " (Lvl:" literal sits right after the
// unit's vtable at 0x00C70E60). Builds name + " (Lvl:" + _itoa(level) + ")"
// through the narrow concat chain: rowed operator+ 0x000B49C5 then rowed
// 0x0059AFC2 and 0x0059AFFB then the rowed materializer 0x0059B355 then the
// StringBase copy 0x000365F0 and release 0x00036410. The name is the
// AsciiString at +0x64 of the object at +0x2C and the level is the int at
// +0x0C of the object at +0x08 (same reads as the sibling 0x0059B5A3).
// No direct caller or vtable reference in retail; the class name is
// address-derived.

extern "C" __declspec(dllimport) char *__cdecl _itoa(int value, char *buffer, int radix);

template <class T> class StringBase;
template <> class StringBase<char>
{
public:
	StringBase(const StringBase<char> &other);
	~StringBase();
private:
	void *m_data;
};

class AsciiString;

struct Rva0059AFC2In
{
	int m_a;
	int m_b;
	int m_c;
};
struct AsciiStringPlusText : Rva0059AFC2In
{
};
struct Rva0059AFFBIn
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
};
struct Rva0059AFC2Out : Rva0059AFFBIn
{
};
struct Rva0059AFFBOut
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;
	int m_g;
};

AsciiStringPlusText __cdecl operator+(const AsciiString &left, const char *right);
Rva0059AFC2Out *__cdecl Rva0059AFC2Copy(Rva0059AFC2Out *dst, Rva0059AFC2In *src, const char *name);
Rva0059AFFBOut *__cdecl Rva0059AFFBCopy(Rva0059AFFBOut *dst, Rva0059AFFBIn *src, const char *name);

class Rva0059B355
{
public:
	StringBase<char> rva0059B355();
};

struct Rva0059B4FFLevel
{
	char m_pad[0x0C];
	int m_level;
};

struct Rva0059B4FFNamed
{
	char m_pad[0x64];
	const AsciiString &name() const { return *(const AsciiString *)(m_pad + 0x64); }
};

class Rva0059B4FF
{
public:
	StringBase<char> rva0059B4FF();
private:
	char m_pad00[0x08];
	Rva0059B4FFLevel *m_level;
	char m_pad0C[0x2C - 0x0C];
	Rva0059B4FFNamed *m_named;
};

StringBase<char> Rva0059B4FF::rva0059B4FF()
{
	char buffer[128];
	int level = m_level->m_level;
	const AsciiString &name = m_named->name();
	Rva0059AFFBOut whole;
	Rva0059AFC2Out part;
	StringBase<char> result = ((Rva0059B355 *)Rva0059AFFBCopy(&whole,
		Rva0059AFC2Copy(&part, &operator+(name, " (Lvl:"), _itoa(level, buffer, 10)),
		")"))->rva0059B355();
	return result;
}
