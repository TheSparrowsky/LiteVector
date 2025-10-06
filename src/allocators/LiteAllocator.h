#include <utility>
#include <new>
#include <memory>

namespace LV
{
	template<typename T>
	class LiteAllocator {

	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		LiteAllocator() = default;
		template<typename U>
		LiteAllocator(const LiteAllocator<U>&) noexcept {}

		pointer allocate(size_type n) 
		{
			return static_cast<pointer>(::operator new(n * sizeof(value_type)));
		}

		template<typename U>
		struct rebind 
		{
			using other = LiteAllocator<U>;
		};

		void deallocate(pointer ptr, size_type)
		{
			::operator delete(ptr);
		}

		template<typename U, typename... Args>
		void construct(U* ptr, Args&&... args)
		{
			new (ptr) U(std::forward<Args>(args)...);
		}

		template<typename U>
		void destroy(U* ptr)
		{
			ptr->~U();
		}

		template<typename U>
		bool operator==(const LiteAllocator<U>&) const noexcept {return true;}

		template<typename U>
		bool operator!=(const LiteAllocator<U>&) const noexcept {return false;}
	};
}
