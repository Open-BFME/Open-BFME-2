// cl: /DNDEBUG /MD /EHsc
// Small leaf bodies whose owners retail does not name; holder names are
// address-derived.

class DelayedExperienceLevelGrantSystem
{
public:
	char m_pad00[0x14];
	bool m_14;
};

extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem; // 0x00E03144

// Native 0x0028A9F2, 12B: copy this flag to the grant system's +0x14.
struct Rva0028A9F2Flag
{
	void apply();
	bool m_flag;
};
void Rva0028A9F2Flag::apply()
{
	TheDelayedExperienceLevelGrantSystem->m_14 = m_flag;
}

// Native 0x0053B90F, 5B: increment the counter this points at.
struct Rva0053B90FCounterRef
{
	void increment();
	int *m_count;
};
void Rva0053B90FCounterRef::increment()
{
	++*m_count;
}

// Native 0x005CB283, 5B: tail-call virtual slot 11.
class Rva005CB283
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	void rva005CB283();
};
void Rva005CB283::rva005CB283()
{
	s11();
}
