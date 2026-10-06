// cl: /DNDEBUG /MD
// ?Rva0043DB3DSet@@YAXE@Z @ 0x0043DB3D, 10 bytes.
// Global byte setter at VA 0x00E03340 from stack byte.
// Evidence: retail mov al [esp+4] mov [0xE03340] al ret; caller 0x5BDB42; neighbours Rva0043DA65Getter and Rva0043DB47DoubleSetter.
// g_Va00E03340: VA 0x00E03340 (.data/bss); zero-filled one-byte flag.
unsigned char g_Va00E03340;

void __cdecl Rva0043DB3DSet(unsigned char v)
{
	g_Va00E03340 = v;
}
