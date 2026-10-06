// cl: /DNDEBUG /MD
// ?rva0044EF2C@Rva0044EF2C@@QAEHXZ @0x0044EF2C 22B
// Null-checked final-override int forward. Retail is mov eax [ecx+4]
// mov ecx [eax+0x38] test ecx jne call rowed
// Overridable::friend_getFinalOverride at 0x00288609 then mov eax [eax+0x1C].
// Evidence: unlock lane; caller at 0x0028BDBA in 0x0028BD92 which cmps the
// result; unblocks 0x0028BD92; flags copied from prev TU
// ModuleDataBuildFieldParseChained.cpp. Owner unproven so the name stays
// address-derived.
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x1C];
	int m_val1C;
};

struct Rva0044EF2CHolder
{
	char m_pad[0x38];
	Overridable *m_over38;
};

class Rva0044EF2C
{
public:
	char m_pad0[4];
	Rva0044EF2CHolder *m_holder04;
	int rva0044EF2C();
};

int Rva0044EF2C::rva0044EF2C()
{
	Overridable *o = m_holder04->m_over38;
	if (o == 0)
		return 0;
	const Overridable *f = o->friend_getFinalOverride();
	return f->m_val1C;
}
