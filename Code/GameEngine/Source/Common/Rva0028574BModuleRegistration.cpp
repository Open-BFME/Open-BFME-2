// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Complete 21B leaf 28574B..285760 calls the independently rowed
// Rva0020DFFBRegister on unchanged this only when word4 is zero, then
// increments word4. The callee establishes the ModuleData-pointer registry
// relationship; the original receiver name and counter's purpose are not
// established by ZH's ModuleData declaration. Only a borrowed prefix.
class ModuleData;
void __cdecl Rva0020DFFBRegister(const ModuleData *);
struct Rva0028574BModulePrefix {
    unsigned char prefix[4];
    unsigned int counter4;
    void registerAndIncrement();
};
void Rva0028574BModulePrefix::registerAndIncrement() {
    if (!counter4) Rva0020DFFBRegister((const ModuleData *)this);
    ++counter4;
}
