// cl: /DNDEBUG /MD /GX
// ?rva00362DBD@BuffManager@@QAEXH@Z @0x00362DBD 89B: ModuleData-like ctor with 9x0x44 array at +8 then register via TheGameClient; callers 0x00271B8C and 0x0027B08C
class ModuleData {
public:
    virtual ~ModuleData();
};
class Rva00362D6C {
public:
    Rva00362D6C();
    ~Rva00362D6C();
private:
    char m_pad[0x44];
};
class Rva00239FE4 {
public:
    void rva00239FE4(const ModuleData *p);
};
class ClientFrameSubsystem;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;
class BuffManager : public ModuleData {
public:
    BuffManager(int v);
private:
    int m_val04;
    Rva00362D6C m_arr08[9];
};
BuffManager::BuffManager(int v) : m_val04(v)
{
    ((Rva00239FE4 *)((ClientFrameSubsystem *)TheGameClient))->rva00239FE4((const ModuleData *)this);
}
