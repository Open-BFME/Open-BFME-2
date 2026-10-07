// cl: /O1 /arch:SSE /G7 /MD
// ?rva002BED10@Rva002BED10@@QAEXXZ @0x002BED10 89B unlock 2 ready.
// Evidence: 7 callers; rowed HideControlBar 0x00402960; TheLivingWorldLogic TheGameLogic TheLivingWorldManager externs; rowed clear 0x0023D2D8 via GameLogic+0 clearer member; pin-only 0x0021427A; virtuals +0x28 +0x4c +0x1c +0x18 tail; prev Rva002BECCDCalls next InlineDtor.
void HideControlBar(bool b);
class LivingWorldLogic
{
public:
	virtual void v0();
	virtual void v1();
};
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0023D2D8DwordClearer
{
public:
	void clear();
};
class GameLogic
{
public:
	Rva0023D2D8DwordClearer m_clear;
};
extern GameLogic *TheGameLogic;
class LivingWorldManager
{
public:
	void rva0021427A();
};
extern LivingWorldManager *TheLivingWorldManager;
class Rva002BED10
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8(); virtual void v9();
	virtual void v10(int a);
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
	virtual void v19(int a, int b);
	void rva002BED10();
};
void Rva002BED10::rva002BED10()
{
	v10(0);
	v19(1, 1);
	v7();
	HideControlBar(true);
	if (TheLivingWorldLogic)
	{
		TheLivingWorldLogic->v1();
		if (TheGameLogic)
			TheGameLogic->m_clear.clear();
	}
	if (TheLivingWorldManager)
		TheLivingWorldManager->rva0021427A();
	v6();
}
