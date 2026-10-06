// cl: /MD
//
// ?Rva00547297Init@@YAPAVRva00547223@@PAV1@PAH1@Z, retail 0x00547297, 22 bytes.
// Free-function wrapper over rowed Rva00547223::rva00547223 0x00547223:
// calls the fluent setter for side effect then returns the object pointer
// via reload (separate return, not tail call). Evidence: calls rowed
// 0x00547223, caller 0x005477D8 in 0x005476C8, prev/next share /O1 /MD.

class Rva00547223
{
public:
	Rva00547223 *rva00547223(int *a, int *b);
};

Rva00547223 *__cdecl Rva00547297Init(Rva00547223 *obj, int *a, int *b)
{
	obj->rva00547223(a, b);
	return obj;
}
