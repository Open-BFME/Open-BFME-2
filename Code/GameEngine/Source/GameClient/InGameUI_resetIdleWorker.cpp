// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// InGameUI::resetIdleWorker, primary vtable slot 117.
#include "unicode_string.h"

class GameWindow;
void GadgetButtonSetText(GameWindow *g, UnicodeString text);

class Rva001EB130Holder
{
public:
	void rva001EB130();
	void *head; // +0x00
};

class InGameUI
{
public:
	virtual ~InGameUI();
#define SLOT(N) virtual void slot##N();
	SLOT(001) SLOT(002) SLOT(003) SLOT(004) SLOT(005) SLOT(006) SLOT(007) SLOT(008)
	SLOT(009) SLOT(010) SLOT(011) SLOT(012) SLOT(013) SLOT(014) SLOT(015) SLOT(016)
	SLOT(017) SLOT(018) SLOT(019) SLOT(020) SLOT(021) SLOT(022) SLOT(023) SLOT(024)
	SLOT(025) SLOT(026) SLOT(027) SLOT(028) SLOT(029) SLOT(030) SLOT(031) SLOT(032)
	SLOT(033) SLOT(034) SLOT(035) SLOT(036) SLOT(037) SLOT(038) SLOT(039) SLOT(040)
	SLOT(041) SLOT(042) SLOT(043) SLOT(044) SLOT(045) SLOT(046) SLOT(047) SLOT(048)
	SLOT(049) SLOT(050) SLOT(051) SLOT(052) SLOT(053) SLOT(054) SLOT(055) SLOT(056)
	SLOT(057) SLOT(058) SLOT(059) SLOT(060) SLOT(061) SLOT(062) SLOT(063) SLOT(064)
	SLOT(065) SLOT(066) SLOT(067) SLOT(068) SLOT(069) SLOT(070) SLOT(071) SLOT(072)
	SLOT(073) SLOT(074) SLOT(075) SLOT(076) SLOT(077) SLOT(078) SLOT(079) SLOT(080)
	SLOT(081) SLOT(082) SLOT(083) SLOT(084) SLOT(085) SLOT(086) SLOT(087) SLOT(088)
	SLOT(089) SLOT(090) SLOT(091) SLOT(092) SLOT(093) SLOT(094) SLOT(095) SLOT(096)
	SLOT(097) SLOT(098) SLOT(099) SLOT(100) SLOT(101) SLOT(102) SLOT(103) SLOT(104)
	SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109) SLOT(110) SLOT(111) SLOT(112)
	SLOT(113) SLOT(114) SLOT(115) SLOT(116)
#undef SLOT
	virtual void resetIdleWorker();
private:
	unsigned char m_pad[0x928 - 4];
	Rva001EB130Holder m_holders[20];
	GameWindow *m_window978;
	int m_97C;
};

// Clear the optional button label with UnicodeString::TheEmptyString and reset its display index.
// Clear the twenty per-player list holders beginning at +0x928.
void InGameUI::resetIdleWorker()
{
	if (m_window978 != 0)
		GadgetButtonSetText(m_window978, UnicodeString::TheEmptyString);
	m_97C = -1;
	for (int i = 0; i < 20; ++i)
		m_holders[i].rva001EB130();
}
