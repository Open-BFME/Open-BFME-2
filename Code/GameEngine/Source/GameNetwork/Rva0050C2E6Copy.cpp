// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?rva0050C2E6@Rva0050C2E6@@QAEXABV1@@Z @ 0x0050C2E6 175B
// Memberwise copier: 10 AsciiStrings interleaved with 8 dwords, all through
// the rowed StringBase<char>::set (called through an explicit base cast, the
// fleet's proven spelling, so the gate resolves the row instead of the
// header's inline AsciiString::set wrapper). Evidence: address gap between
// ??1IPEnumeration 0x0050C283 and 0x0050C446; frameless esp+0xC ret-4
// __thiscall copy shape; all callees rowed (set 0x000366F0); caller
// 0x0050CD4A passes one pointer; owner class unproven (honest Rva name).
#include "ascii_string.h"

class Rva0050C2E6
{
public:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	unsigned int m_14;
	unsigned int m_18;
	AsciiString m_1C;
	AsciiString m_20;
	unsigned int m_24;
	AsciiString m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	AsciiString m_3C;
	unsigned int m_40;
	AsciiString m_44;
	void rva0050C2E6(const Rva0050C2E6 &other);
	void rva0050C395(Rva0050C2E6 &other);
};

void Rva0050C2E6::rva0050C2E6(const Rva0050C2E6 &other)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&other.m_00);
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&other.m_04);
	((StringBase<char> *)&m_08)->set(*(const StringBase<char> *)&other.m_08);
	((StringBase<char> *)&m_0C)->set(*(const StringBase<char> *)&other.m_0C);
	((StringBase<char> *)&m_10)->set(*(const StringBase<char> *)&other.m_10);
	m_14 = other.m_14;
	m_18 = other.m_18;
	((StringBase<char> *)&m_1C)->set(*(const StringBase<char> *)&other.m_1C);
	((StringBase<char> *)&m_20)->set(*(const StringBase<char> *)&other.m_20);
	m_24 = other.m_24;
	((StringBase<char> *)&m_28)->set(*(const StringBase<char> *)&other.m_28);
	m_2C = other.m_2C;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	((StringBase<char> *)&m_3C)->set(*(const StringBase<char> *)&other.m_3C);
	m_40 = other.m_40;
	((StringBase<char> *)&m_44)->set(*(const StringBase<char> *)&other.m_44);
}

void Rva0050C2E6::rva0050C395(Rva0050C2E6 &other)
{
	((StringBase<char> *)&other.m_00)->set(*(const StringBase<char> *)&m_00);
	((StringBase<char> *)&other.m_04)->set(*(const StringBase<char> *)&m_04);
	((StringBase<char> *)&other.m_08)->set(*(const StringBase<char> *)&m_08);
	((StringBase<char> *)&other.m_0C)->set(*(const StringBase<char> *)&m_0C);
	((StringBase<char> *)&other.m_10)->set(*(const StringBase<char> *)&m_10);
	other.m_14 = m_14;
	other.m_18 = m_18;
	((StringBase<char> *)&other.m_1C)->set(*(const StringBase<char> *)&m_1C);
	((StringBase<char> *)&other.m_20)->set(*(const StringBase<char> *)&m_20);
	other.m_24 = m_24;
	((StringBase<char> *)&other.m_28)->set(*(const StringBase<char> *)&m_28);
	other.m_2C = m_2C;
	other.m_30 = m_30;
	other.m_34 = m_34;
	other.m_38 = m_38;
	((StringBase<char> *)&other.m_3C)->set(*(const StringBase<char> *)&m_3C);
	other.m_40 = m_40;
	((StringBase<char> *)&other.m_44)->set(*(const StringBase<char> *)&m_44);
}
