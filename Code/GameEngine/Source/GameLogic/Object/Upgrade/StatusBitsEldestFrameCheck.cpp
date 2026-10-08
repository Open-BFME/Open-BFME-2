// cl: /O1 /DNDEBUG /MD /GX
//
// ?rva00485C19@StatusBitsEldestFrame@@QAE_NPAVObject@@PBURva00485C19Data@@PBW4NameKeyType@@@Z, retail 0x00485C19 109B:
// eldest-of-kind check of the helper member StatusBitsUpgradeIfEldestKindof keeps at +0x1C and
// CreateObjectDieIfEldestKindof at +0x14. Walks the Object's controlling Player's teams (+0x32C)
// through TeamPrototype::rva0039ED9C with the callback 0x004859A2 and answers whether the Object
// found is the given one (dword +0x74). Returning the condition directly is
// what gives retail's xor eax,eax / inc eax tail.
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
// The callback 0x004859A2 is the rowed findEldest::func.
struct findEldest
{
	static Int __cdecl func(Object *obj, void *userData);
};
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
Bool StatusBitsEldestFrame::rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key)
{
	PlayerTeamNode **head = &obj->getControllingPlayer()->m_head32C;
	Rva00485C19Ctx ctx;
	ctx.m_found = 0;
	ctx.m_best = -1;
	ctx.m_data = data;
	ctx.m_key = *key;
	for (PlayerTeamNode *it = (*head)->m_next; it != *head; it = it->m_next)
		it->m_value->rva0039ED9C(findEldest::func, &ctx);
	return ctx.m_found != 0 && ctx.m_found->m_id74 == obj->m_id74;
}
