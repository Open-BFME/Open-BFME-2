// cl: /DNDEBUG /MD /GX- /Oy-
//
// ?Rva003F1E87DeleteRange@@YA_NPAPAVRva003F0C6C@@0URva003F1E87Holder@@@Z, retail 0x003F1E87 33B
// Delete-range loop returning its by-value flag: for (; first != last; ++first)
// Holder::doDelete(*first) then return holder.flag. Push+lea+call shape proves
// the callee takes this in ECX (&holder at [ebp+0x10]) plus one stack arg;
// free __stdcall Rva003F1A44Delete at 0x003F1A44 is the ICF twin (method
// Holder::doDelete compiles to the same 27B, verified in probe) so the gate
// needs an ICF owner or twin pin there. Caller 0x003F2D03 unclaimed 545B.
// Honest free name with verb DeleteRange.
class Rva003F0C6C;
struct Rva003F1E87Holder
{
	bool flag;
	void doDelete(Rva003F0C6C *p);
};

bool __cdecl Rva003F1E87DeleteRange(Rva003F0C6C **first, Rva003F0C6C **last, Rva003F1E87Holder h)
{
	for (; first != last; ++first)
		h.doDelete(*first);
	return h.flag;
}
