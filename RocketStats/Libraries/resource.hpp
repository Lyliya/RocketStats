#include <span>
#include <windows.h>

using namespace std;

class Resource
{
private:
	HRSRC hResource = nullptr;
	HGLOBAL hMemory = nullptr;

	struct ResourceData
	{
		std::size_t size_bytes = 0;
		void* ptr = nullptr;
	};

	ResourceData p;

public:
	Resource(int resource_id, const char* resource_class, HMODULE module_handle = nullptr)
		: hResource(FindResource(module_handle, MAKEINTRESOURCE(resource_id), __TEXT(resource_class)))
	{
		if (!hResource)
			return;

		hMemory = LoadResource(module_handle, hResource);
		if (!hMemory)
			return;

		p.size_bytes = SizeofResource(module_handle, hResource);
		p.ptr = LockResource(hMemory);
	}

	std::span<const char> GetResource()
	{
		return {static_cast<const char*>(p.ptr), p.size_bytes};
	}
};
