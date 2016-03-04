#include "ReadFile.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#include "cocos2d.h"
#include "Sound.h"
using namespace cocos2d;
static CReadFile * _Instance = nullptr;
CReadFile::CReadFile(void)
{
}


CReadFile::~CReadFile(void)
{
}

CReadFile * CReadFile::getInstance()
{
	if (!_Instance)
	{
		_Instance = new CReadFile;
	}
	return _Instance;
}


void CReadFile::init()
{
	if (!_isFileExist("wangbaoku.json"))
	{//���û���ļ�ʱ����һ��
		string data = FileUtils::getInstance()->getStringFromFile("wangbaoku.json");
		_saveFile(data.c_str(), "wangbaoku.json");
	}

	loadSpec();
}

bool CReadFile::loadSpec()
{
	string data = _getFileByName("wangbaoku.json");	// ��ȡ�ļ�����

	rapidjson::Document doc;

	doc.Parse<0>(data.c_str());

	if (doc.HasParseError())
	{// ��������
		CCLOG("%s",doc.GetParseError());
		return false;
	}
	else
	{// ��ʼ�����ļ�
		int j = 0;
		bool kg = doc["music"][j]["play"].GetBool();
		CSound::getInstance()->setIsPlay(kg);

		for (int i = 0; i < doc["user"].Size(); ++i)
		{
			ST_USER * user = new ST_USER;
			user->name = doc["user"][i]["name"].GetString();
			user->time = doc["user"][i]["time"].GetInt();
			
			m_userList.push_back(user);
		}
	}

	return true;
}

void CReadFile::saveUserInfo()
{
	//*** ���� json �ļ����洢�� getWritablePath �ļ����� ***
	rapidjson::Document writedoc;
	writedoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	rapidjson::Value array1(rapidjson::kArrayType);
	rapidjson::Value array2(rapidjson::kArrayType);

	//rapidjson::Value object(rapidjson::kObjectType);

	rapidjson::Value object1(rapidjson::kObjectType);

	// json object ��ʽ��� ������/ֵ�� ��
	object1.AddMember("play", CSound::getInstance()->getIsPlay(),	allocator);

	// json ��������
	array1.PushBack(object1, allocator);

	for (int i = 0; i < m_userList.size(); ++i)
	{
		rapidjson::Value object(rapidjson::kObjectType);

		// json object ��ʽ��� ������/ֵ�� ��
		object.AddMember("name",	m_userList.at(i)->name.c_str(),	allocator);
		object.AddMember("time",	m_userList.at(i)->time,		allocator);
		
		// json ��������
		array2.PushBack(object, allocator);
	}


	// json object ��ʽ��� ������/ֵ�� ��
	writedoc.AddMember("music", array1, allocator);
	writedoc.AddMember("user", array2, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	writedoc.Accept(writer);

	auto path = FileUtils::getInstance()->getWritablePath();	// д��·��
	path.append("wangbaoku.json");	// д���ļ���
	FILE* file = fopen(path.c_str(), "wb");
	if(file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}

string CReadFile::_getFileByName(string pFileName)
{  
	//��һ�Ȼ�ȡ�ļ���·��  
	string path = FileUtils::getInstance()->getWritablePath() + pFileName;  
	CCLOG("path = %s",path.c_str());  

	//����һ���ļ�ָ��  
	FILE* file = fopen(path.c_str(), "r");  

	if (file) {  
		char* buf;  //Ҫ��ȡ���ַ���  
		int len;    //��ȡ�ĳ���  
		/*��ȡ����*/  
		fseek(file, 0, SEEK_END);   //�Ƶ�β��  
		len = ftell(file);          //��ȡ����  
		rewind(file);               //�ع�ԭλ  
		CCLOG("count the file content len = %d",len);  
		//����buf�ռ�  
		buf = (char*)malloc(sizeof(char) * len + 1);  
		if (!buf) {  
			CCLOG("malloc space is not enough.");  
			return NULL;  
		}  

		//��ȡ�ļ�  
		//��ȡ����buf����λ��С�����ȣ��ļ�ָ��  
		int rLen = fread(buf, sizeof(char), len, file);  
		buf[rLen] = '\0';  
		CCLOG("has read Length = %d",rLen);  
		CCLOG("has read content = %s",buf);  

		string result = buf;  
		fclose(file);  
		free(buf);  
		return result;  
	}  
	else  
		CCLOG("open file error.");  

	return NULL;  
}  

bool CReadFile::_saveFile(const char *pContent, string pFileName)
{  
	//��һ��ȡ������ļ�·��  
	string path = FileUtils::getInstance()->getWritablePath() + pFileName;  
	CCLOG("wanna save file path = %s",path.c_str());  

	//����һ���ļ�ָ��  
	//·����ģʽ  
	FILE* file = fopen(path.c_str(), "w");  
	if (file) {  
		fputs(pContent, file);  
		fclose(file);  
	}  
	else  
		CCLOG("save file error.");  

	return false;  
}

bool CReadFile::_isFileExist(string pFileName)
{
	string path = FileUtils::getInstance()->getWritablePath() + pFileName;  
	return FileUtils::getInstance()->isFileExist(path);
}
