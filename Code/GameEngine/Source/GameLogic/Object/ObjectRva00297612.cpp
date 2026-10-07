// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// Native 0x00297612..0x0029766B, 89B, RET. Object's adjacent rowed
// restoreObjectToWorld and the helper's +0x438 status/+0x84 Drawable accesses
// establish the owner. The entry meaning remains unresolved. BFME1 and ZH
// Object.cpp provide no corresponding countdown-list body.
#include <list>

struct Rva00297612Entry
{
	unsigned char unmodelled00[0x28];
	float remaining;
};

class Object
{
public:
	void rva002975AC(Rva00297612Entry *entry);
	void rva00297612();
private:
	unsigned char unmodelled00[0x440];
	// An int-list view exposes the shared node links and node+8 value address.
	// Native erase 0x00438539 only relinks and frees the node; it does not
	// access its payload, so the already rowed int specialization is its ABI.
	_STL::list<int, _STL::allocator<int> > entries;
};

void Object::rva00297612()
{
	typedef _STL::list<int, _STL::allocator<int> > EntryList;
	for (EntryList::iterator it = entries.begin(); it != entries.end(); )
	{
		Rva00297612Entry *entry = (Rva00297612Entry *)&*it;
		entry->remaining -= 1.0f;
		if (entry->remaining < 0.0f)
		{
			rva002975AC(entry);
			it = entries.erase(it);
		}
		else
			++it;
	}
}
