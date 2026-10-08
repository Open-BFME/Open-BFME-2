// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
//
// ??0Rva005E626D@@QAE@PAURva005E626DOwner@@PAVRva0057C394@@PAURva005E626DListOwner@@PAX@Z,
// retail 0x005E626D..0x005E62F1 (132 bytes, EH, RET 16). No WorldBuilder
// match; every name is address-derived.
//
// A two-base object (vtables 0x00C77DE8 at +0x00 and 0x00C77DD4 at +0x08).
// The primary base is the rowed six-argument constructor 0x005F5614, fed
// from the owner's +0x18 and +0x1C, the list owner, the caller's last
// argument and the address of a temporary built by the rowed 0x005F2381
// and destroyed by the rowed 0x005F23B2 (pinned under this temporary's
// class name). The listener base at +0x08 is announced to the list owner's
// +0x08 list (rowed append 0x005A0B4C) after the owner and list owner are
// stored at +0x0C/+0x10. The earlier verdict was blocked on the primary
// base constructor, which is rowed now.

class Rva0057C394;

class Rva005F2381
{
public:
	Rva005F2381();
	~Rva005F2381();
private:
	unsigned char m_data[0x1C];
};

class Rva005F566A
{
public:
	Rva005F566A(Rva0057C394 *a, void *b, void *c, void *d, void *e, void *f);
	virtual ~Rva005F566A();
private:
	unsigned char m_pad04[4];
};

struct Rva002BA8F1Listener
{
	virtual void notify();
	virtual ~Rva002BA8F1Listener();
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

struct Rva005E626DOwner
{
	unsigned char m_pad00[0x18];
	void *m_18;
	unsigned char m_1C[4];
};

struct Rva005E626DListOwner
{
	unsigned char m_pad00[0x08];
	Rva005A0B4CList m_list08;
};

class Rva005E626D : public Rva005F566A, public Rva002BA8F1Listener
{
public:
	Rva005E626D(Rva005E626DOwner *owner, Rva0057C394 *source, Rva005E626DListOwner *listOwner, void *extra);
	virtual ~Rva005E626D();
	virtual void notify();

private:
	Rva005E626DOwner *m_owner0C;			// +0x0C
	Rva005E626DListOwner *m_listOwner10;	// +0x10
};

Rva005E626D::Rva005E626D(Rva005E626DOwner *owner, Rva0057C394 *source, Rva005E626DListOwner *listOwner, void *extra)
	: Rva005F566A(source, owner->m_18, owner->m_1C, listOwner, &(Rva005F2381 &)Rva005F2381(), extra),
	  m_owner0C(owner),
	  m_listOwner10(listOwner)
{
	listOwner->m_list08.append(this);
}
