// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
//
// Owner method 0x004FAE34 (118B): sweep a 0x58-stride element array held
// through *(this-4), pushing each element's +0x4C field into the caller's
// ScienceType vector when the 0x002B3325 check on the this-12 sub-view
// passes. The idiv-counted bound is recomputed every iteration because the
// callees can mutate the array.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ScienceType { SCIENCE_INVALID = 0 };
enum EvaMessage { EVA_MESSAGE_UNKNOWN = 0 };

namespace _STL
{
// Use the existing vector<EvaMessage> pin for the ICF-shared four-byte
// enum push_back at 0x002E01C6; the value here is still target ScienceType.
template <> void vector<EvaMessage, allocator<EvaMessage> >::push_back(const EvaMessage &);
}

struct Arg54;

class Rva002B3325
{
public:
	bool rva002B3325(Arg54 *a, Arg54 *b);
};

// Bind to the existing data-ledger owner; keep the retail access view local.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva004FAE34Elem
{
	char m_pad[0x4C];
	int val4C;	// +0x4C collected field (int-sized; pushed as ScienceType)
	char m_pad50[0x08];
};

struct Rva004FAE34Holder
{
	char m_pad[8];
	Rva004FAE34Elem *begin;	// +0x08
	Rva004FAE34Elem *end;	// +0x0C
};

class Rva004FAE34Owner
{
public:
	void rva004FAE34(_STL::vector<ScienceType> *out);
};

void Rva004FAE34Owner::rva004FAE34(_STL::vector<ScienceType> *out)
{
	Rva004FAE34Holder *h = *(Rva004FAE34Holder **)((char *)this - 4);
	Rva004FAE34Elem **arr = (Rva004FAE34Elem **)((char *)h + 8);
	Rva004FAE34Elem *end = arr[1];
	Rva004FAE34Elem *begin = arr[0];
	unsigned int count = (unsigned)(end - begin);
	int i = 0;
	if (count <= 0)
		return;
	Rva004FAE34Owner *sub = (Rva004FAE34Owner *)((char *)this - 12);
	int off = 0;
	do
	{
		if (((Rva002B3325 *)TheLivingWorldLogic)->rva002B3325((Arg54 *)sub, (Arg54 *)(*(int *)((char *)begin + off + 0x4C))))
		{
			ScienceType v = *(ScienceType *)((char *)*arr + off + 0x4C);
			((_STL::vector<EvaMessage> *)out)->push_back((EvaMessage)v);
		}
		begin = *arr;
		count = (unsigned)(arr[1] - begin);
		i++;
		off += 0x58;
	} while (i < count);
}
