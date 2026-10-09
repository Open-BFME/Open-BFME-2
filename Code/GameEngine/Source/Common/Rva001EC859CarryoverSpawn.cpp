// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva001EC859@Rva001EC859@@QAEPAXHH@Z retail 0x001EC859..0x001EC8C0 (103
// bytes ret 8). Campaign half of TheLinearCampaignManager forwarder
// 0x001EC99B (object types then player; returns an ObjectID). WorldBuilder
// twin 0x00AF7A40 (callgraph evidence) has the same body: find the
// carryover unit record for the types (rowed search 0x001EB023 over the
// 172-byte records at +0xA4/+0xA8); if found ask it to create one object
// for the player (0x0037DCE8 = WB CarryoverUnit::createSingleObject) and
// take the object's ID (+0x74) and set bit 0x10 of its +0x438 status byte;
// copy the record into the used list at +0xB4 (rowed push_back 0x001EC056)
// then erase the record through 0x001EBCD8 when its count (+0x90) is one
// or less (returning at once as in WB) else decrement the count. The early
// return is what keeps retail's direct [esi+0x90] load and store. The
// pinned address-derived int/int/void* ABI of the existing caller row is
// kept; record and object layouts are views.
class Object;
class Player;
class Rva00376A62;

struct Rva001EB023Elem
{
	char unknown00[0x90];
	int quantity; // +0x90
	char unknown94[0xAC - 0x94];
};

struct BfmePod172
{
	int a[43];
};

class Rva001EB023
{
public:
	Rva001EB023Elem *rva001EB023(Rva00376A62 &key);
};

class CarryoverUnit
{
public:
	Object *createSingleObject(Player *player);
};

struct Rva001EC859ObjectView
{
	char unknown00[0x74];
	unsigned int id; // +0x74
	char unknown78[0x438 - 0x78];
	unsigned char statusBits; // +0x438
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);

private:
	T *first, *last, *limit;
};
}

class Rva001EBCD8
{
public:
	void *rva001EBCD8(void *record);
};

class Rva001EC859
{
public:
	void *rva001EC859(int types, int player);

private:
	char unknown00[0xA4];
	Rva001EB023Elem *m_first; // +0xA4
	Rva001EB023Elem *m_last; // +0xA8
	Rva001EB023Elem *m_limit; // +0xAC
	int unknownB0;
	_STL::vector<BfmePod172> m_used; // +0xB4
};

void *Rva001EC859::rva001EC859(int types, int player)
{
	unsigned int id = 0;
	Rva001EB023Elem *record = reinterpret_cast<Rva001EB023 *>(this)
		->rva001EB023(*reinterpret_cast<Rva00376A62 *>(types));
	if (record != m_last)
	{
		Object *object = reinterpret_cast<CarryoverUnit *>(record)
			->createSingleObject(reinterpret_cast<Player *>(player));
		if (object != 0)
		{
			Rva001EC859ObjectView *view = reinterpret_cast<Rva001EC859ObjectView *>(object);
			id = view->id;
			view->statusBits |= 0x10;
		}
		m_used.push_back(*reinterpret_cast<const BfmePod172 *>(record));
		if (record->quantity <= 1)
		{
			reinterpret_cast<Rva001EBCD8 *>(reinterpret_cast<char *>(this) + 0xA4)
				->rva001EBCD8(record);
			return reinterpret_cast<void *>(id);
		}
		--record->quantity;
	}
	return reinterpret_cast<void *>(id);
}
