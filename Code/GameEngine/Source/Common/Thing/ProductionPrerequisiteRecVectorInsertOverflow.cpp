// cl: /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@UPrereqUnitRec@ProductionPrerequisite@@V?$allocator@UPrereqUnitRec@ProductionPrerequisite@@@_STL@@@_STL@@IAEXPAUPrereqUnitRec@ProductionPrerequisite@@ABU34@ABU__false_type@2@I_N@Z,
// retail 0x004F5165, 183 bytes. Dedicated TU.
//
// STLport 4.5.3 vector<ProductionPrerequisite::PrereqUnitRec>::_M_insert_overflow,
// the growth path of the push_back that RTS/ProductionPrerequisite.cpp already
// matches at 0x004F5243 (called by addUnitPrereq at 0x004F52CB). Sits between
// ??1ProductionPrerequisite at 0x004F5115 and ?clear at 0x004F5227, both in
// ProductionPrerequisiteCtor.cpp.
//
// Byte-identical shape to the AnimSet overflow at 0x001F326F (183B, same /G7
// /arch:SSE + bfmealloc recipe from ObjectCreationList_AnimSetInsertOverflow.cpp):
// this in edi, new length in esi, idiv-by-0x0C count, imul esi,esi,0x0C tail.
// Retail calls the 12-byte helpers at 0x00395928 (allocate), 0x004F5097 (copy),
// 0x002CF99D (_Construct, shared pin), 0x004F50BD (fill_n) and 0x002D044B
// (_M_clear, rowed); the PAU copy/fill this TU emits are byte-identical to the
// PBU bodies there (38B/37B via _Construct), differing only in constness.
//
// Element is 12 bytes, non-trivial via AsciiString at +0x08 (dtor tail-jumps
// to 0x00036410 at 0x00577998). Explicit member (not whole-class)
// instantiation keeps push_back and the other members owned by
// RTS/ProductionPrerequisite.cpp; the helper cascade this emits folds.
//
// Access note: retail's PrereqUnitRec is a public nested struct; the replica
// below is public as well so it mangles identically.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class AsciiString
{
	void *m_data;

protected:
	void releaseBuffer();

public:
	AsciiString(const AsciiString &other);
	~AsciiString() { releaseBuffer(); }
};

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned int m_first;
		unsigned int m_second;
		AsciiString m_name;
		PrereqUnitRec(const PrereqUnitRec &other);
	};
};

namespace _STL
{
template <> void _Construct<ProductionPrerequisite::PrereqUnitRec, ProductionPrerequisite::PrereqUnitRec>(
	ProductionPrerequisite::PrereqUnitRec *, const ProductionPrerequisite::PrereqUnitRec &);
}

template void _STL::vector<ProductionPrerequisite::PrereqUnitRec>::_M_insert_overflow(
	ProductionPrerequisite::PrereqUnitRec *,
	const ProductionPrerequisite::PrereqUnitRec &,
	const _STL::__false_type &,
	unsigned int,
	bool);
