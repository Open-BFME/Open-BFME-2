// cl: /O1 /MD
// ?Rva0040C94ALookup@@YAPAVPlayer@@H@Z @0x0040C94A 35B.
// Id-to-player lookup: pinned Logic id lookup 0x002B488E with the int id,
// null check returning 0, then rowed PlayerList get 0x002A7A6F with Result+0x54.
// Evidence: free cdecl single int arg returning Player pointer; caller at
// 0x0040E53E uses return in eax; ThePlayerList named global shared by 10 TUs.
struct Rva002B488EResult;
class Rva002BA8F1Logic
{
public:
	Rva002B488EResult *rva002B488E(int id);
};
extern Rva002BA8F1Logic *g_009FEF10;
class Player;
class PlayerList
{
public:
	Player *Rva002A7A6F(int id);
};
extern PlayerList *ThePlayerList;
Player *Rva0040C94ALookup(int id)
{
	Rva002B488EResult *result = g_009FEF10->rva002B488E(id);
	if (result == 0)
		return 0;
	return ThePlayerList->Rva002A7A6F(*(int *)((char *)result + 0x54));
}
