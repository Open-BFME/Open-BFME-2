// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii

#include "ascii_string.h"

class CommandButton;
class GameWindow;
class ControlBar
{
public:
 const CommandButton *findCommandButton(const AsciiString &name);
 void rva004C1B60(GameWindow *window, void *command);
};
extern ControlBar *TheControlBar;

struct Rva0058BCD0State
{
	int m_index;
};

class Gen0058BCD0
{
public:
	void handle( int unused );

private:
	Rva0058BCD0State *m_state;
};

void Gen0058BCD0::handle( int )
{
	if( m_state->m_index >= 0 )
	{
		void *command;
		{
			AsciiString name( "NonCommand_Resources" );
			command = (void *)TheControlBar->findCommandButton( name );
		}
		if( command )
			TheControlBar->rva004C1B60( 0, command );
	}
}

// Target 0x002D39E5..0x002D3A53: sibling of the Resources callback.
// The literal establishes the UI command; original receiver identity is unknown.
// The state pointer is at +0 and retail tests its float at +0 against 1.0f.
// Both calls use the established ControlBar definitions, without alias pins.
class Rva002D39E5
{
public:
 void handle(int unused);
private:
 float *m_multiplier;
};
void Rva002D39E5::handle(int)
{
 if (*m_multiplier != 1.0f)
 {
  const CommandButton *command;
  {
   AsciiString name("NonCommand_ResourceMultiplier");
   command = TheControlBar->findCommandButton(name);
  }
  if (command)
   TheControlBar->rva004C1B60(0, (void *)command);
 }
}
