// cl: /MD /EHsc
//
// Zero Hour profile_cmd.cpp as built into BFME2 (retail 0x006C65F0-
// 0x006C6E7F). Zero Hour's static Debug::Command is a call through
// theDebug's vtable (slot 0x8C) here. Not recovered yet: Execute
// (presumably the 503-byte body at 0x006C65F0).

#include <windows.h>
#include <string.h>
#include "internal.h"

// .bss 0x00E0C634 / 0x00E0C630
unsigned ProfileCmdInterface::numResIf;
ProfileCmdInterface::Factory *ProfileCmdInterface::resIf;

// ?AddResultFunction@ProfileCmdInterface@@SAXP6APAVProfileResultInterface@@HPBQBD@ZPBD2@Z
void ProfileCmdInterface::AddResultFunction(ProfileResultInterface *(*func)(int, const char *const *),
	const char *name, const char *arg)
{
	if (!func)
		return;
	if (!name)
		return;
	for (unsigned k = 0; k < numResIf; k++)
		if (!strcmp(resIf[k].name, name))
			return;
	++numResIf;
	resIf = (Factory *)ProfileReAllocMemory(resIf, numResIf * sizeof(Factory));
	resIf[numResIf - 1].func = func;
	resIf[numResIf - 1].name = name;
	resIf[numResIf - 1].arg = arg;
}

// ?RunResultFunctions@ProfileCmdInterface@@QAEXXZ
void ProfileCmdInterface::RunResultFunctions(void)
{
	if (!numResFunc)
		theDebug->Command("profile.result file_csv");

	for (unsigned k = 0; k < numResFunc; k++)
	{
		resFunc[k]->WriteResults();
		resFunc[k]->Delete();
	}
}
