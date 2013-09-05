#include "cocos2d.h"
#include "Model.h"
#include "ModelLoader.h"
#include "ModelAction.h"
NS_CC_BEGIN
static const char* dirs[] = {
	"left",
	"right",
	"up",
	"down",
	"right_up",
	"right_down",
	"left_up",
	"left_down"
};

static const char* states[] = {
	"stop",
	"walk",
	"attack",
	"death",
};
CCTexture2D *Model::getMoveTexutueByDirAndFrameId(int dir,int nFrame)
{
	if (!data)
		data = ModelLoader::getMe().getModelDataByName(name);
	if (data)
	{
		std::string dirname = getDirNameByDirEnum(dir);
		int id = getIdByActionName("walk",dirname.c_str());
		return data->getTextureById(id * DIR_FRAMES+ nFrame);
	}
	return NULL;
}
bool Model::init()
{
	initWithTexture(NULL, CCRectZero);
	data = ModelLoader::getMe().getModelDataByName("test");
	return true;
}
/**
* ����֡����Ϣ
*/
void Model::updateFrame(int id,const char *pngName)
{
	if (data)
	{
		data->loadImageData(id,pngName);
	}
}
/**
 * ����֡������
 **/
void Model::updateFrame(const char *state,const char *dir,int frameId,const char *pngName)
{
	int id = getIdByActionName(state,dir);
	if ( -1 != id)
	{
		updateFrame(id * DIR_FRAMES + frameId,pngName);
	}
}
int Model::getIdByActionName(const char*state,const char *dir)
{
	int stateid = -1;
	int dirid = -1;
	for (int i = 0; i < STATE_COUNT;i++)
	{
		if (!strcmp(state,states[i]))
			stateid = i;
	}
	if (-1 == stateid) return -1;
	for (int i = 0; i < DIR_COUNT;i++)
	{
		if (!strcmp(dir,dirs[i]))
			dirid = i;
	}
	if (-1 == dirid) return -1;

	return stateid * STATE_COUNT + dirid;
}
std::string Model::getDirNameByDirEnum(int dir)
{
	switch(dir)
	{
	case ModelMoveAction::_DIR_NULL: return "";
	case ModelMoveAction::_DIR_LEFT: return "left";
	case ModelMoveAction::_DIR_UP:return "up";
	case ModelMoveAction::_DIR_RIGHT:return "right";
	case ModelMoveAction::_DIR_DOWN:return "down";
	case ModelMoveAction::_DIR_UP_RIGHT: return "rignt_up";
	case ModelMoveAction::_DIR_RIGHT_DOWN: return "right_down";
	case ModelMoveAction::_DIR_LEFT_UP: return "left_up";
	case ModelMoveAction::_DIR_DOWN_LEFT:return "left_down";
	}
	return "";
}
int Model::getDirEnumNyName(const std::string& dirName){
	if (dirName == std::string("left")) return ModelMoveAction::_DIR_LEFT;
	if (dirName == std::string("up")) return ModelMoveAction::_DIR_UP;
	if (dirName == std::string("right")) return ModelMoveAction::_DIR_RIGHT;
	if (dirName == std::string("down")) return ModelMoveAction::_DIR_DOWN;
	if (dirName == std::string("right_up")) return ModelMoveAction::_DIR_UP_RIGHT;
	if (dirName == std::string("right_down")) return ModelMoveAction::_DIR_RIGHT_DOWN;
	if (dirName == std::string("left_up")) return ModelMoveAction::_DIR_LEFT_UP;
	if (dirName == std::string("left_down")) return ModelMoveAction::_DIR_DOWN_LEFT;
	return ModelMoveAction::_DIR_NULL;
}

void Model::moveDir(const std::string& dirName)
{
	moveDir(getDirEnumNyName(dirName));
}
void Model::execEachState(stModelExecCharStar * exec)
{
	for (int i = 0; i < STATE_COUNT;i++)
	{
		if (exec)
			exec->exec(states[i]);
	}
}
void Model::execEachDir(stModelExecCharStar * exec)
{
	for (int i = 0; i < DIR_COUNT;i++)
	{
		if (exec)
			exec->exec(dirs[i]);
	}
}

/**
 * ͣ����ĳ������
 **/
void Model::stopDir(const char *dir)
{
	int id = getIdByActionName("stop",dir);
	if (-1 != id)
	{
		if (data)
		{
			this->stopAllActions();
			// ��������֡
			CCAnimation* animation = CCAnimation::create();
			for ( int i = 0; i < DIR_FRAMES;i++)
			{
				int nowFrameId = id * DIR_FRAMES+ i;
				CCTexture2D *texture = data->getTextureById(nowFrameId);
				if (texture)
				{
					 CCRect rect = CCRectZero;
					 rect.size = texture->getContentSize();
					animation->addSpriteFrameWithTexture(texture,rect);
				}
			}

			animation->setDelayPerUnit(0.2f);
			animation->setRestoreOriginalFrame(true);

			CCAnimate* animateAction = CCAnimate::create(animation);
#if (0)
			// ����spwan
			CCFiniteTimeAction*  action = CCSpawn::create(
			animateAction,
			NULL);
#endif
			this->runAction(animateAction);
		}
	}
}

/**
 * ��һ�������ƶ�һ��
 * ���Զ�ִ��һ��moveAction
 */
void Model::moveDir(int dir)
{
	float x = getPositionX();
	float y = getPositionY();
	switch(dir)
	{
		case ModelMoveAction::_DIR_NULL:
			{
				return;
			}break;
		case ModelMoveAction::_DIR_LEFT:
			{
				x = x - step;
			}break;
		case ModelMoveAction::_DIR_UP:
			{
				y = y + step;
			}
			break;
		case ModelMoveAction::_DIR_RIGHT:
			{
				x = x + step;
			}break;
		case ModelMoveAction::_DIR_DOWN:
			{
				y = y - step;
			}break;
		case ModelMoveAction::_DIR_UP_RIGHT: 
			{
				y = y + step;
				x = x + step;
			}break;
		case ModelMoveAction::_DIR_RIGHT_DOWN: 
			{
				x = x + step;
				y = y - step;
			}break;
		case ModelMoveAction::_DIR_LEFT_UP:
			{
				x = x - step;
				y = y + step;
			}break;
		case ModelMoveAction::_DIR_DOWN_LEFT:
			{
				x = x - step;
				y = y - step;
			}break;
		default:
			return;
	}
	CCPoint dest = ccp(x,y);
	// �����ƶ�����
	CCActionInterval*  moveToAction = ModelMoveAction::create(1.5f,ccp(dest.x,dest.y )); // ���ݷ������  
	if (moveToAction)
	{
		this->runAction(CCSequence::create(moveToAction,
				CCCallFunc::create(this, callfunc_selector(Model::moveActionEnd)),NULL)
				);
	}
}

/**
 * �ж��Ƿ��յ�
 */
void Model::moveActionEnd()
{

}
NS_CC_END