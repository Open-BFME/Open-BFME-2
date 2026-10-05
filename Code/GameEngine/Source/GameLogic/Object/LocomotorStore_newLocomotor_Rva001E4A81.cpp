// cl: /O1 /MD /EHsc /DNDEBUG
//
// ?newLocomotor@LocomotorStore@@QAEPAVLocomotor@@PBVLocomotorTemplate@@_N@Z
// retail 0x001E4A81, 61 bytes (Ghidra FUN_005e4a81), pinned from
// LocomotorSet::addLocomotor.
//
// Donor: GeneralsMD Locomotor.cpp LocomotorStore::newLocomotor
// (newInstance(Locomotor)(tmpl)); BFME 2 allocates the 0xB0-byte locomotor
// with plain operator new and passes the extra flag to the constructor at
// 0x001E449A.

typedef bool Bool;

class LocomotorTemplate;

class Locomotor
{
public:
	Locomotor(const LocomotorTemplate *tmpl, Bool flag);
private:
	unsigned char m_pad[0xB0];
};

class LocomotorStore
{
public:
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl, Bool flag);
};

Locomotor *LocomotorStore::newLocomotor(const LocomotorTemplate *tmpl, Bool flag)
{
	return new Locomotor(tmpl, flag);
}
