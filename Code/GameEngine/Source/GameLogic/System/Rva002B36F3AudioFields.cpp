// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
// ?rva002B36F3@Rva002BA8F1Logic@@QAEXXZ @0x002B36F3 77B
// Target evidence: obtains the current Rva002B3740Item through rowed method
// 0x002B2B2D, checks TheGameLogic, then forwards fields through rowed
// accessors to 0x0023DC8E and 0x0023DCCE. Retail's pushes place the
// 0x53B8E5 value in 0x0023DCCE's first (AsciiString) parameter, the
// 0x3EFDD7 value second, and the sounds-vector address third.
// Structural inference: the item uses AudioEventInfo's sounds-vector view;
// its address is passed through the callee's opaque third-parameter view.
#include "ascii_string.h"
#include <vector>

#include "../../../Include/Common/RvaPair001D9F62.h"

class AudioEventInfo
{
public:
	typedef _STL::vector<RvaPair001D9F62> SoundsList;
	const SoundsList &getSoundsVector() const;
};

#include "../../../Include/Common/OpaqueRefElement4.h"

class Rva0049CB86LeaField
{
public:
	void *get() const;
};
#include "../../../Include/GameLogic/Rva003EFDD7LeaField.h"
class Rva0053B8E5LeaField
{
public:
	void *get() const;
};

#include "../../../Include/GameLogic/Rva0023DC8E.h"
#include "../../../Include/GameClient/Rva0023DCCE.h"

class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva002B3740Item;
class Rva0020E89C;
#include "../../../Include/GameLogic/Rva0020EAF6View.h"
#include "../../../Include/GameLogic/Rva002BA8F1Logic.h"

void Rva002BA8F1Logic::rva002B36F3()
{
	Rva002B3740Item *item = rva002B2B2D();
	if (item == 0 || TheGameLogic == 0)
		return;

	((Rva0023DC8E *)TheGameLogic)->rva0023DC8E(
		*(const AsciiString *)((Rva0049CB86LeaField *)item)->get());
	((Rva0023DCCE *)TheGameLogic)->rva0023DCCE(
		*(const AsciiString *)
			((Rva0053B8E5LeaField *)item)->get(),
		*(const OpaqueRefElement4 *)
			((Rva003EFDD7LeaField *)item)->get(),
		*(const OpaqueRefElement4 *)(const void *)&
			((AudioEventInfo *)item)->getSoundsVector());
}
