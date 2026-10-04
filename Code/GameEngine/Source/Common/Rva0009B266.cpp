// cl: /O1 /DNDEBUG /MD
// ?rva0009B266@Rva0009B266@@QBE?AV?$RefCountPtr@VTextureClass@@@@HHH@Z @0x0009B266 38B: forward to +0x94 texture provider Get_Texture. Evidence: same +0x94 shape as Rva006FD440::bfmeGet, callee rowed Get_Texture 0x15A910, caller unclaimed 0x9CD9B.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {
public:
    void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this)+4); }
};
template<class T> class RefCountPtr {
public:
    T *p;
    RefCountPtr() : p(0) {}
    RefCountPtr(RefCountPtr const &other) : p(other.p) { if (p) p->Add_Ref(); }
    ~RefCountPtr() { if (p) p->Release_Ref(); }
};
class MeshMatDescClass {
public:
    RefCountPtr<TextureClass> Get_Texture(int index, int pass, int stage) const;
};

class Rva0009B266
{
public:
    RefCountPtr<TextureClass> rva0009B266(int pidx, int pass, int stage) const;
private:
    char m_pad00[0x94];
    MeshMatDescClass *m_cur;
};

RefCountPtr<TextureClass> Rva0009B266::rva0009B266(int pidx, int pass, int stage) const
{
    return m_cur->Get_Texture(pidx, pass, stage);
}
