// cl: /O1 /MD
//
// ?DeleteModelGapFiller@Rva00DF6F94GapFillerContext@@QAEXPAVMeshModelClass@@@Z @ 0x001732E2 40B
// Evidence: callers in MeshModelClassDtor.cpp (0x001716FE 0x00172AFD) and MeshModelReset.cpp (0x00171FA4); callee dtor pin 0x0018C57C plus operator delete row 0x0002FD60; GapFiller at +0xBC per MeshModelClass layout.
class Rva001732C6 {
public:
  ~Rva001732C6();
};
void operator delete(void *p);
class MeshModelClass {
public:
  char m_pad[0xBC];
  Rva001732C6 *m_gapFiller;
};
class Rva00DF6F94GapFillerContext {
public:
  void DeleteModelGapFiller(MeshModelClass *mmc);
};
void Rva00DF6F94GapFillerContext::DeleteModelGapFiller(MeshModelClass *mmc)
{
  if (mmc->m_gapFiller != 0) {
    delete mmc->m_gapFiller;
  }
  mmc->m_gapFiller = 0;
}
