// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva004FDB57@Rva004FDB57@@QAEXVAsciiString@@@Z, retail 0x004FDB57, 83 bytes.
// Assigns the by-value AsciiString arg into the member at +0x1000 via the
// pinned AsciiString::operator= at 0x000366F0, resolves an int through the
// GameSpy global at 0x00A02320 slot 0x120 (same object as the rowed
// getLocalProfileID slot 0x7C caller), stores it at +0x1004, then releases
// the by-value arg via the rowed StringBase releaseBuffer at 0x00036410.
// Evidence: EH-prolog + state 0/-1 shape; caller 0x005AF5BF; AsciiString is
// 4 bytes here (single-word StringBase) so the arg fits ret 4.
#include "ascii_string.h"


class GameSpyInfoInterface
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual void _M_slot_7c();
	virtual void _M_slot_80();
	virtual void _M_slot_84();
	virtual void _M_slot_88();
	virtual void _M_slot_8c();
	virtual void _M_slot_90();
	virtual void _M_slot_94();
	virtual void _M_slot_98();
	virtual void _M_slot_9c();
	virtual void _M_slot_a0();
	virtual void _M_slot_a4();
	virtual void _M_slot_a8();
	virtual void _M_slot_ac();
	virtual void _M_slot_b0();
	virtual void _M_slot_b4();
	virtual void _M_slot_b8();
	virtual void _M_slot_bc();
	virtual void _M_slot_c0();
	virtual void _M_slot_c4();
	virtual void _M_slot_c8();
	virtual void _M_slot_cc();
	virtual void _M_slot_d0();
	virtual void _M_slot_d4();
	virtual void _M_slot_d8();
	virtual void _M_slot_dc();
	virtual void _M_slot_e0();
	virtual void _M_slot_e4();
	virtual void _M_slot_e8();
	virtual void _M_slot_ec();
	virtual void _M_slot_f0();
	virtual void _M_slot_f4();
	virtual void _M_slot_f8();
	virtual void _M_slot_fc();
	virtual void _M_slot_100();
	virtual void _M_slot_104();
	virtual void _M_slot_108();
	virtual void _M_slot_10c();
	virtual void _M_slot_110();
	virtual void _M_slot_114();
	virtual void _M_slot_118();
	virtual void _M_slot_11c();
	virtual int _M_slot_120(const AsciiString &name);
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva004FDB57 {
	char m_pad[0x1000];
	AsciiString m_name1000;
	int m_id1004;
public:
	void rva004FDB57(AsciiString arg);
};

void Rva004FDB57::rva004FDB57(AsciiString arg)
{
	AsciiString &slot = m_name1000;
	slot = arg;
	m_id1004 = TheGameSpyInfo->_M_slot_120(arg);
}
