// ?rva00062928@Rva00062928@@QAEXXZ
// cl: /O1 /DNDEBUG /MD /EHsc
// Native 00062928..00062972, RET0. Temporarily clear the rowed shader flag
// and byte3C of the global flag-holder around three engine calls. Original
// receiver identity and the flag-holder's original class remain unresolved.
extern bool ShaderOverbrightEnabled;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
void Rva000A8F98();
void Rva000A9071();
class Rva0022244D { public: void rva0022244D(); };
class Rva00062928 { public: void rva00062928(); };
void Rva00062928::rva00062928()
{
    unsigned char *flags = reinterpret_cast<unsigned char *>(TheWritableGlobalData);
    bool overbright = ShaderOverbrightEnabled;
    ShaderOverbrightEnabled = false;
    unsigned char flag = flags[0x3C];
    flags[0x3C] = 0;
    Rva000A8F98();
    reinterpret_cast<Rva0022244D *>(this)->rva0022244D();
    Rva000A9071();
    reinterpret_cast<unsigned char *>(TheWritableGlobalData)[0x3C] = flag;
    ShaderOverbrightEnabled = overbright;
}
