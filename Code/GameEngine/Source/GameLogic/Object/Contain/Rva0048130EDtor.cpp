// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva0048130E@@QAE@XZ, retail 0x0048130E, 53 bytes.
// ??0Rva0048130E@@QAE@ABV0@@Z, retail 0x0048147C, 57 bytes.
// ??_GRva0048130E@@QAEPAXI@Z, retail 0x004814B5, 28 bytes.
// 8-byte vector element for ProductionQueueHordeContainModuleData's +0xD4
// vector (destroyed by its dtor at 0x004817B6 via 0x004815AE): filter at +0
// via rowed 0x00360D26 plus AsciiString-equivalent StringBase<char> at +4
// via pinned 0x0036410/0x00365F0. Destruction is reverse declaration
// (string at +4 first arming state 0, then filter). Copy is dword for the
// filter plus StringBase copy for +4. Same 53B/28B shape as rowed
// ProductionModifierEntry (0x0049D12D/0x0049D82F) with members swapped.
// Identity is honest Rva (class name unproven); layout from the two bodies
// plus the 8-byte stride (sar 3) in 0x0048160B and the INI parse temp at
// 0x004816F4 constructing filter via 0x003623E5 and string via 0x00055F5.

class Rva0048130E;

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	StringBase(const StringBase &src);
	void *m_data;
	friend class Rva0048130E;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class Rva0048130E
{
public:
	~Rva0048130E();
	Rva0048130E(const Rva0048130E &src);

private:
	Rva00360D26Member m_filter; // +0
	StringBase<char> m_str; // +4
};

Rva0048130E::~Rva0048130E()
{
}

Rva0048130E::Rva0048130E(const Rva0048130E &src)
	: m_filter(src.m_filter)
	, m_str(src.m_str)
{
}

void deleteRva0048130E(Rva0048130E *p) { delete p; }

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva0048130E@@QAE@ABU0@@Z=??0Rva0048130E@@QAE@ABV0@@Z")
