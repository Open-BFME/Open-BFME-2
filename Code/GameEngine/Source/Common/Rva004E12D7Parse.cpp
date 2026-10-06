// cl: /DNDEBUG /MD /EHsc
// ?Rva004E12D7Parse@@YAXPAX0@Z @0x004E12D7, 24B.
// INI parse helper for LivingWorldSpawnArmyID: calls INI slot 0x94 with
// the string plus dest plus 4. Callers at 0x002BC6C7 plus 6 more pass
// INI plus field at this plus 0x9C. Same 24B shape as 0x00318D1E.
class INI
{
public:
    virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
    virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
    virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
    virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
    virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
    virtual void f24(); virtual void f25(); virtual void f26(); virtual void f27();
    virtual void f28(); virtual void f29(); virtual void f30(); virtual void f31();
    virtual void f32(); virtual void f33(); virtual void f34(); virtual void f35();
    virtual void f36();
    virtual void parse(const char *name, void *dest, int count) = 0;
};
void __cdecl Rva004E12D7Parse(void *ini, void *dest)
{
    ((INI *)ini)->parse("LivingWorldSpawnArmyID", dest, 4);
}
