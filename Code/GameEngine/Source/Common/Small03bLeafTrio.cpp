// Ported from Open-BFME-1's game/GameEngine/Source/Common/Small03bLeafTrio.cpp
// (donor revision: reference/open-bfme-1 @ a38d345e) by tools/bfme1_sweep.py:
// 0x009339F0 (22B) -> 0x00118DE0 (22B), tier T1 "clean transfer", base build
// flags. The donor holds three unrelated leaf bodies and the sweep placed one,
// so the file was held at copy-tier S and this TU carries only the placed body.
//
// The donor's own comment gives the shape: "unsigned clamp: past-the-end index
// returns the base pointer." The comparison is `(unsigned int)i >= m_size`,
// which is what makes a negative index take the clamp rather than the indexed
// path. No pin is needed -- the body reaches no global and no callee.

class Rva009339F0Box
{
public:
	short *at(int i);
	short *m_data;
	int m_pad4;
	unsigned int m_size;
};

short *Rva009339F0Box::at(int i)
{
	if ((unsigned int)i >= m_size)
		return m_data;
	return m_data + i;
}

struct Rva0092D430Inner
{
	char m_pad[0x1C];
	signed char m_value;
};

class Rva0092D430Box
{
public:
	int get() const;
	char m_pad[0xC4];
	Rva0092D430Inner *m_ptr;
};

// mov eax,[ecx+0xC8] / test / movsx eax,byte ptr [eax+0x1C] / null on miss.
int Rva0092D430Box::get() const
{
	return m_ptr ? m_ptr->m_value : 0;
}
