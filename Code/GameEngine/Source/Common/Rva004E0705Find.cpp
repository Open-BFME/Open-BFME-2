// ?rva004E0705@Rva004E0705@@QAEPAVRva002E2903Player@@XZ @0x004E0705 24B
// Player lookup via LivingWorld find 0x002B51F8: follows this+0x24 then +0x13C
// for the id and returns TheRva00DFEF10->find(id, 0). Retail is mov
// eax,[ecx+0x24] / mov eax,[eax+0x13C] / mov ecx,[0x00DFEF10] / push 0 /
// push eax / call 0x002B51F8 / ret (24B).
// Evidence: unlock lane; callers at 0x004E08C2 0x004E248B 0x004E255C 0x004E2615;
// same id-chase plus find pattern as LivingWorldBuildingNuggetSpawnArmy and Rva005F002CImageFind.
// No // cl: line (defaults; neighbours default).

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E2903Player;
class Rva002BA8F1Logic { public: Rva002E2903Player *find(int, unsigned int *); };

#define TheRva00DFEF10 (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)
struct Rva004E0705Inner { char m_pad[0x13C]; int m_id; };
class Rva004E0705
{
public:
	Rva002E2903Player *rva004E0705();
	char m_pad[0x24];
	Rva004E0705Inner *m_ptr;
};
Rva002E2903Player *Rva004E0705::rva004E0705()
{
	int id = m_ptr->m_id;
	return TheRva00DFEF10->find(id, 0);
}
