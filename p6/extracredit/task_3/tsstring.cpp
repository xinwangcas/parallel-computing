#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

#include "tsstring.hpp"

__attribute__((transaction_pure))
tsstring::tsstring() : str(NULL), length(0), cap(16){
	str = (char *)malloc(sizeof(char)*(cap + 1));
	memset(str, 0, sizeof(char)*(cap + 1));
}

__attribute__((transaction_pure))
tsstring::tsstring(const tsstring& o) : str(NULL) {
	length = o.size();
	cap = o.capacity();
	str = (char *)malloc(sizeof(char)*(cap + 1));
	strcpy(str, o.c_str());
	return;
}

__attribute__((transaction_pure))
bool tsstring::operator== (const tsstring& o) {
	if(strcmp(str, o.str) == 0)
		return true;
	else
		return false;
}

__attribute__((transaction_pure))
bool tsstring::operator>= (const tsstring& o) {
	if(strcmp(str, o.str) >= 0)
		return true;
	else
		return false;
}

__attribute__((transaction_pure))
tsstring& tsstring::operator+= (const tsstring& o) {
	if(length + o.size()  <= cap) {
		strcat(str, o.str);
	} else {
		while(cap < length + o.size()) {
			cap <<= 1;
		}
		char * str2 = (char*)malloc(sizeof(char)*(cap + 1));
		memset(str2, 0, sizeof(char)*(cap + 1));
		strcpy(str2, str);
		strcat(str2, o.str);
		free(str);
		str = str2;
	}
	length += o.size();
	return *this;
}

__attribute__((transaction_pure))
tsstring& tsstring::operator+= (const char* s) {
	int len = strlen(s);

	if(length + len  <= cap) {
		strcat(str, s);
	} else {
		while(cap < length + len) {
			cap <<= 1;
		}
		char * str2 = (char*)malloc(sizeof(char)*(cap + 1));
		memset(str2, 0, sizeof(char)*(cap + 1));
		strcpy(str2, str);
		strcat(str2, s);
		free(str);
		str = str2;
	}
	length += len;
	return *this;
}

__attribute__((transaction_pure))
tsstring& tsstring::operator+= (char c) {
	if(length + 1  <= cap) {
		str[length] = c;
	} else {
		while(cap < length + 1) {
			cap <<= 1;
		}
		char * str2 = (char*)malloc(sizeof(char)*(cap + 1));
		memset(str2, 0, sizeof(char)*(cap + 1));
		strcpy(str2, str);
		str2[length] = c;
		free(str);
		str = str2;
	}
	length++;
	return *this;
}

ostream& operator<< (ostream& os, const tsstring& o) {
	os << o.c_str();
	return os;
}

__attribute__((transaction_pure))
inline const char* tsstring::c_str() const {
	return str;
}

__attribute__((transaction_pure))
char& tsstring::operator[] (size_t pos) {
	if(pos < 0 || pos >= length)
		return str[length];
	else
		return str[pos];
}

__attribute__((transaction_pure))
const char& tsstring::operator[] (size_t pos) const {
	if(pos < 0 || pos >= length)
		return str[length];
	else
		return str[pos];
}

__attribute__((transaction_pure))
tsstring::~tsstring() {
	free(str);
}
