// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva0052D6BEConstruct@@YAXPAVRva0056616B@@ABV1@@Z @0x0052D6BE 45B
// Single-element placement copy-construct helper called by array copy loops 0x0052D6EB and 0x0052D71A stepping by 0xB8.
// Evidence: chain from 0x0052D555 copy ctor; callers push (dst src) and step sizeof 0xB8; test+je matches placement new null check.
class Rva0056616B
{
public:
	Rva0056616B(const Rva0056616B &other);
	~Rva0056616B();
};
inline void *__cdecl operator new(unsigned int, void *p) throw() { return p; }
inline void __cdecl operator delete(void *, void *) throw() { }
void __cdecl Rva0052D6BEConstruct(Rva0056616B *dst, const Rva0056616B &src)
{
	new(dst) Rva0056616B(src);
}
