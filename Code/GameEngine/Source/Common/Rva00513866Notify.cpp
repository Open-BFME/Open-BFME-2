// cl: /O1 /G7 /MD /EHsc
// Native513866..513888 complete34B body uses no input arguments. Target
// data row identifies AptCreateAHero::s_instance at RVA A048D4; only its
// presence is tested. MessageStream slot18 receives29, then existing Apt
// enable owner222479 is tail-called through the canonical Apt manager global.
// The original method name and containing-class ownership are unresolved.
class AptCreateAHero {friend void Rva00513866();static AptCreateAHero *s_instance;};
class GameMessage;
class MessageStream {public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();virtual void slot16();virtual void slot17();virtual GameMessage *appendMessage(int);};
extern MessageStream *TheMessageStream;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222479ByteOneSetter {public:void enable();};
void Rva00513866(){if(AptCreateAHero::s_instance){TheMessageStream->appendMessage(29);((Rva00222479ByteOneSetter*)g_bfmeAptWindowManager)->enable();}}
