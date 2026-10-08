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
