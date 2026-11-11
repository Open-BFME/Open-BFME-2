// FormationAssistant: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_FORMATIONASSISTANT_H
#define CANONICAL_FORMATIONASSISTANT_H

struct Coord3D;
class Formation;
class FormationObjectList;
class FormationRowList;
class FormationTemplateRows;
class Player;
class Rva001EB130Holder;

class FormationAssistant
{
public:
	bool getValidObjectList(Rva001EB130Holder *members, Player *player, Rva001EB130Holder *valid);
	int rva00422D1C(int key);
	bool rva0042481E(FormationRowList *rows, const FormationTemplateRows *cells, FormationObjectList *objects);
	Formation *rva00424E77(int formationType, Rva001EB130Holder *objects, const Coord3D *pos);
};

#endif // CANONICAL_FORMATIONASSISTANT_H
