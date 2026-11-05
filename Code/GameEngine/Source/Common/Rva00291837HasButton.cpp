// cl: /EHs-
// ?rva00291837@Object@@QBE_NXZ, retail 0x00291837, 60 bytes.
// Looks up this object's command set through TheControlBar (0x0031D5F8 on
// the 0x00290E67 command-set name) and returns true when any of its 32
// buttons has option bit 0x200000 (byte +0x1E, bit 0x20) set.

class AsciiString;
class ControlBar;
extern ControlBar *TheControlBar;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *);
};

#include "../../Include/GameClient/CommandButton.h"

#include "../../Include/GameClient/CommandSet.h"

#include "../GameLogic/Object/object.h"

bool Object::rva00291837() const
{
	const CommandSet *commandSet = reinterpret_cast<const CommandSet *>(
		reinterpret_cast<Rva0031D5F8 *>(TheControlBar)->rva0031D5F8(rva00290E67()));
	if (commandSet) {
		for (int i = 0; i < 32; ++i) {
			const CommandButton *button = commandSet->getCommandButton(i);
			if (button && (button->m_options & 0x200000))
				return true;
		}
	}
	return false;
}