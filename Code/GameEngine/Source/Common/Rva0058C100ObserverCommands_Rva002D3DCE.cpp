// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

#include "ascii_string.h"

class Rva0058C100CommandManager
{
public:
	void *find( const AsciiString *name );
	void execute( int value, void *command );
};

// Retail global 0x012F33F8; the canonical mangled spelling is
// ?TheControlBar@@3PAVControlBar@@A, so the pointee must be the real
// ControlBar and only the calls need the TU-local view of it.
class ControlBar;
extern ControlBar *TheControlBar;

void __stdcall rva0058C100ObserveNext( void * )
{
	void *command;
	{
		AsciiString name( "NonCommand_ObserveNextPlayer" );
		command = ((Rva0058C100CommandManager *)TheControlBar)->find( &name );
	}
	if( command )
		((Rva0058C100CommandManager *)TheControlBar)->execute( 0, command );
}
