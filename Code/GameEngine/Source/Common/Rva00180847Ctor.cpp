// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva00180847@@QAE@PBDHH@Z @0x00180847 77B
// Twin of Rva001805E0 ctor (77B): GenBase009EB7D0 base via rowed
// 0x0061ED40, vtable 0x007D5010, +0x14 zeroed (no tree arg), +0x18
// StringClass from (name false) via rowed 0x000F0ED1, +0x1C/+0x20 from
// second/third args. Unlocks 0x001809EA. Flags and base from donor
// Rva001805E0Ctor.cpp.
class StringClass
{
public:
	StringClass(const char *name, bool flag);
	~StringClass();
};

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
};

class Rva00180847 : public GenBase009EB7D0
{
public:
	Rva00180847(const char *name, int a, int b);

	char m_pad04[0x10];
	void *m_14;
	StringClass m_name;
	int m_1C;
	int m_20;
};

Rva00180847::Rva00180847(const char *name, int a, int b)
	: m_14(0), m_name(name, false)
{
	m_1C = a;
	m_20 = b;
}
