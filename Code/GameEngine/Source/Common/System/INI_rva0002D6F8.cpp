// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0002D6F8@INI@@QAE?AVAsciiString@@XZ @0x0002D6F8 176B. INI block accumulate
// until m_blockEndToken via readLine plus strtok plus _strcmpi with concat.
// Evidence: rowed 0x0002D669 0x00037BA0 0x00006987 0x00036410 0x000365F0 plus
// IAT strtok _strcmpi plus caller 0x0002DE3C hidden-pointer return pattern
// plus INI layout from neighbour INI_readLine.cpp and ZH seps blockEnd order.
#include "ascii_string.h"
#include <string.h>
enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};
class Xfer;
class INI
{
public:
	void rva0002CBCC(const AsciiString &text, char separator);
protected:
	void readLine();
public:
	AsciiString rva0002D6F8();
	bool loadBlock(AsciiString filename, AsciiString blockType, AsciiString blockName, INILoadType loadType, Xfer *pXfer);
	void parseLine(AsciiString &filename);
	static bool isDeclarationOfType(AsciiString blockType, AsciiString blockName, char *bufferToCheck);
protected:
	bool prepFile(const AsciiString &filename, INILoadType loadType);
	void unPrepFile();
private:
	void *m_file; // +0x00
	AsciiString m_filename; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	int m_lineNum; // +0x10
	char m_buffer[0x418 - 0x14]; // +0x14
	const char *m_seps; // +0x418
	const char *m_sepsPercent; // +0x41C
	const char *m_sepsColon; // +0x420
	const char *m_sepsQuote; // +0x424
	const char *m_428; // +0x428
	const char *m_blockEndToken; // +0x42C
	bool m_endOfFile; // +0x430 +0x430
	char m_curBlockStart[0x404]; // +0x431 +0x431
	char m_pad835[0x37];
public:
	AsciiString m_pending; // +0x86C
	char m_pad870[0xC];
};
AsciiString INI::rva0002D6F8()
{
	AsciiString acc;
	char *buf = m_buffer;
	for (;;) {
		readLine();
		AsciiString line(buf);
		char *tok = strtok(buf, m_seps);
		if (tok != 0) {
			if (_strcmpi(m_blockEndToken, tok) == 0)
				break;
		}
		((StringBase<char> *)&acc)->concat((const StringBase<char> &)line);
	}
	return acc;
}
