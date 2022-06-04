#include "pch.h"
#include "Literal.h"
//string view

Light::string_view::string_view()
{
	len = 0;
	str = NULL;
}

Light::string_view::string_view(const char * str)
{
	this->str = (char*)str;
	len = strlen(str);
}

Light::string_view::string_view(const char * str, int len)
{
	this->str = (char*)str;
	this->len = len;
}

char * Light::string_view::data()
{
	return str;
}

size_t Light::string_view::find(char c, size_t offset)
{
	auto current = str + offset;
	if (current != nullptr)
	{
		auto count_chars = size() - offset;
		for (register size_t i = 0; i < count_chars; i++)
		{
			auto val = *(current++);
			if (val == c)
			{
				return offset + i;
			}
		}
		return -1;
	}
	else
	{
		return -1;
	}
}

bool Light::string_view::startWith(const char * str, size_t offset)
{
	auto v1 = Light::string_view(str).size();
	auto v2 = size() - offset;

	if (v1 <= v2)
	{
		auto data_ = data() + offset;
		for (register size_t i = 0; i < v1; i++)
		{
			if (*(str++) != *(data_++))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}

}

size_t Light::string_view::size()
{
	return len;
}

char& Light::string_view::operator[](int index)
{
	return str[index];
}


char & Light::string_view::at(int index)
{
	return str[index];
}

Light::string_view Light::string_view::SubString(int index)
{
	if (index < len)
	{
		return Light::string_view(str + index, len - index);
	}
	return Light::string_view(0, 0);
}

bool Light::string_view::Equals(const char * str)
{
	if (str == this->str)
	{
		return true;
	}
	else
	{
		Light::string_view str1(str);
		auto sizetext = str1.size();
		if (sizetext == this->size())
		{
			const char* temp1 = str,*temp2 = (const char*)(this->str);
			for (size_t i = 0; i < sizetext; i++)
			{
				if (*(temp1++) != *(temp2++))
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

}

bool Light::string_view::Equals(string_view & str)
{
	auto sizetext = str.size();
	if (sizetext == this->size())
	{
		const char* temp1 = str.data(), *temp2 = (const char*)(this->str);
		for (size_t i = 0; i < sizetext; i++)
		{
			if (*(temp1++) != *(temp2++))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
int Light::string_view::Hash()
{
	if (len > 0)
	{
		int hash = 0;
		hash = *((int*)str);
		int free = 4 - len;
		if (free > 0)
		{
			auto hash_char = ((char*)&hash) + 3;
			while (free > 0)
			{
				(*hash_char--) = 0;
				free--;

			}
		}
		return hash;
	}
	return 0;
	
}
Light::string_view Light::string_view::operator=(const char * strng)
{
	return Light::string_view(strng);
}
void Light::string_view::Free()
{
	delete[] str;
	str = NULL;
	len = 0;
}

// string buffer
Light::StringBuffer::StringBuffer()
{
	offset = 0;
	len = 15;
	buff = TAlloc<char>(15);

}
void Light::StringBuffer::Add(char c)
{
	if (offset >= len)
	{
		resize(len * 2);
	}
	auto f = offset++;
	buff[f] = c;
}
void Light::StringBuffer::RemoveLast()
{
	if (offset > 0)
	{
		--offset;
	}
}
void Light::StringBuffer::resize(int newsize)
{
	auto newbuff = TAlloc<char>(newsize);
	auto minlen = len < newsize ? len : newsize;
	for (size_t i = 0; i < minlen; i++)
	{
		newbuff[i] = buff[i];
	}
	delete[] buff;

	buff = newbuff;
	len = newsize;
	if (offset >= newsize)
	{
		offset = newsize;
	}
}

Light::string_view Light::StringBuffer::ToString()
{
	return Light::string_view(buff);
}