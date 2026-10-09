// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1ShadowTypeInfo@Shadow@@QAE@XZ, retail 0x000793FA, 53 bytes. Dedicated
// TU (its file name is from the row's earlier, wrong AudioEventRTS name).
//
// Shadow::ShadowTypeInfo teardown destroys its two strings through the
// folded string teardown (0x36410 pin). The retail body follows that shape
// with the usual cookie and state transitions; the class view matches the
// constructor TU (AudioEventRTSCtor.cpp), which gives the identity evidence.
// The real AudioEventRTS has a virtual destructor elsewhere (pinned
// ??1AudioEventRTS@@UAE@XZ), so nothing here stands in for it.

#include "ascii_string.h"

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		~ShadowTypeInfo();

		AsciiString m_first;
		AsciiString m_second;
	};
};

// ??1ShadowTypeInfo@Shadow@@QAE@XZ
Shadow::ShadowTypeInfo::~ShadowTypeInfo()
{
}
