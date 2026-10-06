// cl: /DNDEBUG /MD /GX-
// ?rva004383EB@Rva004383EB@@QAEHPAVObject@@@Z @0x004383EB (130B): Free-standing check via ThePlayerList plus Team relationship plus bfmeAskRV plus Object status gates returning 0 1 3 4 5. Evidence: caller 0x004384A3 thiscall with 1 stack arg plus ecx; rowed getRelationship 0x003A0FD2 bfmeAskRV 0x002AA231 rva0028F518 0x0028F518 rva002933CD 0x002933CD testStatus 0x0004E536; ThePlayerList global; ret 4 one stack arg.
enum Relationship
{
	REL_DUMMY = 0
};
class Team
{
public:
	Relationship getRelationship(const Team *other) const;
};
class BfmeMemberRV
{
public:
	bool bfmeAskRV();
public:
	char m_pad[0x2ec];
	Team *m_2ec; // +0x2ec
};
class PlayerList
{
public:
	char m_pad[0x10];
	BfmeMemberRV *m_10; // +0x10
};
extern PlayerList *ThePlayerList;
enum ObjectStatusTypes
{
	STATUS_5F = 0x5f
};
class Object
{
public:
	bool rva0028F518();
	int rva002933CD();
	bool testStatus(ObjectStatusTypes t) const;
public:
	char m_pad[0x304];
	Team *m_304; // +0x304
};
class Rva004383EB
{
public:
	int rva004383EB(Object *obj);
};

int Rva004383EB::rva004383EB(Object *obj)
{
	PlayerList *pl = ThePlayerList;
	Team *team1 = obj->m_304;
	BfmeMemberRV *mem = pl->m_10;
	int rel;
	if (team1) {
		Team *team2 = mem->m_2ec;
		rel = (int)team1->getRelationship(team2);
	} else {
		rel = 1;
	}
	if (!mem->bfmeAskRV()) {
		rel = 2;
	}
	if (obj->rva0028F518()) {
		if (rel != 2) {
			return 5;
		} else {
			return 1;
		}
	}
	if (!(unsigned char)obj->rva002933CD()) {
		return 0;
	}
	if (!obj->testStatus(STATUS_5F)) {
		if (rel == 2) {
			return 4;
		} else {
			return 3;
		}
	} else {
		return 0;
	}
}
