// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva000427195@@QAE@XZ @0x001FDEDB 57B.
// Hash-table destructor for the AsciiString-keyed bucket table: clears via
// the rowed rva003A2A41, then the inline bucket-handle member dtor frees the
// bucket array at +4 via free 0x00030830 with a null guard. Same EH
// clear-plus-free shape as the rowed tree dtors ??1Rva001FD42B@@QAE@XZ
// 0x001FD6BC (Rva001FD42BDtor.cpp precedent: a throwing free under /EHs
// emits retail's unwind state store). Header at +4 costs
// one disp8 byte over the tree dtors. Callers at 0x001FE26E 0x002B1390
// 0x002B139F and jmp at 0x001FE065; unblocks 0x002B11A7.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct Rva000427195BucketHandle
{
	~Rva000427195BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

struct Rva000427195
{
	Rva000427195 &operator=(const Rva000427195 &other);
	void rva003A2A41();
	~Rva000427195();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva000427195::~Rva000427195()
{
	rva003A2A41();
}

// Native 1FDC0F is already owned by the STLport hashtable copy worker.
// This declaration names that owner; its opaque record is a donor type, while
// the caller's reference/receiver ABI and full 192-byte provider are verified.
struct Rva001FDC0FRecord;
namespace _STL {
 template<class A,class B> struct pair;
 template<class T> struct hash;
 template<class T> struct _Select1st;
 template<class T> struct equal_to;
 template<class T> class allocator;
 template<class Value,class Key,class Hash,class Extract,class Equal,class Alloc>
 class hashtable {
 private: void _M_copy_from(const hashtable &);
 friend struct ::Rva000427195;
 };
}
typedef _STL::pair<const int,Rva001FDC0FRecord> NativeCopyValue;
typedef _STL::hashtable<NativeCopyValue,int,_STL::hash<int>,
 _STL::_Select1st<NativeCopyValue>,_STL::equal_to<int>,
 _STL::allocator<NativeCopyValue> > NativeCopyTable;

// ??4Rva000427195@@QAEAAU0@ABU0@@Z
Rva000427195 &Rva000427195::operator=(const Rva000427195 &other)
{
	if (&other != this) {
		rva003A2A41();
		reinterpret_cast<NativeCopyTable *>(this)->_M_copy_from(reinterpret_cast<const NativeCopyTable &>(other));
	}
	return *this;
}

// ??1Rva002CFF2D@@QAE@XZ @0x002CFF2D 57B: byte-identical to ~Rva000427195 above except its own
// EH handler (formerly matched as the alias dup_002cff2d); ThingFactoryDtor.cpp calls it by this
// name. Same layout; the clear is the same rowed 0x003A2A41 body.
struct Rva002CFF2D
{
	~Rva002CFF2D();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva002CFF2D::~Rva002CFF2D()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// ??1Rva001F8D70Map@@QAE@XZ @0x001F8D70 57B: byte-identical to ~Rva000427195 above except its own EH handler
// (formerly the alias dup_001f8d70); its callers bind it through a pin by this name.
struct Rva001F8D70Map
{
	~Rva001F8D70Map();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva001F8D70Map::~Rva001F8D70Map()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// ??1Rva00242E71@@QAE@XZ @0x00242E71 57B: byte-identical to ~Rva000427195 above except its own EH handler
// (formerly the alias dup_00242e71); its callers bind it through a pin by this name.
struct Rva00242E71
{
	~Rva00242E71();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva00242E71::~Rva00242E71()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// ??1Rva002BB281Member08@@QAE@XZ @0x002BAD1C 57B: byte-identical to ~Rva000427195 above except its own EH handler
// (formerly the alias dup_002bad1c); its callers bind it through a pin by this name.
struct Rva002BB281Member08
{
	~Rva002BB281Member08();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva002BB281Member08::~Rva002BB281Member08()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// ??1Rva0031C79DMap@@QAE@XZ @0x0031C79D 57B: byte-identical to ~Rva000427195 above except its own EH handler
// (formerly the alias dup_0031c79d); its callers bind it through a pin by this name.
struct Rva0031C79DMap
{
	~Rva0031C79DMap();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva0031C79DMap::~Rva0031C79DMap()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// ??1Rva002129DD@@QAE@XZ @0x002129DD 57B: byte-identical to ~Rva000427195 above except its own EH handler
// (formerly the alias dup_002129dd); its callers bind it through a pin by this name.
struct Rva002129DD
{
	~Rva002129DD();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva002129DD::~Rva002129DD()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// ??1Rva0021231B@@QAE@XZ @0x0021231B 57B: ~LivingWorldManager's (0x00214405, its
// only caller) +0x218 hash table destructor (formerly the alias dup_0021231b);
// the shape above, clearing through the node/bucket clear 0x001DBCDC
// (?clear@Rva004DFC20@@QAEXXZ). Retail folds its EH handler with 0x002129DD's.
#include "../../Include/Common/Rva004DFC20.h"

struct Rva0021231B
{
	~Rva0021231B();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva0021231B::~Rva0021231B()
{
	((Rva004DFC20 *)this)->clear();
}

// ??1Rva0030A083Map@@QAE@XZ @0x0030A083 57B: byte-identical to ~Rva000427195 above
// (formerly the alias dup_0030a083); retail folds its EH handler with 0x0030A0BC's.
// Reached only through the five-byte forwarder 0x0030A0FC below.
struct Rva0030A083Map
{
	~Rva0030A083Map();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva0030A083Map::~Rva0030A083Map()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// ??1Rva0030A0FCDtor@@QAE@XZ @0x0030A0FC 5B: bare tail jump to ~Rva0030A083Map;
// the atexit cleanup 0x007B7AE1 of the global table at 0x00DFF494 calls it.
struct Rva0030A0FCDtor
{
	~Rva0030A0FCDtor();
};

Rva0030A0FCDtor::~Rva0030A0FCDtor()
{
	((Rva0030A083Map *)this)->~Rva0030A083Map();
}

// The 0x001DBCDC-clear shape of ~Rva0021231B above (formerly the aliases
// dup_00524c88 and dup_00240c27); each folds its EH handler
// with another table's.
// ??1Rva00524C88Map@@QAE@XZ @0x00524C88 57B: reached only through the
// five-byte forwarder 0x00524CC1 below.
struct Rva00524C88Map
{
	~Rva00524C88Map();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva00524C88Map::~Rva00524C88Map()
{
	((Rva004DFC20 *)this)->clear();
}

// ??1Rva00524CC1Dtor@@QAE@XZ @0x00524CC1 5B: bare tail jump to ~Rva00524C88Map;
// the atexit cleanup 0x007B91F8 of the global table at 0x00E04938 calls it.
struct Rva00524CC1Dtor
{
	~Rva00524CC1Dtor();
};

Rva00524CC1Dtor::~Rva00524CC1Dtor()
{
	((Rva00524C88Map *)this)->~Rva00524C88Map();
}

// ??1Rva00240C27@@QAE@XZ @0x00240C27 57B: the +0xB4 table destructor of
// 0x00243BA0 (REL32 at 0x00243E0A); GameLogicDestructor.cpp calls it by this name.
struct Rva00240C27
{
	~Rva00240C27();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva00240C27::~Rva00240C27()
{
	((Rva004DFC20 *)this)->clear();
}

// ??1Rva003ED1BEMap@@QAE@XZ @0x003ED1BE 57B: the 0x001DBCDC-clear shape of
// ~Rva0021231B (formerly the gen-alias dup_003ed1be) with its own EH handler,
// folded with 0x007836C4. ~Rva003ED1FC (0x003ED1FC) calls it for its +0x0C
// table and the five-byte forwarder ~Rva003ED1F7 (0x003ED1F7) tail-jumps to it.
struct Rva003ED1BEMap
{
	~Rva003ED1BEMap();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva003ED1BEMap::~Rva003ED1BEMap()
{
	((Rva004DFC20 *)this)->clear();
}

// Native 0x0052B6FE: clears the local registration table and frees its buckets.
// The original table specialization remains unidentified.
struct Rva0052B6FE
{
    ~Rva0052B6FE();
    void *m_unused00;
    Rva000427195BucketHandle m_buckets;
    unsigned int m_numElements;
};

Rva0052B6FE::~Rva0052B6FE()
{
    ((Rva000427195 *)this)->rva003A2A41();
}

// Native 0x00410C7B: the two registration tables' clear-and-free destructor.
// Original table specialization and element identity remain unidentified.
struct Rva00410C7B
{
    ~Rva00410C7B();
    void *m_unused00;
    Rva000427195BucketHandle m_buckets;
    unsigned int m_numElements;
};

Rva00410C7B::~Rva00410C7B()
{
    ((Rva000427195 *)this)->rva003A2A41();
}
