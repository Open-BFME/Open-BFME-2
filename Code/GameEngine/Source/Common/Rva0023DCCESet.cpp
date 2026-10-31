// cl: /MD
// ?rva0023DC8E@Rva0023DC8E@@QAEXABVAsciiString@@@Z — RVA 0x0023DC8E, 64B.
// Ghidra FUN_0063dc8e is the 64-byte sibling of the conditional
// string-and-handles setter that retail emits inline (COMDAT) in GameLogic's own
// unit; that 122-byte body at 0x0023DCCE now compiles from its retail home,
// Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp. This file keeps
// only the sibling, an address-derived host.
// Evidence: retail branch bytes; callees rowed (isEmpty 0x1E2F, StringBase set
// 0x366F0, releaseBuffer 0x36410); global at VA 0xdfe758.

class Rva0023DC8E;

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


struct OpaqueRefElement4
{
	void *m_ptr;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva000A8C9B
{
	void *m_ptr;
	void clear();
};

class GlobalData
{
public:
	char m_pad[0x9AD];
	unsigned char m_flag9AD; // +0x9AD
	char m_pad9AE[0x1110 - 0x9AE];
	unsigned char m_1110; // +0x1110
};
extern GlobalData *TheWritableGlobalData;

// Ghidra FUN_0063dc8e is a 64-byte conditional string setter: it applies the
// empty-string/global-flag test to a single string member at +0x74. Its public
// setter body at 0x0023DCCE lives in GameLogicInit.cpp, its retail COMDAT home.
class Rva0023DC8E
{
public:
	void rva0023DC8E(const AsciiString &value);

private:
	char m_pad00[0x72];
	unsigned char m_flag;
	char m_pad73;
	AsciiString m_string;
};

void Rva0023DC8E::rva0023DC8E(const AsciiString &value)
{
	if (value.isEmpty() || TheWritableGlobalData->m_flag9AD)
	{
		m_flag = 0;
		((StringBase<char> *)&m_string)->clear();
	}
	else
	{
		m_flag = 1;
		((StringBase<char> *)&m_string)->set(*(const StringBase<char> *)&value);
	}
}
// ?TheWritableGlobalData@@3PAVGlobalData@@A: the global at VA 0xdfe758.
