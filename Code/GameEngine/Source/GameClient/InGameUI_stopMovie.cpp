// cl: /Ireference/shims/bfme2_ascii /MD
// InGameUI::stopMovie, primary vtable slot 88.
#include "ascii_string.h"

class Rva0029B4C4Holder
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
};

#include "../../Include/GameClient/InGameUI.h"

// Close and null the stream at +0x5C4, then clear the movie name at +0x1C.
void InGameUI::stopMovie()
{
	if (m_videoStream != 0) {
		reinterpret_cast<Rva0029B4C4Holder *>(m_videoStream)->s07();
		m_videoStream = 0;
	}
	if (!((const StringBase<char> *)&field01C)->isEmpty())
		((StringBase<char> *)&field01C)->set(*(const StringBase<char> *)&AsciiString::TheEmptyString);
}
