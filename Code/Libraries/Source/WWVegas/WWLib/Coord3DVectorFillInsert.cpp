// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// BFME1 semantic donor9cbfb551fe20dae985f91f2319d8997287b6a705:
// game/Libraries/Source/WWVegas/WWLib/Coord3DVectorFillInsert.cpp.
// Target82719..82819 proves256-byte fill insertion and all seven edges.
// The canonical vector<Coord3D>::_M_fill_insert name already owns the distinct
//227-byte body4E29C8. Keep this separate native build variant address-derived,
// using a zero-extra-storage vector view with the same12-byte receiver ABI.
// Target Coord3D identity: typed copy346C2D, fill_n CA1D3, overflow2CDF8A,
// and12-byte resize82C98. Scalar word assignment is independently established
// by fill7E3B1/40B and backward copy7E4B5/60B; their old opaque owner rows
// are renamed here, not counted again. Wrapper7EB51/29B forwards to7E4B5.
// All seven emitted helper bodies independently match their native extents.
// Select only the allocation shim; stock dispatch layers must stay out of line.
#define _STLP_NO_EXCEPTIONS 1
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
using namespace _STL;
namespace _STL {
static inline const unsigned int &max(const unsigned int &a,const unsigned int &b) { return a < b ? b : a; }
}
#include <vector>

#include "../../../Include/Lib/Coord3D.h"
namespace _STL {
template<> void _Construct(Coord3D*,const Coord3D&);
template<> void fill(Coord3D *dst,Coord3D *end,const Coord3D &value) {
 int *p=(int*)dst; const int *v=(const int*)&value;
 while(p!=(int*)end){p[0]=v[0];p[1]=v[1];p[2]=v[2];p+=3;}
}
template<> Coord3D *__copy_backward(Coord3D *first,Coord3D *last,Coord3D *result,const random_access_iterator_tag&,int*){
 for(int n=last-first; n>0;--n){--last;--result;int *p=(int*)result;const int *v=(const int*)last;p[0]=v[0];p[1]=v[1];p[2]=v[2];}
 return result;
}
}
class Rva00082719Vector : public _STL::vector<Coord3D> {
public:
 void fillInsert(Coord3D*,unsigned int,const Coord3D&);
};
void Rva00082719Vector::fillInsert(
	Coord3D *position, unsigned int count, const Coord3D &value)
{
	if (count != 0)
	{
		if ((unsigned int)(this->_M_end_of_storage._M_data - this->_M_finish)
			>= count)
		{
			const volatile Coord3D *value_source = &value;
			Coord3D value_copy;
			value_copy.x = value_source->x;
			value_copy.y = value_source->y;
			value_copy.z = value_source->z;
			const unsigned int elements_after =
				(unsigned int)(this->_M_finish - position);
			Coord3D *old_finish = this->_M_finish;
			if (elements_after > count)
			{
				__uninitialized_copy(this->_M_finish - count,
					this->_M_finish, this->_M_finish, _IsPODType());
				this->_M_finish += count;
				__copy_backward_ptrs(position, old_finish - count,
					old_finish, _TrivialAss());
				_STLP_STD::fill(position, position + count, (const Coord3D &)value_copy);
			}
			else
			{
				uninitialized_fill_n(this->_M_finish,
					count - elements_after, value_copy);
				this->_M_finish += count - elements_after;
				__uninitialized_copy(position, old_finish,
					this->_M_finish, _IsPODType());
				this->_M_finish += elements_after;
				_STLP_STD::fill(position, old_finish, (const Coord3D &)value_copy);
			}
		}
		else
			this->_M_insert_overflow(position, value, _IsPODType(), count);
	}
}
