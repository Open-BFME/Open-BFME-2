// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc
//
// Retail 0x00461DB5, 18 bytes, RET.
// Two flag bytes (+0x30, +0x31) gate a tail-jump into an unnamed member at
// 0x00461C1F (address-derived pin). Owner class name is address-derived.
class Rva00461DB5Owner
{
public:
 void rva00461DB5();
 void rva00461C1F();
private:
 char unknown00[0x30];
 bool flag30;
 bool flag31;
};
void Rva00461DB5Owner::rva00461DB5()
{
 if (flag31)
  return;
 if (flag30)
  return;
 rva00461C1F();
}
