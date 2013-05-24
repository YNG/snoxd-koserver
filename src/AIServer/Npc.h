#pragma once

#include "NpcTable.h"
#include "NpcMagicProcess.h"

#define MAX_PATH_SIZE		100

#define NPC_MAX_USER_LIST	5

#define NPC_ATTACK_SHOUT	0
#define NPC_SUBTYPE_LONG_MON 1

#define NPC_TRACING_STEP	100

#define NPC_HAVE_USER_LIST	5
#define NPC_HAVE_ITEM_LIST	6
#define NPC_PATTEN_LIST		5
#define NPC_PATH_LIST		50
#define NPC_MAX_PATH_LIST	100
#define NPC_EXP_RANGE		50
#define NPC_EXP_PERSENT		50

#define NPC_SECFORMETER_MOVE	4
#define NPC_SECFORMETER_RUN		4
#define NPC_VIEW_RANGE			100

#define MAX_MAGIC_TYPE3			20
#define MAX_MAGIC_TYPE4			9

struct  _NpcSkillList
{
	short	sSid;
	uint8	tLevel;
	uint8	tOnOff;
};

struct  _NpcGiveItem
{
	int 	sSid;			// item serial number
	short	count;			// item 갯수(돈은 단위)
};

struct	_ExpUserList
{
	char	strUserID[MAX_ID_SIZE+1];		// 아이디(캐릭터 이름)
	int		iUid;							// User uid
	int		nDamage;						// 타격치 합
	bool	bIs;							// 시야에 존재하는지를 판단(true:존재)
	//bool	bSameParty;						
};

struct _Target
{
	int	id;							// 공격대상 User uid
	float x;						// User의 x pos
	float y;						// User의 y pos
	float z;						// User의 z pos
	int failCount;
};

struct _PattenPos
{
	short x;
	short z;
};

struct _Patten
{
	int	patten_index;
	_PattenPos pPattenPos[NPC_MAX_PATH_LIST];
};

struct _PathList
{
	_PattenPos pPattenPos[NPC_MAX_PATH_LIST];
};

struct _MagicType3
{
	short		sHPAttackUserID;	// 지속 마법을 사용한 유저의 아이디 저장
	short		sHPAmount;			// 지속 damage ( 지속총양 / (지속시간 / 2) )
	uint8		byHPDuration;		// 지속 시간
	uint8		byHPInterval;		// 지속 간격
	time_t		tStartTime;	
};

struct _MagicType4
{
	uint8	byAmount;
	short	sDurationTime;		// duration, in seconds
	time_t	tStartTime;
};

struct _TargetHealer
{
	short	sNID;				// npc nid
	short	sValue;				// 점수
};

class MAP;

struct __Vector3;
class CNpc  
{
public:
	CNpcTable *m_proto;

	_Target	m_Target;				// 공격할 유저 저장,,
	short		m_ItemUserLevel;		// 죽을때 매직 이상 아이템를 떨구기위해 참조해야하는 유저의레벨

	int		m_TotalDamage;	// 총 누적된 대미지양
	_ExpUserList m_DamagedUserList[NPC_HAVE_USER_LIST]; // 나에게 타격치를 준 유저정보를 리스트로 관리한다.(경험치 분배)
	short   m_sMaxDamageUserid;		// 나에게 최고의 데미지를 준 유저의 아이디 저장..

	_PathList m_PathList;			// Npc의 패스 리스트 
	_PattenPos m_pPattenPos;		// Npc의 패턴,,

	//int m_iPattenNumber;		// 현재의 패턴번호
	short m_iPattenFrame;			// 패턴의 현재 위치..

	uint8 m_byMoveType;			// NPC의 행동타입(이동관련)
	uint8 m_byInitMoveType;		// NPC의 초기 행동타입(이동관련)
	short m_sPathCount;			// NPC의 PathList Count
	short m_sMaxPathCount;		// NPC의 PathList Max Count

	bool	m_bFirstLive;		// NPC 가 처음 생성되는지 죽었다 살아나는지 판단.
	uint8	m_NpcState;			// NPC의 상태 - 살았다, 죽었다, 서있다 등등...
	MAP *	m_pZone;

	short	m_sNid;				// NPC (서버상의)일련번호

	float		m_nInitX;			// 처음 생성된 위치 X
	float		m_nInitY;			// 처음 생성된 위치 Y
	float		m_nInitZ;			// 처음 생성된 위치 Z

	uint8		m_bCurZone;			// Current Zone;
	float		m_fCurX;			// Current X Pos;
	float		m_fCurY;			// Current Y Pos;
	float		m_fCurZ;			// Current Z Pos;

