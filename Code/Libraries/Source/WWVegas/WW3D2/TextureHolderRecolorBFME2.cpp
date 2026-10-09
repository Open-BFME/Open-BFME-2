// cl: /O1 /DNDEBUG /MD /EHsc
// Native132A93..132AF8/101B, holder-bound resource operation. WB9D4570
// and caller MeshClass::RecolorHouseColor14C470 independently establish the
// operation's relationship to recolour options. The original holder name and
// backend virtual method name remain unknown. Existing11F520/120F50 guard
// and rowed Apply132AF8 establish the same resource initialization protocol.
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class TextureRecolorLock {public:TextureRecolorLock(){BFME_DX8_Thread_Lock();}~TextureRecolorLock(){BFME_DX8_Thread_Assert();}};
class TextureRecolorResource {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();
 virtual bool Is_Initialized();virtual void Ensure();virtual void slot12();virtual void slot13();virtual void slot14();virtual bool RecolorOperation(void *);
};
class Rva00132A93 {public:TextureRecolorResource *object;bool rva00132A93(void *);bool Is_Initialized(){return object?object->Is_Initialized():false;}};
bool Rva00132A93::rva00132A93(void *options)
{
 TextureRecolorResource *resource=object;
 if(!resource)return false;
 TextureRecolorLock lock;
 if(!Is_Initialized())resource->Ensure();
 return resource->RecolorOperation(options);
}
