// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native Ghidra 005E9687..005E96D4, 77B, no-argument thiscall.
// +18 is the existing prompt wrapper: rowed 5F93CB/5F93D3/5F93DB forward
// bool arguments to the named AutoResolve/RealTime/Retreat button setters.
// The +8 receiver's flags helper 3F4FD4 (446B, RET) calls rowed
// LivingWorldBattle::rva003F4DEE and rva003F4831 on its original this;
// its complete native body returns integer flags 2/4/8. Owner name unresolved.
// The final operation is the already-rowed no-argument method at 5E9601.

class LivingWorldBattle
{
public:
    int rva003F4FD4();
};

class Rva005F93CB
{
public:
    void rva005F93CB(bool enabled);
};
class Rva005F93D3
{
public:
    void rva005F93D3(bool enabled);
};
class Rva005F93DB
{
public:
    void rva005F93DB(bool enabled);
};
class Rva005E9601
{
public:
    void rva005E9601();
};

class Rva005E9687
{
public:
    void rva005E9687();
private:
    char unknown00[8];
    LivingWorldBattle *battle;
    char unknown0C[0x18 - 0x0C];
    Rva005E9601 *prompt;
};

void Rva005E9687::rva005E9687()
{
    if (prompt)
    {
        unsigned int flags = battle->rva003F4FD4();
        reinterpret_cast<Rva005F93CB *>(prompt)->rva005F93CB((flags >> 1) & 1);
        reinterpret_cast<Rva005F93D3 *>(prompt)->rva005F93D3((flags >> 3) & 1);
        reinterpret_cast<Rva005F93DB *>(prompt)->rva005F93DB((flags >> 2) & 1);
        prompt->rva005E9601();
    }
}
