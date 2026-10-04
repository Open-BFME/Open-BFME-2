// cl: /O1 /MD
// ??0Rva00605C91@@QAE@XZ, retail 0x00605C91 (22B).
// Unlock: ctor calls rowed ModuleData 0x006024FD then or handle -1 at +0x14
// then vtable 0x00C7AB28; unblocks 0x00605C58; callers 0x00605C5B;
// neighbours 0x00605C75 and 0x00605CA7; frameless __thiscall ret void.
class ModuleData
{
public:
	ModuleData();
	virtual ~ModuleData();
};

extern const void *const g_00C7AB28[];

class Rva00605C91 : public ModuleData
{
public:
	Rva00605C91();
private:
	char m_pad04[0x10];
	int m_handle;
};

Rva00605C91::Rva00605C91()
	: ModuleData()
{
	m_handle |= -1;
	*(const void * *)this = g_00C7AB28;
}
