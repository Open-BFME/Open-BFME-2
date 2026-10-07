// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD
// Reference lead: BFME 1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// S3GuardedGlobalTriples.cpp: three guarded manager calls and boolean list walks.
// Target wrappers 9A4A4/46 and 9A4D2/46 follow the rowed getLightPosWorld
// at 9A497/13 and end at 9A500. Native globals are DEBCD8, DEC2CC, DEC2D8;
// use their existing providers. The donor's manager order differs, so retain
// the target's volumetric/projected/opaque-manager mapping and existing names.
// Native third-manager callees are closed extents 1087BB/66 and 1087FD/69,
// with three list heads at +0C/+04/+08. Each detaches the head, then sets
// the node's byte at +04 while following +114. Node type, flag meaning and
// original method names remain unknown; these views carry address names.
// Reconstructed list walks adapt the donor's established boolean traversal
// pattern using those target-proven offsets and head-detachment stores.
struct Rva001087BBNode
{
    char m_unknown00[4];
    bool m_flag04;
    char m_unknown05[0x114-5];
    Rva001087BBNode *m_next114;
};
class Rva00108660ResourceManager
{
    void *m_unknown00;
    Rva001087BBNode *m_head04;
    Rva001087BBNode *m_head08;
    Rva001087BBNode *m_head0C;
public:
    void rva001087BB();
    void rva001087FD();
};
void Rva00108660ResourceManager::rva001087BB()
{
    Rva001087BBNode *node=m_head0C;
    m_head0C=0;
    for(;node;node=node->m_next114) node->m_flag04=false;
    node=m_head04;
    m_head04=0;
    for(;node;node=node->m_next114) node->m_flag04=false;
    node=m_head08;
    m_head08=0;
    for(;node;node=node->m_next114) node->m_flag04=false;
}
void Rva00108660ResourceManager::rva001087FD()
{
    Rva001087BBNode *node=m_head0C;
    m_head0C=0;
    for(;node;node=node->m_next114) node->m_flag04=true;
    node=m_head04;
    m_head04=0;
    for(;node;node=node->m_next114) node->m_flag04=true;
    node=m_head08;
    m_head08=0;
    for(;node;node=node->m_next114) node->m_flag04=true;
}
class W3DVolumetricShadowManager;
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
class W3DProjectedShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
class GenAlpha
{
public:
    void h00040601();
    void h000053B7();
};
class GenBeta
{
public:
    void h000217DD();
    void h00005592();
};
void rva0009A4A4()
{
    if(TheW3DVolumetricShadowManager)
        reinterpret_cast<GenAlpha *>(TheW3DVolumetricShadowManager)->h00040601();
    if(TheW3DProjectedShadowManager)
        reinterpret_cast<GenBeta *>(TheW3DProjectedShadowManager)->h000217DD();
    if(Rva00DEC2D8Manager) Rva00DEC2D8Manager->rva001087BB();
}
void rva0009A4D2()
{
    if(TheW3DVolumetricShadowManager)
        reinterpret_cast<GenAlpha *>(TheW3DVolumetricShadowManager)->h000053B7();
    if(TheW3DProjectedShadowManager)
        reinterpret_cast<GenBeta *>(TheW3DProjectedShadowManager)->h00005592();
    if(Rva00DEC2D8Manager) Rva00DEC2D8Manager->rva001087FD();
}
