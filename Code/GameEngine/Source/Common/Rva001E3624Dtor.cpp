// cl: /DNDEBUG /MD
//
// ??1Rva001E3624@@UAE@XZ, retail 0x001E3624, 35 bytes.
// Virtual destructor of an opaque chain node (vptr 0x00BDDC48) that owns the
// next node at +4 (the layout RankInfoDtor.cpp models): when present the next
// node is destroyed through its virtual destructor and freed with the global
// operator delete (`::delete`), then the pointer is cleared. Evidence: symbols.csv pin (tail-called by the
// single-inheritance destructor at 0x003FA776); five units call it by this
// name. Class identity unproven, so the address-derived name stays.

class Rva001E3624
{
public:
	virtual ~Rva001E3624();

private:
	Rva001E3624 *m_next;	// +4
};

Rva001E3624::~Rva001E3624()
{
	if (m_next)
		::delete m_next;
	m_next = 0;
}
