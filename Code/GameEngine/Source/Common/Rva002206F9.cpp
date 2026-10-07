// cl: /O1 /arch:SSE /G7 /MD
// Native 002206F9..0022074B RET4. Mode at +20 selects either the descriptor's
// bulk operation or count(+90) individual template lookups delivered to the
// embedded +4 sink's first virtual slot. Always returns true. Names are opaque.
class Rva002206F9Sink { public: virtual void add(void *value); };
class Rva0037DCA5
{
public:
 void *rva0037DC52();
 void rva0037DF8D(Rva002206F9Sink *sink);
 char pad[0x90];
 int count;
};
class Rva002206F9
{
public:
 bool rva002206F9(Rva0037DCA5 *descriptor);
private:
 char pad0[4];
 Rva002206F9Sink m_sink;
 char pad8[0x20-8];
 int m_mode;
};

bool Rva002206F9::rva002206F9(Rva0037DCA5 *descriptor)
{
 if (m_mode == 0)
  descriptor->rva0037DF8D(&m_sink);
 else
 {
  for (int i = 0; i < descriptor->count; ++i)
   m_sink.add(descriptor->rva0037DC52());
 }
 return true;
}
