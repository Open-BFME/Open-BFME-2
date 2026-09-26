// cl: /O1 /DNDEBUG /MD /GX-
// Rva001DCAED_ParseTransition (retail 0x001DCAED, 69 bytes). Serves the
// Transition entry of the 3-entry table at 0x7DBDB0 (siblings WinName,
// FrameDelay). The token resolves through the rowed
// NameKeyGenerator::nameToKey at 0x00148E1A (const-char overload, called
// on the extern singleton pointer at 0xDF36A4, DIR32 from retail), then
// the key looks up a function slot through the pinned
// ObjectLookupMap::findSlot at 0x0041F4E5 on the map at +0x0C of the
// object pointed to by 0xDFDC14 (DIR32 from retail). The slot holds a
// cdecl INI-parser-shaped callback invoked with (ini, instance, store,
// userData); the indirect call cleans its own four pushes. All callees
// are rowed or pinned; the owning struct is BFME2-new (no BFME1 donor).

class INI;

typedef void (__cdecl *TransitionFunc)(INI *ini, void *instance, void *store, const void *userData);

class ObjectLookupMap
{
public:
	class Object **findSlot(int *id);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern void *Rva00DFDC14Object;

class INI
{
public:
	const char *getNextToken(const char *seps);
	static void Rva001DCAED_ParseTransition(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva001DCAED_ParseTransition@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva001DCAED_ParseTransition(INI *ini, void *instance, void *store, const void *userData)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(ini->getNextToken(0));
	TransitionFunc *slot = (TransitionFunc *)((ObjectLookupMap *)((char *)Rva00DFDC14Object + 0xC))->findSlot((int *)&key);
	(*slot)(ini, instance, store, userData);
}
