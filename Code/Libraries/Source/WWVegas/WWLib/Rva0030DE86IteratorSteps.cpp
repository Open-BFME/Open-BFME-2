// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Reference: STLport4.5.3 _deque.h prefix ++/-- (BF1ba7 lines186/193)
//. Each target is independently a complete12B
// leaf which passes unchanged ECX to its rowed helper and returns ECX in EAX.
// The helper declarations retain their ledger ABI. BfmePod40/E8/E12 are
// existing opaque provider element names, not newly identified target types.
// Original wrapper names/specializations and allocation extents are unknown.
// These empty borrowed receiver views declare no storage/allocation size.
struct BfmePod40;
struct BfmeE8;
struct BfmeE12;
namespace _STL {
template<class T> struct _Deque_iterator_base {
    void _M_increment();
    void _M_decrement();
};
}
struct Rva0030DE86Step { Rva0030DE86Step &retreat(); };
struct Rva00421EAEStep { Rva00421EAEStep &advance(); };
struct Rva00421FD2Step { Rva00421FD2Step &retreat(); };
struct Rva00549FCCStep { Rva00549FCCStep &retreat(); };
struct Rva0054A1ABStep { Rva0054A1ABStep &advance(); };
struct Rva00585277Step { Rva00585277Step &retreat(); };
//30DE86..30DE92 ->3B3EA8 (35B deque<int> predecessor).
Rva0030DE86Step &Rva0030DE86Step::retreat() {
    ((_STL::_Deque_iterator_base<int> *)this)->_M_decrement();
    return *this;
}
//421EAE..421EBA ->42198C (36B 40-byte-stride successor).
Rva00421EAEStep &Rva00421EAEStep::advance() {
    ((_STL::_Deque_iterator_base<BfmePod40> *)this)->_M_increment();
    return *this;
}
//421FD2..421FDE ->421B68 (33B 40-byte-stride predecessor).
Rva00421FD2Step &Rva00421FD2Step::retreat() {
    ((_STL::_Deque_iterator_base<BfmePod40> *)this)->_M_decrement();
    return *this;
}
//549FCC..549FD8 ->549D7B (35B 8-byte-stride predecessor).
Rva00549FCCStep &Rva00549FCCStep::retreat() {
    ((_STL::_Deque_iterator_base<BfmeE8> *)this)->_M_decrement();
    return *this;
}
//54A1AB..54A1B7 ->549E19 (38B 8-byte-stride successor).
Rva0054A1ABStep &Rva0054A1ABStep::advance() {
    ((_STL::_Deque_iterator_base<BfmeE8> *)this)->_M_increment();
    return *this;
}
//585277..585283 ->421B47 (33B 12-byte-stride predecessor).
Rva00585277Step &Rva00585277Step::retreat() {
    ((_STL::_Deque_iterator_base<BfmeE12> *)this)->_M_decrement();
    return *this;
}
