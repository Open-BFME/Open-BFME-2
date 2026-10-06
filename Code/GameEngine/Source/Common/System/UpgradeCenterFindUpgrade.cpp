// cl: /DNDEBUG /MD /EHsc
//
// ?findUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@ABVAsciiString@@@Z,
// retail 0x0026F26D, 28 bytes. Dedicated TU (Upgrade.cpp itself is
// unstageable: ~20 unmarked defs trip the declare gate; and the callee
// findUpgradeByKey must stay declared-not-defined here or it inlines and
// breaks this body's out-of-line call).
//
// Zero Hour reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source/Common/System/Upgrade.cpp,
// UpgradeCenter::findUpgrade): name-to-key via TheNameKeyGenerator, then
// delegate to the const key walk. Callees resolve via matched rows, no
// pins: nameToKey(AsciiString) 0x009FA65, findUpgradeByKey 0x0026EEB8.

class AsciiString;
class UpgradeTemplate;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
};

// ?findUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@ABVAsciiString@@@Z
const UpgradeTemplate *UpgradeCenter::findUpgrade(const AsciiString &name) const
{
	return findUpgradeByKey(TheNameKeyGenerator->nameToKey(name));
}
