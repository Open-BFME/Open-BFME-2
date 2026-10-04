// cl: /O1 /arch:SSE
// 18-byte guarded offset addition getter
//
// ?rva001DBDA4@Rva001DBDA4@@QBEHXZ @0x001DBDA4 34B: the largest get() (floor
// 0) over the list whose sentinel node the owner holds at +0x00 (next at
// +0x00, value pointer at +0x08); callers 0x001DC18B and 0x001DC22D. Retail
// keeps the node in edx across the get() call, which cl only does when get()
// was compiled earlier in the same TU, so it joins this file; its cmovg and
// jump-to-test loop need /O1 /arch:SSE, which leave get() unchanged.
//
// The rest of the same cluster, all honest-address names: element methods
// rva001DBAF6 (14B, the +0x08 flag of the +0x10 inner object, true when
// absent) and the forwarders rva001DBB04 (17B, ignores its int and calls inner
// vslot +0x0C), rva001DBB15/24/33 (15B each, tail calls to vslots +0x14,
// +0x18, +0x10); container methods rva001DBD83 (33B, all of rva001DBAF6) and
// rva001DBE17/34/51 (29B each, apply rva001DBB15/24/33 to every element).
// Each list walk sits after its callee here, as retail keeps the node or the
// container in a volatile register or reloads exactly what that knowledge
// allows. Callers: 0x001DBD8D, 0x001DBE01, 0x001DBE26, 0x001DBE43,
// 0x001DBE60, 0x001DBF0C, 0x001DBE7B, 0x001DC2C7, 0x001DBFDB.

class Inner00489360
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08(int value);
	virtual void v0C(); // +0x0C
	virtual void v10(); // +0x10
	virtual void v14(); // +0x14
	virtual void v18(); // +0x18
	int m_val; // +0x04
	bool m_flag; // +0x08
};

class Rva00489360
{
public:
	bool rva001DBAF6() const;
	void rva001DBB04(int value);
	void rva001DBB15();
	void rva001DBB24();
	void rva001DBB33();
	int get() const;
	void rva001DBACA(int value);
	bool rva001DBD24();

	char            m_pad00[ 0x4 ];
	int             m_baseVal;
	char            m_pad08[ 0x8 ];
	Inner00489360 * m_inner;
	int             m_14;
};

bool Rva00489360::rva001DBAF6() const
{
	if( m_inner )
		return m_inner->m_flag;
	return true;
}

void Rva00489360::rva001DBB04(int)
{
	if( m_inner )
		m_inner->v0C();
}

void Rva00489360::rva001DBB15()
{
	if( m_inner )
		m_inner->v14();
}

void Rva00489360::rva001DBB24()
{
	if( m_inner )
		m_inner->v18();
}

void Rva00489360::rva001DBB33()
{
	if( m_inner )
		m_inner->v10();
}

int Rva00489360::get() const
{
	if( m_inner )
		return m_inner->m_val + m_baseVal;
	return m_baseVal;
}

struct Node001DBDA4
{
	Node001DBDA4 *m_next;
	Node001DBDA4 *m_prev;
	Rva00489360 *m_value;
};

class Rva001DBDA4
{
public:
	bool rva001DBD83() const;
	int rva001DBDA4() const;
	void rva001DBD5D();
	void rva001DBE17();
	void rva001DBE34();
	void rva001DBE51();
	void rva001DC164();

	Node001DBDA4 *m_head;
	int m_04;
	int m_08;
};

bool Rva001DBDA4::rva001DBD83() const
{
	for( Node001DBDA4 *n = m_head->m_next; n != m_head; n = n->m_next )
	{
		if( !n->m_value->rva001DBAF6() )
			return false;
	}
	return true;
}

int Rva001DBDA4::rva001DBDA4() const
{
	int best = 0;
	for( Node001DBDA4 *n = m_head->m_next; n != m_head; n = n->m_next )
	{
		int v = n->m_value->get();
		if( v > best )
			best = v;
	}
	return best;
}

void Rva001DBDA4::rva001DBE17()
{
	for( Node001DBDA4 *n = m_head->m_next; n != m_head; n = n->m_next )
		n->m_value->rva001DBB15();
}

void Rva001DBDA4::rva001DBE34()
{
	for( Node001DBDA4 *n = m_head->m_next; n != m_head; n = n->m_next )
		n->m_value->rva001DBB24();
}

void Rva001DBDA4::rva001DBE51()
{
	for( Node001DBDA4 *n = m_head->m_next; n != m_head; n = n->m_next )
		n->m_value->rva001DBB33();
}

// ?rva001DBACA@Rva00489360@@QAEXH@Z @0x001DBACA 44B: range-guarded inner
// v08 dispatch. Caller 0x001DBD5D passes list values (Rva00489360) with the
// accumulated offset; +0x14 base and +0x10 inner (m_val at +4 v08 at +8)
// from retail lea/cmp/call immediates.
void Rva00489360::rva001DBACA(int value)
{
	if( value < m_14 )
		return;
	int limit = m_inner->m_val + m_14;
	if( value > limit )
		return;
	if( m_inner == 0 )
		return;
	m_inner->v08(value - m_14);
}

// ?rva001DBD5D@Rva001DBDA4@@QAEXXZ @0x001DBD5D 38B: accumulate m_04 into m_08
// then apply rva001DBACA(m_08) to every element. Evidence: same list layout
// as siblings (+0x00 head +0x04 +0x08) rowed callee 0x001DBACA caller 0x001DBF17.
void Rva001DBDA4::rva001DBD5D()
{
	m_08 += m_04;
	for( Node001DBDA4 *n = m_head->m_next; n != m_head; n = n->m_next )
		n->m_value->rva001DBACA(m_08);
}

// The 0x00DFDC14 singleton (theBfmeDfdc14, defined in WinMain.cpp); only its
// +0x64 frame count is used here.
class AudioManager
{
public:
	char m_pad00[0x64];
	int m_64;
};
extern AudioManager *theBfmeDfdc14;

// ?rva001DC164@Rva001DBDA4@@QAEXXZ @0x001DC164 59B: Zero Hour's
// TransitionGroup::init shape (frame 0 at +0x08, direction 1 at +0x04, init
// every element through the rowed rva001DBD24), then BFME 2 stores this
// group's largest total (rva001DBDA4, compiled earlier in this TU) plus 3 at
// +0x64 of the 0x00DFDC14 singleton. Callers 0x001DC2EB (setGroup 0x001DC252)
// and 0x001DC3F3 (0x001DC345).
void Rva001DBDA4::rva001DC164()
{
	m_08 = 0;
	m_04 = 1;
	for( Node001DBDA4 *n = m_head->m_next; n != m_head; n = n->m_next )
		n->m_value->rva001DBD24();
	theBfmeDfdc14->m_64 = rva001DBDA4() + 3;
}
