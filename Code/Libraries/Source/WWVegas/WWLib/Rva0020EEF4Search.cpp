// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020EEF4@Rva0020EEF4Outer@@QAEHH@Z @0x0020EEF4 74B
// Predicate search over inner vector at *(this+8)+0x2C/+0x30: skips elements
// with +0x13C == -1, runs pinned 0x003F08D7(int) on each, returns its value
// on first nonzero (preserved eax, no mov), else 0. Reload-each-iteration
// count idiom like the proven EE29 trio; int (not bool) gives retail test
// eax and xor eax.
class Rva003F08D7
{
public:
	int rva003F08D7(int v);
};
struct Rva0020EEF4Inner
{
	char m_pad[0x2C];
	Rva003F08D7 **m_begin;
	Rva003F08D7 **m_end;
};
struct Rva0020EEF4Elem
{
	char m_pad[0x13C];
	int m_13C;
};
class Rva0020EEF4Outer
{
public:
	int rva0020EEF4(int v);
private:
	char m_pad[8];
	Rva0020EEF4Inner *m_inner;
};
int Rva0020EEF4Outer::rva0020EEF4(int v)
{
	Rva0020EEF4Inner *inner = m_inner;
	if (inner != 0)
	{
		for (unsigned i = 0; i < (unsigned)(((char *)inner->m_end - (char *)inner->m_begin) >> 2); ++i)
		{
			Rva0020EEF4Elem *e = (Rva0020EEF4Elem *)inner->m_begin[i];
			if (e->m_13C == -1)
				continue;
			int r = ((Rva003F08D7 *)e)->rva003F08D7(v);
			if (r)
				return r;
		}
	}
	return 0;
}
