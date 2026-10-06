// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005CCD61@Rva005CCD61@@QAEXABVUnicodeString@@@Z @0x005CCD61 51B: inner at outer+8 (thunk 0x005CCE13 mov ecx [ecx+8]); +4 ProcessAnimateWindowSlideFromBottomTimed*, +8 UnicodeString; arg is UnicodeString per caller 0x005D1BA1 lea [ebp-0x14] (format target). Evidence: rowed StringBase compare 0x6A7A and set 0x37150 plus reverse 0x005CB265.
#include "unicode_string.h"

class AnimateWindow;
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual bool reverseAnimateWindow(AnimateWindow *animWin);
};

class Rva005CCD61
{
public:
	void rva005CCD61(const UnicodeString &arg);
private:
	int m_00;
	ProcessAnimateWindowSlideFromBottomTimed *m_process;
	UnicodeString m_str;
};

void Rva005CCD61::rva005CCD61(const UnicodeString &arg)
{
	if (arg.compare(m_str) != 0) {
		if (m_process)
			m_process->ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow((AnimateWindow *)&arg);
		m_str.set(arg);
	}
}

class Rva005CCE13
{
public:
	void rva005CCE13(const UnicodeString &arg);
private:
	int m_00;
	int m_04;
	Rva005CCD61 *m_08;
};

void Rva005CCE13::rva005CCE13(const UnicodeString &arg)
{
	return m_08->rva005CCD61(arg);
}
