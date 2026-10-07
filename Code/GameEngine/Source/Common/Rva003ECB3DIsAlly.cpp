// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /Os
// ?Rva003ECB3DIsAlly@@YAHPBVPlayer@@0@Z @0x003ECB3D 21B
// Banked attempt reverse/attempts/0x003ecb3d.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// ?Rva003ECB3DIsAlly@@YAHPBVPlayer@@0@Z @0x003ECB3D 21B via Ally-check twin
// Evidence: push arg2/mov ecx arg1/call rowed ?getRelationship@Player@@QBE?AW4Relationship@@PBV1@@Z 0x2AC3E0
// then dec/dec/neg/sbb/inc for ==ALLIES (2); Relationship ENEMIES=0 NEUTRAL=1 ALLIES=2 per PlayerGetRelationship;
// callback constant at 0x3ED144; prev/next Rva003ECA69ElementClear same dir/flags.
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
class Player
{
public:
	Relationship getRelationship(const Player *that) const;
};
int Rva003ECB3DIsAlly(const Player *a, const Player *b)
{
	int r = a->getRelationship(b);
	--r;
	--r;
	return r == 0;
}
