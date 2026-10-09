// cl: /DNDEBUG /MD
//
// ?rva0004E4C9@Rva0004E4C9@@QAEAAV1@PAX@Z @0x0004E4C9 24B: honest smart-pointer store with AddRef
// Evidence: rowed inc 0x002D76B7 Rva002D76B7DwordCounter disp8+0x08; caller 0x0004F84E; neighbours share // cl: /O1 /DNDEBUG /MD
class RadarMarker
{
public:
	void AddReference();
};

class Rva0004E4C9
{
public:
	Rva0004E4C9 &rva0004E4C9(void *p);
private:
	void *m_ptr;
};

Rva0004E4C9 &Rva0004E4C9::rva0004E4C9(void *p)
{
	m_ptr = p;
	if (p)
		((RadarMarker *)p)->AddReference();
	return *this;
}
