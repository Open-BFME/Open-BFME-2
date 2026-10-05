// cl: /O1 /MD
// ?rva002B4D41@Rva002B4D41@@QAEXXZ @0x002B4D41 128B: __thiscall void
// countdown driver. Gated on the +0xE8 flag; an armed +0x169 byte plus a
// clear +0x2C0 byte on the 0xDFE1C8 singleton fires the 0x2B35F7 pin; the
// +0xE4 countdown hitting zero fetches a sound name through the rowed
// 0x20E3EF getter (null -> empty literal, else +8) into the rowed PlaySound;
// the +0x16C countdown hitting zero clears the flag. Evidence: retail
//   push ebx/esi; mov esi,ecx; xor ebx,ebx; cmp [esi+0xE8],bl; je END
//   lea eax,[esi+0x169]; cmp [eax],bl; je COUNT1
//   mov ecx,[0xDFE1C8]; cmp [ecx+0x2C0],bl; jne END
//   mov ecx,esi; mov [eax],bl; call 0x2B35F7
//   COUNT1: lea eax,[esi+0xE4]; mov ecx,[eax]; cmp ecx,ebx; jle COUNT2
//   dec ecx; mov [eax],ecx; jg END
//   mov ecx,[esi+0xB0]; call 0x20E3EF; mov eax,[eax]; cmp eax,ebx
//   je DEFAULT; add eax,8; jmp GO; DEFAULT: mov eax,0xBBAC1C
//   GO: push eax; call 0x412A51; pop ecx
//   COUNT2: lea eax,[esi+0x16C]; mov ecx,[eax]; cmp ecx,ebx; je TEST
//   dec ecx; mov [eax],ecx; TEST: cmp [eax],ebx; jne END
//   mov [esi+0xE8],bl; END: pops; ret
// Boundary: range-table 128B ending at 0x2B4DC1 (push esi). Address
// reuse: g_rva00DFE1C8 singleton follows Rva0020EE29Clear.cpp. Names are
// address-derived except rowed callees.
class Rva0020E3EFNullAdjustGlobalField
{
public:
	int get() const;
};

class Rva00DFE1C8Host
{
public:
	char m_pad[0x2C0];
	unsigned char m_2C0;
};

extern Rva00DFE1C8Host *g_rva00DFE1C8;

void __cdecl PlaySound(const char *eventName);

class Rva002B4D41
{
public:
	void rva002B35F7();
	void rva002B4D41();
private:
	char m_pad[0xB0];
	Rva0020E3EFNullAdjustGlobalField *m_b0;
	char m_padB4[0xE4 - 0xB0 - 4];
	int m_countE4;
	unsigned char m_flagE8;
	char m_padE9[0x169 - 0xE9];
	unsigned char m_byte169;
	char m_pad16A[0x16C - 0x16A];
	int m_count16C;
};

void Rva002B4D41::rva002B4D41()
{
	if (m_flagE8 == 0)
		return;
	unsigned char *armed = &m_byte169;
	if (*armed != 0) {
		if (g_rva00DFE1C8->m_2C0 != 0)
			return;
		*armed = 0;
		rva002B35F7();
	}
	int *pcount = &m_countE4;
	if (*pcount > 0) {
		if (--*pcount > 0)
			return;
		int p = m_b0->get();
		const char *sound = *(const char **)p;
		if (sound != 0)
			sound += 8;
		else
			sound = "";
		PlaySound(sound);
	}
	int *pcount2 = &m_count16C;
	if (*pcount2 != 0)
		--*pcount2;
	if (m_count16C == 0)
		m_flagE8 = 0;
}
