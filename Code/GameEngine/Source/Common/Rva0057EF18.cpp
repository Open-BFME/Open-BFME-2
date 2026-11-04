// cl: /DNDEBUG /MD
// ?rva0057EF18@AptMpGameRules@@QAEXXZ @0x0057EF18 46B
// Clears the +0x7C widget vector via rowed voidptr erase then rowed Drawable
// resize to 10, clears +0x89, then tail jmps to pinned 0x0057ED2B. Evidence:
// packet disasm with rowed callees 0x0031BD55 and 0x000E6D39; callers
// 0x0057EF95 0x0057F02D and InitGadgets; AptMpGameRules layout in
// AptMpGameRules.cpp; neighbours in Common.
#include "../GameClient/GUI/GUICallbacks/Apt/AptMpGameRulesView.h"

class AptMpGameRules
{
public:
	virtual void v00();
	virtual void ruleChanged(int rule, bool silent);
	void rva0057EF18();
	bool rva0057ED2B();	// row 0x0057ED2B returns bool; the tail call ignores it
private:
	char m_pad04[0x7C - 0x04];
	AptMpGameRulesWidgets m_ruleWindows; // +0x7C
	bool m_88; // +0x88
	bool m_89; // +0x89
};

void AptMpGameRules::rva0057EF18()
{
	m_89 = false;
	_STL::vector<void *> *v = (_STL::vector<void *> *)&m_ruleWindows;
	v->erase(v->begin(), v->end());
	((_STL::vector<Drawable *> *)&m_ruleWindows)->resize(10, (Drawable *)0);
	rva0057ED2B();
}
