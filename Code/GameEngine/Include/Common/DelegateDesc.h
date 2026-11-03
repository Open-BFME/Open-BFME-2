// Target facts (code addresses are RVAs; table addresses are VAs):
// 0x00579E64..0x00579E6C copies descriptor dwords +0/+4 into Impl +8/+0xC; 0x005B4C73 loads that object into ECX and jumps to that callback.
// 0x00527C77..0x00527C90 builds the descriptor from this and callback VA 0x00927827; 0x005D5024..0x005D5036 binds VA 0x009D4F27 the same way.
// 0x005D4D55..0x005D4D6E and 0x002D522C..0x002D5245 build the same pair for callbacks 0x005D4867 and 0x002D2D63; argument-order overloads preserve those stores.
// 0x0021674F, 0x00525AAC, 0x0052AC16, 0x0052AC29 and 0x005B1275 pass the descriptor's stack address and return with RET 8: sizeof is 8.
// 0x00216239 copies Impl +0xC into the object at Impl +8, field +0x38: the descriptor's second word can also carry an integer payload.
// DelegateDesc has no virtual functions, vfptr or base subobject. Its +0 is the bound object, not a table; no ledger row names a DelegateDesc special member.
// 0x00579E48 allocates a separate 0x10-byte Impl. Its table VA 0x00C6ECB4 has deleting destructor 0x005FAA31 and invoker 0x005B4C73.
// 0x002165C7, 0x0052592D, 0x0052A79D and 0x0052A7D8 store the other Impl tables (VAs 0x00BE5898, 0x00C67E80, 0x00C684AC, 0x00C684B4), not DelegateDesc tables.
// Field identifiers are neutral; the original descriptor declaration and callback type names are not established by retail.

#pragma once

#ifndef BFME2_COMMON_DELEGATEDESC_H
#define BFME2_COMMON_DELEGATEDESC_H

struct DelegateDesc
{
	DelegateDesc() {}

	template <class T, class M> DelegateDesc(T *object, M method)
		: field00(object), field04(*reinterpret_cast<void **>(&method))
	{
		typedef char PayloadMustOccupyOneDword[sizeof(M) == 4 ? 1 : -1];
	}

	template <class T, class O, class A> DelegateDesc(void (T::*method)(A), O *object)
		: field00(object), field04(*reinterpret_cast<void **>(&method))
	{
		typedef char PayloadMustOccupyOneDword[sizeof(method) == 4 ? 1 : -1];
	}

	template <class T, class O, class A, class B, class C, class D>
	DelegateDesc(void (T::*method)(A, B, C, D), O *object)
		: field00(object), field04(*reinterpret_cast<void **>(&method))
	{
		typedef char PayloadMustOccupyOneDword[sizeof(method) == 4 ? 1 : -1];
	}

	void *field00;
	void *field04;
};

#endif
