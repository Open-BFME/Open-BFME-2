// ?InitGadgets@AptOnlineLogin@@QAEXPBDPAXPAVGameWindow@@@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /EHsc /MD /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>
#include "unicode_string.h"
extern "C" int __cdecl strcmp(const char *,const char *);
class BfmeObjELB;
extern BfmeObjELB *g_bfmeObjELB;
class GameWindow {public: void *winGetUserData();};
class BfmeKeyLC;
void GadgetListBoxReset(GameWindow *);
void GadgetComboBoxReset(GameWindow *);
void GadgetComboBoxSetMaxChars(GameWindow *,int);
void GadgetComboBoxSetValidationFlags(GameWindow *,int);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *,unsigned short);
void GadgetTextEntrySetValidationFlags(GameWindow *,int);
struct GadgetUserData { unsigned char pad[0x12]; unsigned char m_field12; };
typedef _STL::list<GameWindow *> GameWindowList;
class GameWindowManager {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void registerTabList(GameWindowList);
virtual void clearTabList();
};
extern GameWindowManager *TheWindowManager;
class Rva00222A8BTarget {public:int invoke(void *,const char *,int,const char *,void *,void *,void *,void *);};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
struct AptOnlineLoginOwner { unsigned char pad[0x274]; void *m_window; };
class AptOnlineLogin {public:
 void InitGadgets(const char *,void *,GameWindow *);
 bool rva0056EC54(const UnicodeString &,bool);
 void rva0056FEA8();
private:
 unsigned char pad00[0x58]; AptOnlineLoginOwner *m_context;
 unsigned char pad5c[0xA4-0x5C]; GameWindow *m_control74; GameWindow *m_control78;
 GameWindow *m_control7C; GameWindow *m_dependentControl;
 unsigned char padB4[4]; GameWindow *m_countryList;
 int m_pendingButtonState; int m_fieldMask;
 unsigned char padC4[8]; bool m_ready;
};
void AptOnlineLogin::InitGadgets(
	const char *name, void *, GameWindow *window)
{
	if (g_bfmeObjELB && window)
	{
		GadgetListBoxReset(window);

		if (strcmp(name, "OnlineLogin::Password") == 0)
		{
			m_control7C = window;
			((GadgetUserData *)window->winGetUserData())->m_field12 = 1;
			GadgetTextEntrySetMaxChars((BfmeKeyLC *)window, 0x10);
			GadgetTextEntrySetValidationFlags(window, 0x40);
			rva0056EC54(UnicodeString::TheEmptyString, true);
			m_fieldMask |= 4;
		}
		else if (strcmp(name, "OnlineLogin::Nickname") == 0)
		{
			GadgetComboBoxReset(window);
			GadgetComboBoxSetMaxChars(window, 0xf);
			GadgetComboBoxSetValidationFlags(window, 4);
			m_control78 = window;
			m_fieldMask |= 2;
		}
		else if (strcmp(name, "OnlineLogin::Email") == 0)
		{
			GadgetComboBoxReset(window);
			GadgetComboBoxSetMaxChars(window, 0x10);
			m_control74 = window;
			m_fieldMask |= 1;
		}
		else if (strcmp(name, "OnlineLogin::RememberInfo") == 0)
		{
			m_dependentControl = window;
			m_fieldMask |= 8;
		}
		else if (strcmp(name, "OnlineLogin::CountryList") == 0)
		{
			m_countryList = window;
			rva0056FEA8();
			m_fieldMask |= 0x100;
		}

		else { strcmp(name, "OnlineLogin::TOSText"); }

		if (!m_ready && m_control74 && m_control78 && m_control7C && m_dependentControl)
		{
			GameWindowList tabList;
			m_ready = true;
			tabList.push_front(m_control74);
			tabList.push_back(m_control7C);
			tabList.push_back(m_control78);
			tabList.push_back(m_dependentControl);
			TheWindowManager->clearTabList();
			TheWindowManager->registerTabList(tabList);
		}

		if (m_pendingButtonState == 1 && m_fieldMask == 0x10f)
			m_pendingButtonState = 0;
		void *window2 = m_context->m_window;
		TheRva00222A8BTarget->invoke(window2, "CallChild", 1,
			"EnableButtonDeleteNickname", 0, 0, 0, 0);
	}
}
