// cl: /DNDEBUG /MD
// ?Rva003F10D0Pick@@YAXPAH0@Z @0x003F10D0 44B
// ?Rva003F10FCPick@@YAXPAH0@Z @0x003F10FC 44B
// ?Rva003F1128Pick@@YAXPAH0@Z @0x003F1128 44B
// ?Rva003F1154Pick@@YAXPAH0@Z @0x003F1154 44B
// Stack-pick pairs via ebp/esp low bits into two parallel int[4] tables.
// Inline asm for mov t,ebp/esp: plain C cannot read them, so __asm
// is the only way; surrounding movs are plain C assignments.
// Siblings of Rva0056ED34Pick 44B per Rva0056EDBAPick.cpp precedent;
// unlock 0x003F17D6/0x003F1863/0x003F18F0/0x003F1976 obfuscated inits.
// Evidence: and [ebp-4]0 mov [ebp-4]ebp/esp and-3 shl-2 indexed loads.
// g_Va00DC15EC: matched references place it at VA 0xdc15ec (retail .data contents).
int g_Va00DC15EC[4] = {
	-1603791285, 0x4359050b, 0x5bc6af4b, 0x6a41934b
};
// g_Va00DC15DC: matched references place it at VA 0xdc15dc (retail .data contents).
int g_Va00DC15DC[4] = {
	-1597750262, 0x3f9454a, 0x1f66af0a, 0x2ec99b0a
};
// g_Va00DC160C: matched references place it at VA 0xdc160c (retail .data contents).
int g_Va00DC160C[4] = {
	-888970165, -660034293, 0x32fde04b, -341853173
};
// g_Va00DC15FC: matched references place it at VA 0xdc15fc (retail .data contents).
int g_Va00DC15FC[4] = {
	-1761380854, -2144555702, 0x3259ba0a, -141054390
};
// g_Va00DC162C: matched references place it at VA 0xdc162c (retail .data contents).
int g_Va00DC162C[4] = {
	-1716753461, -888970165, -660034293, 0x32fde04b
};
// g_Va00DC161C: matched references place it at VA 0xdc161c (retail .data contents).
int g_Va00DC161C[4] = {
	-2128600182, -1761380854, -2144555702, 0x3259ba0a
};
// g_Va00DC164C: matched references place it at VA 0xdc164c (retail .data contents).
int g_Va00DC164C[4] = {
	-1645147189, -1603791285, 0x4359050b, 0x5bc6af4b
};
// g_Va00DC163C: matched references place it at VA 0xdc163c (retail .data contents).
int g_Va00DC163C[4] = {
	-915078262, -1597750262, 0x3f9454a, 0x1f66af0a
};
void __cdecl Rva003F10D0Pick(int *out1, int *out2);
void __cdecl Rva003F10D0Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, ebp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DC15EC[i];
	*out2 = g_Va00DC15DC[i];
}
void __cdecl Rva003F10FCPick(int *out1, int *out2);
void __cdecl Rva003F10FCPick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, ebp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DC160C[i];
	*out2 = g_Va00DC15FC[i];
}
void __cdecl Rva003F1128Pick(int *out1, int *out2);
void __cdecl Rva003F1128Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, esp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DC162C[i];
	*out2 = g_Va00DC161C[i];
}
void __cdecl Rva003F1154Pick(int *out1, int *out2);
void __cdecl Rva003F1154Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, esp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DC164C[i];
	*out2 = g_Va00DC163C[i];
}
