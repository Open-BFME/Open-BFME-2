// ?rva004BF40F@Rva004BF40F@@QAEXXZ
// partial score=0.99 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ?rva004BF40F@Rva004BF40F@@QAEXXZ @0x004BF40F 191B lane=chain
// Evidence: calls 0x0028AB75 just landed plus rowed loadPostProcess 0x0058B03E testStatus 0x0004E536 bfmeAtE15 0x006BD980 compare 0x000069B1 StringBase ctor 0x00037BA0 rva0087FA50 0x006BF450 releaseBuffer 0x00036410; vtable slot 1 of 0x0085B038 (ActiveBody ctor); string "Bookend" literal; callers 0x004C202F; prev 0x004BF186 next 0x004BF4CE.
enum ObjectStatusTypes
{
	STATUS_53 = 0x53
};
class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void rva0028AB75(bool flag);
};
struct BfmeShapeE15
{
	char _00[0x1C];
	AsciiString m_name;
};
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int index);
};
class BfmeStrF9;
class BfmeObjF9
{
public:
	void rva0087FA50(const BfmeStrF9 &s, char c);
};
class UpdateModule
{
protected:
	virtual void loadPostProcess();
	friend class Rva004BF40F;
};
class Rva004BF40F
{
public:
	void rva004BF40F();
private:
	char _00[8];
	Object *m_object;
	char _0C[0x30 - 0x0C];
	int m_30;
};
// ?rva004BF40F@Rva004BF40F@@QAEXXZ present-unmatched
void Rva004BF40F::rva004BF40F()
{
	((UpdateModule *)this)->UpdateModule::loadPostProcess();
	Object *obj = m_object;
	if (!obj->testStatus((ObjectStatusTypes)0x53))
		return;
	int sub = *(int *)((char *)obj + 0xD8) - *(int *)((char *)obj + 0xD4);
	obj = (Object *)((char *)obj + 0xA8);
	int count = sub / 36;
	int i = 0;
	if (count <= 0)
		return;
	for (; i < count; ++i)
	{
		BfmeShapeE15 *shape = ((BfmeObjE15 *)obj)->bfmeAtE15(i);
		if (shape->m_name.compare("Bookend") == 0)
			goto found;
	}
	return;
found:
	{
		AsciiString tmp("Bookend");
		((BfmeObjF9 *)obj)->rva0087FA50((const BfmeStrF9 &)tmp, 0);
	}
	m_30 = 0;
	m_object->rva0028AB75(true);
	m_30 = 3;
}
