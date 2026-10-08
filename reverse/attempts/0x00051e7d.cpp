// ?Rva00051E7DStreamLoopCount@@YIHPAXPBUStreamLoopEventView@@@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /MD
// Clean semantic donor: BF1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngineDevice/Source/MilesAudioDevice/StartAudioStream006AE2C0.cpp,
// its streamLoopCount006990E0 helper. WB79C6F0 names the target
// getAppropriateStreamLoopCount in MilesAudioManager.cpp and corroborates
// music count, stream control, permanent-loop and null-info behavior.
// Complete native51E7D..51EC2 proves incoming event in EDX, no consumed ECX
// input, no stack arguments, info+8/control4C/typeB0/event count7C, sentinel
// -12345 and the one-million loop limit. BF1's offsets/sentinel differ.
// This address-qualified fastcall ABI view represents the observed EDX
// input; its ignored first register is not an inferred EA source parameter.
// The accessed event/info prefixes are not complete application layouts.
struct StreamLoopInfoView
{
	char unknown00[0x4C];
	unsigned char control;
	char unknown4D[0xB0 - 0x4D];
	unsigned type;
};
struct StreamLoopEventView
{
	char unknown00[8];
	StreamLoopInfoView *info;
	char unknown0C[0x7C - 0xC];
	int loops;
};

int __fastcall Rva00051E7DStreamLoopCount(void *ignoredECX, const StreamLoopEventView *event)
{
	const StreamLoopInfoView *info = event->info;
	if (!info) return 1;
	switch (info->type) {
	case 1:
	case 4:
		return (info->control & 1) ? 1000000 : 1;
	case 3:
		return 1000000;
	case 0:
	{
		int loops = event->loops;
		if (loops == -12345) return 1000000;
		if (loops >= 1) return loops;
		return 1;
	}
	default:
		return 1;
	}
}
