#include "stdafx.h"
#include "LuaEngine.h"
#include "User.h"
#include "Npc.h"

/* 
	Classes
*/

/**
 * Defining a class is simple: just #define LUA_CLASS to your class name, 
 * then call DEFINE_LUA_CLASS(), specifying each method to expose.
 *
 * Remember to #undef LUA_CLASS when you're done.
 *
 * Doing so sacrifices a little readability, however it
 * makes manually defining methods much quicker (less to type).
 *
 * Also, as our method doesn't support inheritance, you'll need
 * to redefine the same methods for each class.
 *
 * This is because of the way we dynamically pull instance pointers;
 * these are typedef'd within the class, so that we can refer to them 
 * to grab the class name from within. As we type check these with Lua,
 * they'll fail, so we won't be able to use them.
 *
 * I don't think this is such a big issue, as there's only a handful of
 * cases that actually require this behaviour.
 **/

#define LUA_CLASS CUser
DEFINE_LUA_CLASS
(
	// Getters
	MAKE_LUA_METHOD(GetName)
	MAKE_LUA_METHOD(GetAccountName)
	MAKE_LUA_METHOD(GetZoneID)
	MAKE_LUA_METHOD(GetX)
	MAKE_LUA_METHOD(GetY)
	MAKE_LUA_METHOD(GetZ)
	MAKE_LUA_METHOD(GetNation)
	MAKE_LUA_METHOD(GetLevel)
	MAKE_LUA_METHOD(GetClass)
	MAKE_LUA_METHOD(GetCoins)
	MAKE_LUA_METHOD(GetInnCoins)
	MAKE_LUA_METHOD(GetLoyalty)
	MAKE_LUA_METHOD(GetMonthlyLoyalty)
	MAKE_LUA_METHOD(GetManner)
	MAKE_LUA_METHOD(GetActiveQuestID)

	MAKE_LUA_METHOD(isWarrior)
	MAKE_LUA_METHOD(isRogue)
	MAKE_LUA_METHOD(isMage)
	MAKE_LUA_METHOD(isPriest)
	MAKE_LUA_METHOD(isInClan)
	MAKE_LUA_METHOD(isClanLeader)
	MAKE_LUA_METHOD(isInParty)
	MAKE_LUA_METHOD(isPartyLeader)

	// Shortcuts for lazy people
	MAKE_LUA_METHOD(hasCoins)
	MAKE_LUA_METHOD(hasInnCoins)
	MAKE_LUA_METHOD(hasLoyalty)
	MAKE_LUA_METHOD(hasMonthlyLoyalty)
	MAKE_LUA_METHOD(hasManner)

	// Here lie the useful methods.
	MAKE_LUA_METHOD(GiveItem)
	MAKE_LUA_METHOD(RobItem)
	MAKE_LUA_METHOD(CheckExistItem)
	MAKE_LUA_METHOD(GoldGain)
	MAKE_LUA_METHOD(GoldLose)
	MAKE_LUA_METHOD(ExpChange)
	MAKE_LUA_METHOD(GiveLoyalty)
	MAKE_LUA_METHOD(RobLoyalty)
	// MAKE_LUA_METHOD(RequestReward)
	// MAKE_LUA_METHOD(RequestPersonalRankReward)
	MAKE_LUA_METHOD(SaveEvent)
	MAKE_LUA_METHOD(SearchQuest)
	MAKE_LUA_METHOD(ShowMap)
	MAKE_LUA_METHOD(SelectMsg) // menu
	MAKE_LUA_METHOD(NpcSay) // dialog
	MAKE_LUA_METHOD(NpcMsg) // new automated quest prompt (does whatever's needed, menu, quest prompt, etc)
	MAKE_LUA_METHOD(CheckWeight)
	MAKE_LUA_METHOD(CheckSkillPoint)
	// MAKE_LUA_METHOD(CheckStatPoint)
	MAKE_LUA_METHOD(isRoomForItem) // FindSlotForItem()
	// MAKE_LUA_METHOD(CountMonsterQuestSub) // CheckMonsterCount(2)
	// MAKE_LUA_METHOD(CountMonsterQuestMain) // CheckMonsterCount(3)
	MAKE_LUA_METHOD(CheckExchange)
	MAKE_LUA_METHOD(RunExchange)
	MAKE_LUA_METHOD(SendNameChange)
	// MAKE_LUA_METHOD(SendRestatDialog) // these two are the same thing
	// MAKE_LUA_METHOD(SendReskillDialog)
	MAKE_LUA_METHOD(ResetSkillPoints) // AllSkillPointChange(1)
	MAKE_LUA_METHOD(ResetStatPoints) // AllStatPointChange(1)
	MAKE_LUA_METHOD(PromoteUserNovice)
	MAKE_LUA_METHOD(PromoteUser)
	MAKE_LUA_METHOD(RobAllItemParty)
	MAKE_LUA_METHOD(ZoneChange)
	MAKE_LUA_METHOD(ZoneChangeParty)
	MAKE_LUA_METHOD(ZoneChangeClan)
	// MAKE_LUA_METHOD(PromoteKnight)
	MAKE_LUA_METHOD(ShowEffect)
	MAKE_LUA_METHOD(ShowNpcEffect)
	MAKE_LUA_METHOD(KissUser)
	MAKE_LUA_METHOD(ChangeManner)
	MAKE_LUA_METHOD(PromoteClan)
);
#undef LUA_CLASS

