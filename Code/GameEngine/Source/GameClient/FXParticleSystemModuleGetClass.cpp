// cl: /O1
// BFME1 ConcreteModuleTemplate forwarding accessor transferred to BFME2.

namespace FXParticleSystem
{

template <int CATEGORY>
class DefaultModuleTag
{
};

template <typename TAG>
class ConcreteModuleClass
{
public:
    static const ConcreteModuleClass<TAG> &getInstance();
};

template <typename TAG>
class ConcreteModuleTemplate
{
public:
    virtual const ConcreteModuleClass<TAG> &getClass() const;
};

// ?getClass@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$DefaultModuleTag@$05@FXParticleSystem@@@2@XZ
template <>
const ConcreteModuleClass<DefaultModuleTag<6> > &
ConcreteModuleTemplate<DefaultModuleTag<6> >::getClass() const
{
    return ConcreteModuleClass<DefaultModuleTag<6> >::getInstance();
}

#define FX_DEFAULT_GET_CLASS(CATEGORY)                                      \
template <>                                                                \
const ConcreteModuleClass<DefaultModuleTag<CATEGORY> > &                   \
ConcreteModuleTemplate<DefaultModuleTag<CATEGORY> >::getClass() const       \
{                                                                          \
    return ConcreteModuleClass<DefaultModuleTag<CATEGORY> >::getInstance(); \
}

FX_DEFAULT_GET_CLASS(1)
FX_DEFAULT_GET_CLASS(2)
FX_DEFAULT_GET_CLASS(3)
FX_DEFAULT_GET_CLASS(7)
FX_DEFAULT_GET_CLASS(0)

#undef FX_DEFAULT_GET_CLASS

struct OrthoEmissionVelocityModuleTag
{
};

struct PointEmissionVolumeModuleTag
{
};

template <>
const ConcreteModuleClass<OrthoEmissionVelocityModuleTag> &
ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::getClass() const
{
    return ConcreteModuleClass<OrthoEmissionVelocityModuleTag>::getInstance();
}

template <>
const ConcreteModuleClass<PointEmissionVolumeModuleTag> &
ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::getClass() const
{
    return ConcreteModuleClass<PointEmissionVolumeModuleTag>::getInstance();
}

}
