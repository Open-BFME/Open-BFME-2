// ?Rva0030C114@@YA_NPBURva0030BFE8Range@@0@Z
// Retail 0x0030C114 21B: negated Rva0030BFE8Equal result as a bool.

struct Rva0030BFE8Range;

int __cdecl Rva0030BFE8Equal(const Rva0030BFE8Range *a, const Rva0030BFE8Range *b);

bool __cdecl Rva0030C114(const Rva0030BFE8Range *a, const Rva0030BFE8Range *b)
{
	return !(char)Rva0030BFE8Equal(a, b);
}
