// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Complete 50B body 35B6C8..35B6FA, RET4. ECX is unused; the single
// stack Object pointer is nullable. It flips status index 100 through
// independently rowed Object::testStatus 4E536 and setStatus 23DB0E,
// then sets byte 28 of TheControlBar (owned global VA E01CFC). The
// original callback owner/name and meaning of status 100 are unknown.
enum ObjectStatusTypes;
class Object {
public:
    bool testStatus(ObjectStatusTypes) const;
    void setStatus(ObjectStatusTypes, bool);
};
class ControlBar;
extern ControlBar *TheControlBar;
struct Rva0035B6C8ControlBarPrefix {
    unsigned char prefix[0x28];
    unsigned char latched28;
};
void __stdcall rva0035B6C8ToggleStatus(Object *object) {
    if (object) {
        if (object->testStatus((ObjectStatusTypes)100))
            object->setStatus((ObjectStatusTypes)100, false);
        else
            object->setStatus((ObjectStatusTypes)100, true);
        ((Rva0035B6C8ControlBarPrefix *)TheControlBar)->latched28 = 1;
    }
}
