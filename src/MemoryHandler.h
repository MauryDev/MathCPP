#pragma once
namespace std
{
	template<typename T>
	class Array_PTR
	{
	public:
		Array_PTR(T* array);
		~Array_PTR();
		T& operator[](int index);
		operator T*();

		void Free();
	private:
		T* val;
	};
	template<typename T>
	inline Array_PTR<T>::Array_PTR(T * array)
	{
		val = array;
	}
	template<typename T>
	inline Array_PTR<T>::~Array_PTR()
	{
		Free();
	}
	template<typename T>
	inline T& Array_PTR<T>::operator[](int index)
	{
		return val[index];
	}
	template<typename T>
	inline Array_PTR<T>::operator T*()
	{
		return this->val;
	}
	template<typename T>
	inline void Array_PTR<T>::Free()
	{
		if (val != nullptr)
		{
			delete[] val;
			val = NULL;
		}
	}
}