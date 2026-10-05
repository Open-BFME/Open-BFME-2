// cl: /MD
// Sibling of rowed Animatable3DObjClass::Get_Bone_Name at 0x001A4B90 (21B),
// matched on mnemonic shape only -- the identity differs. Retail 0x0061F090
// (21B) forwards through the singleton pointer at 0x00E09C0C and otherwise
// returns 100. The tail jump targets the incremental-link thunk at
// 0x00620DA0, which the resolver finds on the already-rowed bfmeForward name.
class Gen_009EBB60Target
{
public:
	int bfmeForward();
};

extern "C" Gen_009EBB60Target *g_bfme00E09C0C;

int __cdecl rva0061F090()
{
	if (g_bfme00E09C0C)
		return g_bfme00E09C0C->bfmeForward();
	return 100;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:_g_bfme00E09C0C=?TheInvokeRegistry@@3PAVGen_009EBA60Target@@A")
