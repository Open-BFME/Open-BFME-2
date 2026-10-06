// cl: /Ireference/shims/bfme2_ascii
// ?Rva0031B4D6Load@@YGEPAVINI@@H@Z @0x0031B4D6 103B: load three CommandButton CommandSet INIs via INI* plus type and OR results. Evidence: caller 0x0031B57D plus literals Data\INI\Default\CommandButton.ini Data\INI\CommandButton.ini Data\INI\CommandSet.ini plus ControlBarScheme donor init pattern. loadFile pin void type wrong: retail uses al for ORs so declare uchar.
class Xfer;
enum INILoadType { INI_LOAD_OVERWRITE = 1 };
#include "ascii_string.h"
class INI {
public:
  unsigned char loadFile(AsciiString s, INILoadType t, Xfer *x);
};
unsigned char __stdcall Rva0031B4D6Load(INI *ini, int type)
{
  unsigned char b0 = ini->loadFile(AsciiString("Data\\INI\\Default\\CommandButton.ini"), (INILoadType)type, 0);
  b0 |= ini->loadFile(AsciiString("Data\\INI\\CommandButton.ini"), (INILoadType)type, 0);
  b0 |= ini->loadFile(AsciiString("Data\\INI\\CommandSet.ini"), (INILoadType)type, 0);
  return b0;
}
