// cl: /O1 /DNDEBUG /MD
// ?rva003F9DB0@Rva003F9DB0@@QAEXXZ @0x003F9DB0 14B vector<BfmePod8> range-erase.
// Evidence: calls rowed ?erase@?$vector@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAEPAUBfmePod8@@PAU3@0@Z 0x003FA4DB with this+0x3C plus pushes of [this+0x40] then [this+0x3C]; caller 0x00210EBF tail-jmps after null-checking [ecx+0x2C4]; same erase-begin-end shape as MilesAudioManagerRva0005710F.
struct BfmePod8
{
	int a[2];
};
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_end;
};
template <> class vector<BfmePod8, allocator<BfmePod8> >
{
public:
	BfmePod8 *m_start;
	BfmePod8 *m_finish;
	BfmePod8 *m_end;
	BfmePod8 *erase(BfmePod8 *first, BfmePod8 *last);
	BfmePod8 *begin() { return m_start; }
	BfmePod8 *end() { return m_finish; }
	void clear() { erase(begin(), end()); }
};
}

class Rva003F9DB0
{
public:
	void rva003F9DB0();
private:
	char m_pad[0x3C];
	_STL::vector<BfmePod8> m_vec;
};

void Rva003F9DB0::rva003F9DB0()
{
	m_vec.clear();
}
