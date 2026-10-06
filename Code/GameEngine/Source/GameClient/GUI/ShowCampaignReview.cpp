// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// Retail 0x0050DCB0: BFME replacement of ZH TheShell->push for CampaignReview.
// Returns true at once if the CampaignReview singleton at 0x012F495C exists;
// otherwise Shell::push("CampaignReview.apt", false).  No /EHsc: retail
// carries the by-value stash without a registered handler.

#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
extern void *g_obj12F495C;
// g_obj12F495C: matched references place it at VA 0xe048c8 (zero-filled .bss).
void * g_obj12F495C;

// ?_bfme_showCampaignReview@@YA_NXZ
bool _bfme_showCampaignReview( void )
{
	if( g_obj12F495C == 0 )
		TheShell->push( AsciiString( "CampaignReview.apt" ), false );
	return true;
}
