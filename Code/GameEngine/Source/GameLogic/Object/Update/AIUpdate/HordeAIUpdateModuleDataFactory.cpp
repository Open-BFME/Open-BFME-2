// cl: /DNDEBUG /MD /EHsc
// Target registration pairs both HordeAIUpdate and HordeWorkerAIUpdate with
// RVA 0x2541A3. This is their folded data factory, not DamageModule.
// Retail allocates 0x64 bytes, calls the rowed TransportAIUpdateModuleData
// constructor (0x26E5D7), stores vptr VA 0xC4B6C8, then optionally invokes
// INI::initFromINIMultiProc with the rowed Transport parse proc (0x2638FF).
// The donor ModuleFactory.cpp (BFME1 1281192f68) supplies the factory pattern.
// The Horde spelling is supported by registration; unaccessed layout is opaque.
class ModuleData;
class MultiIniFieldParse;
class INI {
public:
    void initFromINIMultiProc(void *, void (__cdecl *)(MultiIniFieldParse &));
};
extern "C" void *__identifier("??_7HordeAIUpdateModuleData@@6B@")[ ];
class TransportAIUpdateModuleData {
public:
    TransportAIUpdateModuleData();
    static void buildFieldParse(MultiIniFieldParse &);
protected:
    void **m_vtable;
    unsigned char m_opaque[0x60];
};
class HordeAIUpdateModuleData : public TransportAIUpdateModuleData {
public:
    HordeAIUpdateModuleData() {
        m_vtable = __identifier("??_7HordeAIUpdateModuleData@@6B@");
    }
};
class HordeAIUpdate {
public:
    static ModuleData *friend_newModuleData(INI *);
};
ModuleData *HordeAIUpdate::friend_newModuleData(INI *ini) {
    HordeAIUpdateModuleData *data = new HordeAIUpdateModuleData;
    if (ini) ini->initFromINIMultiProc(data, TransportAIUpdateModuleData::buildFieldParse);
    return reinterpret_cast<ModuleData *>(data);
}
