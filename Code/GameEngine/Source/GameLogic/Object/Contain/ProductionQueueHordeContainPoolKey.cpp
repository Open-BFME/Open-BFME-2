// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@ProductionQueueHordeContain@@UBE?AW4NameKeyType@@XZ @0x4812b9
// (69B): cached pool-name key for ProductionQueueHordeContain. The class
// identity comes from the pool-name string the body pushes
// ("ProductionQueueHordeContain"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };
class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~OpenContain();
};
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class GarrisonContain : public OpenContain
{
public:
	virtual ~GarrisonContain();

private:
	unsigned char m_padFC424[0x424 - 0xFC];
	Coord3D m_garrisonPoint[120];
	unsigned char m_tail[0x9E0 - 0x9C4];
};

class ProductionQueueHordeContain : public GarrisonContain
{
public:
	virtual ~ProductionQueueHordeContain();
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ProductionQueueHordeContain@@UBE?AW4NameKeyType@@XZ
NameKeyType ProductionQueueHordeContain::getModuleNameKey() const
{
	static NameKeyType TheProductionQueueHordeContainPoolKey =
		TheNameKeyGenerator->nameToKey("ProductionQueueHordeContain");
	return TheProductionQueueHordeContainPoolKey;
}

