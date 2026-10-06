// cl: /MD
// APT0.19.03 Xbox final PDB/MAP names ForceDelete and the virtual interface.
// Target constructor6DCD20 installs vtable VA CEAED0 after which its type setter
// names AptValue/AptValue.inl. Slot8 of that table contains this26-byte body.
// Recovered ReleaseValues6E6D90 invokes slot8 for zero-refcount values. Target
// ForceDelete itself calls slots28/2C then scalar deleting destructor slot38.
// PreDestroy/DestroyGCPointers spellings come from donor, virtual offsets and
// deletion flag1 from target. No unused method identities or full layout claimed.
class AptValue {
    virtual void unused0();
    virtual void unused1();
public:
    virtual void ForceDelete();
private:
    virtual void unused3(); virtual void unused4(); virtual void unused5();
    virtual void unused6(); virtual void unused7(); virtual void unused8();
    virtual void unused9();
    virtual void PreDestroy();
    virtual void DestroyGCPointers();
    virtual void unused12(); virtual void unused13();
public:
    virtual ~AptValue();
};
void AptValue::ForceDelete() { PreDestroy(); DestroyGCPointers(); delete this; }
