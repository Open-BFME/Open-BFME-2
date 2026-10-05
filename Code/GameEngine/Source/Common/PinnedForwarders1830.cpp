// cl: /O1 /MD /DNDEBUG
//
// Four tiny members already pinned under placeholder names, each a guarded
// forward to one callee (pinned here under its address):
//   0x0030B719 19B Rva0030B719Shape::getRadius  - refresh via 0x0030B3D1
//                                                  while +0x24 is set, then
//                                                  return the float at +0x20
//   0x002B3740 19B Rva002BA8F1Logic::rva002B3740 - byte +0xA8 of what
//                                                  0x002B2B2D returns, or false
//   0x000A8AC0 12B MilesStreamRef::rva000A8AC0   - tail call 0x0010FB64 on the
//                                                  referenced stream if any
//   0x001ECEF6 13B Rva0023D607Holder::rva001ECEF6 - tail call 0x001ECE98 on
//                                                  the +0x10 member if any
// Identities beyond these shapes are not recovered.

typedef bool Bool;
typedef float Real;

class Rva0030B719Shape
{
public:
	Real getRadius() const;
	void rva0030B3D1();
private:
	unsigned char m_pad00[0x20];
	Real m_radius;
	Bool m_dirty;
};

Real Rva0030B719Shape::getRadius() const
{
	if (m_dirty)
		const_cast<Rva0030B719Shape *>(this)->rva0030B3D1();
	return m_radius;
}

struct Rva002B3740Item
{
	unsigned char m_pad00[0xA8];
	Bool m_flag;
};

class Rva002BA8F1Logic
{
public:
	Bool rva002B3740();
	Rva002B3740Item *rva002B2B2D();
};

Bool Rva002BA8F1Logic::rva002B3740()
{
	Rva002B3740Item *item = rva002B2B2D();
	if (item)
		return item->m_flag;
	return false;
}

class MilesStream
{
public:
	void rva0010FB64();
};

class MilesStreamRef
{
public:
	void rva000A8AC0();
private:
	MilesStream *m_stream;
};

void MilesStreamRef::rva000A8AC0()
{
	if (m_stream)
		m_stream->rva0010FB64();
}

class Rva001ECE98
{
public:
	void rva001ECE98();
};

class Rva0023D607Holder
{
public:
	void rva001ECEF6();
private:
	unsigned char m_pad00[0x10];
	Rva001ECE98 *m_10;
};

void Rva0023D607Holder::rva001ECEF6()
{
	if (m_10)
		m_10->rva001ECE98();
}
