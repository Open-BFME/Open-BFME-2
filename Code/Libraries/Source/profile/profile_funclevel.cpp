// cl: /MD /EHsc
// platformsdk
//
// Zero Hour profile_funclevel.cpp as built into BFME2 (retail 0x006C8380-
// 0x006C87AF): the !HAS_PROFILE build. Every accessor returns empty data,
// so retail's ICF folds most of them onto identical bodies (symbols.csv
// pins: GetSource/GetFunction/GetAddress/GetLine at 0x0065CE90,
// GetTime/GetFunctionTime onto GetCalls at 0x006C8780, EnumThreads at
// 0x0073B660); those definitions carry unmatched-function markers because
// their retail addresses belong to the surviving fold rows. The tracer's
// frame entry points are BFME2 hook gates.

#include <windows.h>
#include "internal.h"

// .bss 0x00E0C768 / 0x00E0C76C; optional hooks, called __stdcall with (1, 0).
ProfileFuncLevelHook ProfileFuncLevelTracer::frameStartHook;
ProfileFuncLevelHook ProfileFuncLevelTracer::frameEndHook;

// .bss 0x00E0C764; the VSPerf80 module loaded by rva006C83B0, external so this
// TU can release it. Descriptive name; the EA identifier is not recovered.
extern void *g_bfmeProfilePerfLibrary;

// ?Shutdown@ProfileFuncLevelTracer@@SAXXZ (0x006C8360)
void ProfileFuncLevelTracer::Shutdown(void)
{
	void *library = g_bfmeProfilePerfLibrary;
	frameStartHook = 0;
	frameEndHook = 0;
	if (library)
		FreeLibrary((HMODULE)library);
}

// ?FrameStart@ProfileFuncLevelTracer@@SAHXZ (0x006C8380)
int ProfileFuncLevelTracer::FrameStart(void)
{
	if (frameStartHook)
		frameStartHook(1, 0);
	return 1;
}

// ?FrameEnd@ProfileFuncLevelTracer@@SAXHH@Z (0x006C83A0)
void ProfileFuncLevelTracer::FrameEnd(int /*which*/, int /*mixIndex*/)
{
	if (frameEndHook)
		frameEndHook(1, 0);
}

// ?Enum@IdList@ProfileFuncLevel@@QBE_NIAAVId@2@PAI@Z (0x006C8770)
bool ProfileFuncLevel::IdList::Enum(unsigned index, Id &id, unsigned *) const
{
	return false;
}

// ?GetSource@Id@ProfileFuncLevel@@QBEPBDXZ present-unmatched
const char *ProfileFuncLevel::Id::GetSource(void) const
{
	return NULL;
}

// ?GetFunction@Id@ProfileFuncLevel@@QBEPBDXZ present-unmatched
const char *ProfileFuncLevel::Id::GetFunction(void) const
{
	return NULL;
}

// ?GetAddress@Id@ProfileFuncLevel@@QBEIXZ present-unmatched
unsigned ProfileFuncLevel::Id::GetAddress(void) const
{
	return 0;
}

// ?GetLine@Id@ProfileFuncLevel@@QBEIXZ present-unmatched
unsigned ProfileFuncLevel::Id::GetLine(void) const
{
	return 0;
}

// ?GetCalls@Id@ProfileFuncLevel@@QBE_KI@Z (0x006C8780)
unsigned __int64 ProfileFuncLevel::Id::GetCalls(unsigned frame) const
{
	return 0;
}

// ?GetTime@Id@ProfileFuncLevel@@QBE_KI@Z present-unmatched
unsigned __int64 ProfileFuncLevel::Id::GetTime(unsigned frame) const
{
	return 0;
}

// ?GetFunctionTime@Id@ProfileFuncLevel@@QBE_KI@Z present-unmatched
unsigned __int64 ProfileFuncLevel::Id::GetFunctionTime(unsigned frame) const
{
	return 0;
}

// ?GetCaller@Id@ProfileFuncLevel@@QBE?AVIdList@2@I@Z (0x006C87A0)
ProfileFuncLevel::IdList ProfileFuncLevel::Id::GetCaller(unsigned frame) const
{
	return ProfileFuncLevel::IdList();
}

// ?EnumProfile@Thread@ProfileFuncLevel@@QBE_NIAAVId@2@@Z (0x006C8790)
bool ProfileFuncLevel::Thread::EnumProfile(unsigned index, Id &id) const
{
	return false;
}

// ?EnumThreads@ProfileFuncLevel@@SA_NIAAVThread@1@@Z present-unmatched
bool ProfileFuncLevel::EnumThreads(unsigned index, Thread &thread)
{
	return false;
}

// ProfileFastCS's contention-yield event (.data 0x00E0C774, after the two
// hooks above), created by the startup initializer at 0x007B6720:
// CreateEventA(NULL, FALSE, FALSE, "") stored to it, as Zero Hour defines it
// here outside HAS_PROFILE. Read by ThreadSafeSetFlag (0x006C5EF0).
HANDLE ProfileFastCS::testEvent=::CreateEvent(NULL,FALSE,FALSE,"");
