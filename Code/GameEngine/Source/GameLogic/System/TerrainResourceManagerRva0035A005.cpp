// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0035A005@Rva0035A292@@QAEXHM@Z, retail 0x0035A005..0x0035A14F (330
// bytes, RET 8). Callback of the matched list-erase body 0x0035A292, which
// passes its object argument and Real unchanged. WB E60D60 is the twin:
// a function-local "TerrainResourceBehavior" module key, Object::findModule,
// world position to cell (floor of offset/cell+0.5) and ceil(radius/cell)
// like the matched sibling 0x00359A0C, a 12-byte visitor (vtable 0x008153D4
// with receiver and the object +74 ID) walked through the existing grid
// traversal 0x0035997F, a zero Real stored through the 14-byte setter
// 0x00481FAF on the module, then the existing 0x00359D99 with the +18 Real
// plus the argument. The visitor's base destructor (unwind funclet target
// 0x005FED52) is the same inline base view the sibling uses. Receiver and
// argument spellings follow the existing address-derived pin; the receiver
// is TerrainResourceManager by its callees but no name is asserted here.
#include <math.h>
#include "TerrainResourceVisitorView.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };
class Module;
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva0035A292;
class Object
{
public:
	float x38() const { return *(const float *)((const char *)this + 0x38); }
	float y3C() const { return *(const float *)((const char *)this + 0x3c); }
	unsigned int id74() const { return *(const unsigned int *)((const char *)this + 0x74); }
protected:
	Module *findModule(NameKeyType) const;
	friend class Rva0035A292;
};

class Rva00481FAFFloatSlot { public: void store(float); };
class Rva000CBA20;
class Rva0035A238 { public: void rva00359D99(Rva000CBA20 *center, float radius); };
class TerrainResourceManager { public: void rva0035997F(int, int, int, void *); };

class Rva00359853: public Rva0035A97EVisitor
{
public:
	Rva00359853(unsigned int field04, unsigned int field08)
	{
		m_field04 = field04;
		m_field08 = field08;
	}
	virtual void slot00(int, int);
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

__forceinline int cellInteger(float value)
{
	int result;
	__asm fld value
	__asm fistp result
	return result;
}

class Rva0035A292
{
public:
	void rva0035A005(int argument, float value);
private:
	char pad00[0x18];
	float m_18;
	float m_originX1C;
	float m_originY20;
	char pad24[0x18];
	float m_cell3C;
};

void Rva0035A292::rva0035A005(int argument, float value)
{
	static NameKeyType key = TheNameKeyGenerator->nameToKey("TerrainResourceBehavior");
	Object *object = reinterpret_cast<Object *>(argument);
	Module *module = object->findModule(key);
	if (module == 0)
		return;
	float x = object->x38() - m_originX1C;
	float y = object->y3C() - m_originY20;
	int cellX = cellInteger((float)floor((x / m_cell3C) + 0.5f));
	int cellY = cellInteger((float)floor((y / m_cell3C) + 0.5f));
	int cellRadius = cellInteger((float)ceil(value / m_cell3C));
	Rva00359853 visitor((unsigned int)this, object->id74());
	reinterpret_cast<TerrainResourceManager *>(this)->rva0035997F(cellX, cellY, cellRadius, &visitor);
	reinterpret_cast<Rva00481FAFFloatSlot *>(module)->store(0.0f);
	reinterpret_cast<Rva0035A238 *>(this)->rva00359D99(reinterpret_cast<Rva000CBA20 *>(object), m_18 + value);
}
