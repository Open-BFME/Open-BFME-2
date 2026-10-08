// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Retail 0x0047B993, 19 bytes, RET 4.
// Shape: a one-argument thiscall gate. A flag byte at +0x124 short-circuits to
// false; otherwise the same argument and this tail-jump into
// TransportContain::isSpecificRiderFreeToExit (0x004671AC, matched in
// TransportContainRiders.cpp).
// The derived class and its name are address-derived: only the flag offset and
// the tail callee are established by the bytes.
class Object;
class TransportContain
{
protected:
 virtual bool isSpecificRiderFreeToExit(Object *specificObject);
};
class Rva0047B993Contain : public TransportContain
{
public:
 bool rva0047B993(Object *specificObject);
private:
 char unknown04[0x124 - 4];
 bool flag;
};
bool Rva0047B993Contain::rva0047B993(Object *specificObject)
{
 if (flag)
  return false;
 return TransportContain::isSpecificRiderFreeToExit(specificObject);
}