	float		m_fPrevX;			// Prev X Pos;
	float		m_fPrevY;			// Prev Y Pos;
	float		m_fPrevZ;			// Prev Z Pos;

	//
	//	PathFind Info
	//
	short		m_min_x;
	short		m_min_y;
	short		m_max_x;
	short		m_max_y;

	SIZE	m_vMapSize;

	float m_fStartPoint_X, m_fStartPoint_Y;
	float m_fEndPoint_X, m_fEndPoint_Y;

	short m_sStepCount;

	CPathFind m_vPathFind;
	_PathNode	*m_pPath;

	int		m_nInitMinX;					// 초기위치
	int		m_nInitMinY;
	int		m_nInitMaxX;
	int		m_nInitMaxY;

	// 지속 마법 관련..
	time_t	m_fHPChangeTime;			// Hp 회복율
	time_t	m_tFaintingTime;			// 기절해 있는 시간..
	_MagicType3  m_MagicType3[MAX_MAGIC_TYPE3];			// HP 관련된 마법..
	_MagicType4  m_MagicType4[MAX_MAGIC_TYPE4];			// 능력치 관련된 마법..

	//----------------------------------------------------------------
	//	MONSTER DB 쪽에 있는 변수들
	//----------------------------------------------------------------
	short   m_sSize;						// 캐릭터의 비율(100 퍼센트 기준)
	int     m_iWeapon_1;			// 착용 무기
	int     m_iWeapon_2;			// 착용 무기
	uint8	m_byGroup;			// 소속집단(국가 개념)
	uint8	m_byActType;		// 행동패턴
	uint8	m_byRank;			// 작위
	uint8	m_byTitle;			// 지위
	int 	m_iSellingGroup;	// 아이템 그룹(물건매매 담당 NPC의 경우만)
	int		m_iMaxHP;			// 최대 HP
	short	m_sMaxMP;			// 최대 MP
	short	m_sAttack;			// 공격값(지금 사용하지 않음..)
	short	m_sDefense;			// 방어값
	short	m_sHitRate;			// 공격민첩
	short   m_sEvadeRate;		// 방어민첩
	short	m_sDamage;			// 기본 데미지 - 공격값
	short	m_sAttackDelay;		// 공격딜레이
	short	m_sSpeed;			// 이동속도	
	float   m_fSpeed_1;			// 기본 이동 타입		(1초에 갈 수 있는 거리)
	float   m_fSpeed_2;			// 뛰는 이동 타입..		(1초에 갈 수 있는 거리)
	short	m_sStandTime;		// 서있는 시간
	uint16	m_byFireR;			// 화염 저항력
	uint16	m_byColdR;			// 냉기 저항력
	uint16	m_byLightningR;		// 전기 저항력
	uint16	m_byMagicR;			// 마법 저항력
	uint16	m_byDiseaseR;		// 저주 저항력
	uint16	m_byPoisonR;		// 독 저항력
	uint8	m_bySearchRange;	// 적 탐지 범위
	uint8	m_byAttackRange;	// 사정거리
	uint8	m_byTracingRange;	// 추격 거리

	uint8	m_tItemPer;			// 아이템이 떨어질 확률
	uint8	m_tDnPer;			// 돈이 떨어질확률
	uint8	m_byMoneyType;		// Event몬스터일 경우 돈을 많이 주는 것, (0:루팅, 1:루팅을 하지 않고 바로 나눠갖는다)

	int		m_iMoney;			// 떨어지는 돈
	int		m_iItem;			// 떨어지는 아이템

	int			m_iHP;				// 현재 HP
	short		m_sMP;				// 현재 MP
	
	float   m_fSecForMetor;		// 초당 갈 수 있는 거리..

