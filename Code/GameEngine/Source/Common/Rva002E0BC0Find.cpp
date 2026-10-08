// cl: /O1 /DNDEBUG /MD
//
// ?rva002E0BC0@Rva002E071E@@QAEHH@Z @0x002E0BC0 43B: id-gated compare
// (thiscall, 1 int arg, bool). Looks the id up through landed
// Rva002BA8F1Logic::find on g_00DFEF10 (null index); false on miss,
// else forwards the player to landed rva002E071E (player-to-other
// conversion unproven, explicit cast). Owner reuses Rva002E071E so
// the rowed call resolves.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E2903Player;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;
	int rva002E0BC0(int id);
};

// ?rva002E0BC0@Rva002E071E@@QAEHH@Z
int Rva002E071E::rva002E0BC0(int id)
{
	Rva002E2903Player *p = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(id, 0);
	if (p != 0) {
		return rva002E071E((const Rva002E071E *)p);
	}
	return 0;
}
