// Target facts (BFME2 retail; function addresses are RVAs, table addresses are VAs):
// 0x006587A0 returns the pointer at VA 0x00E09FBC. Its factory 0x006589D0 allocates 0x14 bytes, installs table 0x00CE157C at +0 and callback 0x00A587B0 at +4, and clears +8, +0x0C and +0x10. Constructor 0x006587C0 writes the same layout.
// Table 0x00CE157C has six slots: 0x006586F0, 0x00658710, 0x00658820, 0x00658890, 0x00658930 and 0x006587E0. The next word at VA 0x00CE1594 starts an assertion string.
// Slot 0 stores its second argument at +4 and its first at +8 (ret 8). Slot 1 calls the +4 callback with the +8 context and its text argument (ret 4).
// Slot 2 takes this on the stack, an unsigned buffer requirement and a format followed by varargs; 0x00658820 compares the requirement against +0x10, uses the +0x0C buffer for vsprintf, and dispatches slot 1.
// Slot 3 (0x00658890) formats an expression, file and line, returns zero and pops 12 bytes. Slot 4 (0x00658930) formats an error code, expression, file and line, returns zero and pops 16 bytes. These bodies and their existing ledger rows establish fail/report/log behavior; the original API names remain unknown.
// Slot 5 (0x006587E0) restores 0x00CE157C, frees the +0x0C buffer and conditionally deletes 0x14 bytes. Shutdown 0x006586A0 invokes this slot with flags 1. Nondeleting teardown 0x006586D0 restores the same table.
// The nearby constructor 0x006586C0 installs 0x00C078DC, whose first five words are purecall. It does not construct the singleton returned by 0x006587A0; neither singleton construction nor teardown installs that abstract table. No base-class identity is established for this layout.

#pragma once

#ifndef BFME2_RVA007EB810DIAG_H
#define BFME2_RVA007EB810DIAG_H

struct Rva007EB810Diag
{
	virtual void vslot00(int valueAt08, int valueAt04);
	virtual void report(const char *text);
	virtual void __cdecl log(unsigned int requiredSize, const char *format, ...);
	virtual int fail(const char *expression, const char *file, int line);
	virtual int vslot04(int code, const char *expression, const char *file, int line);
	virtual ~Rva007EB810Diag();

	void (__cdecl *field04)(void *context, const char *text);
	void *field08;
	char *field0C;
	unsigned int field10;
};

#endif
