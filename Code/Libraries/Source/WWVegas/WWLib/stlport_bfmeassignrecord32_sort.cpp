// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport's sort over 32-byte BfmeAssignRecord32 records with a comparator
// function pointer: sort (0x00174870, 67B) and its family 0x00173878 ..
// 0x001746C3. Target evidence: the median it calls is the function-pointer
// median folded at 0x004C6F77 (rowed by hand as Rva004C6F77Median), and every
// body copies, assigns and destroys records through the rowed out-of-line
// copy constructor (0x00173731), assignment (0x00173499) and destructor
// (0x0017330A). The inserts, heap adjust and insertion-sort pieces rowed
// in the stlport_bfmeassignrecord32_*.cpp units are this instantiation's
// bodies too.
//
// The record is declared as stlport_bfmeassignrecord32_insertion_sort.cpp
// declares it, with those three members out of line. The introsort loop's
// range test needs /G7.

#include <algorithm>

struct Rva00087A93 { void *m_data; };

struct BfmeAssignRecord32
{
	BfmeAssignRecord32(const BfmeAssignRecord32 &other);
	BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &other);
	~BfmeAssignRecord32();
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
};

typedef bool (__cdecl *BfmePred)(const BfmeAssignRecord32 &, const BfmeAssignRecord32 &);

template void _STL::sort<BfmeAssignRecord32 *, BfmePred>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmePred);
