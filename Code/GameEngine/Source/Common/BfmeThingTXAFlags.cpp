// BfmeThingTXA singleton flag helpers: tiny byte accessors around the
// DEC3C8/DEC3C9 lifecycle bytes (sibling to the DEC3DC object slot, proven
// to hold the global BfmeThingTXA by the creator at 0x1185F4).
// Shapes (all frameless, defaults):
//   set1:  mov byte [addr],1 / ret                                    (8B)
//   setv:  mov al,[esp+4] / mov [addr],al / ret                       (10B)
//   getv:  mov al,[addr] / ret                                         (6B)
//   all3:  cmp-chain over the slot plus both bytes, 1/0, shared false (35B)
//   has:   xor / cmp [slot],eax / setne al / ret                      (12B)
// Identity beyond the slot is not recovered, so flag bodies keep Rva names
// (GlobalFlagClearers precedent); the slot test uses its proven meaning.
// No // cl: line (defaults first; split on mismatch).
extern unsigned char g_Va00DEC3C8;
extern unsigned char g_Va00DEC3C9;

void Rva00117A60SetFlag(void)
{
	g_Va00DEC3C8 = 1;
}

void Rva00117A70SetFlag(unsigned char value)
{
	g_Va00DEC3C9 = value;
}

unsigned char Rva00117A80GetFlag(void)
{
	return g_Va00DEC3C9;
}
