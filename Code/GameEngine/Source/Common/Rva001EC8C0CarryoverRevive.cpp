// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva001EC8C0@Rva001EC8C0@@QAE_NHHH@Z retail 0x001EC8C0..0x001EC97F (193 bytes ret 0xC), the revive
// sibling of Rva001EC859CarryoverSpawn.cpp on the same carryover-unit record ranges (+0xA4/+0xA8, used list +0xB4
// of 172-byte records): find the record for the key (rowed search 0x001EB023); none: false. Otherwise build a
// UnitRevivalEntry (216 bytes, rowed ctor 0x0037E352 / dtor 0x001EB63C), fill it from the record (rowed copy
// 0x0037DE0E, which can fail: false), flag it, hand it to the tracker (rowed UnitRevivalTracker::addRevivableUnit
// 0x0037F38F with the third argument), then move the record into the used list (rowed push_back 0x001EC056) and
// erase it through 0x001EBCD8 when its count (+0x90) is one or less, else decrement the count. The pinned
// ABI (three ints, bool) of the existing caller row 0x001EC9AC is kept; record and entry layouts are views.
// Evidence: target bytes; sibling 0x001EC859 for the record and list handling. The meaning of the flag byte
// (+0xA1 of the entry) and of the arguments is inferred.

class Rva00376A62;
class Player;

struct Rva001EB023Elem
{
	char unknown00[0x90];
	int quantity; // +0x90
	char unknown94[0xAC - 0x94];
};

#include <vector>
struct BfmePod172 {int a[43];};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<BfmePod172,allocator<BfmePod172> >::push_back(BfmePod172 const &); }

class Rva001EB023
{
public:
	Rva001EB023Elem *rva001EB023(Rva00376A62 &key);
};

class Rva0037DE0E
{
public:
	unsigned char rva0037DE0E(void *dest);
};

class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	~UnitRevivalEntry();
	char m_pad00[0xA1];
	bool m_flagA1;
	char m_padA2[0xD8 - 0xA2];
};

struct Rva002E2D10Record
{
	char bytes[216];
};

class UnitRevivalTracker
{
public:
	void addRevivableUnit(const Rva002E2D10Record &item, Player *player);
};

class Slot0Receiver;
class Rva001EBCD8
{
public:
	void *rva001EBCD8(void *a1);
	char m_pad00[0x4];
private:
	Slot0Receiver *m_ptr; // +0x04
};

class Rva001EC8C0
{
public:
	bool rva001EC8C0(int a0, int a1, int a2);
	char m_pad00[0xA4];
private:
	Rva001EB023Elem *m_first; // +0xA4 +0xA4
	Rva001EB023Elem *m_last; // +0xA8 +0xA8
	Rva001EB023Elem *m_limit; // +0xAC +0xAC
	char m_padB0[0x4];
	_STL::vector<BfmePod172> m_used; // +0xB4 +0xB4
};

bool Rva001EC8C0::rva001EC8C0(int key, int tracker, int player)
{
	Rva001EB023Elem *record = reinterpret_cast<Rva001EB023 *>(this)
		->rva001EB023(*reinterpret_cast<Rva00376A62 *>(key));
	// Registers: a redundant re-read of the end pointer inside the existing compare gives `this` the extra
	// register-requiring reference that puts it (not the record) in ESI, as in the target.
	Rva001EB023Elem *last = m_last;
	if (record != last && last == m_last)
	{
		UnitRevivalEntry entry;
		if (reinterpret_cast<Rva0037DE0E *>(record)->rva0037DE0E(&entry))
		{
			entry.m_flagA1 = true;
			reinterpret_cast<UnitRevivalTracker *>(tracker)
				->addRevivableUnit(*reinterpret_cast<const Rva002E2D10Record *>(&entry), reinterpret_cast<Player *>(player));
			m_used.push_back(*reinterpret_cast<const BfmePod172 *>(record));
			if (record->quantity <= 1)
			{
				reinterpret_cast<Rva001EBCD8 *>(reinterpret_cast<char *>(this) + 0xA4)->rva001EBCD8(record);
				return true;
			}
			--record->quantity;
			return true;
		}
	}
	return false;
}