#define LUA_CLASS CNpc
DEFINE_LUA_CLASS
(
	// Getters
	MAKE_LUA_METHOD(GetID)
	MAKE_LUA_METHOD(GetProtoID)
	MAKE_LUA_METHOD(GetName)
	MAKE_LUA_METHOD(GetNation)
	MAKE_LUA_METHOD(GetType)
	MAKE_LUA_METHOD(GetZoneID)
	MAKE_LUA_METHOD(GetX)
	MAKE_LUA_METHOD(GetY)
	MAKE_LUA_METHOD(GetZ)
	MAKE_LUA_METHOD(CastSkill)

	// Useful methods
	// MAKE_LUA_METHOD(CycleSpawn) // i.e. ChangePosition(), used to cycle a spawn through the various trap numbers (like 7 key quest NPCs)

);
#undef LUA_CLASS


/* 
	Global functions 
*/
LUA_FUNCTION(CheckPercent)
{
	LUA_RETURN(CheckPercent(LUA_ARG(int, 1)));
}

#if defined(USE_ORIGINAL_QUESTS)

#define Lua_GetUser() g_pMain->GetUserPtr(LUA_ARG(uint16, 1))

LUA_FUNCTION(HowmuchItem) 
{
	CUser * pUser = Lua_GetUser();
	uint32 result = 0;

	if (pUser != nullptr) 
	{
		uint32 nItemID = LUA_ARG(uint32, 2);
		if (nItemID == ITEM_GOLD)
			result = pUser->GetCoins();
		else
			result = pUser->GetItemCount(nItemID);
	}

	LUA_RETURN(result);
}

LUA_FUNCTION(CheckNation)
{
	CUser * pUser = Lua_GetUser();
	uint8 bNation = Nation::NONE;

	if (pUser != nullptr)
		bNation = pUser->GetNation();

	LUA_RETURN(bNation);
}

LUA_FUNCTION(CheckClass)
{
	CUser * pUser = Lua_GetUser();
	uint8 bClassType = 0;

	if (pUser != nullptr)
		bClassType = pUser->GetClassType();

	LUA_RETURN(bClassType);
}

LUA_FUNCTION(CheckLevel)
{
	CUser * pUser = Lua_GetUser();
	uint8 bClassType = 0;

	if (pUser != nullptr)
		bClassType = pUser->GetLevel();

	LUA_RETURN(bClassType);
}

LUA_FUNCTION(CheckSkillPoint)
{
	CUser * pUser = Lua_GetUser();
	uint8 bPoints = 0;

	if (pUser != nullptr)
		bPoints = pUser->GetSkillPoints((SkillPointCategory)LUA_ARG(uint32, 2));

	LUA_RETURN(bPoints);
}

#define _LUA_WRAPPER_USER_FUNCTION(name, methodName) \
	LUA_FUNCTION(name) { \
		CUser * pUser = Lua_GetUser(); /* get the user from the stack using the specified user ID */ \
		lua_tpush(L, pUser); /* push the user pointer onto the stack, as our code expects */ \
		lua_remove(L, 1); /* removes the user ID from the stack */ \
		lua_insert(L, 1); /* moves the user pointer to the start of the bottom of the stack where it's expected */ \
		return CUser::Lua_ ## methodName(L); \
	}

#define LUA_WRAPPER_USER_FUNCTION(name) \
	_LUA_WRAPPER_USER_FUNCTION(name, name)

