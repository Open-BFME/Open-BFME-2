// ?rva0035BD5D@Shell@@QAEHXZ
// partial score=1.0 date=2026-10-07
// cl: /O1 /arch:SSE /MD
// ?rva002D9608@Rva002D9608@@QAE_NXZ @ 0x002D9608 26B
// Audio gate: if TheAudio is null return false else return TheAudio slot 0xd0 with m_0C.
// Evidence: honest address name; __thiscall bool via test jne xor al and virtual call [edx+0xd0]; TheAudio data 0x009FE6E8; caller in FUN_006d9fd9; neighbours Weapon.cpp and BfmeStringTailRecord144 dtor.
typedef unsigned int AudioHandle;
class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void _pad27() = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	virtual bool slotD0(int v) = 0;
};
extern AudioManager *TheAudio;
class Shell {char pad[0x68];unsigned m_musicHandle;public:int rva0035BD5D();};
int Shell::rva0035BD5D(){if(TheAudio && TheAudio->slotD0(m_musicHandle))return true;return false;}
