// cl: /O1 /DNDEBUG /MD
// ?rva000E6FC8@Rva000E6FC8@@QAEXXZ @0x000E6FC8 27B.
// GlobalData byte +0xD45 selects 0x14 or 2, then thiscall 0x000E6D94.
// /O1 emits the neg/sbb/and 0x12 plus two inc for the +2 base.

class GlobalData;
extern GlobalData *TheWritableGlobalData;

class Rva000E6FC8
{
public:
	void rva000E6D94(int value);
	void rva000E6FC8();
};

void Rva000E6FC8::rva000E6FC8()
{
	unsigned char flag = *((unsigned char *)TheWritableGlobalData + 0xD45);
	rva000E6D94(flag ? 0x14 : 2);
}
