// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// Native unwind action76457B calls the existing base destructor10846E.
class Rva00108475 {
public:
 virtual ~Rva00108475();
 virtual void slot01()=0; virtual void slot02()=0;
 virtual void slot03()=0; virtual void slot04()=0; virtual void slot05()=0;
};
class LightEnvironmentClass {
public: LightEnvironmentClass();
private: char body[0x228];
};
class Rva00108DBC : public Rva00108475 {
public:
 Rva00108DBC();
 virtual ~Rva00108DBC();
 virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void slot04(); virtual void slot05();
private:
 unsigned m_04,m_08,m_0c,m_10,m_14,m_18,m_1c,m_20;
 LightEnvironmentClass m_light;
 unsigned m_24c,m_250,m_254,m_258,m_25c,m_260,m_264,m_268,m_26c,m_270;
};
Rva00108DBC::Rva00108DBC() {
 m_0c=0;m_04=0;m_08=0;m_10=0;m_14=0;m_18=0;m_1c=0;
 m_250=0;m_24c=0;m_20=0;m_254=0;m_258=0;m_25c=0;
 m_260=0;m_264=0;m_268=0;m_26c=0;m_270=0;
}
