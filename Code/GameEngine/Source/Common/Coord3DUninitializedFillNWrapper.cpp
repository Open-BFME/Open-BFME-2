// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Whole-file extension of the existing Coord3D fill_n wrapper at CA1D3.
// BFME1 semantic guide: 0bef414b52a39a3ab1ec98dca60d8a214de4260e,
// game/Libraries/Source/WWVegas/WWLib/Coord3DVectorFillInsert.cpp; verified
// BFME2 sibling: Code/Libraries/Source/WWVegas/WWLib/Coord3DVectorFillInsert.cpp.
// Native CA1EE..CA2EE is a complete 256B RET12 vector fill insertion.
// Its 12-byte element identity follows the rowed Coord3D construction/copy,
// fill_n and overflow workers (346C2D, CA1D3, 2CDF8A). Its stock fill and
// backward-copy dispatch call B431D and B6813, rather than the sibling's
// specialized integer-copy helpers 7E3B1/7E4B5. Use the existing BfmeE12
// provider spelling for these two structural 12-byte operations: emitting
// this unit's Coord3D copies creates divergent COMDATs. The casts preserve
// the proven three-word value/stride; they assert no original element name.
// The full call-resolved body establishes every edge; no new pins or aliases.
// The separate address-derived receiver names this build variant: the
// canonical vector<Coord3D>::_M_fill_insert owns the distinct 227B 4E29C8.
// The old 27B fill_n wrapper remains byte-exact under the shared flags.
#define _STLP_NO_EXCEPTIONS 1
#include "../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../vendor/stlport/stl/_uninitialized.h"
using namespace _STL;
namespace _STL {
static inline const unsigned int &max(const unsigned int &a,const unsigned int &b) { return a < b ? b : a; }
}
#include <vector>

#include "../../../Libraries/Include/Lib/Coord3D.h"
// Same structural view as the existing provider stlport_vector_e12_o1.cpp.
struct BfmeE12 { float x, y, z; };
namespace _STL {
template<> void _Construct(Coord3D*,const Coord3D&);
}
class Rva000CA1EEVector : public _STL::vector<Coord3D> {
public:
 void fillInsert(Coord3D*,unsigned int,const Coord3D&);
};
void Rva000CA1EEVector::fillInsert(
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
				__copy_backward_ptrs(reinterpret_cast<BfmeE12 *>(position),
					reinterpret_cast<BfmeE12 *>(old_finish - count),
					reinterpret_cast<BfmeE12 *>(old_finish), _TrivialAss());
				_STLP_STD::fill(reinterpret_cast<BfmeE12 *>(position),
					reinterpret_cast<BfmeE12 *>(position + count),
					reinterpret_cast<const BfmeE12 &>(value_copy));
			}
			else
			{
				uninitialized_fill_n(this->_M_finish,
					count - elements_after, value_copy);
				this->_M_finish += count - elements_after;
				__uninitialized_copy(position, old_finish,
					this->_M_finish, _IsPODType());
				this->_M_finish += elements_after;
				_STLP_STD::fill(reinterpret_cast<BfmeE12 *>(position),
					reinterpret_cast<BfmeE12 *>(old_finish),
					reinterpret_cast<const BfmeE12 &>(value_copy));
			}
		}
		else
			this->_M_insert_overflow(position, value, _IsPODType(), count);
	}
}
