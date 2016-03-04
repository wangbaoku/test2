#include <cocos2d.h>
#pragma comment(lib,"libiconv.lib")

class Tools
{
public:
	Tools();
	~Tools();
	static std::string Unicode2Utf8(const std::wstring& widestring);
	static int GBKToUTF8(std::string &gbkStr);
private:

};


