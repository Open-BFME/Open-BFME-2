// cl: /DNDEBUG /MD
//
// Five slot bodies (slots 1, 4, 7, 8 and 11) shared by the four unnamed
// vftables 0x00C04C28, 0x00C04C7C, 0x00C07F4C and 0x00C08974 (no name
// getter; the owners use virtual inheritance and are not recovered). Each
// edits the 8-byte container at +0x08 through one of its rowed members and
// then calls the owner's own slot 12 (offset 0x30), a change notification:
//
//   0x00330ABE  the rowed Rva0030BA8C::rva0030BA8C (push of a BfmeE8)
//   0x00330B14  the rowed Rva0030B92C::rva0030B85A (erase at an index)
//   0x00330B6B  the rowed Rva0030B92C::rva0030B135 (with a BfmePod8 pointer)
//   0x00330BBD  the rowed Rva0030B812::rva0030B812 (swap)
//   0x00330BEB  the rowed Rva00330B50::rva00330B50 (assignment)
//
// The ledger names the container differently at each of those members, so
// the member is a raw +0x08 block viewed through each name. Address-named
// owner (identity not recovered); 26 bytes each.

struct BfmeE8 { int a[2]; };
struct BfmePod8;

class Rva0030BA8C
{
public:
	void rva0030BA8C(const BfmeE8 &value);
};

class Rva0030B92C
{
public:
	void rva0030B85A(int index);
	void rva0030B135(const BfmePod8 *value);
};

struct Rva0030B812
{
public:
	void rva0030B812(Rva0030B812 *other);
};

class Rva00330B50
{
public:
	Rva00330B50 &rva00330B50(const Rva00330B50 &other);
};

class Rva00330ABE
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void changed();	// slot 12

	void rva00330ABE(const BfmeE8 &value);
	void rva00330B14(int index);
	void rva00330B6B(const BfmePod8 *value);
	void rva00330BBD(Rva0030B812 *other);
	void rva00330BEB(const Rva00330B50 &other);

private:
	char m_pad04[0x08 - 0x04];
	char m_container08[8];	// +0x08
};

void Rva00330ABE::rva00330ABE(const BfmeE8 &value)
{
	((Rva0030BA8C *)m_container08)->rva0030BA8C(value);
	changed();
}

void Rva00330ABE::rva00330B14(int index)
{
	((Rva0030B92C *)m_container08)->rva0030B85A(index);
	changed();
}

void Rva00330ABE::rva00330B6B(const BfmePod8 *value)
{
	((Rva0030B92C *)m_container08)->rva0030B135(value);
	changed();
}

void Rva00330ABE::rva00330BBD(Rva0030B812 *other)
{
	((Rva0030B812 *)m_container08)->rva0030B812(other);
	changed();
}

void Rva00330ABE::rva00330BEB(const Rva00330B50 &other)
{
	((Rva00330B50 *)m_container08)->rva00330B50(other);
	changed();
}

class Rva00330C05
{
public:
	int rva00330C05() const;
};

int Rva00330C05::rva00330C05() const
{
	BfmeE8 *const *start = (BfmeE8 *const *)((const char *)this - 0x34);
	BfmeE8 *const *finish = (BfmeE8 *const *)((const char *)this - 0x30);
	return *finish - *start;
}
