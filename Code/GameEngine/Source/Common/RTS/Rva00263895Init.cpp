// cl: /O1 /arch:SSE /DNDEBUG /MD /GX-
// ??0Rva00263895Member@@QAE@XZ 0x00263895 45B
// Member ctor: vtable g_00BF9200, Rva00263653 ctor at +4, ptr g_00BF91AC at +0x6c, floats 0.0f at +0x70/+0x74, byte 0 at +0x78.
// Evidence: 40+ callers incl matched attemptHealing (DamageInfo 0x7C view) and AICommandParmsCtor tail; callee Rva00263653 ctor rowed; LINK BONUS init pin is void alias of this ctor body (mov eax esi proves ctor returns this).
extern const void *const g_00BF9200[];
extern const void *const g_00BF91AC[];

class Rva00263653
{
public:
	Rva00263653() throw();
	char m_data[0x68];
};

class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	virtual void rva00263895_dummy();

private:
	Rva00263653 m_mem;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};

Rva00263895Member::Rva00263895Member() throw()
	: m_ptr(g_00BF91AC),
	  m_f70(0.0f),
	  m_f74(0.0f),
	  m_b78(0)
{
}

// ?rva00263895_dummy@Rva00263895Member@@UAEXXZ present-unmatched
void Rva00263895Member::rva00263895_dummy() {}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0AICommandParmsTail@@QAE@XZ=??0Rva00263895Member@@QAE@XZ")
#pragma comment(linker, "/alternatename:?init@Rva00263895Member@@QAEXXZ=??0Rva00263895Member@@QAE@XZ")

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00BF91AC@@3QBQBXB=??_7Rva0028C6D6@@6B@")
