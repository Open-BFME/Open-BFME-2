// cl: /MD
//
// ?rva004F77AD@Rva004F60AA@@QAEPAV1@PAD0@Z, retail 0x004F77AD, 51 bytes.
// Unlocks 0x004F8C16; caller passes local Temporary_buffer at ecx with first/last.
// Count (last-first)>>2 into +4 calls rowed reserve 0x004F60AA then fills buffer +8
// via pinned uninitialized_fill_n AsciiString 0x004F6CDD when count>0 returns this.
// Evidence: reserve TU Rva004F60AAReserve layout m_00 m_04 m_08; disassembly
// mov sub sar mov call mov test jle push push push call add mov pop ret 8.

class AsciiString;
extern "C" __declspec(dllimport) void __cdecl free(void*);
struct Rva004F77E0Element {char bytes[4];};

namespace _STL {
	template<class Iter> void _Destroy(Iter,Iter);
	template <class _ForwardIter, class _Size, class _Tp>
	_ForwardIter uninitialized_fill_n(_ForwardIter first, _Size n, const _Tp &x);
}

class Rva004F60AA
{
public:
	void rva004F60AA();
 ~Rva004F60AA();
	Rva004F60AA *rva004F77AD(char *first, char *last);
private:
	int m_00;
	int m_04;
	void *m_08;
};

Rva004F60AA *Rva004F60AA::rva004F77AD(char *first, char *last)
{
	m_04 = (int)(last - first) >> 2;
	rva004F60AA();
	if (m_04 > 0)
		_STL::uninitialized_fill_n((AsciiString *)m_08, m_04, *(const AsciiString *)first);
	return this;
}

// Native Ghidra [4F77E0,4F7801),33B. Inplace-merge wrapper131B
// 4F8C16 constructs this same12B temporary atEBP-18 via full51B
// initialization4F77AD then destroys it here. Target count4/buffer8
// and stride4 are established independently from the STLport4.5.3
// Temporary_buffer semantic guide. Original element identity remains
// unknown: native full24B Destroy5F97BC calls full27B destroy-aux4F72ED
// through flags0 element teardown5F8FCC rather than AsciiString release.
// The scoped4B view asserts no unconsumed fields or original template name.
// Storage is freed through the native CRT free import after destruction.
Rva004F60AA::~Rva004F60AA()
{
 Rva004F77E0Element *buf=static_cast<Rva004F77E0Element*>(m_08);
 _STL::_Destroy(buf,buf+m_04);
 ::free(m_08);
}

#pragma comment(linker, "/alternatename:??$_Destroy@PAURva004F77E0Element@@@_STL@@YAXPAURva004F77E0Element@@0@Z=??$_Destroy@PAUTreeHintRef00217D4C@@@_STL@@YAXPAUTreeHintRef00217D4C@@0@Z")
