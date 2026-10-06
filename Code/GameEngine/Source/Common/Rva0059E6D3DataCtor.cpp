// cl: /Oy- /DNDEBUG /MD /GX-
// stlport
// ??0Rva0059E6D3Data@@QAE@XZ @0x0059E574 58B: OwnershipSet record ctor with vtable 0x00871094 plus three BfmeE16 vectors at +4/+10/+1C plus zero at +28.
// Evidence: rowed Vector_base 0x00211E58 thrice; neighbours 0x0059E511/0x0059E6D3 in Rva003F9258Siblings.cpp; caller 0x0059E6F3; pin ??0Rva0059E6D3Data@@QAE@XZ.
struct BfmeE16 { float x, y, z, w; };

namespace _STL {
template <typename T> class allocator { public: allocator() {} };
template <typename T, typename A> class _Vector_base
{
public:
	_Vector_base(const A &);
private:
	void *_M_start;
	void *_M_finish;
	void *_M_end;
};
}

class Rva0059E6D3Data
{
public:
	Rva0059E6D3Data();
	virtual ~Rva0059E6D3Data();
private:
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_v04;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_v10;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_v1C;
	int m_28;
};

Rva0059E6D3Data::Rva0059E6D3Data()
	: m_v04(_STL::allocator<BfmeE16>()),
	  m_v10(_STL::allocator<BfmeE16>()),
	  m_v1C(_STL::allocator<BfmeE16>()),
	  m_28(0)
{
}
