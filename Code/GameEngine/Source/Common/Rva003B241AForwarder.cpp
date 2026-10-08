// cl: /MD
// Native3B241A..3B242C complete18B destructor. Verified30D8B1 EH callback
//77A2D8 calls this target; ABB87 registration proves input4/token8 and
// BC9574 two-slot table. Existing consumer compatibility class spelling
// retained; original retail class name remains unknown. Explicit table
// store reproduces native cleanup without emitting a competing vtable.
// Namespace scope separates the external compatibility table declaration
// from MSVC's synthetic class vtable declaration. The linker name is unchanged.
namespace ParserBindingTable { extern "C" const void *const __identifier("??_7BfmeParserBindingBaseVE@@6B@")[]; }
class Q1Forwardee0000871A {public: void handle(int);};
class BfmeParserBindingBaseVE {
public: virtual ~BfmeParserBindingBaseVE(); virtual void bfmeSlot1()=0;
private: Q1Forwardee0000871A *m_4; int m_8;
};
BfmeParserBindingBaseVE::~BfmeParserBindingBaseVE() { int arg=m_8; *(const void **)this=ParserBindingTable::__identifier("??_7BfmeParserBindingBaseVE@@6B@"); m_4->handle(arg); }
