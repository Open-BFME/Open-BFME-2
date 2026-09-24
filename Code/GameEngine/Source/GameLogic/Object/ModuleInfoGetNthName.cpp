// cl: /O1 /Oy- /DNDEBUG /MD /GX /G7
//
// ModuleInfo::getNthName, retail 0x001F12DF (64 bytes): bounds-checked
// indexed copy-out of a module name. A negative index or one past the end
// yields the empty module name; otherwise the nugget at the index feeds the
// StringBase copy body at 0x365F0 straight into the hidden return slot (RVO).
// The inlined count is a byte difference divided by the 20-byte nugget stride
// (push-14/cdq/pop-ecx idiv); the second bound compares unsigned so the miss
// jumps with jae while the negative guard keeps its signed jl.

template <typename T>
class StringBase
{
	friend class BFMERetailAsciiString;

public:
	StringBase() : m_data(0) {}

private:
	StringBase(const StringBase<T> &that);
	T *m_data;
};

class BFMERetailAsciiString : public StringBase<char>
{
public:
	__forceinline BFMERetailAsciiString(const BFMERetailAsciiString &other) : StringBase<char>(other) {}
	~BFMERetailAsciiString();
};

struct ModuleNugget
{
	char m_bytes[20];
};

class ModuleInfo
{
public:
	BFMERetailAsciiString getNthName(int index) const;
	int getCount() const { return ((char *)m_end - (char *)m_begin) / 20; }

	ModuleNugget *m_begin;
	ModuleNugget *m_end;
	ModuleNugget *m_cap;
};

extern BFMERetailAsciiString g_emptyModuleName;

// ?getNthName@ModuleInfo@@QBE?AVBFMERetailAsciiString@@H@Z @0x001F12DF
BFMERetailAsciiString ModuleInfo::getNthName(int index) const
{
	if (index < 0 || (unsigned)index >= (unsigned)getCount())
		return g_emptyModuleName;
	return *(const BFMERetailAsciiString *)(m_begin + index);
}
