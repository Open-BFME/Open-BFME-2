// ?rva00485C19@StatusBitsEldestFrame@@QAE_NPAVObject@@PBURva00485C19Data@@PBW4NameKeyType@@@Z
// partial score=0.97 date=2026-10-05
// ?rva00485C19@StatusBitsEldestFrame@@QAE_NPAVObject@@PBURva00485C19Data@@PBW4NameKeyType@@@Z
// cl: /O1 /DNDEBUG /MD /GX
//
// ?rva00485C19@StatusBitsEldestFrame@@QAE_NPAVObject@@PBURva00485C19Data@@PBW4NameKeyType@@@Z, retail 0x00485C19 109B:
// eldest-of-kind check of the helper member StatusBitsUpgradeIfEldestKindof keeps at +0x1C and
// CreateObjectDieIfEldestKindof at +0x14. Walks the Object's controlling Player's teams (+0x32C)
// through TeamPrototype::rva0039ED9C with the callback 0x004859A2 and answers whether the Object
// found is the given one (dword +0x74).
//
// Evidence: LINK BONUS pin name; called by StatusBitsUpgradeIfEldestKindof 0x004B4AFF and
// CreateObjectDieIfEldestKindof::onDie 0x00485D11 with the module data's eldest-kind block and a
// cached module name key; callees getControllingPlayer 0x0028AFA9 and TeamPrototype 0x0039ED9C.
typedef bool Bool;
typedef int Int;
enum NameKeyType
{
	NK_UNKNOWN = 0
};
struct Rva00485C19Data
{
	int m_00;
};
class Object;
typedef Int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);
Int __cdecl Rva004859A2Callback(Object *obj, void *userData);
class TeamPrototype
{
public:
	Int rva0039ED9C(ObjectIterateFunc func, void *userData);
};
struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};
class Player
{
public:
	unsigned char m_pad00[0x32C];
	PlayerTeamNode *m_head32C;
};
class Object
{
public:
	Player *getControllingPlayer() const;
private:
	unsigned char m_pad00[0x74];
public:
	int m_id74;
};
struct StatusBitsEldestFrame
{
	Bool rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key);
private:
	int m_cachedFrame;
};
struct Rva00485C19Ctx
{
	Object *m_found;
	int m_best;
	const Rva00485C19Data *m_data;
	NameKeyType m_key;
};
// ?rva00485C19@StatusBitsEldestFrame@@QAE_NPAVObject@@PBURva00485C19Data@@PBW4NameKeyType@@@Z present-unmatched
Bool StatusBitsEldestFrame::rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key)
{
	PlayerTeamNode **head;
	{
		Player *player = obj->getControllingPlayer();
		head = (PlayerTeamNode **)((char *)player + 0x32C);
	}
	Rva00485C19Ctx ctx;
	ctx.m_found = 0;
	ctx.m_best = -1;
	ctx.m_data = data;
	ctx.m_key = *key;
	for (PlayerTeamNode *it = (*head)->m_next; it != *head; it = it->m_next)
		it->m_value->rva0039ED9C(Rva004859A2Callback, &ctx);
	if (ctx.m_found != 0 && ctx.m_found->m_id74 == obj->m_id74)
		return true;
	return false;
}
