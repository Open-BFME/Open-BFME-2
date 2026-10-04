// cl: /O1 /EHsc
// ?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$05@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@2@@Z @0x003AD6DF 60B
// Chain factory calling just-landed ctor 0x003ACD71 via new 0x1c. Evidence:
// export name; vtable slot 2 of 0x0081BE20; call to rowed ctor; operator new row.
class Rva003ACD71
{
public:
	Rva003ACD71(void *a, void *b);
private:
	char m_pad[0x1C];
};
namespace FXParticleSystem
{
class ParticleSystem;
template <class T> class TrackingPtr
{
};
template <int N> class DefaultModule
{
public:
	virtual ~DefaultModule();
};
template <int N> class DefaultModuleTag
{
};
template <class TAG> class ConcreteModuleTemplate
{
public:
	virtual DefaultModule<6> *createModule(TrackingPtr<ParticleSystem> &system);
};
}
FXParticleSystem::DefaultModule<6> *FXParticleSystem::ConcreteModuleTemplate<FXParticleSystem::DefaultModuleTag<6> >::createModule(TrackingPtr<ParticleSystem> &system)
{
	return (DefaultModule<6> *)new Rva003ACD71(&system, this);
}
