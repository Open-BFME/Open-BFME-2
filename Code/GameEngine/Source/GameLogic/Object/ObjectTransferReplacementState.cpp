// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX
//
// Object::bfmeTransferReplacementState, retail 0x002928B5 (180 bytes): when an
// Object is replaced (HordeContain slot 99 calls it on a status-0x3E Object with
// the replacement), hands the name at +0x308 to the replacement through the
// rowed by-value setter 0x0029173E, then, when both carry a
// "TemporarilyDefectUpdate", re-points the replacement's at the old module's
// defector (+0x28, by ID) with the old end frame (+0x20) through the rowed
// 0x004CC795. Target facts: the string, the +0x308 setter, the module offsets
// and the call order are read from retail. Donor: BFME 1's
// Object_bfmeTransferReplacementState.cpp (retail 0x001C5620) has this exact
// shape; its name and the module field names are carried from it.

#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

enum NameKeyType
{
	INVALID_NAME_KEY = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Object;
class Module;

extern GameLogic *TheGameLogic;

// TemporarilyDefectUpdate's transfer entry, under the owner name its row
// (0x004CC795) carries.
class Rva004CC829
{
public:
	void rva004CC795(Object *defector, unsigned int endFrame);
};

struct TemporarilyDefectUpdateFields
{
	unsigned char m_pad00[0x20];
	unsigned int m_endFrame; // +0x20
	unsigned int m_startFrame; // +0x24
	ObjectID m_defectorID; // +0x28
};

// The +0x308 name setter, under the owner name its row (0x0029173E) carries.
class Rva0029173EAsciiField
{
public:
	void rva0029173E(AsciiString value);
};

class Object
{
public:
	void bfmeTransferReplacementState(Object *replacement);
protected:
	Module *findModule(NameKeyType key) const;
private:
	unsigned char m_pad000[0x308];
	AsciiString m_name; // +0x308
};

// ?bfmeTransferReplacementState@Object@@QAEXPAV1@@Z @0x002928B5
void Object::bfmeTransferReplacementState(Object *replacement)
{
	if (replacement != 0)
	{
		((Rva0029173EAsciiField *)replacement)->rva0029173E(m_name);

		static NameKeyType key_TemporarilyDefectUpdate =
			TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");

		TemporarilyDefectUpdateFields *oldUpdate =
			(TemporarilyDefectUpdateFields *)findModule(key_TemporarilyDefectUpdate);
		TemporarilyDefectUpdateFields *newUpdate =
			(TemporarilyDefectUpdateFields *)replacement->findModule(key_TemporarilyDefectUpdate);

		if (newUpdate != 0 && oldUpdate != 0)
		{
			Object *defector = TheGameLogic->findObjectByID(oldUpdate->m_defectorID);
			if (defector != 0)
				((Rva004CC829 *)newUpdate)->rva004CC795(defector, oldUpdate->m_endFrame);
		}
	}
}
