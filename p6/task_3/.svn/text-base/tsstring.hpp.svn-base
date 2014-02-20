#ifndef TSSTRING_HPP
#define TSSTRING_HPP

class tsstring {
	char * str;
	size_t length;
	size_t cap;

public:
	//constructors
	__attribute__((transaction_pure))
		tsstring();
	__attribute__((transaction_pure))
		tsstring(const tsstring& o);

	__attribute__((transaction_pure))
		~tsstring();

	//compare
	__attribute__((transaction_pure))
		bool operator== (const tsstring& o);
	__attribute__((transaction_pure))
		bool operator>= (const tsstring& o); 

	//capacity
	inline size_t size() const {return length;}
	inline size_t capacity() const {return cap;}

	//modifiers
__attribute__((transaction_pure))
	tsstring& operator+= (const tsstring& o);
__attribute__((transaction_pure))
	tsstring& operator+= (const char* s);
__attribute__((transaction_pure))
	tsstring& operator+= (char c);

__attribute__((transaction_pure))
	const char* c_str() const;

__attribute__((transaction_pure))
	char& operator[] (size_t pos);
__attribute__((transaction_pure))
	const char& operator[] (size_t pos) const;
};

ostream& operator<< (ostream& os, const tsstring& o);

namespace std {
 template <> struct hash<tsstring> 
 {
 	size_t operator() (const tsstring& x) const
	{
		size_t ret = 5381;
		for(unsigned int i = 0; i < x.size(); ++i){
//			char ch = x[i];
//			ret += (hash<char>()(ch)<<i);
			ret = ((ret<<5) + ret) + x[i];
		}
		return ret;
	}
 };
}
#endif
