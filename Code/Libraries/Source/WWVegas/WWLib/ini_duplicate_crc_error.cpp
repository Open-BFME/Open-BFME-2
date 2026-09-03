// cl: /MD
//
// WWLib INIClass::DuplicateCRCError, the warning Load and Put_String raise
// when an entry's CRC collides with one already in the file's index.
//
// Named from the Generals reference, which declares
//   void DuplicateCRCError(const char *message, const char *entry);
// on INIClass. This engine's copy takes a third argument - the section - and
// reports through a formatted buffer rather than the piecewise
// OutputDebugString the reference uses, so the body is written from retail
// rather than ported.
//
// The three calls are imports, resolved by /MD: _snprintf at 0x00BBA5C0,
// OutputDebugStringA at 0x00BBA19C and MessageBoxA at 0x00BBA7F8. The
// argument order is fixed by the format string - message, entry, section,
// then the filename the object carries at +0x0C - which is why `entry` is
// passed before `section` despite being the last parameter.

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer,
		unsigned int count, const char *format, ...);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(
		const char *output);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *owner,
		const char *text, const char *caption, unsigned int type);

class INIClass
{
public:
	void DuplicateCRCError(const char *message, const char *section,
			const char *entry);

private:
	void *_M_unused0;
	void *_M_unused1;
	void *_M_unused2;
	const char *Filename;
};

void INIClass::DuplicateCRCError(const char *message, const char *section,
		const char *entry)
{
	char buffer[512];

	_snprintf(buffer, sizeof(buffer),
			"%s - Duplicate Entry \"%s\" in section \"%s\" (%s)\n",
			message, entry, section, Filename);
	OutputDebugStringA(buffer);
	MessageBoxA(0, buffer, "Duplicate CRC in INI file.", 0x10);
}
