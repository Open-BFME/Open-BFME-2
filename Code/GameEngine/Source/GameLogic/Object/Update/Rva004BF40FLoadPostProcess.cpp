// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ?rva004BF40F@Rva004BF40F@@QAEXXZ @0x004BF40F 191B lane=chain
// Evidence: calls 0x0028AB75 just landed plus rowed loadPostProcess 0x0058B03E testStatus 0x0004E536 bfmeAtE15 0x006BD980 compare 0x000069B1 StringBase ctor 0x00037BA0 rva0087FA50 0x006BF450 releaseBuffer 0x00036410; vtable slot 1 of 0x0085B038 (ActiveBody ctor); string "Bookend" literal; callers 0x004C202F; prev 0x004BF186 next 0x004BF4CE.
// After the base loadPostProcess, an object with status 0x53 searches its
// shape list (+0xA8) for "Bookend"; on a hit it applies the name through
// 0x006BF450 and toggles the object through 0x0028AB75 with +0x30 set to 0
// then 3. Taking the list's address before its count gives retail's order.
enum ObjectStatusTypes
{
	STATUS_53 = 0x53
};
struct BfmeShapeE15
{
	char _00[0x1C];
	AsciiString m_name;
};
// The shape list at Object +0xA8: 36-byte records between +0x2C and +0x30,
// indexed through 0x006BD980 and searched by name through 0x006BF450.
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int index);
	int getCount() const { return (m_end - m_begin) / 36; }

private:
	char _00[0x2C];
	char *m_begin; // +0x2C
	char *m_end; // +0x30
};
class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void rva0028AB75(bool flag);
	BfmeObjE15 *getShapes() { return &m_shapes; }

private:
	char _000[0xA8];
	BfmeObjE15 m_shapes; // +0xA8
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
void Rva004BF40F::rva004BF40F()
{
	((UpdateModule *)this)->UpdateModule::loadPostProcess();
	Object *obj = m_object;
	if (!obj->testStatus(STATUS_53))
		return;
	BfmeObjE15 *shapes = obj->getShapes();
	int count = shapes->getCount();
	for (int i = 0; i < count; ++i)
	{
		BfmeShapeE15 *shape = shapes->bfmeAtE15(i);
		if (shape->m_name.compare("Bookend") == 0)
		{
			{
				AsciiString name("Bookend");
				((BfmeObjF9 *)shapes)->rva0087FA50((const BfmeStrF9 &)name, 0);
			}
			m_30 = 0;
			m_object->rva0028AB75(true);
			m_30 = 3;
			return;
		}
	}
}
