// cl: /DNDEBUG /MD
// ZH donor: GeneralsMD GameClient/MessageStream/SelectionXlat.cpp
// selectFriendsWrapper, verbatim. ?selectFriendsWrapper@@YA_NPAVDrawable@@PAX@Z
// retail 0x00430000 29B: a Zero Hour engine sweep built /O1 /G7 /arch:SSE
// places it once in .text, in SelectionXlat's retail range after the unit's
// hash_map lookup row (0x0042FE40). Its one call pins
// SelectionTranslator::selectFriends at 0x0042FE7F (Ghidra extent 321B).

typedef bool Bool;

class Drawable;
class GameMessage;

class SelectionTranslator
{
public:
	Bool selectFriends( Drawable *draw, GameMessage *createTeamMsg, Bool dragSelecting );
};

//-----------------------------------------------------------------------------
struct SFWRec
{
	SelectionTranslator *translator;
	GameMessage *createTeamMsg;
	Bool dragSelecting;
};

//-----------------------------------------------------------------------------
/*friend*/ Bool selectFriendsWrapper( Drawable *draw, void *userData )
{
	SFWRec *info = (SFWRec *)userData;
	return info->translator->selectFriends(draw, info->createTeamMsg, info->dragSelecting) != 0;
}  // end selectFriendsWrapper