LUA_WRAPPER_USER_FUNCTION(ShowMap);
LUA_WRAPPER_USER_FUNCTION(SaveEvent);
LUA_WRAPPER_USER_FUNCTION(CheckExchange);
LUA_WRAPPER_USER_FUNCTION(RunExchange);
LUA_WRAPPER_USER_FUNCTION(SearchQuest);
LUA_WRAPPER_USER_FUNCTION(NpcMsg);
LUA_WRAPPER_USER_FUNCTION(ShowEffect);
LUA_WRAPPER_USER_FUNCTION(ShowNpcEffect);
_LUA_WRAPPER_USER_FUNCTION(ExistMonsterQuestSub, GetActiveQuestID);
_LUA_WRAPPER_USER_FUNCTION(PromoteKnight, PromoteClan);
/*New Quest*/
	LUA_WRAPPER_USER_FUNCTION(GetName);
	LUA_WRAPPER_USER_FUNCTION(GetAccountName);
	LUA_WRAPPER_USER_FUNCTION(GetZoneID);
	LUA_WRAPPER_USER_FUNCTION(GetX);
	LUA_WRAPPER_USER_FUNCTION(GetY);
	LUA_WRAPPER_USER_FUNCTION(GetZ);
	LUA_WRAPPER_USER_FUNCTION(GetNation);
	LUA_WRAPPER_USER_FUNCTION(GetLevel);
	LUA_WRAPPER_USER_FUNCTION(GetClass);
	LUA_WRAPPER_USER_FUNCTION(GetCoins);
	LUA_WRAPPER_USER_FUNCTION(GetInnCoins);
	LUA_WRAPPER_USER_FUNCTION(GetLoyalty);
	LUA_WRAPPER_USER_FUNCTION(GetMonthlyLoyalty);
	LUA_WRAPPER_USER_FUNCTION(GetManner);
	LUA_WRAPPER_USER_FUNCTION(isWarrior);
	LUA_WRAPPER_USER_FUNCTION(isRogue);
	LUA_WRAPPER_USER_FUNCTION(isMage);
	LUA_WRAPPER_USER_FUNCTION(isPriest);
	LUA_WRAPPER_USER_FUNCTION(isInClan);
	LUA_WRAPPER_USER_FUNCTION(isClanLeader);
	LUA_WRAPPER_USER_FUNCTION(isInParty);
	LUA_WRAPPER_USER_FUNCTION(isPartyLeader);
	// Shortcuts for lazy people
	LUA_WRAPPER_USER_FUNCTION(hasCoins);
	LUA_WRAPPER_USER_FUNCTION(hasInnCoins);
	LUA_WRAPPER_USER_FUNCTION(hasLoyalty);
	LUA_WRAPPER_USER_FUNCTION(hasMonthlyLoyalty);
	LUA_WRAPPER_USER_FUNCTION(hasManner);
	// Here lie the useful methods.
	LUA_WRAPPER_USER_FUNCTION(GiveItem);
	LUA_WRAPPER_USER_FUNCTION(RobItem);
	LUA_WRAPPER_USER_FUNCTION(CheckExistItem);
	LUA_WRAPPER_USER_FUNCTION(GoldGain);
	LUA_WRAPPER_USER_FUNCTION(GoldLose);
	LUA_WRAPPER_USER_FUNCTION(ExpChange);
	LUA_WRAPPER_USER_FUNCTION(GiveLoyalty);
	LUA_WRAPPER_USER_FUNCTION(RobLoyalty);
	LUA_WRAPPER_USER_FUNCTION(NpcSay); // dialog
	LUA_WRAPPER_USER_FUNCTION(CheckWeight);
	LUA_WRAPPER_USER_FUNCTION(isRoomForItem); // FindSlotForItem();
	LUA_WRAPPER_USER_FUNCTION(SendNameChange);
	LUA_WRAPPER_USER_FUNCTION(ResetSkillPoints); // AllSkillPointChange(1);
	LUA_WRAPPER_USER_FUNCTION(ResetStatPoints); // AllStatPointChange(1);
	LUA_WRAPPER_USER_FUNCTION(PromoteUserNovice);
	LUA_WRAPPER_USER_FUNCTION(PromoteUser);
	LUA_WRAPPER_USER_FUNCTION(RobAllItemParty);
	LUA_WRAPPER_USER_FUNCTION(ZoneChange);
	LUA_WRAPPER_USER_FUNCTION(ZoneChangeParty);
	LUA_WRAPPER_USER_FUNCTION(ZoneChangeClan);
	LUA_WRAPPER_USER_FUNCTION(KissUser);
	LUA_WRAPPER_USER_FUNCTION(ChangeManner);

LUA_FUNCTION(SelectMsg)
{
	CUser * pUser = Lua_GetUser();
	if (pUser == nullptr) 
		return LUA_NO_RESULTS;

	uint32 arg = 2; // start from after the user instance.
	int32 menuButtonText[MAX_MESSAGE_EVENT], 
		menuButtonEvents[MAX_MESSAGE_EVENT];
	uint8 bFlag = LUA_ARG(uint8, arg++);
	int32 nQuestID = LUA_ARG_OPTIONAL(int32, -1, arg++);
	int32 menuHeaderText = LUA_ARG(int32, arg++);
	arg++; // skip the NPC ID
	foreach_array(i, menuButtonText)
	{
		menuButtonText[i] = LUA_ARG_OPTIONAL(int32, -1, arg++);
		menuButtonEvents[i] = LUA_ARG_OPTIONAL(int32, -1, arg++);
	}

	LUA_NO_RETURN(pUser->SelectMsg(bFlag, nQuestID, menuHeaderText, menuButtonText, menuButtonEvents));
}

LUA_FUNCTION(CastSkill)
{
	CUser * pUser = Lua_GetUser();
	bool bResult = false;
	if (pUser != nullptr)
	{
		CNpc * pNpc = g_pMain->GetNpcPtr(pUser->m_sEventNid);
		if (pNpc != nullptr)
		{
			bResult = pNpc->CastSkill(
				reinterpret_cast<Unit *>(pUser),
				LUA_ARG(uint32, 2)
			);
		}
	}
	return bResult;
}

#endif
