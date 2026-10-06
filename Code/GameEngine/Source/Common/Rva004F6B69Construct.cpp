// cl: /DNDEBUG /MD
// ?Rva004F6B69Construct@@YAXPAURva004F6966@@PBU1@@Z @0x004F6B69 (18B): placement copy-construct.
// Null-checked placement copy via rowed copy ctor ??0Rva004F6966@@QAE@ABU0@@Z
// at 0x004F6966. Callers at 0x004F6B9B 0x004F6BC6 0x004F8A8B 0x004F902A walk
// 0xC-sized elements. Prev UninitializedCopy next Rva004F6B7BInit /O1 /DNDEBUG /MD.
inline void *operator new(unsigned int, void *p) { return p; }

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva004F6966
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
	Rva004F6966(const Rva004F6966 &other);
};

void Rva004F6B69Construct(Rva004F6966 *dst, const Rva004F6966 *src)
{
	if (dst != 0)
		new (dst) Rva004F6966(*src);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Construct@URva004F6966@@U1@@_STL@@YAXPAURva004F6966@@ABU1@@Z=?Rva004F6B69Construct@@YAXPAURva004F6966@@PBU1@@Z")
