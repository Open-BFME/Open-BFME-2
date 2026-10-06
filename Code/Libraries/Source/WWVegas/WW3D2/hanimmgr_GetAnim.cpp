// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Get_Anim@HAnimManagerClass@@QAEPAVHAnimClass@@PBD@Z, retail 0x000F0B98, 19 bytes.
// HAnimManagerClass::Get_Anim between Peek_Anim 0xF0B81 and Add_Anim 0xF0BAB
// in hanimmgr.cpp. Donor is ZH hanimmgr.cpp Get_Anim (Peek then Add_Ref).
// Evidence: calls rowed Peek_Anim 0xF0B81; callers at 0xF2C07 0xF2C21 0x10BD02;
// Add_Ref inlines to inc [eax+4] so HAnimClass models vptr +0 refs +4;
// Peek_Anim declared-only so the call stays a call like retail.

class HAnimClass
{
public:
	void Add_Ref() { ++m_refs; }
private:
	void *m_vtable;
	int m_refs;
};

class HAnimManagerClass
{
public:
	HAnimClass *Peek_Anim(const char *name);
	HAnimClass *Get_Anim(const char *name);
};

HAnimClass *HAnimManagerClass::Get_Anim(const char *name)
{
	HAnimClass *anim = Peek_Anim(name);
	if (anim != 0)
	{
		anim->Add_Ref();
	}
	return anim;
}
