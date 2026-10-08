// cl: /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// stlport

// ??0Rva005DA6F3@@QAE@PAX@Z @0x005DA6F3 (230B).
// Identity inference: calls the rowed Rva005DAA36 base constructor and
// installs a derived vptr. Member offsets and filtering follow target loads.
#include "ascii_string.h"
// The native17B unsigned-max provider is owned by stlport_narrow_istream.cpp
// at0x13740. Declare it here instead of emitting a private compiler variant.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <vector>

enum ObjectID { Rva005DA6F3_ObjectID = 0 };

class Rva005DAA36
{
public:
	Rva005DAA36(void *held);
	virtual void slot0() = 0;
	virtual ~Rva005DAA36() {}

	void *m_held;
};

class ModuleData
{
public:
	virtual ~ModuleData();
};

typedef const ModuleData *PlayerAITypeEntry;

// Native49B provider at4DFCB0 is owned by stlport_moduledatavector_push.cpp.
namespace _STL {
template <> void vector<const ModuleData *>::push_back(const ModuleData *const &);
}

class ThingTemplate : public ModuleData
{
};

class Rva005DA6F3Object
{
public:
	char m_pad00[8];
	ObjectID m_id;
	char m_pad0C[0x24];
	void *m_field30;
};

struct Rva005DA6F3Link
{
	char m_pad00[0x0c];
	const void *m_value;
};

struct Rva005DA6F3OwnerLink
{
	char m_pad00[0x0c];
	const void *m_value;
};

struct Rva005DA6F3Owner
{
	char m_pad00[0x24];
	Rva005DA6F3OwnerLink *m_link;
};

struct Rva005DA6F3Entry
{
	Rva005DA6F3Link *m_link;
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class CommandButton
{
public:
	const ThingTemplate *rva0035B570() const;
	int m_pad00[5];
	int m_type;
	int m_pad18[4];
	Rva005DA6F3Link **m_begin;
	Rva005DA6F3Link **m_end;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);
};

class ControlBar : public Rva0031D5F8
{
};

extern ControlBar *TheControlBar;

class AIUpgradeHeuristicFactoryUnlock : public Rva005DAA36
{
public:
	AIUpgradeHeuristicFactoryUnlock(void *held);

private:
	std::vector<PlayerAITypeEntry> m_modules;
};

AIUpgradeHeuristicFactoryUnlock::AIUpgradeHeuristicFactoryUnlock(void *held)
	: Rva005DAA36(held)
	, m_modules()
{
	Object *object = TheGameLogic->findObjectByID(
		((const Rva005DA6F3Object *)m_held)->m_id);
	const AsciiString *name = object->rva00290E67();
	CommandSet *set = (CommandSet *)TheControlBar->rva0031D5F8(name);
	if (set == 0)
		return;

	for (int i = 0; i < 32; ++i) {
		const CommandButton *button = set->getCommandButton(i);
		if (button == 0)
			continue;
		if (button->m_type != 3 && button->m_type != 4)
			continue;

		bool found = false;
		Rva005DA6F3Link **entry = button->m_begin;
		Rva005DA6F3Link **end = button->m_end;
		if (entry != end) {
			do {
				if (found)
					break;
				const Rva005DA6F3Owner *owner = (const Rva005DA6F3Owner *)
					((const Rva005DA6F3Object *)m_held)->m_field30;
				const void *ownerValue = owner->m_link->m_value;
				const void *entryValue = (*entry)->m_value;
				if (entryValue == ownerValue) {
					m_modules.push_back(button->rva0035B570());
					found = true;
				}
				++entry;
			} while (entry != end);
		}
	}
}
