// cl: /MD /EHsc
//
// Harness for tools/subsystem_link.py: links the profile library
// (Code/Libraries/Source/profile) and drives its public API once.

#include <stdio.h>
#include "../../../Code/Libraries/Source/profile/internal.h"

__int64 GetClockCyclesFast(void);

int main(void)
{
	ProfileHighLevel::Id id = ProfileHighLevel::AddProfile("harness", "pilot", "calls", 0, 0);
	id.Increment(2.0);
	Profile::StartRange("frame");
	Profile::StopRange("frame");
	ProfileId::Shutdown();
	ProfileFuncLevel::Thread thread;
	ProfileResultInterface *csv = ProfileResultFileCSV::Create(0, 0);
	csv->Delete();
	printf("frames=%u total=%s clock=%s\n", Profile::GetFrameCount(), id.GetTotalValue(),
		GetClockCyclesFast() > 0 ? "ok" : "zero");
	return ProfileFuncLevel::EnumThreads(0, thread) ? 1 : 0;
}
