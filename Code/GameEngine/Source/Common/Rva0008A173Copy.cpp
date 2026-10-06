// cl: /MD
// ?Rva0008A173Copy@@YAXPAVRva00089822@@ABV1@@Z, retail 0x0008A173, 18 bytes.
// Guarded copy-construct helper: if dst non-null placement-new copy via rowed 0x00089822.
// Evidence: mov ecx from [esp+4] test je push [esp+8] call copy ctor bare ret. Callers loop with 0x18 stride and caller cleans via pops. Owner unknown so honest Rva name.
class Rva00089822
{
public:
	Rva00089822(const Rva00089822 &other);
};

inline void *operator new(unsigned int, void *p)
{
	return p;
}

void __cdecl Rva0008A173Copy(Rva00089822 *dst, const Rva00089822 &src)
{
	if (dst != 0)
		new (dst) Rva00089822(src);
}
