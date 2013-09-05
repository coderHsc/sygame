#include "AboutRequest.h"
#include "socket.h"
/**
 * ���󳡾�����Ϣ
 * \param mapWidth ��ͼ�Ŀ�
 * \param mapHeight ��ͼ�ĸ�
 */
IMP_REMOTE_FUNCTION(AboutRequest::getMapInfo)
	PARAM(int,mapWidth);
	PARAM(int ,mapHeight);
	BODY
	{
		printf("hello,world!");
		std::string content="test";
		theRequest.retMapInfo(socket,100,"test");
	}
REMOTE_FUNCTION_END

/**
 * ���󳡾�����Ϣ
 * \param mapWidth ��ͼ�Ŀ�
 * \param mapHeight ��ͼ�ĸ�
 */
IMP_REMOTE_FUNCTION(AboutRequest::reqLogin)
	PARAM(std::string,name);
	PARAM(std::string,pwd);
	BODY
	{
		printf("reqLogin");
	}
REMOTE_FUNCTION_END

