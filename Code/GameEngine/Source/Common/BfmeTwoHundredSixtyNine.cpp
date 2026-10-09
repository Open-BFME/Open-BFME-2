// cl: /Od
// BFME1 donor span-wrapper lead; target 2AC90..2ACBB RET8 is called for its unsigned search result.
// Native tokenizer309358 consumes EAX and supplies an unsigned position; earlier void/pointer ABI was incorrect.
// The range is the string prefix begin/end, position is an unsigned word.
struct BfmeRangePI { char *m_bfmeAt;char *m_bfmeEnd; };
class BfmeS1155 { public: unsigned bfmeFind1155(const char *,unsigned,unsigned); };
class BfmeThingPI { public: unsigned bfmeGoPI(const BfmeRangePI *,unsigned); };
unsigned BfmeThingPI::bfmeGoPI(const BfmeRangePI *span,unsigned pos)
{
 return reinterpret_cast<BfmeS1155 *>(this)->bfmeFind1155(span->m_bfmeAt,pos,span->m_bfmeEnd-span->m_bfmeAt);
}
