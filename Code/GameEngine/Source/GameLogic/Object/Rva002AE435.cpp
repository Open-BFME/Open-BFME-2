// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002AE435@@YAHPBVThing@@PAV?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@@Z @0x002AE435 64B
// Target evidence: checks the key at Thing+0x74 through the rowed armor
// lookup, then when that test and getDrawable both succeed appends a second
// getDrawable result to the caller's Drawable* list. It returns true on all
// paths. The global and helper names are already used by matched source.
// Structural inference: the callback identity is unknown; Thing and list types
// follow the rowed helper signatures and existing target field access.
#include <list>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class ArmorTemplate;
class Rva0035516C
{
public:
	bool rva003551B5(NameKeyType key) const;
};
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;

class Drawable;
class Thing
{
public:
	Drawable *getDrawable(void) const;
};

int rva002AE435(const Thing *thing, std::list<Drawable *> *output)
{
	NameKeyType key = *(const NameKeyType *)((const char *)thing + 0x74);
	if (((Rva0035516C *)(void *)TheAiOrdersManager)->rva003551B5(key)) {
		if (thing->getDrawable() != 0)
			output->push_back(thing->getDrawable());
	}
	return 1;
}
