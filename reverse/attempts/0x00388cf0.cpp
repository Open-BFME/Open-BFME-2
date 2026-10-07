// ?advance@Rva00388CF0Step@@QAEAAU1@XZ
// partial score=1.0 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Complete target388CF0..388CFC12B leaf; exact clean body is banked because
// current PartitionManager's first _M_bump_up definition differs from retail.
// Minimal borrowed receiver; original iterator specialization unknown.
namespace _STL { struct _Bit_iterator_base { void _M_bump_up(); }; }
struct Rva00388CF0Step { Rva00388CF0Step &advance(); };
Rva00388CF0Step &Rva00388CF0Step::advance() {
    ((_STL::_Bit_iterator_base *)this)->_M_bump_up();
    return *this;
}
