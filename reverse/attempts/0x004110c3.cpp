// ?Rva004110C3Get@@YAPAXPBVAsciiString@@@Z
// partial score=0.93 date=2026-10-07
// cl: /DNDEBUG /MD /EHsc
// ?Rva004110C3Get@@YAPAXPBVAsciiString@@@Z, retail 0x004110C3, 25 bytes.
// Packet caller passes an AsciiString key; adjacent Rva004110DCGet wraps this same map lookup.

class AsciiString;

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
};

extern Rva00056F61 g_00E02FE4;

void *__cdecl Rva004110C3Get(const AsciiString *key)
{
	void *node = g_00E02FE4.rva00056F61(&*key);
	return node != 0 ? (char *)node + 8 : 0;
}
