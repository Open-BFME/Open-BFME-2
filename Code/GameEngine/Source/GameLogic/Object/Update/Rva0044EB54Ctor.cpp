// ??0SpecialAbilityUpdateModuleData@@QAE@XZ
// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
// ??0SpecialAbilityUpdateModuleData@@QAE@XZ at 0x0044EB54 (378 bytes).
// Identity: ModuleFactory registers SpecialAbilityUpdate with the data factory
// at 0x0024A882, which calls this ctor and pushes buildFieldParse 0x0044ED95
// (tools/check_module_registry.py); it was rowed by address as Rva0044EB54.
// Address-derived opaque intermediate default ctor. Target evidence: vtable
// immediate 0x00C3F2A8, 26 this-only module-data ctor callers, a 0xC8 prefix
// shared by derived factories, and the rowed chained parser at 0x0044ED95.
// Ghidra boundary is 378 bytes. Association with the SpecialAbility family
// is structural inference; exact semantic identity is unproven.
#include <stddef.h>
#include "Common/Snapshot.h"


template <typename T> class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);
public:
	StringBase() : m_data(0) {}
private:
	void releaseBuffer();
protected:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() { releaseBuffer(); }
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class OpaqueRefPtr
{
public:
	OpaqueRefPtr() : m_p(0) {}
	~OpaqueRefPtr() { if (m_p) m_p->Release_Ref(); }
private:
	OpaqueRefCounted *m_p;
};

// The four dwords form one layout-only group so the +1C/+20 zero stores precede
// the paired -1 stores, matching the target's schedule without asserting names.
class Rva0044EB54Fields18
{
public:
	__forceinline Rva0044EB54Fields18()
	{
		m_1C = 0;
		m_20 = 0;
		m_18 = -1;
		m_24 = -1;
	}

private:
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
};

class SpecialAbilityUpdateModuleData : public Snapshot
{
public:
	SpecialAbilityUpdateModuleData();
private:
	int m_04;
	OpaqueRefPtr m_08;
	OpaqueRefPtr m_0C;
	OpaqueRefPtr m_10;
	OpaqueRefPtr m_14;
	Rva0044EB54Fields18 m_fields18;
	int m_28;
	int m_2C;
	float m_30;
	OpaqueRefPtr m_34;
	int m_38;
	int m_3C;
	AsciiString m_40;
	AsciiString m_44;
	AsciiString m_48;
	float m_4C;
	float m_50;
	float m_54;
	float m_58;
	int m_5C;
	float m_60;
	int m_64;
	int m_68;
	int m_6C;
	int m_70;
	int m_74;
	int m_78;
	int m_7C;
	int m_80;
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
	int m_94;
	int m_98;
	int m_9C;
	int m_A0;
	int m_A4;
	unsigned char m_A8;
	unsigned char m_A9;
	unsigned char m_AA;
	unsigned char m_AB;
	unsigned char m_AC;
	unsigned char m_AD;
	unsigned char m_AE;
	unsigned char m_AF;
	unsigned char m_B0;
	unsigned char m_B1;
	unsigned char m_B2;
	unsigned char m_B3;
	unsigned char m_B4;
	unsigned char m_B5;
	unsigned char m_B6;
	unsigned char m_B7;
	unsigned char m_B8;
	AsciiString m_BC;
	AsciiString m_C0;
	unsigned char m_C4;
	unsigned char m_C5;
	unsigned char m_C6;
};

SpecialAbilityUpdateModuleData::SpecialAbilityUpdateModuleData()
	: m_08()
	, m_0C()
	, m_10()
	, m_14()
	, m_28(0)
	, m_2C(0)
	, m_30(100.0f)
	, m_34()
	, m_38(0)
	, m_3C(0)
	, m_40()
	, m_44()
	, m_48()
	, m_4C(10000000.0f)
	, m_50(10000000.0f)
	, m_54(0.0f)
	, m_58(0.0f)
	, m_5C(1)
	, m_60(0.0f)
	, m_64(0)
	, m_68(-1)
	, m_6C(0)
	, m_70(-1)
	, m_74(0)
	, m_78(0)
	, m_7C(0)
	, m_80(1)
	, m_84(0)
	, m_88(0)
	, m_8C(0)
	, m_90(0)
	, m_94(0)
	, m_98(0)
	, m_9C(0)
	, m_A0(0)
	, m_A4(0)
	, m_A8(0)
	, m_A9(0)
	, m_AA(0)
	, m_AB(0)
	, m_AC(0)
	, m_AD(0)
	, m_AE(0)
	, m_AF(0)
	, m_B0(0)
	, m_B1(1)
	, m_B2(0)
	, m_B3(0)
	, m_B4(0)
	, m_B5(0)
	, m_B6(0)
	, m_B7(0)
	, m_B8(0)
	, m_BC()
	, m_C0("")
	, m_C4(0)
	, m_C5(0)
	, m_C6(0)
{
}
