#pragma once
#include "PngPack.h"
NS_CC_BEGIN
class RpgResourceManager{
public:
	static RpgResourceManager & getMe()
	{
		static RpgResourceManager rrm;
		return rrm;
	}
	void addResource(int resourceType,const char* packName,stLoadPackCallback *callback);
	enum{
		RESOURCE_TYPE_UI, // ������ 
		RESOURCE_TYPE_ACTION, // ������
		RESOURCE_TYPE_MAP, // ��ͼ�� 
	};
	PngPack * getResource(int resourceType);

	std::map<int,PngPack> packs;
	typedef std::map<int,PngPack>::iterator PACKS_ITER;
};

#define theUIPack RpgResourceManager::getMe().getResource(RpgResourceManager::RESOURCE_TYPE_UI)
#define theMapPack RpgResourceManager::getMe().getResource(RpgResoureManager::RESOURCE_TYPE_MAP)
#define theActionPack RpgResourceManager::getMe().getResource(RpgResoureManager::RESOURCE_TYPE_ACTION)
NS_CC_END