// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// ?rva004B9DA9@TransitionDamageFX@@QAEX_N@Z @0x004B9DA9 367B
// TransitionDamageFX walk over the 0x2C-byte records at +0xD4/+0xD8: each
// record's object (findObjectByID) supplies a status through the virtual at
// slot 8 of its +0x254 module; every AsciiString in the record's +4/+8 array
// goes to Drawable::rva002724FD with status != 3. When the bool argument is
// set the record object's own TransitionDamageFX (findModule with a static
// "TransitionDamageFX" key) recurses with false and a status-3 record with an
// OCL at +0x10 converts its +0x20 bone position and creates the OCL.
// Donor: BFME1 TransitionDamageFX::rva002523E0 (same control flow).
// Recursion at 0x004B9EA9; caller 0x004BA19D.

#include "ascii_string.h"
#include "Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

class Matrix3D;
class Module;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Drawable
{
public:
	void rva002724FD(const AsciiString &name, unsigned char visible, int a, float b, float c);
};

class Rva004B9DA9Status
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual int getStatus();
};

class Thing
{
public:
	Drawable *getDrawable() const;
	void convertBonePosToWorldPos(const Coord3D *bonePos, const Matrix3D *boneTransform,
		Coord3D *worldPos, Matrix3D *worldTransform) const;
};

class Object : public Thing
{
public:
	Module *findDamageModule(NameKeyType key) const { return findModule(key); }

protected:
	Module *findModule(NameKeyType key) const;

public:
	unsigned char m_unmodelled[0x254];
	Rva004B9DA9Status *m_status;
};

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *lifetime);
};

struct Rva004B9DA9Record
{
	ObjectID m_objectID;
	AsciiString *m_nameBegin;
	AsciiString *m_nameEnd;
	void *m_unmodelled0C;
	ObjectCreationList *m_objectCreationList;
	unsigned char m_unmodelled14[0x0C];
	Coord3D m_localPosition;
};

class TransitionDamageFX
{
public:
	void rva004B9DA9(bool applyTransition);

private:
	const void *getModuleData() const { return m_moduleData; }

	void *m_vtable;
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled0C[0xC8];
	Rva004B9DA9Record *m_recordBegin;
	Rva004B9DA9Record *m_recordEnd;
};

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;

void TransitionDamageFX::rva004B9DA9(bool applyTransition)
{
	const void *data = getModuleData();
	if (data == 0)
		return;

	Drawable *draw = m_object->getDrawable();
	if (draw == 0)
		return;

	for (Rva004B9DA9Record *it = m_recordBegin; it != m_recordEnd; )
	{
		Rva004B9DA9Record *record = it++;

		int status = 3;
		Object *object = TheGameLogic->findObjectByID(record->m_objectID);
		if (object != 0)
			status = object->m_status->getStatus();

		for (AsciiString *name = record->m_nameBegin; name != record->m_nameEnd; ++name)
			draw->rva002724FD(*name, status != 3, 0, 0.0f, 0.0f);

		if (applyTransition)
		{
			static NameKeyType transitionDamageKey =
				TheNameKeyGenerator->nameToKey("TransitionDamageFX");

			if (object != 0)
			{
				TransitionDamageFX *transition =
					(TransitionDamageFX *)object->findDamageModule(transitionDamageKey);
				if (transition != 0)
					transition->rva004B9DA9(false);
			}

			if (status == 3 && record->m_objectCreationList != 0)
			{
				Coord3D worldPosition;
				worldPosition.x = record->m_localPosition.x;
				worldPosition.y = record->m_localPosition.y;
				worldPosition.z = record->m_localPosition.z;
				m_object->convertBonePosToWorldPos(&worldPosition, 0, &worldPosition, 0);
				ObjectCreationList *ocl = record->m_objectCreationList;
				if (ocl != 0)
					ocl->create(m_object, m_object, 0);
			}
		}
	}
}
