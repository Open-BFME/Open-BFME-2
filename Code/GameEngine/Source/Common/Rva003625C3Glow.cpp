// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// ?Rva003625C3Glow@@YGDHHHHHH@Z retail 0x003625C3 70 bytes. Free __stdcall
// 6-int char-0 stub logging unsupported GlowOutline buffs. Evidence: donor
// game/GameEngine/Source/Common/BfmeConv1362.cpp bfmeGoVHK, caller 0x003627F9
// passes 6 slots ret 0x18, string GlowOutline buffs are no longer supported,
// rowed callees 0x000387C0 0x00038790, Debug slots 0x60 0x6c 0x38 0x4c.

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

char __stdcall Rva003625C3Glow(int a1, int a2, int a3, int a4, int a5, int a6)
{
	if (bfmeRva000387C0())
	{
		_bfme_debugRecordCallsite(1);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "GlowOutline buffs are no longer supported. They need to be removed from an INI file.").CrashDone(2);
	}
	return 0;
}
