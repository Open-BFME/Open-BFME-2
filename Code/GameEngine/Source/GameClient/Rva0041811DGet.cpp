// cl: /DNDEBUG /MD /EHsc
// ?rva0041811D@Rva0041811D@@QAEPAXPBVAsciiString@@@Z, retail 0x0041811D (38B).
// Lookup in the embedded Rva00056F61 bucket table at +0xC via rowed
// iterator find 0x0041534B. Returns node+8 or null (inline payload, add
// not deref, unlike siblings at +0x26c/+0x280/+0x294 which deref).
// Callers at 0x00418169 (Leadership INI parse via global 0x00A030A8 with
// Unknown LivingWorldAutoResolveLeadership), 0x00418879 (Body via
// 0x00A030B0), 0x004191A8 (CombatChain via 0x00A030B8), 0x0041974C
// (Weapon via 0x00A030C0) and default getters 0x0041883F
// (AutoResolve_DefaultBody) 0x0041916E (AutoResolve_DefaultCombatChain)
// 0x00419712 (AutoResolve_DefaultWeapon). Chain over 0x0041534B.
// Owner unproven so honest-address class Rva0041811D.
class AsciiString;

template <typename T>
class StringBase
{
private:
	friend class AsciiString;
	friend class Rva0041811D;
	void releaseBuffer();
	StringBase(const T *text);
	StringBase(const StringBase<T> &that);
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

class AsciiString
{
public:
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
private:
	char *m_text;
};
class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};
class Rva0041811D
{
public:
	void *rva0041811D(const AsciiString *key);
	void *rva00418825();
	void *rva00419154();
	void *rva004196F8();
private:
	char m_pad[0xC];
	Rva00056F61 m_table;
};
void *Rva0041811D::rva0041811D(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node != 0)
		return (void *)((char *)it.m_node + 8);
	return 0;
}
void *Rva0041811D::rva00418825()
{
	AsciiString tmp("AutoResolve_DefaultBody");
	void *res = rva0041811D(&tmp);
	((StringBase<char> *)&tmp)->releaseBuffer();
	return res;
}
// ?rva00419154@Rva0041811D@@QAEPAXXZ, retail 0x00419154, 46 bytes. Default
// CombatChain getter via rowed 0x0041811D with DefaultCombatChain string.
// Evidence: same 46B shape as sibling 0x00418825; callers 0x00419406
// and jmp 0x0033A684; string literal AutoResolve_DefaultCombatChain.
void *Rva0041811D::rva00419154()
{
	AsciiString tmp("AutoResolve_DefaultCombatChain");
	void *res = rva0041811D(&tmp);
	((StringBase<char> *)&tmp)->releaseBuffer();
	return res;
}
// ?rva004196F8@Rva0041811D@@QAEPAXXZ, retail 0x004196F8, 46 bytes. Default
// Weapon getter via rowed 0x0041811D with DefaultWeapon string. Evidence:
// same 46B shape as siblings; callers 0x0033AA11 and 0x004199C3.
void *Rva0041811D::rva004196F8()
{
	AsciiString tmp("AutoResolve_DefaultWeapon");
	void *res = rva0041811D(&tmp);
	((StringBase<char> *)&tmp)->releaseBuffer();
	return res;
}
