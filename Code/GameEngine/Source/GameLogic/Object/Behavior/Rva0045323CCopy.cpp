// cl: /MD /GX-
// ?Rva0045323CCopy@@YAXPAVRva004530ED@@ABV1@@Z @ 0x0045323C 18B evidence: null-checked placement copy via rowed 0x004530ED copy ctor; caller 0x004534B5 allocates 28B node and constructs at +8
inline void *__cdecl operator new(unsigned int, void *p) throw() { return p; }
inline void __cdecl operator delete(void *, void *) throw() { }

class Rva004530ED
{
public:
	Rva004530ED(const Rva004530ED &rhs) throw();
private:
	int m_00;
	int m_04[3];
	int m_10;
};

void __cdecl Rva0045323CCopy(Rva004530ED *dst, const Rva004530ED &src)
{
	if (dst)
		new(dst) Rva004530ED(src);
}
