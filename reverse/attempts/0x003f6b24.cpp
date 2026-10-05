// ?_M_insert_overflow@?$vector@UEvaMessageInfo@@V?$allocator@UEvaMessageInfo@@@_STL@@@_STL@@IAEXPAUEvaMessageInfo@@ABU3@ABU__false_type@2@I_N@Z
// partial score=0.99 date=2026-10-05
// ?_M_insert_overflow@EvaMessageInfo-vector
// partial score=0.99 date=2026-10-05
// cl: /O1 /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// vector<EvaMessageInfo>::_M_insert_overflow 0x003F6B24 (183B). Split from
// EvaMessageVectorAssign.cpp: that TU builds with _STLP_USE_STATIC_LIB,
// whose rebound allocator emits the one-argument allocate (no hint push),
// while retail carries the hint push (allocate with 0). Same 28B opaque
// element, same helper pins (allocate 0x000B40EA, copy 0x003F62F5,
// _Construct 0x003F62C8, fill 0x003F631B, Eva copy ctor 0x003F5F89).
#include <vector>

struct EvaMessageInfo
{
	char m_unported[ 28 ];
	EvaMessageInfo();
	EvaMessageInfo( const EvaMessageInfo & );
	~EvaMessageInfo();
	EvaMessageInfo &operator=( const EvaMessageInfo & );
};

template void _STL::vector<EvaMessageInfo>::_M_insert_overflow(
	EvaMessageInfo *, const EvaMessageInfo &, const _STL::__false_type &,
	_STL::vector<EvaMessageInfo>::size_type, bool );
