// cl: /GX-
// FESL browser owner ctor @ 0x802040 (138B). V2ZeroPair +8; twin Buf +0x10/+0x18;
// Arr2 +0x20 allocate(a->m_08) sibling of matched 0x801BD0; Buf::set from
// owner+0x2AC/+0x2B4. Member ctors supply the early eax-zeros; body zeros
// +28/+30/+55/+2C after the lea trio.

// The owner at 0x802040 installs vtable 0x0112C4A8 and its matched sibling
// allocator at 0x801BD0 placement-news 0x38-byte records whose constructor at
// 0x802640 installs vtable 0x0112C548.  Slot +0x1c of that record vtable is
// the still-neutral 0x802310 predicate (it reads the record's +0x0c field).
// This view records only the observed virtual slot and storage extent; the
// +0x10 write below is the index assigned by the 0x801A90 search.
class Rva00802680Owner
{
public:
	virtual ~Rva00802680Owner();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual int rva00802310();

	char m_observed004[0x0c];
	int m_observedIndex;
	char m_observed014[0x0c];
	char m_observed020[0x18];
};

struct V2ZeroPair
{
	__forceinline V2ZeroPair() : m_a( 0 ), m_b( 0 ) {}
	int m_a;
	int m_b;
};

class Rva00802040Buf
{
public:
	__forceinline Rva00802040Buf() : m_p( 0 ), m_n( 0 ) {}
	void set( void *p );

	void *m_p;
	int m_n;
};

class Rva00802040Arr
{
public:
	__forceinline Rva00802040Arr() : m_a( 0 ), m_n( 0 ) {}
	void allocate( int n );
	__forceinline Rva00802680Owner *at( int index )
	{
		if (index >= m_n)
			return 0;
		return m_a + index;
	}

	Rva00802680Owner *m_a;
	int m_n;
};

class Rva00802040Src
{
public:
	char m_pad[8];
	int m_08;
	char m_pad2[0xb4 - 0x0c];
	void *m_b4;
	void *m_b8;
};

class Rva00802040OwnerSrc
{
public:
	char m_pad[0x2ac];
	void *m_2ac;
	char m_pad2[4];
	void *m_2b4;
};

// Abstract base of the owner: vftable 0x00CE3BE8 holds the base scalar
// deleting dtor (0x0066DBA0) in slot 0 and __purecall in its 13 other slots.
// The owner ctor installs only the derived vftable 0x00CE3C88; the derived
// deleting dtor (0x0066E3D0) restores 0x00CE3BE8 after the member dtors.
class Rva00802040OwnerBase
{
public:
	Rva00802040OwnerBase();
	virtual ~Rva00802040OwnerBase() {}
	virtual void p01() = 0;
	virtual void p02() = 0;
	virtual void p03() = 0;
	virtual void p04() = 0;
	virtual void p05() = 0;
	virtual void p06() = 0;
	virtual void p07() = 0;
	virtual void p08() = 0;
	virtual void p09() = 0;
	virtual void p10() = 0;
	virtual void p11() = 0;
	virtual void p12() = 0;
	virtual void p13() = 0;
};
// ??0Rva00802040OwnerBase@@QAE@XZ @0x0066D760 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE3BE8) and returning this.
Rva00802040OwnerBase::Rva00802040OwnerBase()
{
}

class Rva00802040Owner : public Rva00802040OwnerBase
{
public:
	__declspec(noinline) Rva00802040Owner( Rva00802040Src *a, Rva00802040OwnerSrc *b );
	virtual ~Rva00802040Owner() {}
	Rva00802680Owner *findFree();
	void rva00801ae0( int *outMatches, int *outOther );

	Rva00802040OwnerSrc *m_04;
	V2ZeroPair m_08;
	Rva00802040Buf m_10;
	Rva00802040Buf m_18;
	Rva00802040Arr m_20;
	int m_28;
	int m_2c;
	char m_30;
	char m_pad31[0x24];
	char m_55;
};

Rva00802680Owner *Rva00802040Owner::findFree()
{
	for (int i = 0; i < m_20.m_n; ++i)
	{
		Rva00802680Owner *slot = m_20.at( i );
		if (!slot->rva00802310())
		{
			slot->m_observedIndex = i;
			return slot;
		}
	}
	return 0;
}

void Rva00802040Owner::rva00801ae0( int *outMatches, int *outOther )
{
	int matches = 0;
	int other = 0;
	for (int i = 0; i < m_20.m_n; ++i)
	{
		Rva00802680Owner *slot = m_20.at( i );
		int state = slot->rva00802310();
		if (state)
		{
			if (state == 4)
				++matches;
			else
				++other;
		}
	}
	*outMatches = matches;
	*outOther = other;
}

Rva00802040Owner::Rva00802040Owner( Rva00802040Src *a, Rva00802040OwnerSrc *b )
{
	int z = 0;
	m_28 = z;
	m_30 = (char)z;
	m_55 = (char)z;
	m_2c = z;
	m_04 = b;
	m_08.m_a = (int)a->m_b8;
	m_08.m_b = (int)a->m_b4;
	m_20.allocate( a->m_08 );
	m_10.set( m_04->m_2ac );
	m_18.set( m_04->m_2b4 );
}
