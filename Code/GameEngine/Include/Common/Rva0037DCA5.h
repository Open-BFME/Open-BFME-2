// Rva0037DCA5: canonical declarations for the members units call through private views of it.
// Retail 0x0037DC52 and 0x0037DCA5 pass +0x04 as findTemplate's AsciiString; 0x0037DCA5, 0x0037DF8D and
// 0x002206F9 read the int count at +0x90. Other bytes stay opaque; the size is known only to reach +0x94.
#ifndef CANONICAL_RVA0037DCA5_H
#define CANONICAL_RVA0037DCA5_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Rva002206F9Sink;

class Rva0037DCA5
{
public:
	int GetCommandPointSize();
	void *GetDisplayNameStrategicGame();
	void *GetDisplayNameStrategicGame(int index);
	void *GetThingTemplate();
	int rva0037DF8D(Rva002206F9Sink *sink);

	char m_pad0[4];
	AsciiString m_04;
	char m_pad8[0x90 - 0x08];
	int m_90;
};

#endif // CANONICAL_RVA0037DCA5_H
