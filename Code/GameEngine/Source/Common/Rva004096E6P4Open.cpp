// cl: /O1 /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva004096E6@@YA_NABVAsciiString@@@Z, retail 0x004096E6 (201B): cdecl
// bool helper that opens a file for edit in Perforce. It locates "p4.exe"
// through 0x004095D5 (the PATH search beside it: getenv plus SplitString in
// the WorldBuilder twin; the name is address-derived), then runs
// "p4.exe edit <file>" and, when that succeeds, "p4.exe add <file>" through
// the rowed command runner 0x00407AF9 (CreateProcessA). False as soon as a
// step fails. Retail literals: "p4.exe" (VA 0x00C38DC4), "edit "
// (0x00C38DBC), "add " (0x00C38DB4).
#include "ascii_string.h"

bool Rva004095D5(AsciiString &path, const AsciiString &exeName);
bool Rva00407AF9Run(const AsciiString &exePath, const AsciiString &arguments);

bool Rva004096E6(const AsciiString &fileName)
{
	AsciiString exeName("p4.exe");
	AsciiString arguments("edit ");
	AsciiString exePath;
	arguments += fileName;

	if (!Rva004095D5(exePath, exeName))
		return false;
	if (!Rva00407AF9Run(exePath, arguments))
		return false;

	arguments = "add ";
	arguments += fileName;
	if (!Rva00407AF9Run(exePath, arguments))
		return false;

	return true;
}
