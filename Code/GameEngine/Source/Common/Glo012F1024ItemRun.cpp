// cl: /DNDEBUG /MD /EHsc

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Glo012F1028Type
{
public:
	void j_00008c0b(void);
};

// Rows 0x00565148 and 0x005651D2 are LivingWorldCampaignAct members.
class LivingWorldCampaignAct
{
public:
	void rva00564EC0(void);
	void rva00565106(void);
	void SetPlayerControlOfArmies(void);
	void MoveArmies(void);
	void rva00565148(void);
	void rva005651D2(void);
};

class Glo012F1024Item
{
public:
	bool j_0000ca59(void);
	void j_0002a969(void);
	void run(void);
};

void Glo012F1024Item::run(void)
{
	if (j_0000ca59())
		(*(Glo012F1028Type **)&TheLivingWorldLogic)->j_00008c0b();
	j_0002a969();
	((LivingWorldCampaignAct *)this)->rva00565148();
	((LivingWorldCampaignAct *)this)->rva005651D2();
}
