// cl: /O1 /MD /arch:SSE
// ?updateFadeLevel@ScreenCrossFadeFilter@@IAE_NXZ @0x000F633A 193B
// Evidence: named lane pin, BFME1 donor W3DShaderManager.cpp ScreenCrossFadeFilter::updateFadeLevel, caller preRender 0x000F63FB, globals g_00DEBFF8 g_00DEBFFC g_00DEC000 g_00DEBFF4.
extern int g_00DEBFF8;
extern int g_00DEBFFC;
extern int g_00DEC000;
extern float g_00DEBFF4;
extern float g_Va00BBB8D8;

class TacticalView
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void unused8();
	virtual void unused9();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual bool setViewFilterMode(int mode);
	virtual void unused46();
	virtual bool setViewFilter(int filter);
};

extern TacticalView *TheTacticalView;

class ScreenCrossFadeFilter
{
protected:
	bool updateFadeLevel();
};

bool ScreenCrossFadeFilter::updateFadeLevel()
{
	if (g_00DEBFF8 > 0)
	{
		g_00DEC000++;
		int fade = g_00DEC000;
		if (fade < g_00DEBFFC)
		{
			g_00DEBFF4 = (float)fade / (float)g_00DEBFFC;
		}
		else
		{
			g_00DEC000 = 0;
			g_00DEBFF4 = g_Va00BBB8D8;
			g_00DEBFF8 = 0;
			return false;
		}
	}
	else if (g_00DEBFF8 < 0)
	{
		int fade = g_00DEC000;
		if (fade < g_00DEBFFC)
		{
			g_00DEBFF4 = g_Va00BBB8D8 - (float)fade / (float)g_00DEBFFC;
			g_00DEC000++;
		}
		else
		{
			g_00DEBFF4 = 0.0f;
			TheTacticalView->setViewFilterMode(0);
			TheTacticalView->setViewFilter(0);
			g_00DEC000 = 0;
			g_00DEBFF8 = 0;
			return false;
		}
	}
	return true;
}
