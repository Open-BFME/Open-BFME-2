// cl: /DNDEBUG /MD /EHsc
//
// ?Rva00372D3AFind@@YAPAXPAX@Z retail 0x00372D3A 108 bytes.
// Free-function finder for MineshaftPortalBehaviour: caches the
// MineshaftPortalBehaviour NameKey via TheNameKeyGenerator in a function-local
// static then scans the null-terminated behaviour pointer list at +0x244,
// calling vtable slot +0x10 for each entry's key and returning the first match
// or null. Evidence: string literal MineshaftPortalBehaviour with EH prolog and
// static-guard shape matching MineshaftPortalBehaviourPoolKey; callers at
// 0x001E78BA and 0x0026AA0A take one pointer and use the result; +0x244 list
// and +0x10 key getter read directly from retail; while-deref shape gives
// retail ecx-only loop with reload-on-match and no saved edi.
enum NameKeyType
{
	NK_UNKNOWN = 0
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Behaviour
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual NameKeyType getKey();
};
struct Holder
{
	char m_pad[0x244];
	Behaviour **m_list;
};
void *Rva00372D3AFind(void *arg)
{
	static NameKeyType s_key = TheNameKeyGenerator->nameToKey("MineshaftPortalBehaviour");
	Behaviour **p = ((Holder *)arg)->m_list;
	while (*p) {
		if ((*p)->getKey() == s_key)
			return *p;
		++p;
	}
	return 0;
}

// Native [0x00498725,0x00498798) is a 115B cdecl finder. Its literal
// identifies GateOpenAndCloseBehavior; retail scans the same +0x244 pointer
// list and compares virtual slot +0x10 against a function-local cached key.
// A matched nonnull interface is adjusted by -4 before returning its owner.
// This offset is independently visible in BFME 2 and is also used by BFME 1
// BfmeConv1956/1957 at donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
// The original function name and complete owner class layout remain unknown.
void *Rva00498725Find(void *arg)
{
	static NameKeyType s_key = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	Behaviour **p = ((Holder *)arg)->m_list;
	while (*p) {
		if ((*p)->getKey() == s_key) {
			Behaviour *hit = *p;
			if (hit == 0)
				return 0;
			return (char *)hit - 4;
		}
		++p;
	}
	return 0;
}
