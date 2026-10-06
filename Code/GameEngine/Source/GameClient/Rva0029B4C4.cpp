// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0029B4C4@Rva0029B4C4@@QAEXXZ @0x0029B4C4 53B leaf called from 0x002A5BE9 AsciiString at +0x1c ptr at +0x5c4 virtual slot 0x1c then clear string via rowed isEmpty/set
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

class Rva0029B4C4
{
public:
	void rva0029B4C4();
private:
	char m_pad[0x1c];
	AsciiString m_name;
	char m_pad2[0x5c4 - 0x20];
	Rva0029B4C4Holder *m_ptr;
};

void Rva0029B4C4::rva0029B4C4()
{
	if (m_ptr != 0) {
		m_ptr->s07();
		m_ptr = 0;
	}
	if (!((const StringBase<char> *)&m_name)->isEmpty())
		((StringBase<char> *)&m_name)->set(*(const StringBase<char> *)&AsciiString::TheEmptyString);
}
