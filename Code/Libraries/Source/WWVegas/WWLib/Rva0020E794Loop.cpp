// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0020E794@Rva0020E794@@QAEPAVRva003F498A@@XZ, retail 0x0020E794, 41 bytes.
// Pointer scan at +0x14/+0x18 over Rva003F498A pointers via rowed 0x003F4831
// returning first element with positive count else NULL. Caller at 0x0020EC21.

class Rva003F498A
{
public:
	int rva003F4831();
};

class Rva0020E794
{
public:
	Rva003F498A *rva0020E794();

private:
	unsigned char m_pad[0x14];
	Rva003F498A **m_begin;
	Rva003F498A **m_end;
};

Rva003F498A *Rva0020E794::rva0020E794()
{
	Rva003F498A **begin = m_begin;
	Rva003F498A **end = m_end;
	for (; begin != end; ++begin) {
		Rva003F498A *elem = *begin;
		if (elem->rva003F4831() > 0)
			return elem;
	}
	return 0;
}
