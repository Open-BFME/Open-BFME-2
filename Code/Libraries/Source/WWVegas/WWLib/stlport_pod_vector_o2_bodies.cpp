// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector members for placeholder POD elements, as
// emitted at /O2. BfmePod36 stands for the real 36-byte element; the placed
// body's stride fixes the size. No retail caller is claimed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Retail's 36-byte storage constructor is rowed in StlVectorRva00162800.cpp.
// The captured-bone copy calls that same 0x00162800 body. Keep this spelling
// external so the linker uses the verified constructor instead of this TU's
// different implicit copy; the allocator is stateless in both views.
struct BfmePod36;
namespace _STL { template <> _Vector_base<BfmePod36, allocator<BfmePod36> >::_Vector_base(unsigned int, const allocator<BfmePod36> &); }
// Suppress this TU's non-retail copy of ??$uninitialized_fill_n@PAUBfmePod36@@IU1@@_STL@@YAPAUBfmePod36@@PAU1@IABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * uninitialized_fill_n<BfmePod36 *,unsigned int,BfmePod36>(BfmePod36 *,unsigned int,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_fill_insert(BfmePod36 *,unsigned int,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PAU1@00ABU__false_type@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __uninitialized_copy<BfmePod36 *,BfmePod36 *>(BfmePod36 *,BfmePod36 *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PBUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PBU1@0PAU1@ABU__false_ty:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __uninitialized_copy<BfmePod36 const *,BfmePod36 *>(BfmePod36 const *,BfmePod36 const *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__copy_backward@PAUBfmePod36@@PAU1@H@_STL@@YAPAUBfmePod36@@PAU1@00ABUrandom_access_iter:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __copy_backward<BfmePod36 *,BfmePod36 *,int>(BfmePod36 *,BfmePod36 *,BfmePod36 *,random_access_iterator_tag const &,int *); }
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod36@@U1@@_STL@@YAXPAUBfmePod36@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void _Construct<BfmePod36,BfmePod36>(BfmePod36 *,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ??$__copy_backward_ptrs@PAUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PAU1@00ABU__false_type@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __copy_backward_ptrs<BfmePod36 *,BfmePod36 *>(BfmePod36 *,BfmePod36 *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXPAUBfm:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_insert_overflow(BfmePod36 *,BfmePod36 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAUBfmePod36@@IU1@@_STL@@YAPAUBfmePod36@@PAU1@IABU1@ABU__false_t:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __uninitialized_fill_n<BfmePod36 *,unsigned int,BfmePod36>(BfmePod36 *,unsigned int,BfmePod36 const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$fill@PAUBfmePod36@@U1@@_STL@@YAXPAUBfmePod36@@0ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void fill<BfmePod36 *,BfmePod36>(BfmePod36 *,BfmePod36 *,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ?_M_set@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXPAUBfmePod36@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_set(BfmePod36 *,BfmePod36 *,BfmePod36 *); }
// Suppress this TU's non-retail copy of ?size@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QBEIXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> unsigned int vector<BfmePod36,allocator<BfmePod36> >::size() const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAUBfmePod36@@U1@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void _STLP_alloc_proxy<BfmePod36 *,BfmePod36,allocator<BfmePod36> >::deallocate(BfmePod36 *,unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmePod36@@U1@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEP:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * _STLP_alloc_proxy<BfmePod36 *,BfmePod36,allocator<BfmePod36> >::allocate(unsigned int); }
// The 36-byte record, spelled as htree.cpp spells it.
struct BfmeCapturedBoneRotation
{
    float X, Y, Z, W; BfmeCapturedBoneRotation &operator=(const BfmeCapturedBoneRotation &q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;}
};

struct BfmeCapturedBoneTranslation
{
    float X, Y, Z;
    BfmeCapturedBoneTranslation() {}
    BfmeCapturedBoneTranslation &operator=(const BfmeCapturedBoneTranslation &v){X=v.X;Y=v.Y;Z=v.Z;return *this;}
    BfmeCapturedBoneTranslation(const BfmeCapturedBoneTranslation &v)
        : X(v.X), Y(v.Y), Z(v.Z) {}
};

struct CapturedTransform{BfmeCapturedBoneRotation Rotation;BfmeCapturedBoneTranslation Translation;};

struct BfmePod36{int Index;CapturedTransform Transform;bool WorldSpace;};

// The random-access copy helper, row 0x00161350, emitted as htree.cpp emits it.
template BfmePod36 *_STL::__copy<BfmePod36 *,BfmePod36 *,int>(BfmePod36 *,BfmePod36 *,BfmePod36 *,const _STL::random_access_iterator_tag &,int *);
// Emit the owned erase operations and their copy helper, not unused vector
// constructors whose non-retail copies can win selection for other units.
template BfmePod36 *_STL::vector<BfmePod36>::erase(BfmePod36 *);
template BfmePod36 *_STL::vector<BfmePod36>::erase(BfmePod36 *, BfmePod36 *);
