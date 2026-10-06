// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0Rva0014CE67_Prototype@@QAE@PBDHH@Z @ 0x0014CE67 (75 bytes). Prototype
// ctor for the vtable at 0x00BD37EC: builds the GenBase009EB7D0 base via
// its 0x0061ED40 row, stores the vtable, nulls the +0x14 tree link,
// constructs the +0x18 StringClass from (name, false) via the 0x000F0ED1
// pin, then stores the two int args at +0x1C/+0x20. The tree link and the
// name ride the init list in declaration order (matching retail's
// vptr/null/call sequence); the args are body stores. Called from Create
// at 0x0014D058; the arg types are ints per the pin until proven otherwise.

class PrototypeTreeRef
{
public:
	virtual void DeleteThis(); // slot 0, destroys on final release
	int m_refCount; // +0x04
};

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

class Rva0014CE67_Prototype : public GenBase009EB7D0
{
public:
	Rva0014CE67_Prototype(const char *name, int arg1, int arg2);

	char m_pad04[0x10]; // +0x04..+0x13, untouched by this body
	PrototypeTreeRef *m_tree; // +0x14
	StringClass m_name; // +0x18
	int m_arg1C; // +0x1C
	int m_arg20; // +0x20
};

// ??0Rva0014CE67_Prototype@@QAE@PBDHH@Z
Rva0014CE67_Prototype::Rva0014CE67_Prototype(const char *name, int arg1, int arg2)
	: m_tree(0), m_name(name, false)
{
	m_arg1C = arg1;
	m_arg20 = arg2;
}
