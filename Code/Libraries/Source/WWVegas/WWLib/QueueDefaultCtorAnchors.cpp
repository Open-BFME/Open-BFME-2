// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport

// Open-BFME5: STLport queue<T>::queue(), 15 bodies of 44 bytes.  Every one
// carried only a machine byte-dump row; the same shape is already converted at
// 0x00660EB0, 0x00660EF0 and 0x0065A990.
//
// A queue is one deque and nothing else, so this is the deque's default
// constructor inlined into it: forty bytes of the object zeroed a dword at a
// time -- the two iterators' four members each, the map pointer and the map
// size -- and then one call, _M_initialize_map with a count of zero, which is
// what actually buys the first node.
//
// sizeof(T) never appears.  The deque's buffer arithmetic lives in
// _M_initialize_map and in _M_allocate_node, not here, so these 44 bytes are
// the same for every element type and say nothing whatever about T -- not even
// its width.  Elements below are named by that width plus an ordinal, since
// the width is all any of these fifteen retail sites actually prove about T.
//
// _M_initialize_map does say it, and nine of them are converted in
// RvaDequeInitializeMap.cpp: the shift it divides the element count by is
// 128/sizeof(T),
// STLport's buffer size -- 128 bytes of node divided by the element -- so a
// `shr 5` is a four-byte element and a `shr 2` a 32-byte one.  Ten elements carry the width their callee proves -- the
// tenth callee is still a dump, but its shift is just as readable.  The five
// whose _M_initialize_map is not a dump at all keep a nominal four bytes, which
// is all that is needed to instantiate the deque and all that is claimed.

#include <queue>
#include <new>

struct QueueElem4A
{
	char m_body[ 4 ];
};

typedef _STL::queue<QueueElem4A> Queue4A;

// retail 0x00089CA0
void BfmeQueueCtorAnchor4A( void *place )
{
	new ( place ) Queue4A();
}

struct QueueElem4B
{
	char m_body[ 4 ];
};

typedef _STL::queue<QueueElem4B> Queue4B;

// retail 0x0035A900
void BfmeQueueCtorAnchor4B( void *place )
{
	new ( place ) Queue4B();
}

struct QueueElem4C
{
	char m_body[ 4 ];
};

typedef _STL::queue<QueueElem4C> Queue4C;

// retail 0x0035A940
void BfmeQueueCtorAnchor4C( void *place )
{
	new ( place ) Queue4C();
}

struct QueueElem4D
{
	char m_body[ 4 ];
};

typedef _STL::queue<QueueElem4D> Queue4D;

// retail 0x0035AF40
void BfmeQueueCtorAnchor4D( void *place )
{
	new ( place ) Queue4D();
}

struct QueueElem4E
{
	char m_body[ 4 ];
};

typedef _STL::queue<QueueElem4E> Queue4E;

// retail 0x0035AF80
void BfmeQueueCtorAnchor4E( void *place )
{
	new ( place ) Queue4E();
}

struct QueueElem4F
{
	char m_body[ 4 ];
};

typedef _STL::queue<QueueElem4F> Queue4F;

// retail 0x00369550
void BfmeQueueCtorAnchor4F( void *place )
{
	new ( place ) Queue4F();
}

struct QueueElem4G
{
	int m_body;
};

typedef _STL::queue<QueueElem4G> Queue4G;

// retail 0x0063DF60
void BfmeQueueCtorAnchor4G( void *place )
{
	new ( place ) Queue4G();
}

struct QueueElem4H
{
	int m_body;
};

typedef _STL::queue<QueueElem4H> Queue4H;

// retail 0x0063DFA0
void BfmeQueueCtorAnchor4H( void *place )
{
	new ( place ) Queue4H();
}

struct QueueElem32
{
	char m_body[ 32 ];
};

typedef _STL::queue<QueueElem32> Queue32;

// retail 0x00642060
void BfmeQueueCtorAnchor32( void *place )
{
	new ( place ) Queue32();
}

struct QueueElem16
{
	char m_body[ 16 ];
};

typedef _STL::queue<QueueElem16> Queue16;

// retail 0x006420A0
void BfmeQueueCtorAnchor16( void *place )
{
	new ( place ) Queue16();
}

struct QueueElem4I
{
	char m_body[ 4 ];
};

typedef _STL::queue<QueueElem4I> Queue4I;

// retail 0x00647200
void BfmeQueueCtorAnchor4I( void *place )
{
	new ( place ) Queue4I();
}

struct QueueElem4J
{
	int m_body;
};

typedef _STL::queue<QueueElem4J> Queue4J;

// retail 0x0064CA60
void BfmeQueueCtorAnchor4J( void *place )
{
	new ( place ) Queue4J();
}

struct QueueElem4K
{
	int m_body;
};

typedef _STL::queue<QueueElem4K> Queue4K;

// retail 0x0064CAF0
void BfmeQueueCtorAnchor4K( void *place )
{
	new ( place ) Queue4K();
}

struct QueueElem4L
{
	int m_body;
};

typedef _STL::queue<QueueElem4L> Queue4L;

// retail 0x0065A950
void BfmeQueueCtorAnchor4L( void *place )
{
	new ( place ) Queue4L();
}

struct QueueElem4M
{
	char m_body[ 4 ];
};

typedef _STL::queue<QueueElem4M> Queue4M;

// retail 0x006AADB0
void BfmeQueueCtorAnchor4M( void *place )
{
	new ( place ) Queue4M();
}
