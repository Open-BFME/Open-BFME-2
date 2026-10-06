// cl: /MD
//
// Eight empty non-virtual dtors (8B each) of one shape: add ecx, N then
// tail-jump the teardown of the member at +N. No vtable install, no other
// teardown, no null-this guard (member teardown, not an MI base).
// 0x0022630F (+4 -> 0x002DFAD1, opaque pin; row keeps the peer pin name,
//   called by the scalar deleting dtor 0x00229487),
// 0x0023863E (+4 -> matched ~VersionBlockParserInner 0x002385FF),
// 0x002A9ECA (+8 -> 0x00380459, opaque pin),
// 0x002B0B8E (+4 -> 0x002B0B32, opaque alias pin; same body as the matched
//   STLport vector dtor row),
// 0x0042581E (+8 -> 0x00425756, opaque alias pin; same body as the matched
//   STLport deque dtor row),
// 0x0050174A (+4 -> 0x005016C3, opaque pin; row keeps the peer pin name),
// 0x005C8565 (+8 -> 0x005C8494, opaque pin; row keeps the peer pin name),
// 0x00603C57 (+4 -> 0x00603AA8, opaque alias pin; same body as the matched
//   STLport rb-tree dtor row; row keeps the peer pin name).
// Member/owner identities unproven except where the peer pins and the three
// matched callee rows say otherwise; new names are address-derived.
// One ledger row per dtor.

class VersionBlockParserInner
{
public:
	~VersionBlockParserInner();
};

class Rva002DFAD1Dtor
{
public:
	~Rva002DFAD1Dtor();
};

class Rva00229487
{
public:
	~Rva00229487();

private:
	char m_pad[4];
	Rva002DFAD1Dtor m_inner;
};

class Rva0023863E
{
public:
	~Rva0023863E();

private:
	char m_pad[4];
	VersionBlockParserInner m_inner;
};

class Rva00380459Dtor
{
public:
	~Rva00380459Dtor();
};

class Rva002A9ECA
{
public:
	~Rva002A9ECA();

private:
	char m_pad[8];
	Rva00380459Dtor m_inner;
};

class Rva002B0B32Dtor
{
public:
	~Rva002B0B32Dtor();
};

class Rva002B0B8E
{
public:
	~Rva002B0B8E();

private:
	char m_pad[4];
	Rva002B0B32Dtor m_inner;
};

class Rva00425756Dtor
{
public:
	~Rva00425756Dtor();
};

class Rva0042581E
{
public:
	~Rva0042581E();

private:
	char m_pad[8];
	Rva00425756Dtor m_inner;
};

class Rva005016C3Dtor
{
public:
	~Rva005016C3Dtor();
};

class Rva0050174A
{
public:
	~Rva0050174A();

private:
	char m_pad[4];
	Rva005016C3Dtor m_inner;
};

class Rva005C8494Dtor
{
public:
	~Rva005C8494Dtor();
};

class Rva005C8565
{
public:
	~Rva005C8565();

private:
	char m_pad[8];
	Rva005C8494Dtor m_inner;
};

class Rva00603AA8Dtor
{
public:
	~Rva00603AA8Dtor();
};

class Rva00603C57
{
public:
	~Rva00603C57();

private:
	char m_pad[4];
	Rva00603AA8Dtor m_inner;
};

Rva00229487::~Rva00229487()
{
}

Rva0023863E::~Rva0023863E()
{
}

Rva002A9ECA::~Rva002A9ECA()
{
}

Rva002B0B8E::~Rva002B0B8E()
{
}

Rva0042581E::~Rva0042581E()
{
}

Rva0050174A::~Rva0050174A()
{
}

Rva005C8565::~Rva005C8565()
{
}

Rva00603C57::~Rva00603C57()
{
}
