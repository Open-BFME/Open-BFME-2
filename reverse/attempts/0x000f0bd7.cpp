// ?get@Rva000F0BD7NullAdjustField@@QBEPAXXZ
// partial score=0.75 date=2026-10-09
// cl: /O1 /G6
// Disp8 null-adjust getters: __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / test eax,eax / je <ELSE> / add eax,<IMM> / ret
//     <ELSE>: xor eax,eax / ret  OR  mov eax,<GLOBAL> / ret
//
// A dword at a fixed displacement from `this` is null-tested; when nonzero
// it is adjusted by a small immediate, otherwise a default (null or a shared
// global address) is returned. The xor-else form is fourteen bytes, the
// mov-global-else form seventeen. Identity is not recovered: every name is
// derived from its address.
// The donor-supported /G6 also preserves every pre-existing body in this unit.
#define BFME_DISP8_NULL_ADJUST_GETTER(NAME, DISP, ADJ) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return m_ptr ? m_ptr + ADJ : 0; \
	}

struct BfmeNullAdjustDefault;
extern BfmeNullAdjustDefault g_bfmeNullAdjustBBAC1C;
extern BfmeNullAdjustDefault g_bfmeNullAdjustDE0878;

#define BFME_DISP8_NULL_ADJUST_GLOBAL_GETTER(NAME, DISP, ADJ, GLOBAL) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return m_ptr ? m_ptr + ADJ : (int)&GLOBAL; \
	}

BFME_DISP8_NULL_ADJUST_GETTER(Rva002B2252NullAdjustField, 0x08, 0x2C)
BFME_DISP8_NULL_ADJUST_GETTER(Rva002C5FCBNullAdjustField, 0x0C, 8)
BFME_DISP8_NULL_ADJUST_GETTER(Rva002D2548NullAdjustField, 0x08, -4)
BFME_DISP8_NULL_ADJUST_GETTER(Rva002D25ACNullAdjustField, 0x04, -4)
BFME_DISP8_NULL_ADJUST_GLOBAL_GETTER(Rva00136164NullAdjustGlobalField, 0x14, 8, g_bfmeNullAdjustBBAC1C)
BFME_DISP8_NULL_ADJUST_GLOBAL_GETTER(Rva00151733NullAdjustGlobalField, 0x18, 8, g_bfmeNullAdjustBBAC1C)
BFME_DISP8_NULL_ADJUST_GLOBAL_GETTER(Rva0020E3EFNullAdjustGlobalField, 0x08, 0x50, g_bfmeNullAdjustDE0878)
// ?g_bfmeNullAdjustDE0878@@3UBfmeNullAdjustDefault@@A: the global at VA 0xde0878 is ?TheEmptyString@AsciiString@@2V1@B.
#pragma comment(linker, "/alternatename:?g_bfmeNullAdjustDE0878@@3UBfmeNullAdjustDefault@@A=?TheEmptyString@AsciiString@@2V1@B")
// ?g_bfmeNullAdjustBBAC1C@@3UBfmeNullAdjustDefault@@A: the global at VA 0xbbac1c is ?g_Rva0107301CEmptyString@@3QBDB (data_ledger.csv).
#pragma comment(linker, "/alternatename:?g_bfmeNullAdjustBBAC1C@@3UBfmeNullAdjustDefault@@A=?g_Rva0107301CEmptyString@@3QBDB")

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705
// game/GameEngine/Source/Common/R1MemberValueReads.cpp /O1 /arch:SSE /G7
// supplies the nullable interior-pointer expression. Independently, retail
// 0x00661610..0x0066161B is INT3-bracketed, tests incoming ECX, returns ECX+4
// when nonnull and zero otherwise, with no memory reads or stack arguments.
// A free fastcall ABI view represents that one ECX input without invoking a
// member through a null receiver. It does not recover an original member or
// free-function signature, class identity, inheritance or pointed-at type.
void *__fastcall Rva00661610Adjust(void *owner)
{
    if (owner)
        return (char *)owner + 4;
    return 0;
}

