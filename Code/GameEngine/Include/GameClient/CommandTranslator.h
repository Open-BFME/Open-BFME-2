// CommandTranslator: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_COMMANDTRANSLATOR_H
#define CANONICAL_COMMANDTRANSLATOR_H

class CommandButton;
struct Coord3D;
class Drawable;
class GameMessage;

class CommandTranslator
{
public:
	const CommandButton *rva0042970A(int);
	void rva0042AF97(GameMessage *);
private:
	int issueFireWeaponCommand(const CommandButton *command, int commandType, Drawable *target, const Coord3D *pos);
};

#endif // CANONICAL_COMMANDTRANSLATOR_H
