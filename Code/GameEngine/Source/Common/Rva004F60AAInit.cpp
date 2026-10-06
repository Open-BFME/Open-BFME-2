// cl: /MD
//
// ?rva004F77AD@Rva004F60AA@@QAEPAV1@PAD0@Z, retail 0x004F77AD, 51 bytes.
// Unlocks 0x004F8C16; caller passes local Temporary_buffer at ecx with first/last.
// Count (last-first)>>2 into +4 calls rowed reserve 0x004F60AA then fills buffer +8
// via pinned uninitialized_fill_n AsciiString 0x004F6CDD when count>0 returns this.
// Evidence: reserve TU Rva004F60AAReserve layout m_00 m_04 m_08; disassembly
// mov sub sar mov call mov test jle push push push call add mov pop ret 8.

class AsciiString;

namespace _STL {
	template <class _ForwardIter, class _Size, class _Tp>
	_ForwardIter uninitialized_fill_n(_ForwardIter first, _Size n, const _Tp &x);
}

class Rva004F60AA
{
public:
	void rva004F60AA();
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
