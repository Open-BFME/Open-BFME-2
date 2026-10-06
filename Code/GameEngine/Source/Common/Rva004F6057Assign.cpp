// cl: /DNDEBUG /MD /EHsc
// ??4Rva004F6057@@QAEAAU0@ABU0@@Z, retail 0x004F6057, 39 bytes.
// Ref-holder copy-assign: AddRef incoming TargetRef at +4 then Release held
// via rowed fastcall 0x0007DEEF then copy ptr and return this. No self-check;
// AddRef-before-Release keeps self-assign safe. Evidence: sole callee rowed
// ReleaseTreeHintRef00217D4C; caller 0x004F99CC; ends exactly at next row
// 0x004F607E; same shape as rowed TreeHintRef assign 0x002174A4 minus check.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva004F6057
{
	TargetRef00217D4C *m_ptr;

	Rva004F6057 &operator=(const Rva004F6057 &other);
};

Rva004F6057 &Rva004F6057::operator=(const Rva004F6057 &other)
{
	if (other.m_ptr)
		++other.m_ptr->references;
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
	m_ptr = other.m_ptr;
	return *this;
}
