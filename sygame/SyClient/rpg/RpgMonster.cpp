#include "cocos2d.h"
#include "RpgMonster.h"
#include "PngPack.h"
#include "CalcDir.h"
#include "RpgMap.h"
#include "RpgUI.h"
#include "SoudManager.h"
NS_CC_BEGIN
/**
 * ��ȡ��֡
 */
bool RpgDirAction::getFrames(std::vector<CCSpriteFrame *> &frames)
{
	for (std::vector<std::string>::iterator iter = this->frames.begin(); iter != this->frames.end();++iter)
	{
		
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(iter->c_str());
		if (texture)
		{
		CCSpriteFrame *frame = CCSpriteFrame::frameWithTexture(texture,CCRectMake(0,0,texture->getContentSize().width,texture->getContentSize().height));
		frame->retain();
		frames.push_back(frame);
		}
		else
		{
			CCLOG("cant find texture");
			//TODO
		}
	}
	return true;
}
void RpgDirAction::takeNode(script::tixmlCodeNode *node)
{
	frameLoadType = node->getAttr("framestype");
	FramesName = node->getAttr("framenode");
		
	script::tixmlCodeNode frameNode = node->getFirstChildNode("frame");
	while(frameNode.isValid())
	{
		std::string frameName = frameNode.getAttr("name");
		frames.push_back(frameName);
		frameNode = frameNode.getNextNode("frame");
	}
}
void RpgConbineAction::takeNode(script::tixmlCodeNode *node)
{
	RpgAction::takeNode(node);
	node->getAttr("nexttype",nextType);
}
/**
 * ��������
 */
CartoonInfo* RpgConbineAction::getCartoonInfo(int dir)
{
	CartoonInfo *info = CartoonInfo::create();
	if (getFrames(dir,info->frames))
	{
		info->actionType = actionType;
		info->cartoonName = actionName;
		info->needTime = needTime;
		info->frameType = frameType;
		info->cartoonType = cartoonType;
	}
	return info;
}
/**
 * ����ڵ�
 */
void RpgAction::takeNode(script::tixmlCodeNode *node)
{
	actionName = node->getAttr("name");
	node->getAttr("type",actionType);
	std::string frameTypeStr = node->getAttr("frametype");
	if (frameTypeStr == "follow")
	{
		this->frameType = CartoonInfo::FOLLOW_FRAMES;
	}
	else if (frameTypeStr == "time")
	{
		this->frameType = CartoonInfo::TIME_FRAMES;
	}
	else
	{
		this->frameType = CartoonInfo::MOVE_FRAMES;
	}
	std::string cartoonTypeStr = node->getAttr("cartoontype");
	if (cartoonTypeStr == "other")
	{
		this->cartoonType = CartoonInfo::OTHER;
	}
	else
	{
		this->cartoonType = CartoonInfo::SELF;
	}
	script::tixmlCodeNode dirNode = node->getFirstChildNode("dir");
	if(dirNode.isValid())
	{
		int dirId = 0;
		RpgDirAction dirAction;
		dirNode.getAttr("id",dirId);
		dirAction.takeNode(&dirNode);
		dirActions[dirId] = dirAction;
	}
	node->getAttr("needtime",needTime);
	node->getAttr("actiontype",actionType);
}
/**
 * ��ȡ֡����
 * \param frames ֡���� 
 */
bool RpgAction::getFrames(int dir,std::vector<CCSpriteFrame *> &frames)
{
	DIRACTIONS_ITER iter = dirActions.find(dir);
	if (iter != dirActions.end())
	{
		if (iter->second.frameLoadType == "frames")
		{
			return iter->second.getFrames(frames);
		}
		if (iter->second.frameLoadType == "pack")
		{
			std::string &framesName = iter->second.FramesName;
			return PngPack::getMe().getFrames(framesName.c_str(),frames);
		}
	}
	return false;
}
/**
 * ��������
 */
