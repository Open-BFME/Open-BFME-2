// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0002D6F8@INI@@QAE?AVAsciiString@@XZ @0x0002D6F8 176B. INI block accumulate
// until m_blockEndToken via readLine plus strtok plus _strcmpi with concat.
// Evidence: rowed 0x0002D669 0x00037BA0 0x00006987 0x00036410 0x000365F0 plus
// IAT strtok _strcmpi plus caller 0x0002DE3C hidden-pointer return pattern
// plus INI layout from neighbour INI_readLine.cpp and ZH seps blockEnd order.
#include "ascii_string.h"
class INI
{
protected:
	void readLine();
private:
	void *m_file;
	AsciiString m_filename;
	int m_08;
	int m_0C;
	int m_lineNum;
	char m_buffer[0x418 - 0x14];
	const char *m_seps;
	const char *m_sepsPercent;
	const char *m_sepsColon;
	const char *m_sepsQuote;
	const char *m_428;
	const char *m_blockEndToken;
public:
	AsciiString rva0002D6F8();
};
extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delim);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
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
