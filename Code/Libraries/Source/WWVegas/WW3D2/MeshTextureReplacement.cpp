// cl: /DNDEBUG /MD
// BFME2 MeshClass::Replace_Texture, complete 189B body at RVA 0x0014B800.
// Reference source: EA BFME1 W3DAssetManager::replaceMeshTexture algorithm,
// adapted into MeshClass with retail owning handles and no status return.
// MeshClass ownership and VIRTUAL slot124 are independently established:
// .rdata raw7D29A8 -> RVA7D35A8 -> VA00BD35A8; constructors1495A0/149680
// and destructor14A5B0 store this vptr. Slots67/68/91 contain the verified
// MeshClass bounding-sphere/bounding-box/Scale methods; slot124 is 14B800.
// Get_Material_Info is slot85 (+154); Model is at +C4. The model replacement
// callee at172BF0 is independently recovered in MeshModelTextureReplacement.cpp.
// Sparse virtual declarations preserve the observed slot numbers.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {
public: void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this)+4); }
};
template<class T> class RefCountPtr {
public:
    T *p;
    RefCountPtr(const RefCountPtr &other) : p(other.p) { if(p) p->Add_Ref(); }
    ~RefCountPtr() { if(p) p->Release_Ref(); }
    bool operator==(const RefCountPtr &other) const { return p == other.p; }
    RefCountPtr &operator=(const RefCountPtr &other) {
        if(other.p) other.p->Add_Ref();
        if(p) p->Release_Ref();
        p=other.p;
        return *this;
    }
};
class RefCountClass {
public:
    virtual void Delete_This();
    int RefCount;
    void Add_Ref() { ++RefCount; }
    void Release_Ref() { if(--RefCount==0) Delete_This(); }
};
class MeshModelClass : public RefCountClass {
public: void Replace_Texture(const RefCountPtr<TextureClass>&, const RefCountPtr<TextureClass>&);
};
class MaterialInfoClass : public RefCountClass {
    char gap[0x1c];
    RefCountPtr<TextureClass> *Textures;
    char gap28[8];
    int TextureCount;
public:
    int Texture_Count() const { return TextureCount; }
    RefCountPtr<TextureClass> Peek_Texture(int);
    void Replace_Texture(int index,const RefCountPtr<TextureClass> &texture) { Textures[index]=texture; }
};
class MeshClass {
public:
    virtual void Unknown0();
    virtual void Unknown1();
    virtual void Unknown2();
    virtual void Unknown3();
    virtual void Unknown4();
    virtual void Unknown5();
    virtual void Unknown6();
    virtual void Unknown7();
    virtual void Unknown8();
    virtual void Unknown9();
    virtual void Unknown10();
    virtual void Unknown11();
    virtual void Unknown12();
    virtual void Unknown13();
    virtual void Unknown14();
    virtual void Unknown15();
    virtual void Unknown16();
    virtual void Unknown17();
    virtual void Unknown18();
    virtual void Unknown19();
    virtual void Unknown20();
    virtual void Unknown21();
    virtual void Unknown22();
    virtual void Unknown23();
    virtual void Unknown24();
    virtual void Unknown25();
    virtual void Unknown26();
    virtual void Unknown27();
    virtual void Unknown28();
    virtual void Unknown29();
    virtual void Unknown30();
    virtual void Unknown31();
    virtual void Unknown32();
    virtual void Unknown33();
    virtual void Unknown34();
    virtual void Unknown35();
    virtual void Unknown36();
    virtual void Unknown37();
    virtual void Unknown38();
    virtual void Unknown39();
    virtual void Unknown40();
    virtual void Unknown41();
    virtual void Unknown42();
    virtual void Unknown43();
    virtual void Unknown44();
    virtual void Unknown45();
    virtual void Unknown46();
    virtual void Unknown47();
    virtual void Unknown48();
    virtual void Unknown49();
    virtual void Unknown50();
    virtual void Unknown51();
    virtual void Unknown52();
    virtual void Unknown53();
    virtual void Unknown54();
    virtual void Unknown55();
    virtual void Unknown56();
    virtual void Unknown57();
    virtual void Unknown58();
    virtual void Unknown59();
    virtual void Unknown60();
    virtual void Unknown61();
    virtual void Unknown62();
    virtual void Unknown63();
    virtual void Unknown64();
    virtual void Unknown65();
    virtual void Unknown66();
    virtual void Unknown67();
    virtual void Unknown68();
    virtual void Unknown69();
    virtual void Unknown70();
    virtual void Unknown71();
    virtual void Unknown72();
    virtual void Unknown73();
    virtual void Unknown74();
    virtual void Unknown75();
    virtual void Unknown76();
    virtual void Unknown77();
    virtual void Unknown78();
    virtual void Unknown79();
    virtual void Unknown80();
    virtual void Unknown81();
    virtual void Unknown82();
    virtual void Unknown83();
    virtual void Unknown84();
    virtual MaterialInfoClass *Get_Material_Info();
    char gap[0xc0];
    MeshModelClass *Model;
    MeshModelClass *Get_Model() { if(Model) Model->Add_Ref(); return Model; }
    virtual void Unknown86();
    virtual void Unknown87();
    virtual void Unknown88();
    virtual void Unknown89();
    virtual void Unknown90();
    virtual void Unknown91();
    virtual void Unknown92();
    virtual void Unknown93();
    virtual void Unknown94();
    virtual void Unknown95();
    virtual void Unknown96();
    virtual void Unknown97();
    virtual void Unknown98();
    virtual void Unknown99();
    virtual void Unknown100();
    virtual void Unknown101();
    virtual void Unknown102();
    virtual void Unknown103();
    virtual void Unknown104();
    virtual void Unknown105();
    virtual void Unknown106();
    virtual void Unknown107();
    virtual void Unknown108();
    virtual void Unknown109();
    virtual void Unknown110();
    virtual void Unknown111();
    virtual void Unknown112();
    virtual void Unknown113();
    virtual void Unknown114();
    virtual void Unknown115();
    virtual void Unknown116();
    virtual void Unknown117();
    virtual void Unknown118();
    virtual void Unknown119();
    virtual void Unknown120();
    virtual void Unknown121();
    virtual void Unknown122();
    virtual void Unknown123();
    virtual void Replace_Texture(const RefCountPtr<TextureClass>&, const RefCountPtr<TextureClass>&);
};
void MeshClass::Replace_Texture(const RefCountPtr<TextureClass> &texture, const RefCountPtr<TextureClass> &new_texture)
{
    MeshModelClass *model = Get_Model();
    MaterialInfoClass *material = Get_Material_Info();
    for (int i = 0; i < material->Texture_Count(); ++i) {
        if (material->Peek_Texture(i) == texture) {
            model->Replace_Texture(texture, new_texture);
            material->Replace_Texture(i, new_texture);
        }
    }
    if(material) material->Release_Ref();
    if(model) model->Release_Ref();
}
