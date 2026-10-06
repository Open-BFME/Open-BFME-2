// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva005480E8@@YAXPAXW4NameKeyType@@H@Z @0x005480E8 35B.
// Target identity evidence: Ghidra gives a 35-byte FUN boundary. The body
// looks up its second argument through the rowed Rva00355B61::rva00355155
// using the global at VA 0x00E01E18, then calls 0x00548984 on a successful
// result. The wrapper's original name and the callee's class identity remain
// unknown.
// Calling/layout evidence: stack offsets show a cdecl wrapper whose middle
// argument is the lookup key and whose outer arguments flow to 0x00548984.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
};

class Rva00548984
{
public:
	void rva00548984(void *first, int third);
};

class ArmorTemplate
{
};

class Rva00355B61
{
public:
	const ArmorTemplate *rva00355155(NameKeyType key) const;
};

class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;

void __cdecl rva005480E8(void *first, NameKeyType key, int third)
{
	const ArmorTemplate *entry =
		((Rva00355B61 *)TheAiOrdersManager)->rva00355155(key);
	if (entry)
		((Rva00548984 *)entry)->rva00548984(first, third);
}