RpgMonster * RpgMonster::create(int id)
{
	RpgMonster * pRet = new RpgMonster();
	if (pRet && pRet->init(id))
	{
        pRet->autorelease();
		pRet->setColor(ccc3(200,189,167));
		//pRet->setScale(1.6);
		theObjectM.addObject(pRet);
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
bool RpgMonster::isReachDestination()
{
	if (this->getGridPoint().equal(nowDestination,3))
	{
		return true;
	}
	return false;
}
bool RpgMonster::init(int id)
{
	CCSprite::init();
	rpgSprite = CCSprite::create();
	if (rpgSprite)
	{
		this->addChild(rpgSprite);
		attachSprite(this);
		MonsterManager::getMe().initMonsterData(id,monsterData);
		MonsterManager::getMe().initMonseterPath(monsterData.walkPathId,this->path);
		hp = monsterData.maxHp;
		MonsterManager::getMe().getActionByName(monsterData.monsterName.c_str(),actions);
		setDir(CalcDir::_DIR_LEFT);
		this->start(IDLE_ACTION);
		showHp();
	}
	return true;
}
void RpgMonster::setDir(int dirType)
{
	dir = dirType;
	switch(dirType)
	{
		case CalcDir::_DIR_LEFT_UP:
		case CalcDir::_DIR_DOWN_LEFT:
		case CalcDir::_DIR_LEFT:
		{
			this->setFlipX(true);
            faceDir = CalcDir::_DIR_LEFT;
		}break;
		case CalcDir::_DIR_UP_RIGHT:
		case CalcDir::_DIR_RIGHT_DOWN:
		case CalcDir::_DIR_RIGHT:
		{
			this->setFlipX(false);
            faceDir = CalcDir::_DIR_RIGHT;
		}break;
	}
}

/**
 * ��ȡ������Ϣ
 * \param actionName ��������
 * \param dir ��������
 * \param info ������Ϣ
 */
bool RpgMonster::getCartoonInfo(const std::string& actionName,int dir, CartoonInfo &info)
{
	ACTIONS_ITER iter = actions.find(actionName);
	if (iter != actions.end())
	{
		if (iter->second.getFrames(dir,info.frames))
		{
		//	info.actionType = iter->second.actionType;
			info.cartoonName = iter->second.actionName;
			info.needTime = iter->second.needTime;
			info.cartoonType = iter->second.cartoonType;
		}
	}
	return true;
}
/**
 * ִ����һ��
 */
void RpgMonster::nextStep()
{
	if (isDeath())
	{
		this->setVisible(false);
		return;
	}
	RpgMap * map = (RpgMap*) this->getParent();
	if (this->isNowAction(ACTION_DEATH))
	{
		this->setVisible(false);
		deathTag = true;
		/**
		 * ���õ����ڳ�����
		 */
		dropItems();
	}
	else
	{
		theActionLib.doAction(monsterData.actionId,this);
	}
	/*
	else if (this->isNowAction(ACTION_MOVE))
	{
		tryMove();
	}
	else if (this->isNowAction(ACTION_BE_ATTACK))
	{
		// �����ǰ�Ǳ���״̬
		this->tryConbineAction(IDLE_ACTION);
	}
	else if (this->isNowAction(ACTION_ATTACK))
	{
		// ���Լ��㹥����ֵ
		
		nowSkillName = "";
	}
	else this->tryConbineAction(IDLE_ACTION); // Ĭ��ִ�п�����Ϊ
	doAttack();
//	doDeath();
*/
}
void RpgMonster::doDeath()
{
	// �鿴�Լ��Ƿ�Ӧ����ʧ
/*	cc_timeval nowTime;
	CCTime::gettimeofdayCocos2d(&nowTime, NULL);
	if (CCTime::timersubCocos2d(&birthTime,&nowTime) >= 1000*60)
*/
	{
		//this->setColor(ccc3(255,0,0));
		tryConbineAction(ACTION_DEATH);
	}
}
void RpgMonster::visit()
{
	/*
	cc_timeval nowTime;
	CCTime::gettimeofdayCocos2d(&nowTime, NULL);
	double tapTime = CCTime::timersubCocos2d(&birthTime,&nowTime);
	if (tapTime >= 1000*43 && tapTime < 1000*50)
	{
		if (nowTime.tv_sec % 2 == 1)
			this->setColor(ccc3(255,0,0));
		else
			this->setColor(ccc3(255,255,255));
	}
	if (isNowAction(ACTION_DEATH) && !isDeath())
	{
		
		if (nowTime.tv_sec % 2 == 1)
			this->setColor(ccc3(255,255,0));
		else
			this->setColor(ccc3(0,0,0));
	}
	*/
	RpgObject::visit();
}
/**
 * ��������
 */
CartoonInfo* RpgMonster::v_makeCartoon(int actionType)
{
	RpgMap * map = (RpgMap*) this->getParent();
	CartoonInfo *info = CartoonInfo::create();
	info->actionType = actionType;
	switch(actionType)
	{
		case ACTION_DEATH: // ��������
		{
			 if (getCartoonInfo("death",0,*info))
				 return info;
		}break;
		case ACTION_BIRTH: // ��������
		{
			if (getCartoonInfo("birth",0,*info))
				return info;
		}break;
		case ACTION_MOVE: // ��·
		{
			CCPoint dest = getPixelPositionByDir(dir); // ���ݷ����ȡ��һ��λ��
			if (dest.x <0 || dest.x >= map->canBlockSize.width || dest.y <46 || dest.y >= map->canBlockSize.height)
			{
				return NULL;
			}
			else if (!nowDestination.isInvalid())
				if (getCartoonInfo("move",0,*info))
					return info;
		}break;
		case ACTION_ATTACK: // ����
		{
			//TODO ���ݼ��ܻ�ȡ
			if (!useatkskills.empty())
			{

				std::string& useatkname = useatkskills.front();
				nowSkillName = useatkname;
				//if (getCartoonInfo(useatkname,dir,*info))
				info = MonsterManager::getMe().getCobineCartoon(useatkname.c_str(),0);
				if (info)
				{
					useatkskills.pop_front();
					info->actionType = ACTION_ATTACK;
					return info;
				}
				return NULL;
			}
		}break;
		case ACTION_BE_ATTACK: // ����
		{
			if (getCartoonInfo("beattack",0,*info))
				return info;
		}break;
		case IDLE_ACTION: // ����
		{
			
		}break;
	}
	if (getCartoonInfo("idle",0,*info)) // Ĭ��ִ�п�����Ϊ
		return info;
	return NULL; // error
}
void RpgMonster::putAtkSkill(const std::string& skillname)
{
	for (std::list<std::string>::iterator iter = useatkskills.begin(); iter != useatkskills.end();)
	{
		if (skillname == *iter)
		{
			
			iter = useatkskills.erase(iter);
		}
		else
			++iter;
	}
	useatkskills.push_front(skillname);
	this->tryConbineAction(ACTION_ATTACK);
}
/**
 * ִ�ж���
 */
void RpgMonster::v_putCartoon(CartoonInfo *action)
{
	// �������;����Լ���չʾ
	if (!action) return;
	RpgMap *map = getMap();
	
	switch(action->actionType)
	{
		case ACTION_ATTACK:
		{
			// ���ݼ��ܻ�ȡ
			this->runAction(this->getParent(),action,ccp(0,0),NULL);
		}break;
		case  ACTION_MOVE:
		{
			//theSound.play("monstermove");
			CCPoint dest = getPixelPositionByDir(dir); // ���ݷ����ȡ��һ��λ��
			this->runSelfAction(*action,dest);
		}break;
		case ACTION_BIRTH:
		{
			this->runSelfAction(*action,ccp(0,0));
		}break;
		case IDLE_ACTION:
		{
			this->runSelfAction(*action,ccp(0,0));
		}break;
		case ACTION_BE_ATTACK:
		{
			this->runSelfAction(*action,ccp(0,0));
		}break;
		case ACTION_DEATH:
		{
			theSound.play("monsterattack");
			this->runSelfAction(*action,ccp(0,0));
		}break;
	}
}
struct stFindTarget:stExecEachTarget{
	void exec(RpgObject *object)
	{
		if (objects.size() < 5 && object->isType(RpgObject::RPG_PLAYER))
		{
			objects.push_back(object);
		}
	}
	RpgObject * getRandomObject()
	{
		if (!objects.empty())
		{
			return objects.at(CCRANDOM_0_1() * objects.size());
		}
		return NULL;
	}
	stFindTarget()
	{
		nowSize = 0;
	}
	std::vector<RpgObject*> objects;
	int nowSize;
}findTarget;
void RpgMonster::doAttack()
{
	// ��鵱ǰĿ���Ƿ�ʧЧ ����Ƿ�Զ�� ��Զ����������
	RpgMap *map = getMap();
	if (nowTarget)
	{
		RpgObject * monster = (RpgObject*)theObjectM.findObject(quickTargetId);
		if (monster != nowTarget)
		{
			nowTarget = NULL; // nowTarget ��ʧ
		}
	}
	if (!nowTarget)
	{
		// ���ҵз�Ŀ��
		
		
		if (map)
		{
			map->execTargets(this->getGridPoint(),monsterData.eyeshort,&findTarget);
			RpgObject *object = findTarget.getRandomObject();
			if (object)
			{
				nowTarget = object;
			}
		}
	}
	if (nowTarget)
	{
		quickTargetId = nowTarget->getUniqueQuickId();
		// ����Ƿ��ڹ��������� �����ڹ���������
		int dis = calcDistance(((RpgMonster*)nowTarget)->getGridPoint());
		int atkDis = CCRANDOM_0_1() * monsterData.maxAtkDistance + 2;
		if (/*dis <= eyeshort &&*/ dis >= atkDis) // ��walk ����
		{
			nowDestination = ((RpgMonster*)nowTarget)->getValidCirclePoint();
			tryMove();
		}
		if (dis>= atkDis/2 && dis <= atkDis) // �߹�������
		{
			if (((RpgMonster*)nowTarget)->checkValidAtkPoint(this->getGridPoint()))
		//	if (!map->checkCollide(this,this->getGridPoint()))
			{
				putAtkSkill("mattack");
				int nowDir = CalcDir::calcDir(ccp(this->getGridPoint().x,this->getGridPoint().y),ccp(((RpgMonster*)nowTarget)->getGridPoint().x,((RpgMonster*)nowTarget)->getGridPoint().y));
				setDir(nowDir);
				((RpgMonster*)nowTarget)->beAttacked(10);
			}
			else
			{
				nowDestination = ((RpgMonster*)nowTarget)->getValidAtkPoint();
				tryMove();
			}
		}
	}
}

void RpgMonster::tryMove()
{
	RpgMap *map = getMap();
	bool continueTag = true;
	GridPoint tempPoint = nowDestination;
	if (nowDestination.isInvalid())
	{
		return;
	}
	int count = 0;
	int nowDir = CalcDir::calcDir(ccp(this->getGridPoint().x,this->getGridPoint().y),ccp(tempPoint.x,tempPoint.y));
	while(continueTag)
	{
		if (count++ >= 15)
		{
			break;
		}
		nowDir = CalcDir::calcDir(ccp(this->getGridPoint().x,this->getGridPoint().y),ccp(tempPoint.x,tempPoint.y));
		
		if (map->checkCollide(this,tempPoint))
		{
			tempPoint = this->getValidCirclePoint();
			continueTag = true;
			continue;
		}
		
		continueTag = false;
		
	}
	if (this->isReachDestination())
	{
		return;
	}
	this->tryConbineAction(RpgMonster::ACTION_MOVE);
	CCPoint dest = getPixelPositionByDir(nowDir); // ���ݷ����ȡ��һ��λ��
	if (dest.x <0 || dest.x >= map->canBlockSize.width || dest.y <46 || dest.y >= map->canBlockSize.height)
	{
		this->clearAction(ACTION_MOVE);
		this->tryConbineAction(IDLE_ACTION);
	}
	/*
	zPos out;
	zPos srcPos = zPos(this->getGridPoint().x,this->getGridPoint().y);
	zPos destPos = zPos(nowDestination.x,nowDestination.y);
	if (this->getNextPos(srcPos,destPos,out,monsterData.step/32,100))
	{
		nowDir = CalcDir::calcDir(ccp(this->getGridPoint().x,this->getGridPoint().y),ccp(out.x,out.y));
		map->preUpdateMonster(this,GridPoint(out.x,out.y));
		// �����ǰ���ƶ�״̬ �鿴�Ƿ񵽴�Ŀ�� ������ ���Խ���IDLE ��Ϊ
		this->tryConbineAction(RpgMonster::ACTION_MOVE);
	}
	else
	{
		this->clearAction(ACTION_MOVE);
		this->tryConbineAction(IDLE_ACTION);
	}
	*/
	setDir(nowDir);
	if (map)
	{
		map->updateMonster(this);
	}
}
/**
 * ��ȡһ������Ч�ĵ�
 */
GridPoint RpgMonster::getValidCirclePoint()
{
	RpgMap *map = getMap();
	if (map)
	{
		return map->getValidGridPoint(this->getGridPoint(),RpgMap::MONSTER_BLOCK);
	}
	return GridPoint(-1,-1);
}
GridPoint RpgMonster::getRandomPoint(const CCSize &rect)
{
	return this->getGridPoint();
	GridPoint point = this->getGridPoint();
	point.x = point .x - rect.width /2;
	if (point.x < 0) point.x = 0;
	point.y = point .y - rect.height /2;
	if (point.y < 0) point.y = 0;
	
	point.x += CCRANDOM_0_1() * rect.width;
	point.y += CCRANDOM_0_1() * rect.height;
	return point;
}
/**
 * ��ȡ��Ч�Ĺ�����
 */
GridPoint RpgMonster::getValidAtkPoint()
{
	RpgMap *map = getMap();
	if (map)
	{
		return map->getValidAtkPoint(this->getGridPoint());
	}
	return GridPoint(-1,-1);
}
/**
 * �����Ƿ��ǿ��Թ����ĵ�
 */
bool RpgMonster::checkValidAtkPoint(const GridPoint &point)
{
	RpgMap *map = getMap();
	if (map)
	{
		return map->checkValidAtkPoint(this->getGridPoint(),point);
	}
	return false;
}
/**
 * �������
 * \param point Ŀ�ĵ�
 */
unsigned int RpgMonster::calcDistance(const GridPoint &point)
{
	unsigned int dx = abs(point.x - this->getGridPoint().x);
	unsigned int dy = abs(point.y - this->getGridPoint().y);
	if (dx > dy) return dx;
	return dy;
}
CCPoint RpgMonster::getPixelPositionByDir(int dir)
{
	switch(dir)
	{
		//monsterData.step = 128;
		case CalcDir::_DIR_DOWN:return ccpAdd(this->getPosition(),ccp(0,monsterData.step));
		case CalcDir::_DIR_LEFT:return ccpAdd(this->getPosition(),ccp(-monsterData.step,0));
		case CalcDir::_DIR_RIGHT:return ccpAdd(this->getPosition(),ccp(monsterData.step,0));
		case CalcDir::_DIR_UP:return ccpAdd(this->getPosition(),ccp(0,-monsterData.step));
		case CalcDir::_DIR_DOWN_LEFT:return ccpAdd(this->getPosition(),ccp(-monsterData.step,monsterData.step));
		case CalcDir::_DIR_RIGHT_DOWN:return ccpAdd(this->getPosition(),ccp(monsterData.step,monsterData.step));
		case CalcDir::_DIR_UP_RIGHT:return ccpAdd(this->getPosition(),ccp(monsterData.step,-monsterData.step));
		case CalcDir::_DIR_LEFT_UP:return ccpAdd(this->getPosition(),ccp(-monsterData.step,-monsterData.step));
	}
	return getPosition();
}
GridPoint RpgMonster::getGridPoint()
{
	return oldGridPoint;
}
GridPoint RpgMonster::getNowGridPoint()
{
	RpgMap *map = getMap();
	if (map)
	{
		return map->getGridPointByPixelPoint(this->getPosition());
	}
	return GridPoint(-1,-1);
}
//////////////////MonsterManager����////////////////////////
MonsterManager & MonsterManager::getMe()
{
	static MonsterManager mm;
	return mm;
}
/**
 * ��������
 */
void MonsterManager::loadConfig()
{
	unsigned long nSize = 0;
	unsigned char * buffer = CCFileUtils::sharedFileUtils()->getFileData("monsteraction.xml","rb",&nSize);
	if (!nSize)return;
	if (script::tixmlCode::initFromString((char*) buffer))
	{
		
	}
	return;
}
/**
 * �������ļ��м�������
 * \param node ���ø��ڵ�
 */
void MonsterManager::takeNode(script::tixmlCodeNode *node)
{
	/**
	 * �����Ϊ �Ͷ����Ķ��� �����ڵ�ͼ������ �����ط� ϵͳ����������� ���� �� ����
	 * ���action.pack �л�ȡ������
	 * theActionPack.getFrames(name,frameSet);
	 * action.xml �л�ȡ���Ƶ���Ϊ
	 *	<actions name="">
	 *     <action name="move" type="frames"> <!--�ƶ�-->
	 *			<dir id="" framesname="" framestype="">
	 *				<frame name=""
	 *			</dir>
	 *	   </action>
	 *	   <action name="attack"> <!--����-->
	 *	   </action>
	 *	   <action name="death"> <!--����-->
	 *	   </action>
	 *	   <action name="beattack"> <!--����-->
	 *	   </action>
	 *	   <action name="birth"> <!--����-->
	 *     </action>
	 *	   <action name="short"> <!--�������-->
	 *	   </action>
	 *	</actions>
	 **/
	if (node && node->equal("Config"))
	{
		// ���ع��ﶯ��
		script::tixmlCodeNode actionsNode = node->getFirstChildNode("actions");
		while(actionsNode.isValid())
		{
			std::string actionsName = actionsNode.getAttr("name");
			RpgMonster::ACTIONS actionmap;
			script::tixmlCodeNode actionNode = actionsNode.getFirstChildNode("action");
			while(actionNode.isValid())
			{
				RpgAction rpgAction;
				rpgAction.takeNode(&actionNode);
				actionmap[rpgAction.actionName] = rpgAction;
				actionNode = actionNode.getNextNode("action");
			}
			actionmaps[actionsName] = actionmap;
			actionsNode = actionsNode.getNextNode("actions");
		}
		// ������϶���
		script::tixmlCodeNode conbinesNode = node->getFirstChildNode("cobineactions");
		if (conbinesNode.isValid())
		{
			script::tixmlCodeNode actionsNode = conbinesNode.getFirstChildNode("actions");
			while(actionsNode.isValid())
			{
				std::string actionsName = actionsNode.getAttr("name");
				script::tixmlCodeNode actionNode = actionsNode.getFirstChildNode("action");
				COBINE_ACTIONS actions_vec;
				while(actionNode.isValid())
				{
					RpgConbineAction rpgAction;
					rpgAction.takeNode(&actionNode);
					actions_vec.push_back(rpgAction);
					actionNode = actionNode.getNextNode("action");
				}
				conbineactionmaps[actionsName] = actions_vec;
				actionsNode = actionsNode.getNextNode("actions");
			}
		}
		// ���ع�������
		script::tixmlCodeNode monsterData = node->getFirstChildNode("monsterdata");
		while (monsterData.isValid())
		{
			RpgMonsterData data;
			data.takeNode(&monsterData);
			monsterDatas[data.id] = data;
			monsterData = monsterData.getNextNode("monsterdata");
		}
		script::tixmlCodeNode pathData = node->getFirstChildNode("path");
		while (pathData.isValid())
		{
			int id = 0;
			pathData.getAttr("id",id);
			script::tixmlCodeNode pointData = pathData.getFirstChildNode("point");
			while (pointData.isValid())
			{
				CCPoint point;
				pointData.getAttr("x",point.x);
				pointData.getAttr("y",point.y);
				paths[id].push_back(point);
				pointData = pointData.getNextNode("point");
			}
			pathData = pathData.getNextNode("path");
		}
		script::tixmlCodeNode rectData = node->getFirstChildNode("rect");
		while (rectData.isValid())
		{
			CCRect rect;
			int id = rectData.getInt("id");
			rectData.getAttr("x",rect.origin.x);
			rectData.getAttr("y",rect.origin.y);
			rectData.getAttr("width",rect.size.width);
			rectData.getAttr("height",rect.size.height);
			activeRects[id] = rect;
			rectData = rectData.getNextNode("rect");
		}
	}
}
bool MonsterManager::initMonsterData(int id,RpgMonsterData &data)
{
	MONSTERDATAS_ITER iter = monsterDatas.find(id);
	if (iter != monsterDatas.end())
	{
		data = iter->second;
		return true;
	}
	return false;
}
bool MonsterManager::initMonseterPath(int pathId,std::vector<CCPoint> &path)
{
	PATHS_ITER iter = paths.find(pathId);
	if (iter != paths.end())
	{
		path = iter->second;
		return true;
	}
	return false;
}
bool MonsterManager::initMonsterRect(int rectId,CCRect &rect)
{
	ACTIVE_RECTS_ITER iter = activeRects.find(rectId);
	if (iter != activeRects.end())
	{
		rect = iter->second;
		return true;
	}
	return false;
}
/**
 * ��ȡ��������
 */
bool MonsterManager::getActionByName(const char *actionName,RpgMonster::ACTIONS &actionmap)
{
	ACTIONMAPS_ITER iter = actionmaps.find(actionName);
	if (iter != actionmaps.end())
	{
		actionmap = iter->second;
		return true;
	}
	return false;
}
/**
 * ��ȡ����
 */
CartoonInfo * MonsterManager::getCobineCartoon(const char *actionName,int dir)
{
	CONBINEACTIONMAPS_ITER iter = conbineactionmaps.find(actionName);
	if (iter != conbineactionmaps.end())
	{
		COBINE_ACTIONS& actions = iter->second;
		CartoonInfo *root = NULL;
		CartoonInfo * temp = NULL;
		for (COBINE_ACTIONS::iterator pos = actions.begin(); pos != actions.end();++pos)
		{
			if (temp)
			{
				temp->nextCartoon = pos->getCartoonInfo(dir);
				temp = temp->nextCartoon;
				temp->nextConbineType = pos->nextType;
			}
			else if (!root)
			{
				root = pos->getCartoonInfo(dir);
				temp = root;
				temp->nextConbineType = pos->nextType;
				continue;
			}
			else
			{
				break;
			}
		}
		return root;
	}
	return NULL;
}
bool RpgMonster::moveable(const zPos &tempPos,const zPos &destPos,const int radius1)
{
	GridPoint testPoint = GridPoint(tempPos.x,tempPos.y);
	if (testPoint.isInvalid()) return false;
	RpgMap * map = this->getMap();
	if (map)
	{
		//if (map->checkBlock(map->getIndexByGridPoint(testPoint),RpgMap::MONSTER_BLOCK))
		if (map->checkCollide(this,testPoint))
		{
			return false;
		}
	}
	return true;
}
void RpgMonster::beAttacked(int atkValue)
{
	int oldhp = hp;
	if (hp >= atkValue)
	{
		hp -= atkValue;
	}
	else
	{
		hp = 0;
	}
	if (hp <=0)
	{
		doDeath(); // RpgMonster ������
	}
	atkValue = hp - oldhp;
	if (atkValue)
	{
		std::stringstream ss;
		ss << atkValue;
		// 99
		CCLabelAtlas *labelAtlas = CCLabelAtlas::create(ss.str().c_str(),"numbers_1.png", 41.28, 81, '.');
	//	labelAtlas->setScale(3.0);
		labelAtlas->setVisible(true);
		//labelAtlas->setPosition(ccp(125,125));

		CCAction *spawn = CCSpawn::create(CCMoveBy::create(0.5f,ccp(0,64)),CCFadeOut::create(0.5),NULL);
		labelAtlas->runAction(spawn);
		this->addChild(labelAtlas,2);
		CCSprite::runAction(CCSequence::create(CCDelayTime::create(0.6),
			CCCallFuncND::create(this, callfuncND_selector(RpgMonster::actionEnd_removeLabel), (void*)labelAtlas),NULL));
		showHp();
	}
}
void RpgMonster::showHp()
{
	CCSize size = CCSizeMake(78,215);
	if (!hpShow)
	{
		hpShow = RpgHpValueUI::create(monsterData.maxHp,hp,"hp_line_up.png","hp_line_back.png");
		this->addChild(hpShow);
		hpShow->setScaleY(0.5);
	}
	hpShow->setPosition(ccp(size.width,size.height));
	hpShow->setValue(hp);
}
void RpgMonster::actionEnd_removeLabel(CCNode *pSender,void *arg)
{
	if (pSender->getParent())
	{
		CCLabelAtlas *lbl = (CCLabelAtlas*) arg;
		pSender->removeChild(lbl,true);
	}
}
bool RpgMonster::checkIn(const GridPoint &point,int tag)
{
	GridPoint mePoint = this->getGridPoint();
	if (abs(mePoint.x - point.x) <= tag && abs(mePoint.y - point.y) <= tag)
		return true;
	return false;
}
void RpgMonster::dropItems()
{
	// ������Ʒ�ڳ�����
	RpgMap * map = getMap();
	static int buildIds[] = {1,2,3,4};
	int id = (int)CCRANDOM_0_1() * 3;
	RpgBuildInfo buildInfo = map->findFarmInfoById(buildIds[id]);
	RpgBuild * build = RpgBuild::createFromBuild(&buildInfo);
	if (build && map)
	{
		//build->setCanVisit();
		GridPoint point = getRandomPoint(CCSizeMake(5,5));
		if (!map->placeBuild(build,point.x,point.y))
		{
			build->preSetPosition(point.x*32,point.y *32);
			build->showInvalidGridBack();
			map->addBuild(build);
			map->showBlocks();
		}
		map->score ++;
		map->ui->scoreUI->updateNumber("score",map->score);
	}
}
/**
 * ����Ƿ��Ƿ�ʱ
 */
bool RpgMonster::checkTimeOut(int opId)
{
	cc_timeval nowTime;
	CCTime::gettimeofdayCocos2d(&nowTime,NULL);
	OPTIMES_ITER iter = this->optimes.find(opId);
	if (iter != optimes.end())
	{
		float value = CCTime::timersubCocos2d(&iter->second.opTime,&nowTime);
		if (value / 1000 > iter->second.lastTime)
		{
			return true; 
		}
	}
	return false;
}

bool RpgMonster::checkInTime(int opId)
{
	cc_timeval nowTime;
	CCTime::gettimeofdayCocos2d(&nowTime,NULL);
	OPTIMES_ITER iter = this->optimes.find(opId);
	if (iter != optimes.end())
	{
		float value = CCTime::timersubCocos2d(&iter->second.opTime,&nowTime);
		if (value / 1000 < iter->second.lastTime)
		{
			return true; 
		}
	}
	return false;
}
/**
 * ���Ӹ�ʱ��
 */
void RpgMonster::addTime(int opId,int lastTime)
{
	OPTIMES_ITER iter = this->optimes.find(opId);
	if (iter != optimes.end())
	{
		CCTime::gettimeofdayCocos2d(&iter->second.opTime,NULL);
		iter->second.lastTime = lastTime;
		return;
	}
	stOpTime opTime;
	opTime.lastTime = lastTime;
	CCTime::gettimeofdayCocos2d(&opTime.opTime,NULL);
	optimes[opId] = opTime;
}
//////////////////////////MonsterTable ����///////////////////////////////////
struct stFindMinDistanceTarget:stExecEachTarget{
	void exec(RpgObject *object)
	{
		RpgMonster *monster = (RpgMonster*) object;
		if (object->isType(RpgObject::RPG_PLAYER) && monster != me)
		{
			int nowDis = monster->calcDistance(me->getGridPoint());
			if (!minDis || minDis > nowDis)
			{
				minDis = nowDis;
				nowObject = object;
			}
		}
	}
	RpgPlayer * getPlayer()
	{
		return (RpgPlayer*) nowObject;
	}
	stFindMinDistanceTarget(RpgMonster *monster)
	{
		minDis = 0;
		nowObject = NULL;
		me = monster;
	}
	RpgObject *nowObject;
	int minDis;
	RpgMonster *me;
};

struct stFindMultiTarget:stExecEachTarget{
	void exec(RpgObject *object)
	{
		RpgMonster *monster = (RpgMonster*) object;
		
	}
	RpgPlayer * getPlayer()
	{
		return (RpgPlayer*) nowObject;
	}
	stFindMultiTarget(RpgMonster *monster)
	{
		nowObject = NULL;
	}
	RpgObject *nowObject;
};

std::vector<ACTION_EXT> MonsterActionTable::functions;
void MonsterActionTable::doAction(int id,RpgMonster *monster)
{ 
	// ִ����Ϊ
	if (id < functions.size())
	{
		ACTION_EXT action = functions.at(id);
		(*action)(monster);
	}
}
void MonsterActionTable::doAttackAndWalk(RpgMonster *monster)
{
	RpgMap * map = (RpgMap*) monster->getParent();
	
	if (monster->isNowAction(RpgMonster::ACTION_MOVE))
	{
		monster->tryMove();
	}
	else if (monster->isNowAction(RpgMonster::ACTION_BE_ATTACK))
	{
		// �����ǰ�Ǳ���״̬
		monster->tryConbineAction(RpgMonster::IDLE_ACTION);
	}
	else if (monster->isNowAction(RpgMonster::ACTION_ATTACK))
	{
		// ���Լ��㹥����ֵ
		
		monster->nowSkillName = "";
	}
	else monster->tryConbineAction(RpgMonster::IDLE_ACTION); // Ĭ��ִ�п�����Ϊ
	monster->doAttack();
}
void MonsterActionTable::doOnlyAttack(RpgMonster *monster)
{
	// �����Χ�Ƿ��й��� �еĻ��ͷż��� TODO1
	// ֻ������г��ֵ�Ĺ��� �й�����Ϊ TODO 2
	RpgMap * map = (RpgMap*) monster->getParent();
	stFindMinDistanceTarget findTarget(monster);
	map->execTargets(monster->getGridPoint(),10,&findTarget);
	RpgPlayer *player = findTarget.getPlayer();
	if (player)
	{
		// ���Բ��Ŷ���
		if (monster->calcDistance(player->getGridPoint()) < 3)
		{
			monster->putAtkSkill("mattack");
			int nowDir = CalcDir::calcDir(ccp(monster->getGridPoint().x,monster->getGridPoint().y),ccp(player->getGridPoint().x,player->getGridPoint().y));
			monster->setDir(nowDir);
			((RpgMonster*)player)->beAttacked(10);
			
		}
	}
}
void MonsterActionTable::doOnlyMove(RpgMonster *monster)
{
	// ��ͣ������ƶ� ����Ч��Χ��
	// ����Ƿ���Ŀ��� ����Ŀ��� ��tryMove ���������趨Ŀ��
	if (monster->nowDestination.isInvalid() || monster->isReachDestination())
	{
		float x = CCRANDOM_0_1() * monster->activeRect.size.width + monster->activeRect.origin.x;
		float y = CCRANDOM_0_1() * monster->activeRect.size.height + monster->activeRect.origin.y;
		monster->nowDestination = GridPoint(x,y);
	}
	monster->tryMove();
}
void MonsterActionTable::doStop(RpgMonster *monster)
{
	monster->tryConbineAction(RpgMonster::IDLE_ACTION); // Ĭ��ִ�п�����Ϊ
}

/**
 *  ������������ ͬʱֻ����һ��Ŀ�� �����Эͬ��ս
 */
void MonsterActionTable::doAttackPlayerFirstOnlyOneTarget(RpgMonster *monster)
{
	RpgMap * map = (RpgMap*) monster->getParent();
	RpgBuild *build = map->pickBuild(monster->getGridPoint());
	if (build)
	{
		monster->putAtkSkill("mattack");
		build->hp --;
		build->showHp();
		if (build->hp <= 0)
		{
			map->removeBuild(build);
		}
		return;
	}
	// ����Ұ�ڲ������ �ҵ���� ���������򹥻� �ں��淽��ʱ �����ʵ����ɹ���
	// û��������� �̶�Ŀ���߽�
	// ����Ŀ��
	stFindMinDistanceTarget findTarget(monster);
	map->execTargets(monster->getGridPoint(),10,&findTarget);
	RpgPlayer *player = findTarget.getPlayer();
	if (player)
	{
		// ���Բ��Ŷ���
		if (monster->calcDistance(player->getGridPoint()) < 5)
		{
			monster->putAtkSkill("mattack");
			int nowDir = CalcDir::calcDir(ccp(monster->getGridPoint().x,monster->getGridPoint().y),ccp(player->getGridPoint().x,player->getGridPoint().y));
			monster->setDir(nowDir);
			((RpgMonster*)player)->beAttacked(10);
			return;
		}
	}
	monster->nowDestination = GridPoint(1,10); 
	if (monster->getGridPoint().equal(GridPoint(1,10),3))
	{
		monster->putAtkSkill("mattack");
	}
	else
	{
		monster->tryConbineAction(RpgMonster::ACTION_MOVE);
		CCPoint dest = monster->getPixelPositionByDir(CalcDir::_DIR_LEFT); // ���ݷ����ȡ��һ��λ��
		if (monster->calcDistance(monster->nowDestination) < 15)
		{
			monster->tryMove();
		}
		else
		{
			if (dest.x <0 || dest.x >= map->canBlockSize.width || dest.y <46 || dest.y >= map->canBlockSize.height)
			{
				monster->clearAction(RpgMonster::ACTION_MOVE);
				monster->tryConbineAction(RpgMonster::IDLE_ACTION);
			}
			monster->setDir(CalcDir::_DIR_LEFT);
			if (map)
			{
				map->updateMonster(monster);
			}
		}
	}
}
void MonsterActionTable::doMovePathAndAttack(RpgMonster *monster)
{
	RpgMap * map = (RpgMap*) monster->getParent();
	// ����Ұ�ڲ������ �ҵ���� ���������򹥻� �ں��淽��ʱ �����ʵ����ɹ���
	// û��������� �̶�Ŀ���߽�
	// ����Ŀ��
	stFindMinDistanceTarget findTarget(monster);
	map->execTargets(monster->getGridPoint(),10,&findTarget);
	RpgBuild *build = map->pickBuild(monster->getGridPoint());
	if (build)
	{
		monster->putAtkSkill("mattack");
		build->hp --;
		build->showHp();
		if (build->hp <= 0)
		{
			map->removeBuild(build);
		}
		return;
	}
	RpgPlayer *player = findTarget.getPlayer();
	if (player)
	{
		// ���Բ��Ŷ���
		if (monster->calcDistance(player->getGridPoint()) < 3)
		{
			monster->putAtkSkill("mattack");
			int nowDir = CalcDir::calcDir(ccp(monster->getGridPoint().x,monster->getGridPoint().y),ccp(player->getGridPoint().x,player->getGridPoint().y));
			monster->setDir(nowDir);
			((RpgMonster*)player)->beAttacked(10);
			return;
		}
	}
	if (monster->path.empty())
	{
		if (player && monster->calcDistance(player->getGridPoint()) < 3)
		{
			monster->putAtkSkill("mattack");
			int nowDir = CalcDir::calcDir(ccp(monster->getGridPoint().x,monster->getGridPoint().y),ccp(player->getGridPoint().x,player->getGridPoint().y));
			monster->setDir(nowDir);
			((RpgMonster*)player)->beAttacked(10);
		}
		return;
	}
	monster->nowDestination = map->getGridPointByPixelPoint(monster->path.back()); 
	if (monster->getGridPoint().equal(monster->nowDestination))
	{
		monster->path.pop_back();
	}
	GridPoint tempPoint = monster->nowDestination;
	monster->tryConbineAction(RpgMonster::ACTION_MOVE);
	int nowDir = CalcDir::calcDir(ccp(monster->getGridPoint().x,monster->getGridPoint().y),ccp(tempPoint.x,tempPoint.y));
	monster->setDir(nowDir);
	if (map)
	{
		map->updateMonster(monster);
	}
}
void MonsterActionTable::doAttackMutiTargetDefaultWalkInPath(RpgMonster *monster)
{
    // find targets in eyeshort
    
    // choice target
    
    // attack or move to target
    
    // move in path
}
NS_CC_END