	//----------------------------------------------------------------
	//	MONSTER AI에 관련된 변수들
	//----------------------------------------------------------------
	uint8	m_tNpcLongType;		// 공격 거리 : 원거리(1), 근거리(0), 직.간접(2)
	uint8	m_tNpcAttType;		// 공격 성향 : 선공(1), 후공(0)
	uint8	m_tNpcOldAttType;	// 공격 성향 : 선공(1), 후공(0) (활동영역 제어)
	uint8	m_tNpcGroupType;	// 군집을 형성하냐(1), 안하냐?(0)
	uint8	m_byNpcEndAttType;	// 마지막까지 싸우면(1), 그렇지 않으면(0)
//	uint8	m_tNpcTraceType;	// 끝까지 따라간다(1), 시야에서 없어지면 그만(0)
	uint8	m_byAttackPos;		// User의 어느 부분에서 공격하느지를 판단(8방향)
	uint8	m_byBattlePos;		// 어떤 진형을 선택할 것인지를 판단..
	uint8	m_byWhatAttackType; // 공격 타입 : Normal(0), 근.장거리마법(1), 독(2), 힐링(3), 지역마법만(4), 1+4번 마법(5)
	uint8	m_byGateOpen;		// 성문일 경우에.. 사용... Gate Npc Status -> 1 : open 0 : close
	uint8	m_byMaxDamagedNation;	// 나를 죽인 유저의 국가를 저장.. (1:카루스, 2:엘모라드)
	uint8	m_byObjectType;         // 보통은 0, object타입(성문, 레버)은 1
	uint8	m_byDungeonFamily;		// 던젼에서 같은 패밀리 묶음 (같은 방)
	uint8	m_bySpecialType;		// 몬스터의 형태가 변하는지를 판단(0:변하지 않음, 1:변하는 몬스터, 
									// 2:죽는경우 조정하는 몬스터(대장몬스터 죽을경우 성문이 열림), 
									// 3:대장몬스터의 죽음과 관련이 있는 몬스터(대장몬스터가 죽으면 관계되는 몬스터는 같이 죽도록)
									// 4:변하면서 죽는경우 조정하는 몬스터 (m_sControlSid)
									// 5:처음에 죽었있다가 출현하는 몬스터,,
									// 6:일정시간이 지난 후에 행동하는 몬스터,,
									// 100:죽었을때 데미지를 많이 입힌 유저를 기록해 주세여
	uint8	m_byTrapNumber;			// 던젼에서 트랩의 번호,,
	uint8	m_byChangeType;			// 0:정상상태, 1:변하기 위한 준비, 2:다른몬스터로 변함, 3:몬스터의 출현, 100:몬스터의 죽음
	uint8	m_byRegenType;			// 0:정상적으로 리젠이 됨.. , 1:한번 죽으면 리젠이 안되는 특수 몸, 2:리젠이 안됨
	uint8    m_byDeadType;			// 0:살아 있는 경우, 100:전쟁이벤트중 죽은 경우
	short   m_sChangeSid;			// 변하는 몬스터의 Sid번호..
	short   m_sControlSid;			// 조정하는 몬스터의 Sid번호..


	//----------------------------------------------------------------
	//	MONSTER_POS DB 쪽에 있는 변수들
	//----------------------------------------------------------------
	time_t	m_Delay;			// this doesn't really need to be time_t, but we'll use it (at least for now) for consistency
	time_t	m_fDelayTime;		// Npc Thread체크 타임...

	uint8	m_byType;
	int		m_sRegenTime;		// NPC 재생시간
	
	uint8	m_byDirection;

	int		m_nLimitMinX;		// 활동 영역
	int		m_nLimitMinZ;
	int		m_nLimitMaxX;
	int		m_nLimitMaxZ;

	long	m_lEventNpc;

	float m_fAdd_x;
	float m_fAdd_z;

	float m_fBattlePos_x;	
	float m_fBattlePos_z;

	float m_fSecForRealMoveMetor;		// 초당 갈 수 있는 거리..(실제 클라이언트에 보내주는 거리)

	bool m_bPathFlag;					// 패스 파인드 실행여부 체크 변수..

	//----------------------------------------------------------------
	//	NPC 이동 관련
	//----------------------------------------------------------------
	_NpcPosition	m_pPoint[MAX_PATH_LINE];			// 이동시 참고 좌표

	short m_iAniFrameIndex;
	short m_iAniFrameCount;
	uint8 m_byPathCount;					// 패스를 따라 이동하는 몬스터 끼리 겹치지 않도록,, 
	uint8 m_byResetFlag;					// 추적공격시 패스파인딩을 다시 할것인지,, 말것인지를 판단..
	uint8 m_byActionFlag;				// 행동변화 플래그 ( 0 : 행동변화 없음, 1 : 공격에서 추격)

	bool m_bTracing;
	float m_fTracingStartX, m_fTracingStartZ;

	short m_iRegion_X;					// 현재의 region - x pos
	short m_iRegion_Z;					// 현재의 region - z pos
	short m_iFind_X[4];					// find enemy에서 찾을 Region검사영역
	short m_iFind_Y[4];

	float   m_fOldSpeed_1;			// 기본 이동 타입		(1초에 갈 수 있는 거리)
	float   m_fOldSpeed_2;			// 뛰는 이동 타입..		(1초에 갈 수 있는 거리)

public:
	INLINE MAP * GetMap() { return m_pZone; };

	CNpc();
	virtual ~CNpc();

	void Init();	//	NPC 기본정보 초기화
	void InitTarget(void);
	void InitUserList();
	void InitPos();
	void InitMagicValuable();

	void Load(uint16 sNpcID, CNpcTable * proto);

protected:
	void ClearPathFindData(void);

public:

