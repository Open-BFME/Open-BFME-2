// cl: /O2 /G7 /GX-
// ?Rva00129670Inc@@YAXXZ @0x00129670 8B over 0x00DEE8C0 (add [mem],1; ret).
// Gap between ?Rva00129660Get (0x00129660/6 over 0x00DEE894) and
// ?Rva00129680Get (0x00129680/6 over 0x00DEE8A0) in GlobalGetterSingles.cpp
// (/GX- gives inc FF05 7B; retail is add 8305 8B so /O2 /G7 per flag probe).
extern int g_Va00DEE8C0;

void Rva00129670Inc(void)
{
    ++g_Va00DEE8C0;
}
