// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?rva0002DD38@INI@@QAE_NVAsciiString@@00W4INILoadType@@PAVXfer@@@Z
// @0x0002DD38 (260B).
//
// Target evidence: thiscall, ret 0x14, returns bool; three by-value
// AsciiStrings destroyed through rowed 0x00036410 on both exits. The setup
// matches load 0x0002DA4B: rowed setFPMode (0x00040EA9), arg 5 into 0x00DDF57C,
// then 0x0002D2C1 with &arg1 and arg 4. The loop tests the end-of-file byte at
// +0x430, calls rowed readLine 0x0002D669 and hands copies of args 2 and 3 plus
// the +0x14 buffer to rowed static 0x0002C2C7; on a hit it runs 0x0002C0F5 with
// &arg1 and returns true without 0x0002BF4A, otherwise the loop exit runs
// rowed 0x0002BF4A and returns false. A catch(...) runs 0x0002BF4A and
// rethrows. The only caller (0x002044A5) passes "Data\INI\FXParticleSystem.ini",
// "FXParticleSystem", its own name argument, load type 1 and a null Xfer.
//
// Donor (BFME1 ini.cpp): prepFile, unPrepFile and isDeclarationOfType are
// carried names. Structural inference: this loads the single named block
// (ZH's ScriptEngine reloads one particle system by the same steps inline);
// the original name of this member and of 0x0002C0F5 is not recovered.
// Shape: a false result local set up before the try is what puts retail's
// xor ebx, ebx ahead of the first trylevel store.

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
	bool rva0002DD38(AsciiString filename, AsciiString blockType, AsciiString blockName,
		INILoadType loadType, Xfer *pXfer);

	void rva0002C0F5(AsciiString &filename);

	static bool isDeclarationOfType(AsciiString blockType, AsciiString blockName, char *bufferToCheck);

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

extern void setFPMode();
extern void *g_00DDF57C; // s_xfer, provider INI_readLine.cpp

bool INI::rva0002DD38(AsciiString filename, AsciiString blockType, AsciiString blockName,
	INILoadType loadType, Xfer *pXfer)
{
	setFPMode();
	g_00DDF57C = pXfer;
	prepFile(filename, loadType);

	bool found = false;
	try
	{
		while (m_endOfFile == false)
		{
			readLine();

			if (isDeclarationOfType(blockType, blockName, m_buffer))
			{
				rva0002C0F5(filename);
				return true;
			}
		}
	}
	catch (...)
	{
		unPrepFile();
		throw;
	}

	unPrepFile();
	return found;
}
