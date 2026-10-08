// cl: /DNDEBUG /MD
// ?Rva00135F6CMakeUnique@@YAXPAX@Z retail 0x00135F6C 149B chain now-ready via 0x00171780
// Evidence: calls rowed Make_Unique 0x00149C10 with false; rowed rva0010E4D4 0x0010E4D4; tail jmp rowed rva00171780 0x00171780; callers 0x00137018 0x0013703A push RenderObjClass* from Create_Render_Obj.
class MeshModelClass;
class MeshClass
{
public:
    void Make_Unique(bool);
    MeshModelClass *Get_Model();
};
class Rva0010E4D4
{
public:
    void rva0010E4D4();
};
class MeshModelClass
{
public:
    void rva00171780();
    void Make_Geometry_Unique();
};
class Rva00135F6CNode
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual int v03();
    virtual void v04();
    virtual void *v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual int v28();
    virtual void v29();
    virtual void *v30(int);
    int m_ref;
};
class Rva00135F6CMesh
{
public:
    virtual void m00();
    virtual void m01();
    virtual void m02();
    virtual void m03();
    virtual void m04();
    virtual void m05();
    virtual void m06();
    virtual void m07();
    virtual void m08();
    virtual void m09();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void *m85();
    char m_pad[0xC0];
    MeshModelClass *m_model;
};
void __cdecl Rva00135F6CMakeUnique(void *p)
{
    Rva00135F6CNode *obj = (Rva00135F6CNode *)p;
    if (obj == 0)
        return;
    if (obj->v03() == 0)
    {
        Rva00135F6CMesh *mesh = (Rva00135F6CMesh *)obj->v05();
        ((MeshClass *)mesh)->Make_Unique(false);
        Rva0010E4D4 *holder = (Rva0010E4D4 *)((Rva00135F6CMesh *)mesh)->m85();
        holder->rva0010E4D4();
        if (holder != 0)
        {
            if (--((Rva00135F6CNode *)holder)->m_ref == 0)
                ((Rva00135F6CNode *)holder)->v00();
        }
        MeshModelClass *model = ((Rva00135F6CMesh *)mesh)->m_model;
        if (model == 0)
            return;
        return model->rva00171780();
    }
    int n = obj->v28();
    for (int i = 0; i < n; ++i)
    {
        Rva00135F6CNode *sub = (Rva00135F6CNode *)obj->v30(i);
        Rva00135F6CMakeUnique(sub);
        if (sub != 0)
        {
            if (--sub->m_ref == 0)
                sub->v00();
        }
    }
    return;
}

// Donor reference/open-bfme-1 @34f59164f6d1efd413c5fd37f4894ec834c3c0fe:
// game/GameEngine/Source/Common/Rva00739B30RenderObjectUnique.cpp semantic guide;
// native 10E4F6..10E5A2 proves bool ABI, refcount+4 and slots0/C/70/78/154.
static void releaseUniqueObject(Rva00135F6CNode *p) {
    if (p && --p->m_ref == 0) p->v00();
}
void rva0010E4F6(void *pointer, bool geometry)
{
    Rva00135F6CNode *object=(Rva00135F6CNode *)pointer;
    if (!object) return;
    if (object->v03()==0) {
        MeshClass *mesh=(MeshClass *)object;
        mesh->Make_Unique(false);
        Rva0010E4D4 *material=(Rva0010E4D4 *)((Rva00135F6CMesh *)object)->m85();
        material->rva0010E4D4();
        releaseUniqueObject((Rva00135F6CNode *)material);
        if (geometry) {
            MeshModelClass *model=mesh->Get_Model();
            model->Make_Geometry_Unique();
            releaseUniqueObject((Rva00135F6CNode *)model);
        }
    } else {
        int count=object->v28();
        for (int i=0;i<count;++i) {
            Rva00135F6CNode *sub=(Rva00135F6CNode *)object->v30(i);
            rva0010E4F6(sub,geometry);
            releaseUniqueObject(sub);
        }
    }
}
