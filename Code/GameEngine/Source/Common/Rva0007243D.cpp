// cl: /O1
// ?Rva00739D20@@YAHH_N@Z
// retail 0x0007243D 49B (53B with shared true-tail at 0x0007246E which is rowed separately).
// Free __cdecl mapper from D3D-like codes 0x14-0x18 to small enum 1-5.
// Case 0x15 selects 5 when second byte arg is non-zero else 2 via neg/sbb.
// Donor: reference/open-bfme-1 game/GameEngine/Source/Common/R2GuardedGlobalCalls.cpp Rva00739D20.
// Caller: 0x00044DED in ?createVideoBuffer@W3DDisplay@@UAEPAVVideoBuffer@@_N@Z.
// Prev 0x0007240C Rva0007240CGet is the inverse mapper with the same /O1 dec-je shape.
int Rva00739D20(int value, bool enabled);

int Rva00739D20(int value, bool enabled)
{
	int result = 0;
	switch (value)
	{
	case 21:
		result = enabled ? 5 : 2;
		break;
	case 22:
		result = 2;
		break;
	case 20:
		result = 1;
		break;
	case 23:
		result = 3;
		break;
	case 24:
		result = 4;
		break;
	default:
		break;
	}
	return result;
}