	void FillNpcInfo(Packet & result);
	void NpcStrategy(uint8 type);
	void NpcTypeParser();
	int  FindFriend(int type=0);
	void  FindFriendRegion(int x, int z, MAP* pMap, _TargetHealer* pHealer, int type=0);
	//void  FindFriendRegion(int x, int z, MAP* pMap, int type=0);
	bool IsCloseTarget(CUser *pUser, int nRange);
	void ToTargetMove(CUser* pUser);
	int SendDead(int type = 1);			// Npc Dead
	void SendExpToUserList();								// User 경험치 분배..
	bool SetDamage(int nAttackType, int nDamage, TCHAR *id, int uid);	// Npc의 데미지 계산..
	bool SetHMagicDamage(int nDamage);	// Npc의 데미지 계산..
	int GetDefense();										// Npc의 방어값..
	void ChangeTarget(int nAttackType, CUser *pUser);
	void ChangeNTarget(CNpc *pNpc);
	int GetFinalDamage(CUser *pUser, int type = 1);
	int GetNFinalDamage(CNpc *pNpc);
	uint8 GetHitRate(float rate);
	bool ResetPath();
	bool GetTargetPos(float& x, float& z);
	bool IsChangePath();
	int Attack();
	int LongAndMagicAttack();
	int TracingAttack();
	int GetTargetPath(int option = 0);
	int	GetPartyDamage(int iNumber);
	int IsCloseTarget(int nRange, int Flag=0);
	bool StepMove();
	bool StepNoPathMove();
	bool IsMovingEnd();
	bool IsMovable(float x, float z);
	int  IsSurround(CUser* pUser);
	bool IsDamagedUserList(CUser *pUser);
	void IsUserInSight();
	bool IsLevelCheck(int iLevel);
	bool IsHPCheck(int iHP);
	bool IsCompStatus(CUser* pUser);
	bool IsPathFindCheck(float fDistance);						// 패스 파인드를 할것인지를 체크하는 루틴..
	void IsNoPathFind(float fDistance);						// 패스 파인드를 하지 않고 공격대상으로 가는 루틴..
	bool IsInExpRange(CUser* pUser);
	void GiveNpcHaveItem();		// NPC 가 가진 아이템을 떨군다

	time_t NpcLive();
	time_t NpcFighting();
	time_t NpcTracing();
	time_t NpcAttacking();
	time_t NpcMoving();
	time_t NpcSleeping();
	time_t NpcFainting();
	time_t NpcHealing();
	time_t NpcStanding();
	time_t NpcBack();
	bool SetLive();

	bool IsInRange(int nX, int nZ);
	bool RandomMove();				//
	bool RandomBackMove();				//
	bool IsInPathRange();			//
	int GetNearPathPoint();			//

	// Packet Send부분..
	void SendAttackSuccess(uint8 byResult, int tuid, short sDamage, int nHP=0, uint8 byFlag = 0, short sAttack_type=1);

	// Inline Function
	bool SetUid(float x, float z, int id);

	void Dead(int iDeadType = 0);
	bool FindEnemy();
	bool CheckFindEnermy();
	int FindEnemyRegion();
	float FindEnemyExpand(int nRX, int nRZ, float fCompDis, int nType);
	int GetMyField();

	int GetDir(float x1, float z1, float x2, float z2);
	void NpcMoveEnd();

	INLINE float RandomGenf(float max, float min);
	void GetVectorPosition(__Vector3 & vOrig, __Vector3 & vDest, float fDis, __Vector3 * vResult);
	void CalcAdaptivePosition(__Vector3 & vPosOrig, __Vector3 & vPosDest, float fAttackDistance, __Vector3 * vResult);
	void ComputeDestPos(__Vector3 & vCur, float fDegree, float fDegreeOffset, float fDistance, __Vector3 * vResult);
	void Yaw2D(float fDirX, float fDirZ, float& fYawResult);
	float GetDistance(__Vector3 & vOrig, __Vector3 & vDest);
	int  PathFind(CPoint start, CPoint end, float fDistance);
	bool GetUserInView();	// Npc의 가시 거리안에 User가 있는지를 판단
	bool GetUserInViewRange(int x, int z);
	void MoveAttack();
	void HpChange();
	void MSpChange(int type, int amount);
	void ItemWoreOut( int type, int damage );
	int	 ItemProdution(int item_number);
	int  GetItemGrade(int item_grade);
	int  GetItemCodeNumber(int level, int item_type);
	int  GetWeaponItemCodeNumber(int item_type);
	void DurationMagic_4();
	void DurationMagic_3();
	void ChangeMonsterInfomation(int iChangeType);
	int  GetPartyExp( int party_level, int man, int nNpcExp );
	void ChangeAbility(int iChangeType);
	bool Teleport();
};
