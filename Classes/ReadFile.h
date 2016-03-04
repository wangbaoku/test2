#pragma once
#include <string>
#include <vector>
using namespace std;
struct ST_USER
{
	string name;
	int time;
};
class CReadFile
{
public:
	bool loadSpec();
	void saveUserInfo();
	string _getFileByName(string pFileName);
	bool _saveFile(const char *pContent, string pFileName);
	bool _isFileExist(string pFileName);
	void init();
	static CReadFile * getInstance();
	void setshuomingkg(bool smkg){shuomingkg = smkg;};
	bool getshuomingkg(){return shuomingkg;};
	vector<ST_USER*> getUserList(){return m_userList;};
	void setUserInfo(ST_USER* user){m_userList.push_back(user);};

private:
	CReadFile(void);
	~CReadFile(void);
	vector<ST_USER*> m_userList;
	bool shuomingkg;
};

