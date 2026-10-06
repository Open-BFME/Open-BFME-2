// ?rva005996FF@Rva005996FF@@QAEXPAURva005996FFArg@@_N@Z
// partial score=0.94 date=2026-09-29
// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005996FF@Rva005996FF@@QAEXPAUArg@@_N@Z @ 0x005996FF 85B list erase plus string flag.
// Evidence: walks list<int> nodes via [eax+8] vs arg+0x74 then rowed erase 0x00438539; rowed StringBase compare 0x000069D6 for this+8 vs arg+4+0x64 then byte at +0x10; ret 8 is thiscall 2 args; neighbours Keyframe /O1 /GX- /arch:SSE2 plus DispByte default; unblocks 0x004EC869 plus 0x005ABAF6 plus 0x004ECB19.
#include <list>
template <typename T> class StringBase
{
public:
	int compare(const StringBase &o) const;
private:
	void *m_data;
};
typedef StringBase<char> AsciiString;
struct Inner64
{
	char m_pad[0x64];
	AsciiString m_str;
};
struct Rva005996FFArg
{
	char m_pad00[4];
	Inner64 *m_04;
	char m_pad08[0x6C];
	int m_74;
};
class Rva005996FF
{
public:
	void rva005996FF(Rva005996FFArg *arg, bool flag);
private:
	_STL::list<int, _STL::allocator<int> > m_list;
	char m_pad04[4];
	AsciiString m_08;
	char m_pad0C[0x10 - 0x0C];
	unsigned char m_10;
};
void Rva005996FF::rva005996FF(Rva005996FFArg *arg, bool flag)
{
	_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin();
	if (it == m_list.end())
		goto skip_erase;
	{
		int value = arg->m_74;
		while (it._M_node != m_list.end()._M_node) {
			if (*it == value)
				goto do_erase;
			++it;
		}
		goto skip_erase;
do_erase:
		m_list.erase(it);
	}
skip_erase:
	if (!flag)
		return;
	Inner64 *inner = arg->m_04;
	if (inner->m_str.compare(m_08) != 0)
		return;
	m_10 = 1;
}
