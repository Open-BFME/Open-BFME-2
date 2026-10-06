// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?load@INI@@QAEXVAsciiString@@W4INILoadType@@PAVXfer@@P6AXPAV1@@Z@Z
// @0x0002DA4B (411B).
//
// Target evidence: thiscall, ret 0x10, by-value AsciiString destroyed through
// rowed 0x00036410 on exit. The setup calls rowed setFPMode (0x00040EA9),
// stores arg 3 into 0x00DDF57C (the hash Xfer that rowed readLine 0x0002D669
// tests) and runs 0x0002D2C1 with &filename and arg 2; the loop tests the
// end-of-file byte at +0x430, calls readLine, strtoks the +0x14 buffer with
// the +0x418 separators, copies the line into +0x431 around a cdecl call
// through arg 4 with this, then restores "NO_BLOCK" there. Throws pass
// through rowed INIException ctor 0x0002F681; both exits run rowed 0x0002BF4A.
//
// Donor (BFME1 ini.cpp): INI::load with INI::parseLine inlined, except the
// block parser arrives as the fourth argument instead of from findBlockParse.
// The name load, prepFile and unPrepFile are carried from the donor; the
// fourth-argument overload is a structural inference from the callers that
// push a parse function.

#include <string.h>

#include "ascii_string.h"

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

class INI;
typedef void (*INIBlockParse)(INI *ini);

class INI
{
public:
	void load(AsciiString filename, INILoadType loadType, Xfer *pXfer, INIBlockParse parse);

protected:
	bool prepFile(const AsciiString &filename, INILoadType loadType);
	void unPrepFile();
	void readLine();

private:
	void *m_file;                    // +0x000
	AsciiString m_filename;          // +0x004
	char m_pad08[0x14 - 0x08];
	char m_buffer[0x418 - 0x14];     // +0x014
	const char *m_seps;              // +0x418
	char m_pad41c[0x430 - 0x41c];
	bool m_endOfFile;                // +0x430
	char m_curBlockStart[0x404];     // +0x431
	char m_pad835[0x87C - 0x835];
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int m_argCount;
	INIException(const INIException &that);
	~INIException();
};

extern void setFPMode();
extern void *g_00DDF57C; // s_xfer, provider INI_readLine.cpp

void INI::load(AsciiString filename, INILoadType loadType, Xfer *pXfer, INIBlockParse parse)
{
	setFPMode();
	g_00DDF57C = pXfer;
	prepFile(filename, loadType);

	try
	{
		while (m_endOfFile == false)
		{
			readLine();

			const char *token = strtok(m_buffer, m_seps);
			if (token)
			{
				if (parse)
				{
					strcpy(m_curBlockStart, m_buffer);
					try
					{
						parse(this);
					}
					catch (INIException &e)
					{
						const char *name = m_filename.str();
						char *msg = e.mFailureMessage;
						int argCount = e.m_argCount;
						throw INIException(argCount, "%s\n\nError parsing INI block '%s' in file '%s'.",
							msg, token, name);
					}
					catch (...)
					{
						throw INIException(8, "Unknown error parsing INI block '%s' in file '%s'.",
							token, m_filename.str());
					}
					strcpy(m_curBlockStart, "NO_BLOCK");
				}
				else
				{
					throw INIException(5, "Unknown block '%s'.\n\nError parsing INI block '%s' in file '%s'.",
						token, token, m_filename.str());
				}
			}
		}
	}
	catch (INIException &e)
	{
		throw INIException(e.m_argCount, e.mFailureMessage);
	}
	catch (...)
	{
		unPrepFile();
		throw;
	}

	unPrepFile();
}
