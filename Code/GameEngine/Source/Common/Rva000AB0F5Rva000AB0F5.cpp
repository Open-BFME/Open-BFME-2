// cl: /O1 /MD
//
// ?rva000AB0F5@Rva000AB0F5@@QAEPAXH@Z, retail 0x000ab0f5, 76 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Retail 0x000AB0F5 76B get-or-create via map at +0x1C.
// Evidence: ObjectIdMap::find ICF twin at 0x002888D4 plus ObjectLookupMap::findSlot at 0x0041F4E5 plus new4 zeroed. Enclosing class unproven so honest Rva name. 76B same size 32 insns. Remains: xor esi before call vs retail after plus test eax vs cmp eax esi.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "GameLogicObjectLookupView.h"
class ObjectLookupMap { public: Object **findSlot(int *key); };
void *__cdecl operator new(unsigned int size);
class Rva000AB0F5 { public: void *rva000AB0F5(int key); private: char m_pad[0x1C]; };
void *Rva000AB0F5::rva000AB0F5(int key)
{
	char *mapBase = (char *)this + 0x1C;
	ObjectIdNode *node = ((ObjectIdMap *)mapBase)->find((const ObjectID &)key);
	// Codegen: this barrier fixes the native statement/schedule order (found by a per-statement barrier sweep).
	_ReadWriteBarrier();
	void *ret = 0;
	if (node == 0)
	{
		void *p = operator new(4);
		if (p != 0)
		{
			*(void **)p = 0;
			ret = p;
		}
		Object **slot = ((ObjectLookupMap *)mapBase)->findSlot(&key);
		*slot = (Object *)ret;
	}
	else
	{
		Object **slot = ((ObjectLookupMap *)mapBase)->findSlot(&key);
		ret = *slot;
	}
	return ret;
}
