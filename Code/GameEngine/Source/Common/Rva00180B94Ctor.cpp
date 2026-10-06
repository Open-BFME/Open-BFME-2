// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva00180B94_Prototype@@QAE@PBDPAX@Z, retail 0x00180B94, 76 bytes.
// Unlock: missing callee of 0x00180CCB. Twin of HTree Rva0017FB41 (77B) and
// HAnim Rva0014CE67 (75B): GenBase009EB7D0 base via 0x0061ED40 row, vtable
// 0x007D5050, +0x14 tree link from second arg, +0x18 StringClass from
// (name false) via 0x000F0ED1 row, +0x1C/+0x20 zeroed. Called from 0x00180CCB
// which news 0x24 and passes (name esi). Evidence: unlock lane, caller pushes,
// 0x24 new size matches base 0x14 plus 0x10 members.

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

class Rva00180B94_Prototype : public GenBase009EB7D0
{
public:
	Rva00180B94_Prototype(const char *name, void *tree);
	Rva00180B94_Prototype(const char *name, int arg1, int arg2);

	char m_pad04[0x10];
	void *m_tree;
	StringClass m_name;
	int m_arg1C;
	int m_arg20;
};

Rva00180B94_Prototype::Rva00180B94_Prototype(const char *name, void *tree)
	: m_tree(tree), m_name(name, false)
{
	m_arg1C = 0;
	m_arg20 = 0;
}

Rva00180B94_Prototype::Rva00180B94_Prototype(const char *name, int arg1, int arg2)
	: m_tree(0), m_name(name, false)
{
	m_arg1C = arg1;
	m_arg20 = arg2;
}
