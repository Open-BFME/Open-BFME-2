// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// Debug::SetBuildInfo, retail 0x00039510 (129 bytes, ret 0xC). Debug vtable
// (RVA 0x7BE810) slot 0x9C.
//
// Ported from Open-BFME-1 Debug_SetBuildInfoThunk.cpp (b1 0x0088A430): three
// guarded strncpy(dst, src, 63), the strncpy import CSE'd into a register.
// BFME2 moves the fields to +0x9E90/+0x9ED0/+0x9F10, makes the member
// virtual, and clears each 64-byte field before copying so the result is
// always terminated.

#include <string.h>

class Debug
{
public:
	virtual void SetBuildInfo(const char *version, const char *internalVersion,
		const char *buildDate);

private:
	unsigned char m_pad04[0x9E8C];
	char m_version[64];                  // +0x9E90
	char m_intVersion[64];               // +0x9ED0
	char m_buildDate[64];                // +0x9F10
};

// ?SetBuildInfo@Debug@@UAEXPBD00@Z
void Debug::SetBuildInfo(const char *version, const char *internalVersion,
	const char *buildDate)
{
	if (version)
	{
		memset(m_version, 0, sizeof(m_version));
		strncpy(m_version, version, sizeof(m_version) - 1);
	}
	if (internalVersion)
	{
		memset(m_intVersion, 0, sizeof(m_intVersion));
		strncpy(m_intVersion, internalVersion, sizeof(m_intVersion) - 1);
	}
	if (buildDate)
	{
		memset(m_buildDate, 0, sizeof(m_buildDate));
		strncpy(m_buildDate, buildDate, sizeof(m_buildDate) - 1);
	}
}
