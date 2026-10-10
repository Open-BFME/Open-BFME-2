// cl: /O1 /EHsc /Ireference/shims/bfme2_ascii
// ?rva0031B4D6@Rva0031B53D@@QAEEPAVINI@@H@Z @0x0031B4D6 103B: load three CommandButton CommandSet INIs via INI* plus type and OR results. Evidence: caller 0x0031B57D plus literals Data\INI\Default\CommandButton.ini Data\INI\CommandButton.ini Data\INI\CommandSet.ini plus ControlBarScheme donor init pattern. loadFile pin void type wrong: retail uses al for ORs so declare uchar.
// The caller 0x0031B53D sets ECX to its own this before calling 0x0031B4D6, so the loader is a thiscall member of the same object; its body never reads this.
class Xfer;
enum INILoadType { INI_LOAD_OVERWRITE = 1 };
#include "ascii_string.h"
class INI {
public:
  INI();
  ~INI();
  unsigned char loadFile(AsciiString s, INILoadType t, Xfer *x);
private:
  char m_data[0x87C];
};
class Rva0031B53D {
public:
  unsigned char rva0031B53D();
  unsigned char rva0031B4D6(INI *ini, int type);
private:
  int m_pad0;
  unsigned char m_flag;
};
unsigned char Rva0031B53D::rva0031B4D6(INI *ini, int type)
{
  unsigned char b0 = ini->loadFile(AsciiString("Data\\INI\\Default\\CommandButton.ini"), (INILoadType)type, 0);
  b0 |= ini->loadFile(AsciiString("Data\\INI\\CommandButton.ini"), (INILoadType)type, 0);
  b0 |= ini->loadFile(AsciiString("Data\\INI\\CommandSet.ini"), (INILoadType)type, 0);
  return b0;
}
// ?rva0031B53D@Rva0031B53D@@QAEEXZ @0x0031B53D 102B: build a stack INI (ctor 0x0002CDB0, dtor 0x0002CE5B, EH frame) and load the command INIs with type 5 when the byte at +4 is set, else 1.
unsigned char Rva0031B53D::rva0031B53D()
{
  INI ini;
  unsigned char flag = m_flag;
  int type = flag ? 5 : 1;
  unsigned char r = rva0031B4D6(&ini, type);
  return r;
}
