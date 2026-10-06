// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0055D50DWrite@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABM@Z at 0x0055D50D size 24
// Evidence: chain via 0x003A5D34; conditional float write skipping zero t4IsZero 0x0055D3D9 on +0x14 then tail-jmp Write; precedent FXParticleSystemVecWrite.cpp.
namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
public:
	void _M_put_nowiden(char const *s);
	void _M_put_char(char c);
};
}

int t4IsZero005F4180(const float *v);
void Rva003A5D34Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	float const &value);

void Rva0055D50DWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	float const &value)
{
	if ((unsigned char)t4IsZero005F4180(&value))
		return;
	Rva003A5D34Write(os, pad, key, value);
}
