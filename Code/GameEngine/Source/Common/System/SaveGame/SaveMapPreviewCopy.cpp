// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Vtable0xBE7258 and getter226309 identify SaveMapPreview. Its complete
// copy2262E7 has a Snapshot vptr, dword4 and three-dword aggregate at8.
// STLport4.5.3 range copying uses the retail configuration without catch blocks.
#include <vector>
class Xfer;
class Snapshot {
public:
    __forceinline virtual ~Snapshot() {}
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
class SaveMapPreview : public Snapshot {
public:
    unsigned int word04;
    struct Words { unsigned int a,b,c; } words08;
    __declspec(nothrow) SaveMapPreview(const SaveMapPreview &o) : Snapshot(o), word04(o.word04), words08(o.words08) {}
    virtual ~SaveMapPreview();
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
typedef char SaveMapPreviewSizeCheck[sizeof(SaveMapPreview)==20 ? 1 : -1];
template _STL::vector<SaveMapPreview>::vector(const _STL::vector<SaveMapPreview>&);
template SaveMapPreview *_STL::vector<SaveMapPreview>::_M_allocate_and_copy<SaveMapPreview const *>(unsigned int, SaveMapPreview const *, SaveMapPreview const *);
