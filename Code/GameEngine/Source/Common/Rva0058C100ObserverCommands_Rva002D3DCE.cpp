// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii

#include "ascii_string.h"

// The native calls reach the rowed ControlBar methods at 31BE3C and 405DBC.
// Use their real definitions rather than the retired command-manager aliases.
class CommandButton;
class GameWindow;
#include "../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

void __stdcall rva0058C100ObserveNext( void * )
{
	void *command;
	{
		AsciiString name( "NonCommand_ObserveNextPlayer" );
		command = (void *)TheControlBar->findCommandButton( name );
	}
	if( command )
		TheControlBar->rva004C1B60( 0, command );
}
