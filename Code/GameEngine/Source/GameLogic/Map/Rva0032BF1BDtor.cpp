// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??1Rva0032BF1B@@QAE@XZ @0x0032BF1B 30B.
// Vector-style dtor over Rva0032A3A9Element* (0x80-byte element with virtual dtor):
// calls rowed _STL::_Destroy at 0x0032B580 with (m_start,m_finish), then frees
// m_start via rowed _free at 0x00030830 if non-null. Evidence: chain from
// 0x0032B580 which this session landed; callers at 0x0032C121/0x0032C486;
// prev 0x0032B7A7 (SidesList) fixes /O1 for the pop-cleanup shape.
class Rva0032A3A9Element {
public:
	virtual ~Rva0032A3A9Element();
private:
	char m_pad[124];
};
namespace _STL {
template <class _ForwardIterator>
void _Destroy(_ForwardIterator, _ForwardIterator);
}
extern "C" void free(void *p);
class Rva0032BF1B
{
public:
	~Rva0032BF1B();
private:
	Rva0032A3A9Element *m_start;
	Rva0032A3A9Element *m_finish;
};
Rva0032BF1B::~Rva0032BF1B()
{
	_STL::_Destroy(m_start, m_finish);
	Rva0032A3A9Element *s = m_start;
	if (s)
		free(s);
}
