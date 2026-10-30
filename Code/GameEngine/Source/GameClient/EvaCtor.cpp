// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /EHsc /DNDEBUG /MD /arch:SSE /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??0Eva@@QAE@XZ, retail 0x001DF91B..0x001DFA48 (301 bytes, EH, ret 0):
// Eva's constructor (pinned; GameEngine::init creates the subsystem). Bases:
// SubsystemInterface at +0 (rowed ctor; table 0x00BDC5B8) and Snapshot at +0xC
// (0x00BDC5A8). Members are built through the rowed instantiations each call
// names: the int-keyed map at +0x10 (0x001DDBC6), vectors at +0x1C/+0x28/+0x5C
// (folded vector base), int-keyed hash maps at +0x34/+0x48 (0x001DED2B), the
// event queue list at +0x68 (list base 0x002049AD) with its position at +0x6C
// set to the list's end, then 0/1/3/true at +0x70..+0x7C. The body runs the
// rowed +0x80 setup (0x001DCF82), sizes the +0x5C status and +0x28 info
// vectors to the 22 events (rowed 0x001DEE92 / 0x001DF8F8), and registers each
// name of TheEvaMessageNames with its index in the +0x48 name table (rowed
// insert 0x001DE84F). The member views keep the existing address-derived
// spellings of Eva.cpp and the rowed helpers.
#include <map>
#include <list>
#include <hash_map>
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "ascii_string.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL {
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UupgradePair@@V?$allocator@UupgradePair@@@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct upgradePair;
namespace _STL { template <> void _List_base<upgradePair,allocator<upgradePair> >::clear(); }
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

struct Rva001DDBC6Record
{
	char bytes[4];
};

// Mapped type of the two maps: hash_map<int, T>() is rowed at 0x001DED2B and calls
// the hashtable constructor rowed for Rva001DE80FElement (0x001DE80F).
struct Rva001DE80FElement
{
	char bytes[4];
	bool operator==(const Rva001DE80FElement &) const;
};

struct upgradePair
{
	int a;
	int b;
};

struct NoCaseTreeValue4
{
	int m_index;
	NoCaseTreeValue4(int index) : m_index(index) {}
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;

struct InsertResult
{
	void *m_node;
	void *m_table;
	bool m_inserted;
};

class Rva001DE556
{
public:
	InsertResult *rva001DE84F(InsertResult *out, const NocasePair &obj);	// 0x001DE84F
};

class Rva001DEE92Member
{
public:
	void rva001DEE92(int count);							// 0x001DEE92
};

class Rva001DF88CVector
{
public:
	void resize(unsigned n);								// 0x001DF8F8
};

class Rva001DCF82
{
public:
	void *rva001DCF82();									// 0x001DCF82
};

extern "C" const char *TheEvaMessageNames[];

enum
{
	EVA_MESSAGE_COUNT = 22
};

class Eva : public SubsystemInterface, public Snapshot
{
public:
	Eva();
	virtual ~Eva();
	virtual const char *GetSnapshotName() const;

protected:
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;

private:
	_STL::map<int, Rva001DDBC6Record> m_10;					// +0x10
	_STL::vector<int> m_1C;									// +0x1C
	_STL::vector<int> m_allEventInfos;						// +0x28
	_STL::hash_map<int, Rva001DE80FElement> m_34;			// +0x34
	_STL::hash_map<int, Rva001DE80FElement> m_names;		// +0x48
	_STL::vector<int> m_eventStatus;						// +0x5C
	_STL::list<upgradePair> m_queue;						// +0x68
	_STL::list<upgradePair>::iterator m_queuePosition;		// +0x6C
	int m_70;												// +0x70
	int m_74;												// +0x74
	int m_78;												// +0x78
	bool m_7C;												// +0x7C
	int m_80;												// +0x80
};

Eva::Eva()
	: m_queuePosition(m_queue.end()), m_70(0), m_74(1), m_78(3), m_7C(true)
{
	((Rva001DCF82 *)&m_80)->rva001DCF82();
	((Rva001DEE92Member *)&m_eventStatus)->rva001DEE92(EVA_MESSAGE_COUNT);
	((Rva001DF88CVector *)&m_allEventInfos)->resize(EVA_MESSAGE_COUNT);
	for (unsigned int i = 0; i < EVA_MESSAGE_COUNT; ++i)
	{
		NocasePair entry((AsciiString(TheEvaMessageNames[i])), NoCaseTreeValue4(i));
		InsertResult result;
		((Rva001DE556 *)&m_names)->rva001DE84F(&result, entry);
	}
}

// ?Eva::loadPostProcess present-unmatched
void Eva::loadPostProcess()
{
}
