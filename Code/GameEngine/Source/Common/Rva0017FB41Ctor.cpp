// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0Rva0017FB41_Prototype@@QAE@PBDHH@Z @ 0x0017FB41 (77 bytes). HTree
// prototype ctor, twin of the HAnim Rva0014CE67_Prototype ctor at 0x0014CE67
// (byte-identical except funcinfo and vtable): builds the GenBase009EB7D0
// base via its 0x0061ED40 row, stores vtable 0x00BD4F10, nulls the +0x14
// HTree link, constructs the +0x18 StringClass from (name, false) via the
// 0x000F0ED1 row, then stores the two int args at +0x1C/+0x20. Called from
// the HTree register helper at 0x0017FD2F.

class HTreeClass;

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

class Rva0017FB41_Prototype : public GenBase009EB7D0
{
public:
	Rva0017FB41_Prototype(const char *name, int arg1, int arg2);

	char m_pad04[0x10]; // +0x04..+0x13, untouched by this body
	HTreeClass *m_tree; // +0x14
	StringClass m_name; // +0x18
	int m_arg1C; // +0x1C
	int m_arg20; // +0x20
};

// ??0Rva0017FB41_Prototype@@QAE@PBDHH@Z
Rva0017FB41_Prototype::Rva0017FB41_Prototype(const char *name, int arg1, int arg2)
	: m_tree(0), m_name(name, false)
{
	m_arg1C = arg1;
	m_arg20 = arg2;
}
