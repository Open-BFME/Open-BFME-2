// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc
//
// Retail 0x003F07CE, 23 bytes, RET.
// A byte flag at +0x1A3 returns false; otherwise the result of an unnamed
// thiscall at 0x003F0588 (address-derived pin) is normalised to bool.
// Class name is address-derived.
class Rva003F07CEOwner
{
public:
 bool rva003F07CE();
 int rva003F0588();
private:
 char unknown00[0x1A3];
 bool flag;
};
bool Rva003F07CEOwner::rva003F07CE()
{
 if (flag)
  return false;
 return static_cast<bool>(rva003F0588());
}
