// cl: /O1 /Oy- /EHsc /MD
//
// ?rva00395C80@@YAHPAVObject@@@Z @0x00395C80 107B: cached module-key veto.
// First call resolves the module name key once through TheNameKeyGenerator
// (global 0xDF36A4) and keeps it in a function-static wrapper (guard
// 0xE027E4, storage 0xE027E0); the wrapper's inlined ctor is what holds the
// EH state open across the nameToKey call. Then findModule (rowed 0x28B6D6)
// looks the key up on the caller's Object: missing module, clear +0x25 flag,
// or clear +0x19 flag on the +0x0 next module vetoes (returns true); all set
// returns false. /O1 keeps the frame in the shared __EH_prolog helper
// (0x629188) like the neighbouring NameKeyGenerator bodies. The +0x0 next
// link is dereferenced unconditionally, matching retail; it is evidently
// non-null whenever the +0x25 flag is set. The key string lives outside the
// packed image (slot 0xBF5CCC), so it is modeled as an extern array whose
// slot the DIR32 patcher fills, never as a literal.

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern const char Rva00BF5CCC[];

class Module
{
public:
	char m_pad00[4]; // +0x00
	Module *m_next; // +0x04
	char m_pad08[0x11]; // +0x08
	unsigned char m_flag19; // +0x19
	char m_pad1A[0x0B]; // +0x1A
	unsigned char m_flag25; // +0x25
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend int rva00395C80(Object *obj);
};

struct Rva00395C80Key
{
	NameKeyType key;
	__forceinline Rva00395C80Key(const char *name) { key = TheNameKeyGenerator->nameToKey(name); }
};

// ?rva00395C80@@YAHPAVObject@@@Z
int rva00395C80(Object *obj)
{
	static Rva00395C80Key s_key(Rva00BF5CCC);
	Module *m = obj->findModule(s_key.key);
	if (m != 0 && m->m_flag25 != 0 && m->m_next->m_flag19 != 0)
		return false;
	return true;
}
