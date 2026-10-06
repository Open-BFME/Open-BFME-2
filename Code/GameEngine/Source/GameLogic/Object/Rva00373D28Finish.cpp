// cl: /EHsc
// ?Rva00373D28Get@@YGPAVRva00373EC6@@PAVObject@@@Z @0x00373D28 29B:
// Free forwarder: Object::rva002931F5(false) at 0x002931F5 then rowed
// ?rva0028F4BC@Object@@QAEPAVRva00373EC6@@XZ on the result, else null.
// Callers at 0x00374277 plus 0x004A3706; landing unblocks 2.
class Rva00373EC6;

class Object
{
public:
	Object *rva002931F5(bool flag);
	Rva00373EC6 *rva0028F4BC();
};

Rva00373EC6 *__stdcall Rva00373D28Get(Object *obj)
{
	Object *mid = obj->rva002931F5(false);
	if (mid != 0)
		return mid->rva0028F4BC();
	return 0;
}
