// flags: region default (reverse/retail_inventory/flag_regions.csv)
#include "../../../../GameEngine/Include/Common/Rva00041004Lock.h"
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??0?$StringBase@G@@QAE@ABV0@@Z=??0?$StringBase@G@@AAE@ABV0@@Z")

//
// ??0?$StringBase@G@@AAE@ABV0@@Z @0x00037050 66B.
// Wide StringBase private copy ctor with thread-safe refcount.
// Evidence: BFME1 string_base.h declares the copy private with Header
// *m_data (refcount at +0) and friends Ascii/UnicodeString; friend
// UnicodeString copy at 0x0000661F calls here; lock layout and
// Enter/Leave shape from the rowed wide-lock getter TU (Rva00041004 with
// m_cs at +0x08 and m_flag at +0x20); callers 40+ including UnicodeString
// copy; callees rowed or pinned (lock getter plus kernel32 IAT).

typedef unsigned short wchar_t;

template <typename T>
class StringBase
{
public:
	StringBase<T> &operator=(const StringBase<T> &src);
private:
	StringBase(const StringBase<T> &src);
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

Rva00041004 *Rva00035DF0Get();
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);

template <>
StringBase<wchar_t>::StringBase(const StringBase<wchar_t> &src)
{
	Rva00041004 *lock = Rva00035DF0Get();
	if (!lock->m_flag) {
		EnterCriticalSection(&lock->m_cs);
	}
	Header *data = src.m_data;
	m_data = data;
	if (data) {
		++data->ref_count;
	}
	if (!lock->m_flag) {
		LeaveCriticalSection(&lock->m_cs);
	}
}
