#pragma once
/**
 * ģ�ͼ����� ���ļ��м�������ģ��
 **/
#include <list>
#include <vector>
#include <map>
#include "serialize.h"
#include "cocos2d.h"
//#include <png.hpp>
NS_CC_BEGIN
/**
 * ֡����
 */
class FrameData:public serialize::Object{
public:
	int x,y,width,height;
	IMP_SERIALIZE_DATA_FUNC()
	{
		SERIALIZE_DATA(x,0);
		SERIALIZE_DATA(y,1);
		SERIALIZE_DATA(width,2);
		SERIALIZE_DATA(height,3);
	}
	FrameData()
	{
		x = y = width = height = 0; 
	}
};
/**
 * ͼ������
 */
class ImageData:public serialize::Object{
public:
	std::vector<FrameData> frames; // һ��ͼƬ���֡��
	int id;
	std::string imageName;
	std::vector<unsigned int> contents;
	CCTexture2D* texture;
	/**
	 * ���л�����
	 */
	IMP_SERIALIZE_DATA_FUNC()
	{
		SERIALIZE_DATA_CONDITION(imageName,0,imageName.size());
		SERIALIZE_DATA_CONDITION(contents,1,contents.size());
		SERIALIZE_DATA_CONDITION(frames,2,frames.size());
		SERIALIZE_DATA(id,3);
	}
	void clear()
	{
		contents.clear();
		frames.clear();

		texture = NULL;
	}
	ImageData()
	{
		texture = NULL;
	}
};
class ModelData:public serialize::Object{
public:
	std::string name; // ģ������
	int version; // �汾��
	int hashcode; // У����
	std::vector<ImageData> images;
	/**
	 * ���л�����
	 */
	IMP_SERIALIZE_DATA_FUNC()
	{
		SERIALIZE_DATA(version,0);
		SERIALIZE_DATA(hashcode,1);
		SERIALIZE_DATA_CONDITION(images,2,images.size());
	}
	bool checkImageDataValid(int id);
	
	CCTexture2D * getTextureById(int id);
	bool getFramesById(int id,std::vector<CCSpriteFrame*> &frames);
	/**
	 * �Ż�ģ������ ��Ҫ�ǽ�images �ϲ� �� С�� 256 * 256 ��ͼƬ���кϲ�
	 * �½�һ��png 512 * 512 Ȼ�����ͼƬ �� frameData ����512 �����µ�ͼƬ���� images ���� 512 * 512 ��ͼƬ
	 */
	void conbine();
	/**
	 * ��ȡpng ���ݷ�����imgages
	 */
	void loadImageData(int id, const char *pngName);
protected:
	void beLoaded();
#if (0)
	void doGetImage(ImageData &data,png::image< png::rgba_pixel > &img);
	void doMakeRect(ImageData &data,png::image< png::rgba_pixel > &img,int width,int height);
#endif
	typedef std::vector<ImageData>::iterator IMAGEDATA_LIST_ITER;
};

class ModelLoader{
public:
	static ModelLoader & getMe()
	{
		static ModelLoader loader;
		return loader;
	}
	std::map<std::string,ModelData*> models;
	typedef std::map<std::string,ModelData*>::iterator MODELS_ITER;
	ModelData * getModelDataByName(std::string name);

	static bool getFileList(std::vector<std::string> & fileList);
};

NS_CC_END
