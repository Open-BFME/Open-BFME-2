// cl: /O2 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector copy construction, retail 0x00166110 (175 bytes).
// HTreeClass's verified copy constructor calls this for its +0x1C member.
// BFME1 a7c38d3b2597121f178ab5190b3062478823257d htree.cpp supplies
// hierarchy semantics; BFME2's captured-bone vector is target-specific.
// Its matched Capture_Bone/Control_Bone siblings establish the 36-byte
// record: index, quaternion, translation, and world-space flag. The original
// type name is unknown; retain the existing caller and allocator pin names.
// A memberwise translation copy retains the loop's +0x1C address bases.
// Advancing the source first retains retail's EAX/ECX induction registers.
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$uninitialized_fill_n@PAUBfmePod36@@IU1@@_STL@@YAPAUBfmePod36@@PAU1@IABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * uninitialized_fill_n<BfmePod36 *,unsigned int,BfmePod36>(BfmePod36 *,unsigned int,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_fill_insert(BfmePod36 *,unsigned int,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PAU1@00ABU__false_type@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod36 * __uninitialized_copy<BfmePod36 *,BfmePod36 *>(BfmePod36 *,BfmePod36 *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PBUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PBU1@0PAU1@ABU__false_ty:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod36 * __uninitialized_copy<BfmePod36 const *,BfmePod36 *>(BfmePod36 const *,BfmePod36 const *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__copy_backward@PAUBfmePod36@@PAU1@H@_STL@@YAPAUBfmePod36@@PAU1@00ABUrandom_access_iter:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod36 * __copy_backward<BfmePod36 *,BfmePod36 *,int>(BfmePod36 *,BfmePod36 *,BfmePod36 *,random_access_iterator_tag const &,int *); }
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod36@@U1@@_STL@@YAXPAUBfmePod36@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _Construct<BfmePod36,BfmePod36>(BfmePod36 *,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ??$__copy@PAUBfmePod36@@PAU1@H@_STL@@YAPAUBfmePod36@@PAU1@00ABUrandom_access_iterator_tag@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod36 * __copy<BfmePod36 *,BfmePod36 *,int>(BfmePod36 *,BfmePod36 *,BfmePod36 *,random_access_iterator_tag const &,int *); }
// Suppress this TU's non-retail copy of ??$__copy_backward_ptrs@PAUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PAU1@00ABU__false_type@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod36 * __copy_backward_ptrs<BfmePod36 *,BfmePod36 *>(BfmePod36 *,BfmePod36 *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXPAUBfm:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_insert_overflow(BfmePod36 *,BfmePod36 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAUBfmePod36@@IU1@@_STL@@YAPAUBfmePod36@@PAU1@IABU1@ABU__false_t:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod36 * __uninitialized_fill_n<BfmePod36 *,unsigned int,BfmePod36>(BfmePod36 *,unsigned int,BfmePod36 const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$fill@PAUBfmePod36@@U1@@_STL@@YAXPAUBfmePod36@@0ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void fill<BfmePod36 *,BfmePod36>(BfmePod36 *,BfmePod36 *,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ?_M_set@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXPAUBfmePod36@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_set(BfmePod36 *,BfmePod36 *,BfmePod36 *); }
// Suppress this TU's non-retail copy of ?size@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QBEIXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> unsigned int vector<BfmePod36,allocator<BfmePod36> >::size() const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAUBfmePod36@@U1@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _STLP_alloc_proxy<BfmePod36 *,BfmePod36,allocator<BfmePod36> >::deallocate(BfmePod36 *,unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmePod36@@U1@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEP:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod36 * _STLP_alloc_proxy<BfmePod36 *,BfmePod36,allocator<BfmePod36> >::allocate(unsigned int); }

struct BfmeCapturedBoneRotation
{
    float X, Y, Z, W;
};

struct BfmeCapturedBoneTranslation
{
    float X, Y, Z;
    BfmeCapturedBoneTranslation() {}
    BfmeCapturedBoneTranslation(const BfmeCapturedBoneTranslation &v)
        : X(v.X), Y(v.Y), Z(v.Z) {}
};

struct BfmePod36
{
    int Index;
    BfmeCapturedBoneRotation Rotation;
    BfmeCapturedBoneTranslation Translation;
    bool WorldSpace;

    BfmePod36() {}
    BfmePod36(const BfmePod36 &other)
        : Index(other.Index), Rotation(other.Rotation),
          Translation(other.Translation), WorldSpace(other.WorldSpace) {}
};

// The allocation provider at 0x00162800 owns a 36-byte storage view.
// Use that rowed ABI directly; captured-bone access stays explicitly typed.
struct Rva00162800Record { unsigned char bytes[36]; };
namespace _STL {
template<> _Vector_base<Rva00162800Record, allocator<Rva00162800Record> >::_Vector_base(
    unsigned int, const allocator<Rva00162800Record> &);
}

class BfmeRva00166110
    : public _STL::_Vector_base<Rva00162800Record, _STL::allocator<Rva00162800Record> >
{
public:
    BfmeRva00166110(const BfmeRva00166110 &other)
        : _STL::_Vector_base<Rva00162800Record, _STL::allocator<Rva00162800Record> >(
              size_t(other._M_finish - other._M_start),
              reinterpret_cast<const _STL::allocator<Rva00162800Record> &>(other.get_allocator()))
    {
        const BfmePod36 *last = reinterpret_cast<const BfmePod36 *>(other._M_finish);
        const BfmePod36 *first = reinterpret_cast<const BfmePod36 *>(other._M_start);
        BfmePod36 *out = reinterpret_cast<BfmePod36 *>(this->_M_start);
        while (first != last) {
            new (out) BfmePod36(*first);
            ++first;
            ++out;
        }
        this->_M_finish = reinterpret_cast<Rva00162800Record *>(out);
    }

    _STL::allocator<BfmePod36> get_allocator() const
    {
        return _STLP_CONVERT_ALLOCATOR(
            (const _STL::allocator<BfmePod36> &)this->_M_end_of_storage,
            BfmePod36);
    }
};

// The copy above owns its typed get_allocator call; no complete vector
// instantiation is needed for this storage view.

// ?emitCapturedBoneVectorCopy absent-from-retail
void emitCapturedBoneVectorCopy(const BfmeRva00166110 &first,
                                const BfmeRva00166110 &second)
{
    BfmeRva00166110 copy(first);
    new (&copy) BfmeRva00166110(second);
}
