// cl: /O2 /G7 /GX-
// ?Rva00129510Inc@@YAXXZ @0x00129510 8B over 0x00DEE8B0 (add [mem],1; ret).
// Same /O2 /G7 add-idiom as Rva00129670Inc (retail add 8305 8B not inc FF05).
extern int g_Va00DEE8B0;

void Rva00129510Inc(void)
{
    ++g_Va00DEE8B0;
}
