// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ?loadFile@INI@@QAEEVAsciiString@@W4INILoadType@@PAVXfer@@@Z
// @0x0002DC75 (195B, catch funclets at 0x0002DCE1 and 0x0002DD00 included).
//
// Target evidence: thiscall, ret 0xC, returns a byte in AL; the by-value
// filename is released through rowed 0x00036410 on both exits. Same setup as
// the load variants 0x0002DA4B and 0x0002DD38: rowed setFPMode (0x00040EA9),
// arg 3 into 0x00DDF57C, then 0x0002D2C1 with &arg1 and arg 2. When that
// returns zero the function releases filename and returns 0 without entering
// the try. Otherwise the loop tests the end-of-file byte at +0x430, calls rowed
// readLine 0x0002D669, then 0x0002C0F5 with &arg1; the loop exit runs rowed
// 0x0002BF4A and returns 1. catch(INIException &) rethrows a copy built through
// rowed 0x0002F681 from the caught message and count; catch(...) runs
// 0x0002BF4A and rethrows. Callers OR the result across several files
// (0x00054120, 0x0031B4D6) and SubsystemInterfaceList::initSubsystem
// (0x001B5266) calls it per InitFile.
//
// Donor (BFME1 ini.cpp): prepFile and unPrepFile are carried names, and BFME1's
// provisional loadFile (0x00853A20) is the analogous entry point; the name here
// is that existing pin, not a recovered original. BFME1's version returns
// void and stops on a failed prepFile through DEBUG_CRASH/throw, so the
// byte result is target-specific.

#include "ascii_string.h"

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

class INI
{
public:
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);

	void rva0002C0F5(AsciiString &filename);

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

unsigned char INI::loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer)
{
	setFPMode();
	g_00DDF57C = pXfer;
	if (!prepFile(filename, loadType))
		return 0;

	try
	{
		while (m_endOfFile == false)
		{
			readLine();
			rva0002C0F5(filename);
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
	return 1;
}
