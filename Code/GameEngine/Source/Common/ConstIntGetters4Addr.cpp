// Two getters returning factory entry points: 0x0048FF84 and 0x006D21BB are
// the matched Rva0008FF84Create and Rva002D21BBCreate rows, so take their
// addresses instead of the image constants.
class Rva0008FF3E;
class AptSkirmish;
Rva0008FF3E *__stdcall Rva0008FF84Create(void *context);
AptSkirmish *__stdcall Rva002D21BBCreate(void *context);

int Rva0008FFBEGet(void)
{
	return (int)Rva0008FF84Create;
}
