// cl: /DNDEBUG /MD
// ??4Rva004C9B8F@@QAEAAV0@ABV0@@Z, retail 0x004C9B8F, 45 bytes.
//
// Honest smart-pointer assignment: self-check then Add_Ref the incoming
// referent through rowed inc at 0x002D76B7 plus8 and Release_Ref the held
// referent through rowed release at 0x002D76BB plus8 slot1 before copying
// the pointer. Sole caller at 0x004C9D43 sets the RadarMarkerClientUpdate
// smart member at +0x0C. Shape matches rowed RefCountPtr<TextureClass>
// assignment at 0x000424D0 with an added self-check.
class RadarMarker
{
public:
	void AddReference();
};

class Rva002D76BB
{
public:
	void release();
};

class Rva004C9B8F
{
public:
	~Rva004C9B8F();
	Rva004C9B8F &operator=(const Rva004C9B8F &other);

private:
	void *m_ptr;
};

Rva004C9B8F::~Rva004C9B8F()
{
	if (m_ptr != 0)
		reinterpret_cast<Rva002D76BB *>(m_ptr)->release();
}

Rva004C9B8F &Rva004C9B8F::operator=(const Rva004C9B8F &other)
{
	if (this == &other)
		return *this;
	if (other.m_ptr != 0)
		reinterpret_cast<RadarMarker *>(other.m_ptr)->AddReference();
	if (m_ptr != 0)
		reinterpret_cast<Rva002D76BB *>(m_ptr)->release();
	m_ptr = other.m_ptr;
	return *this;
}