// Native 24E301..24E30E is a complete RET0 leaf after the independently
// rowed GateProxyBehavior constructor, and is referenced by slot BEF26C of
// its +0x10 vtable. The constructor independently establishes interface
// positions +0x10 and +0x14. BF1 9cbfb551fe20 UpdateModule::getUpdate and
// other inherited-interface getters supply the semantic guide; their
// identical bytes do not identify this function's original class or name.
// This one-ECX-input ABI view maps the +0x10 receiver to the +0x14 interface,
// preserving null for a null complete object, without adding class views.
void *__fastcall Rva0024E301Adjust(void *baseAt10)
{
    char *complete = (char *)baseAt10 - 0x10;
    return complete ? (char *)baseAt10 + 4 : 0;
}

// Native 68DC6..68DD6 is a complete RET0 body immediately after RET4.
// It reads receiver+4, then that node's +0x0C pointer, and returns either
// pointer-8 or null. These prefix views record only those observed accesses.
// The original iterator, object type and inheritance remain unidentified.
// Clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d lookuptable.cpp,
// using multilist.h's Current_Object and nullable downcast in Peek_Obj,
// emits the same whole 16 bytes with no relocations under /O1 /G7 /arch:SSE2.
// That is a source guide, not proof of a LookupTableClass or RenderObjClass
// identity in BF2. This unit's established /O1 /G6 emits the same body.
struct Rva00068DC6NodePrefix
{
    char m_unknown[0x0C];
    void *m_object;
};

class Rva00068DC6CurrentObject
{
public:
    void *get() const;
    void *m_unknown;
    Rva00068DC6NodePrefix *m_current;
};

void *Rva00068DC6CurrentObject::get() const
{
    void *object = m_current->m_object;
    return object ? (char *)object - 8 : 0;
}

// Clean BF1 f98983a7 HelixContain.cpp/OpenContain.cpp under O1/SSE2/G6
// emits this nullable interface-projection expression. Its OpenContain and
// ExitInterface labels remain donor facts. Native 4647F0..4647FD is a whole
// RET0 leaf after complete RET4 and before the following argument setter.
// It takes one ECX pointer, tests that pointer minus 0x20, and returns the
// pointer plus 0x10 or null, with no memory read or other input. This free
// fastcall ABI view preserves those operations without adding a class view
// or claiming original inheritance, interfaces, signature or function name.
void *__fastcall Rva004647F0Adjust( void *baseAt20 )
{
    char *complete = static_cast<char *>(baseAt20) - 0x20;
    return complete ? static_cast<char *>(baseAt20) + 0x10 : 0;
}

// Clean BF1 f98983a7 Common/Rva002B9E30Get.cpp is the nullable-pointer
// source guide, compiled under /O2 /arch:SSE2 /G6. Its class name and
// original member signature remain unasserted. Native452D78..452D82 is
// a whole RET0 leaf between the matched452D72 constant-name getter's RET
// and known452D82 float getter. It tests ECX-0x20 and returns ECX or zero,
// with no memory read, other input or call. This free fastcall ABI view
// states that physical projection without claiming inheritance or owner.
void *__fastcall Rva00452D78Adjust(void *baseAt20)
{
    char *complete = static_cast<char *>(baseAt20) - 0x20;
    return complete ? baseAt20 : 0;
}

// BF1 f98983a7 hanimmgr.cpp Get_Current_Anim and the fresh O1/SSE2/G6
// donor trial supply this nullable interior-pointer adjustment expression.
// Native F0BD7..F0BE4 is complete after RET4 at F0BD4 and before an indexed
// getter at F0BE4. It reads only receiver+C, returns that pointer minus8
// when nonnull, and otherwise returns null; RET0, no calls/relocations.
// Original HAnim/hash iterator identity, pointee type and inheritance are
// donor leads, not asserted target facts. The prefix states only the access.
class Rva000F0BD7NullAdjustField
{
public:
    void *get() const;
private:
    unsigned char m_unknown[0x0C];
    void *m_pointer;
};

void *Rva000F0BD7NullAdjustField::get() const
{
    return m_pointer ? static_cast<char *>(m_pointer) - 8 : 0;
}
