// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// Class-name slots of six BFME 2 group orders (no Zero Hour counterpart).
// Each order's slot 12 hands back its class key from the lazily-resolved
// name cache the group-order factory 0x00354EFC compares against
// (Rva00148F5ECache::get 0x00148F5E on the global cache, a tail jump), and
// slot 2 turns that same key back into its name through TheNameKeyGenerator
// (keyToName 0x00148C95, then AsciiString::str()).
//
//   class                     vtable      slot 2      slot 12     cache
//   SynchronizeGroupOrder     0x00C6A314  0x005468BB  0x0054691C  0x00DD1FC8
//   ChangeStanceGroupOrder    0x00C6A36C  0x00546BC7  0x00546B6B  0x00DD200C
//   GarrisonObjectGroupOrder  0x00C6A3C4  0x00546D56  0x00546CEF  0x00DD2050
//   AttackObjectGroupOrder    0x00C6A420  0x00547018  0x00546FA3  0x00DD2094
//   MoveToGroupOrder          0x00C6A478  0x005472AD  0x005474B9  0x00DD20D8
//   MoveToFormationGroupOrder 0x00C6A4CC  0x00547B64  0x00547BC5  0x00DD211C
//
// The factory's own source names slot 12 getClassKey; slot 2's name is an
// inference from what it returns. Each cache's name string is the class name.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00148F5ECache
{
public:
	NameKeyType get();
};

extern Rva00148F5ECache g_00DD1FC8;	// "SynchronizeGroupOrder"
extern Rva00148F5ECache g_00DD200C;	// "ChangeStanceGroupOrder"
extern Rva00148F5ECache g_00DD2050;	// "GarrisonObjectGroupOrder"
extern Rva00148F5ECache g_00DD2094;	// "AttackObjectGroupOrder"
extern Rva00148F5ECache g_00DD20D8;	// "MoveToGroupOrder"
extern Rva00148F5ECache g_00DD211C;	// "MoveToFormationGroupOrder"

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void slot01();
	virtual const char *getClassName();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual NameKeyType getClassKey();
};

class SynchronizeGroupOrder : public GroupOrder
{
public:
	virtual const char *getClassName();
	virtual NameKeyType getClassKey();
};

class ChangeStanceGroupOrder : public GroupOrder
{
public:
	virtual const char *getClassName();
	virtual NameKeyType getClassKey();
};

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	virtual const char *getClassName();
	virtual NameKeyType getClassKey();
};

class AttackObjectGroupOrder : public GroupOrder
{
public:
	virtual const char *getClassName();
	virtual NameKeyType getClassKey();
};

class MoveToGroupOrder : public GroupOrder
{
public:
	virtual const char *getClassName();
	virtual NameKeyType getClassKey();
};

class MoveToFormationGroupOrder : public GroupOrder
{
public:
	virtual const char *getClassName();
	virtual NameKeyType getClassKey();
};

const char *SynchronizeGroupOrder::getClassName()
{
	return TheNameKeyGenerator->keyToName(g_00DD1FC8.get()).str();
}

NameKeyType SynchronizeGroupOrder::getClassKey()
{
	return g_00DD1FC8.get();
}

const char *ChangeStanceGroupOrder::getClassName()
{
	return TheNameKeyGenerator->keyToName(g_00DD200C.get()).str();
}

NameKeyType ChangeStanceGroupOrder::getClassKey()
{
	return g_00DD200C.get();
}

const char *GarrisonObjectGroupOrder::getClassName()
{
	return TheNameKeyGenerator->keyToName(g_00DD2050.get()).str();
}

NameKeyType GarrisonObjectGroupOrder::getClassKey()
{
	return g_00DD2050.get();
}

const char *AttackObjectGroupOrder::getClassName()
{
	return TheNameKeyGenerator->keyToName(g_00DD2094.get()).str();
}

NameKeyType AttackObjectGroupOrder::getClassKey()
{
	return g_00DD2094.get();
}

const char *MoveToGroupOrder::getClassName()
{
	return TheNameKeyGenerator->keyToName(g_00DD20D8.get()).str();
}

NameKeyType MoveToGroupOrder::getClassKey()
{
	return g_00DD20D8.get();
}

const char *MoveToFormationGroupOrder::getClassName()
{
	return TheNameKeyGenerator->keyToName(g_00DD211C.get()).str();
}

NameKeyType MoveToFormationGroupOrder::getClassKey()
{
	return g_00DD211C.get();
}
