// cl: /O1 /Ob0 /DNDEBUG /MD /EHsc
//
// BuffManager / BuffInstance (WorldBuilder GameClient/BuffManager.cpp).
// Target facts: BuffInstance::TurnOff 0x00362609 (thiscall, ret 4) either
// drops the instance's glow effect (+0x18, released through the rowed
// address-named 0x00419BA5) immediately, or, when active (+0x04) and of
// sub type 1 (+0x0C), puts the glow into state 2 (+0x08) to fade; sub type 2
// (WB: BST_EDGE_GLOW) is unsupported and keeps it active.
// BuffManager::TurnOffBuff 0x003626AD turns off the instance for a buff type
// 1..8 (an array of 0x44-byte instances from +0x08, indexed by type).
// The member names follow WorldBuilder's asserts (m_glowMaterial, m_buff);
// their layout is target evidence, the field names past that are inferred.
class Rva00419BA5
{
public:
	void rva00419BA5();

	char m_pad00[0x08];
	int m_state; // +0x08
};

class BuffInstance
{
public:
	void TurnOff(bool immediate);
	bool MakeGlowOutlineBuff(int type, int subtype, void *drawable, int duration, int color, float intensity);

private:
	char m_pad00[0x04];
	bool m_active; // +0x04
	char m_pad05[0x0C - 0x05];
	int m_subType; // +0x0C
	char m_pad10[0x18 - 0x10];
	Rva00419BA5 *m_glow; // +0x18
	char m_pad1C[0x44 - 0x1C];
};

class BuffManager
{
public:
	void TurnOffBuff(int type, bool immediate);

private:
	char m_pad00[0x08];
	BuffInstance m_buffs[9]; // +0x08, by buff type (1..8)
};

void BuffInstance::TurnOff(bool immediate)
{
	if (immediate)
	{
		if (m_glow != 0)
		{
			m_glow->rva00419BA5();
			m_glow = 0;
		}
		m_active = false;
	}
	else if (m_active)
	{
		switch (m_subType)
		{
		case 1:
			if (m_glow != 0)
				m_glow->m_state = 2;
			m_active = false;
			break;
		case 2:
			break;
		default:
			break;
		}
	}
}

void BuffManager::TurnOffBuff(int type, bool immediate)
{
	if (type < 9 && type >= 1)
		m_buffs[type].TurnOff(immediate);
}

// WorldBuilder names this complete 70-byte retail body MakeGlowOutlineBuff.
// The caller 0x003627F9 passes this in ECX, six stack arguments, and a float
// as the final argument; WB 0xF14320 agrees (ret 0x18, BuffManager.cpp:296).
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;

bool BuffInstance::MakeGlowOutlineBuff(int type, int subtype, void *drawable, int duration, int color, float intensity)
{
	if (bfmeRva000387C0())
	{
		_bfme_debugRecordCallsite(1);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "GlowOutline buffs are no longer supported. They need to be removed from an INI file.").CrashDone(2);
	}
	return 0;
}
