// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$copy_backward for deque<BfmeE12> non-const iterators, retail 0x00585A18
// (63B). Same placeholder-element convention as the sibling
// stlport_deque_e12_o1.cpp (BfmeE12 names only the 12-byte element size).
//
// This TU deliberately uses the STOCK vendor headers (no bfmealloc shim).
// The shim marks the __copy_backward_aux forwarder __forceinline, which
// inlines it and calls one layer deeper with an extra distance-pointer
// push (65B). Stock headers keep it a plain inline, which /O1 leaves out
// of line, so the call reaches the ledger's aux row at 0x00422C67 by its
// real name. The entry is an explicit instantiation of the primary
// template, so the tag stays the `_BothPtrType::_Ret()` prvalue: an empty
// type needing no storage, cl materializes its address as the hidden
// return-pointer slot plus three (lea eax,[ebp+0x0b]).
#include <deque>

struct BfmeE12 { float x; float y; float z; };

typedef _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > BfmeE12DequeIterator;

template BfmeE12DequeIterator _STL::copy_backward<BfmeE12DequeIterator, BfmeE12DequeIterator>(
	BfmeE12DequeIterator,
	BfmeE12DequeIterator,
	BfmeE12DequeIterator);
