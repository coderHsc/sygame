#pragma once
#include "cocos2d.h"
#include "ModelLoader.h"
NS_CC_BEGIN
struct stModelExecCharStar{
public:
	virtual void exec(const char *name) = 0;
};
/**
 * ��Ҫ�Ǽ̳���Sprite 
 *		����walkDir(int dir) ��ĳ��������һ�� ModelMoveAction
 */
class Model:public CCSprite{
public:
	CREATE_FUNC(Model);
	static Model * createWithModelName(const char *name);
	static Model * createWithModeXmlName(const char *name);
	/**
	 * ģ��Ĭ�ϳ�ʼ��
	 */
	bool init();
	/**
	 * ��xml �ļ��м���ģ������ ��ģ�����ݴ���ʱ ������
	 */
	bool initWithXml(const  char *name);
	/**
	 * ��ģ�������м���
	 */
	bool initWithModelName(const char*name);
	/**
	 * ͨ������ �� id ��ȡ�ƶ�����
	 */
	CCTexture2D *getMoveTexutueByDirAndFrameId(int dir,int nFrame);
	/**
	 * ����֡����Ϣ
	 */
	void updateFrame(int id,const char *pngName);
	/**
	 * ����֡������
	 **/
	void updateFrame(const char *state,const char *dir,int frameId,const char *pngName);
	static const int DIR_COUNT = 8; // ��ʶ8����
	static const int STATE_COUNT = 4; // ��ʶ״̬����
	static const int DIR_FRAMES = 8; // ÿ�������֡��
	static int getIdByActionName(const char*state,const char *dir);

	static void execEachState(stModelExecCharStar * exec);
	static void execEachDir(stModelExecCharStar * exec);

	/**
	 * ͨ�����õķ���ö�ٻ�ȡ��������
	 */
	static std::string getDirNameByDirEnum(int dir);

	static int getDirEnumNyName(const std::string &dirName);
public:
	/**
	 * ͣ����ĳ������
	 **/
	void stopDir(const char *dir);
	/**
	 * ��һ�������ƶ�һ��
	 * ���Զ�ִ��һ��moveAction
	 */
	void moveDir(int dir);

	void moveDir(const std::string& dirName);
	/**
	 * �ж��Ƿ��յ�
	 */
	void moveActionEnd();
private:
	int step;
	ModelData *data; // ģ�͵�����
	std::string name; // ģ�͵�����
	CCPoint nowPosition; // ��ǰ���ڵ�����λ��
	Model()
	{
		data = NULL;
		step = 45;
	}
};
NS_CC_END