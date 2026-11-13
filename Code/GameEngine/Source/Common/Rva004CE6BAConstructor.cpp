// ??0Rva004CE6BA@@QAE@XZ
// cl: /O1 /arch:SSE /DNDEBUG /MD
// Retail 0x004CE6BA, 42 bytes: record with two words of 2x the logic-frame
// global at 0x009BA4E4 and two -1.0f floats. Owner address-derived.
extern int BfmeLogicFramesPerSecond;

#include "../../Include/Common/Rva004CE6BA.h"

Rva004CE6BA::Rva004CE6BA() :
	m_00(BfmeLogicFramesPerSecond * 2), m_04(BfmeLogicFramesPerSecond * 2), m_08(-1.0f), m_0C(-1.0f)
{
}
