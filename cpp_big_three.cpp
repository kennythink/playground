#include <iostream>
#include <assert.h>
#include <string.h>

using namespace std;

// https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)

class String {
public:
	String (const char *str = NULL);
	String (const String &other);
	~String(void);
	String& operator =(const String &other);
	void dump();
private:
	char *mData;
};

/* default constructor */
String::String(const char *str)
{
	if (str == NULL) 
	{
		mData = new char[1];
		mData[0] = '\0';
	} else {
		mData = new char[strlen(str)+1];
		assert(mData != NULL);
		strcpy(mData, str);
	}
}

/* default destructor */
String::~String() 
{
	delete[] mData;
}

/* copy constructor */
String::String(const String &other)
{
	mData = new char[strlen(other.mData)+1];
	assert(mData != NULL);
	strcpy(mData, other.mData);
}

/* assignment */
String& String::operator =(const String &other) 
{
	if (this == &other)
		return *this;
	delete[] mData;
	mData = new char[strlen(other.mData)+1];
	assert(mData != NULL);
	strcpy(mData, other.mData);
	return *this;	
}

void String::dump() {
	cout << mData << endl;
}


int main() 
{
	String s("Hello");
	String a("World");
	s.dump(), a.dump();
	
	s = a;
	s.dump(), a.dump();
	return 0;
}
