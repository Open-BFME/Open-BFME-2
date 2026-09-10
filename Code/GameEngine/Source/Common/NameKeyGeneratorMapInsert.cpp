// cl: /O1 /DNDEBUG /MD
//
// NameKeyGenerator::KeyToBucketMap::insert, retail 0x004DA240, 36 bytes.
// Dedicated TU so NameKeyGenerator.cpp cannot see this body. resize then
// the hashtable insert; count lives at +0x10.

class NameKeyGenerator
{
public:
	class KeyToBucketMap
	{
	public:
		struct value_type
		{
			int first;
			void *second;
		};

		struct insert_result
		{
			void *first;
			void *second;
			bool inserted;
		};

		insert_result insert(const value_type &value);

	private:
		char pad[0x10];
		unsigned m_count;
		void resize(unsigned);
		insert_result do_insert(const value_type &value);
	};
};

NameKeyGenerator::KeyToBucketMap::insert_result
NameKeyGenerator::KeyToBucketMap::insert(const value_type &value)
{
	resize(m_count + 1);
	return do_insert(value);
}
