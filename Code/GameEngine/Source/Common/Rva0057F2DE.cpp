// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva0057F2DE@@UAE@XZ @0x0057F2DE 111B
// Evidence: unlock lane, vtable 0x00C6F584 at [this], member dtor GameSpyLoginPreferences 0x005CAB59 at +0x58 (0x44 bytes), ReleaseTreeHintRef 0x0007DEEF on +0x9C ptr, releaseBuffer D 0x00036410 at +0xAC and G 0x00036E70 at +0xB0, base dtor pin 0x005248D0; callers 0x0043DAE0/11 0x0057F51C/28 0x004421E1/211.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/GameClient/Rva005248D0.h"

#include "../../Include/GameClient/GameSpyLoginPreferences.h"

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(struct TargetRef00217D4C *p);

struct TreeHintHolder00217D4C
{
	struct TargetRef00217D4C *m_ptr;
	TreeHintHolder00217D4C(TargetRef00217D4C *r)
	{
		m_ptr = r;
		if (r)
			++r->references;
	}
	~TreeHintHolder00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva0057F2DE : public Rva005248D0
{
public:
	Rva0057F2DE(TargetRef00217D4C *ref);
	virtual ~Rva0057F2DE();
	UnicodeString rva0057F3A9();
private:
	GameSpyLoginPreferences m_gameSpy;
	TreeHintHolder00217D4C m_holder;
	int m_a0;		// +0xA0, a combo box window
	int m_a4;
	unsigned char m_a8;
	char m_padA9[3];
	AsciiString m_ascii;
	UnicodeString m_unicode;
};

Rva0057F2DE::Rva0057F2DE(TargetRef00217D4C *ref) : m_holder(ref), m_a0(0), m_a4(0), m_a8(0)
{
	((StringBase<char> &)(m_ascii)).set((const StringBase<char> &)(m_gameSpy.rva005C9FC4()));
}

Rva0057F2DE::~Rva0057F2DE()
{
}

class GameWindow;
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);	// rowed 0x00322D21

// ?rva0057F3A9@Rva0057F2DE@@QAE?AVUnicodeString@@XZ @0x0057F3A9 113B (RET 4;
// caller AptMpGameSetup::HandleClanChange 0x004409D2): the +0xA0 combo box's
// text, trimmed, or UnicodeString::TheEmptyString without a combo box.
UnicodeString Rva0057F2DE::rva0057F3A9()
{
	if (!m_a0)
		return UnicodeString::TheEmptyString;
	UnicodeString text = GadgetComboBoxGetText((GameWindow *)m_a0);
	text.trim();
	return text;
}
