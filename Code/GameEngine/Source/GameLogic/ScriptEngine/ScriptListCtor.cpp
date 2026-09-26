// cl: /O1 /MD /GX-
//
// ScriptList constructor at 0x003B7720 (37B) plus clear at 0x003B7812
// (36B, banked near-miss only -- see below).
//
// Layout (0x4C bytes, BFME1 ScriptList-shaped): a vtable word at +0x00
// (0x00C1FAAC, the same vtable the rowed ??1ScriptList restores), the
// two list head pointers at +0x04/+0x08 zeroed here (they alias the
// Gen_00350E60 record the swap TU swaps through 0x003B33FA), and two
// 0x20-byte subrecords at +0x0C/+0x2C built through the rowed subrecord
// constructor at 0x003B761E. The zeroes and the vtable store live in an
// inline base constructor so they precede the member calls; the derived
// class carries no new logic. No EH state anywhere, hence /GX- (the
// destructor with its EH frame lives in its own unit).
//
// Identity: installs vtable 0xC1FAAC; called from the SidesInfo
// construction neighborhood (0x32C68D/0x32FC9D/0x32FE46), the
// ScriptEngine body 0x209D9C, and ScriptList::clear's temp; clear is
// called from rowed SidesInfo::init (site 0x32CDD5).
//
// Clear wall (banked 0.97): every natural spelling (named temp, temp,
// reference, qualified call, pointer alias, placement new, explicit ctor
// call; /O1 /Os /O2) computes the swap target with lea [ebp-0x4C] while
// retail reuses the constructor return (mov ecx,eax) -- but keeps this
// in esi, which only named-temp spellings do. The two halves have never
// been observed together.

class Rva003B761E
{
public:
	Rva003B761E();

private:
	char m_data[0x20];
};

class ScriptListBase
{
public:
	ScriptListBase()
	{
		m_firstGroup = 0;
		m_firstScript = 0;
		m_vtable = (void *)0x00C1FAAC;
	}

private:
	void *m_vtable;					// +0x00
	void *m_firstGroup;				// +0x04
	void *m_firstScript;			// +0x08
};

class ScriptList : public ScriptListBase
{
public:
	ScriptList();
	~ScriptList();
	void clear();
	void swap(ScriptList *other);

private:
	Rva003B761E m_first;			// +0x0C
	Rva003B761E m_second;			// +0x2C
};

// ??0ScriptList@@QAE@XZ
ScriptList::ScriptList()
{
}
