-- [폴크와인]

-- EVENT 는 100번 이상 부터 사용하라

-- UID : 서버에서 제공하는 유저번호
-- EVENT : 서버에서 제공하는 퀘스트 번호
-- STEP : 서버에서 제공하는 퀘스트 내부 단계

-- 위의 세가지 파라메타는 루아 실행시 항상 전역변수로 제공�

-- 지역변수 선언...
local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 11510;

-- [폴크와인] 클릭시 퀘스트 체크  

-------------------------------
------척후 보고서-----
-------------------------------
if EVENT == 190 then
	QuestNum = SearchQuest(UID, NPC);
		if QuestNum == 0 then --해당 NPC에게 할수 있는 퀘스트가 0개 일때 
          -- SelectMsg(UID, 2. -1...........)
			 SelectMsg(UID, 2, -1, 664, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
			 --SetQuestStep(UID, EVENT, 1); -- 뭘 하는 걸까?
			 Ret = 1; -- 이건 왜 저장 시켜요? 그냥 RETURN은 안되나요?
		elseif QuestNum > 1 and  QuestNum < 100 then--해당 NPC에게 할수 있는 퀘스트가 1개 일때 
          NpcMsg(UID, 665, NPC)
      else --해당 NPC에게 할수 있는 퀘스트가 1개 이상 일때 
          EVENT = QuestNum
		end
end

if EVENT == 193 then
    Ret = 1;
end

--핀서독 수집
--. 미쉘

if EVENT == 195 then
   SelectMsg(UID, 1, 8, 666, NPC, 28, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end

if EVENT == 196 then
   ShowMap(UID, 39);
   SaveEvent(UID, 439);
end

--  102번의 속성 0번 4번일 경우

if EVENT == 200 then
   SelectMsg(UID, 2, 8, 667, NPC, 10, 201, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end

if EVENT == 201 then
   SelectMsg(UID, 4, 8, 668, NPC, 22, 202, 23, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end

local ITEM_COUNT3=0;
local Weight;
local Slot;

if EVENT == 202 then
     ITEM_COUNT3 = HowmuchItem(UID, 910044000); 
   if  ITEM_COUNT3 <= 0 then -- 재료 없을때
   Weight = CheckGiveWeight(UID, 910044000, 1) ;
   Slot = CheckGiveSlot(UID);
   if Weight==1 and Slot >= 1 then 
   GiveItem(UID, 910044000, 1);
   SaveEvent(UID, 440);
   else
   ret = 1 ;
   end
   end
   if  ITEM_COUNT3 > 0 then -- 재료 있을때
      SelectMsg(UID, 2, 8, 671, NPC, 18, 213, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end


-- 재료를 다 모았을 때 
local NATION = 0;--국가 체크

if EVENT == 205 then
   SaveEvent(UID, 442);
   NATION = CheckNation(UID);
   if NATION == 1 then -- 카루스 일때
      SelectMsg(UID, 1, 8, 669, NPC, 32, 208, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   else -- 엘모일때
      SelectMsg(UID, 1, 8, 670, NPC, 21, 208, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end


local ITEM_COUNT1=0;
local ITEM_COUNT2=0;
local RUN_EXCHANGE ;--재료 교체 함수 만들어 주세요 

if EVENT == 210 then
     ITEM_COUNT1 = HowmuchItem(UID, 910040000); 
     ITEM_COUNT2 = HowmuchItem(UID, 910041000); 
		if ITEM_COUNT1 < 5 then 
        SelectMsg(UID, 2, 8, 671, NPC, 18, 213, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
		elseif ITEM_COUNT2 < 1 then--해당 NPC에게 할수 있는 퀘스트가 1개 일때 
        SelectMsg(UID, 2, 8, 672, NPC, 18, 213, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
        else --해당 NPC에게 할수 있는 퀘스트가 1개 이상 일때 
        SelectMsg(UID, 4, 8, 673, NPC, 41, 214, 27, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
		end
end

if EVENT == 213 then
   ShowMap(UID, 40);
end

local Check;

if EVENT == 214 then
        Check = CheckExchange(UID, 88)
        if  Check ==1 then
        RunExchange(UID, 88);	   
        SaveEvent(UID, 441);      
        else
        Ret = 1;	
        end	 
end

-------------------------------
------척후 보고서  끝---
-------------------------------


--******************************************************--
-- 일곱 열쇠 수호자 시작 
--******************************************************--

local NPC = 11510;
local savenum = 9;

-- 9번의 속성 0번 4번일 경우

if EVENT == 532 then   
    SelectMsg(UID, 4, savenum, 4296, NPC, 22, 533, 23, 534, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end

if EVENT == 533 then
   SaveEvent(UID, 4211); --수락시
   GiveItem(UID, 910050000, 1);
end

if EVENT == 534 then
   SaveEvent(UID, 4214); -- 거절시 
end

-- 9번의 속성 1번 3번일 경우

local ItemA
local ItemB

if EVENT == 536 then
ItemA = HowmuchItem(UID, 910057000); --7번째 열쇠
ItemB = HowmuchItem(UID, 910050000); -- 명령서
    if  ItemA == 0 then -- 재료가 없을때
       if ItemB == 0 then -- 명령서도  없을때
       GiveItem(UID, 910050000, 1);
       SelectMsg(UID, 2, savenum, 4298, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
       else -- B 재료 없을때 
       SelectMsg(UID, 2, savenum, 4299, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
       end
    else --7번째 열쇠 있을때 
    SelectMsg(UID, 2, savenum, 4297, NPC, 4172, 537, 4173, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end

if EVENT == 537 then
        SaveEvent(UID, 4212);
         RunExchange(UID, 470);
end


--******************************************************--
-- 일곱 열쇠 수호자 끝 
--******************************************************--

--San-juck captian start
-----------------------------------------------------------
-- 몬스터 토벌대 시작 - 중급
-----------------------------------------------------------
local NPC = 11510;
local savenum = 603;
local savenum1 = 604;

-----------------------------------------------------------

--시드 미셀 호출
if EVENT == 6090 then
   Class = CheckClass (UID);
       if Class == 1 or Class == 5 or Class == 6 then
       SaveEvent(UID, 6039);
       EVENT = 7009
       elseif Class == 2 or Class == 7 or Class == 8 then
       SaveEvent(UID, 6045);
       EVENT = 7009
       elseif Class == 3 or Class == 9 or Class == 10 then
       SaveEvent(UID, 6051);
       EVENT = 7009
      elseif Class == 4 or Class == 11 or Class == 12 then
       SaveEvent(UID, 6057);
       EVENT = 7009
      end
end

if EVENT == 7009 then
   NATION = CheckNation(UID);
   if NATION == 1 then --카營� 占� 
   SelectMsg(UID, 1, savenum, 6039, NPC, 28, 6091, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   else -- 占싹�
   SelectMsg(UID, 1, savenum, 6040, NPC, 28, 6091, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end

if EVENT == 6091 then
   ShowMap(UID,6);
end

------------------------------------------------------------------------
-- SANJUK Campaign Troops Start
------------------------------------------------------------------------

local Level = 0;
if EVENT == 6092 then
   Level = CheckLevel(UID);
   if Level >= 40 and Level <= 50 then
   	SelectMsg(UID, 2, savenum, 6041, NPC, 6007, 6093, 6008, 7002, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   else 
	SelectMsg(UID, 2, savenum, 6042, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end

if EVENT == 6093 then
    SelectMsg(UID, 4, savenum, 6043, NPC, 22, 6094, 23, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end


local WATING = 0;
local PARTYCOUNT = 0;
if EVENT == 6094 then
--   WATING = CheckWaiting(2);  -- 1:Begginer  2:Medium  3:Higher
--   if WATING == 1 then
--      SelectMsg(UID, 2, savenum, 6044, NPC, 10, 3001, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
--      return;
--   end
--   SaveEvent(UID, 6003);
   --카占싶� 占쏙옙占쏙옙占� 占쏙옙占쏙옙占� 
--   SetCampaignGrade(UID, 2, 40, 50, 6095);  -- 1:Begginer  2:Medium  3:Higher, level limitation 40 ~ 50
--   SelectMsg(UID, 8, savenum, 6045, NPC, 6003, 3001, 6004, 3001, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   -- 8 is Campaign Invitation Message...
--end
   PARTYCOUNT = PartyCountMembers(UID, 0);
   if PARTYCOUNT  < 1 then
	SelectMsg(UID, 2, savenum, 6044, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
   if PARTYCOUNT > 1 then
	SetClearType(4, 82, 1, 3500, 20, 2001, 6099, UID, "11510_Forkwain.lua");  -- complete condition setting 1:Boss Mob Eliminate, 12001: Mob ID
   end

--if EVENT == 6095 then
--   SetClearType(2, 82, 1, 3500, 20, 2001, 6099);  -- complete condition setting 1:Boss Mob Eliminate, 12001: Mob ID
--   SetClearType(UID, 2, 30, 30, 101, 4010);  -- complete condition setting 2:Time Endure, 30:Endure time (minutes)
--   SetClearType(UID, 3, 128128, 20, 101, 4010); -- completecondition setting 3:Region Arrival 128128:position cordinate
end

if EVENT == 6096 then   -- A region passed  UID is contained zonenumber... broadcasting packets
  SelectMsg(UID, 6, 8201, 6059, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end
--/*전체 UI 제거
if EVENT == 6097 then   -- B region passed
  SelectMsg(UID, 6, 8202, 6060, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end

if EVENT == 6098 then   -- C region passed
   SelectMsg(UID, 6, 8203, 6061, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end


if EVENT == 6099 then   -- Quest Completed  WARNINIG!!! UID is contained zonenumber... broadcasting packets
     GiveItem(UID, 910135000, 1);		
       SaveEvent(UID, 6041);
          EVENT = 7204
 end


if EVENT == 6099 then   -- Quest Completed  WARNINIG!!! UID is contained zonenumber... broadcasting packets
     GiveItem(UID, 910135000, 1);		
  SaveEvent(UID, 6080);
end



--전체 UI제거 */
------------------------------------------------------------------------
-- SANJUK Campaign Troops End
------------------------------------------------------------------------

---------占� 占쏙옙占�

local quest_ITEM_COUNT=0;
if EVENT == 7000 then
   quest_ITEM_COUNT = HowmuchItem(UID, 910135000);
if quest_ITEM_COUNT == 1 then
   NATION = CheckNation(UID);
   --SaveEvent(UID, 6043);
   if NATION == 1 then --카營� 占� 
   SelectMsg(UID, 1, savenum1, 6046, NPC, 28, 7001, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   else -- 占싹�
   SelectMsg(UID, 1, savenum1, 6047, NPC, 28, 7001, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
  end
end

if EVENT == 7001 then
      ShowMap(UID, 6);
end

--1, 3
local ITEM_COUNT=0;
local ITEM_COUNT1=0;
local RUN_EXCHANGE ;--占쏙옙체 占쏙옙占� 占쏙옙

if EVENT == 7002 then
   ITEM_COUNT = HowmuchItem(UID, 910135000);   
   ITEM_COUNT1 = HowmuchItem(UID, 910138000);
   if  ITEM_COUNT <= 0 then -- 占쏙옙;
      SelectMsg(UID, 2, savenum1, 6048, NPC, 18, 7003, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
   if  ITEM_COUNT1 <= 2 then -- 占쏙옙;
      SelectMsg(UID, 2, savenum1, 6048, NPC, 18, 7003, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
   if ITEM_COUNT  > 0 and ITEM_COUNT1 > 2 then-- 占쏙옙占�;
      --SaveEvent(UID, 6004);
      SelectMsg(UID, 5, savenum1, 6049, NPC, 4006, 7004, 27, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end

if EVENT == 7003 then
--   SaveEvent(UID, 6002);
   ShowMap(UID, 6);
end

if EVENT == 7004 then
   Class = CheckClass (UID);
       if Class == 1 or Class == 5 or Class == 6 then
       EVENT = 7005
       elseif Class == 2 or Class == 7 or Class == 8 then
       EVENT = 7006
       elseif Class == 3 or Class == 9 or Class == 10 then
       EVENT = 7007
      elseif Class == 4 or Class == 11 or Class == 12 then
       EVENT = 7008
      end
end


local Check;
if EVENT == 7005 then
        Check = CheckExchange(UID, 94)
        if  Check ==1 then
        RunSelectExchange(UID, 94)
        else
        Ret = 1;	
        end	 
end

local Check1;

if EVENT == 7006 then
        Check1 = CheckExchange(UID, 95)
        if  Check1 ==1 then
        RunSelectExchange(UID, 95)
        else
        Ret = 1;	
        end	 
end

local Check2;

if EVENT == 7007 then
        Check2 = CheckExchange(UID, 96)
        if  Check2 ==1 then
        RunSelectExchange(UID, 96)
        else
        Ret = 1;	
        end	 
end


local Check3;

if EVENT == 7008 then
        Check3 = CheckExchange(UID, 97)
        if  Check3 ==1 then
        RunSelectExchange(UID, 97)
        else
        Ret = 1;	
        end	 
end
--------------------------------------
-----몬스터 토벌대 끝-----------------
--------------------------------------


--San-juck captian start
-----------------------------------------------------------
-- 占쏙옙占쏙옙占쏙옙- 占�
-----------------------------------------------------------
local NPC = 11510;
local savenum = 607;
local savenum1 = 608;

-----------------------------------------------------------

--천占싱� 호占�

if EVENT == 7010 then
       SaveEvent(UID, 6071);
   NATION = CheckNation(UID);
   if NATION == 1 then --카營� 占� 
   SelectMsg(UID, 1, savenum, 6080, NPC, 28, 7011, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   else -- 占싹�
   SelectMsg(UID, 1, savenum, 6081, NPC, 28, 7011, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end

if EVENT == 7011 then
   ShowMap(UID,39);
end

------------------------------------------------------------------------
-- SANJUK Campaign Troops Start
------------------------------------------------------------------------

local Level = 0;
if EVENT == 7012 then
   Level = CheckLevel(UID);
   if Level >= 60 and Level <= 80 then
   	SelectMsg(UID, 2, savenum, 6051, NPC, 6009, 7013, 6008, 7022, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   else 
	SelectMsg(UID, 2, savenum, 6052, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end

if EVENT == 7013 then
   SelectMsg(UID, 4, savenum, 6053, NPC, 22, 7014, 23, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end

local WATING = 0;
local PARTYCOUNT = 0;
if EVENT == 7014 then
--   WATING = CheckWaiting(3);  -- 1:Begginer  2:Medium  3:Higher
--   if WATING == 1 then
--      SelectMsg(UID, 2, savenum, 6054, NPC, 10, 3001, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
--      return;
--   end
--   SaveEvent(UID, 6003);
   --카占싶� 占쏙옙占쏙옙占� 占쏙옙占쏙옙占� 
--   SetCampaignGrade(UID, 3, 60, 80, 7015);  -- 1:Begginer  2:Medium  3:Higher, level limitation 40 ~ 50
--   SelectMsg(UID, 8, savenum, 6055, NPC, 6003, 3001, 6004, 3001, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   -- 8 is Campaign Invitation Message...
   PARTYCOUNT = PartyCountMembers(UID, 0);
   if PARTYCOUNT < 1 then
	SelectMsg(UID, 2, savenum, 6054, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
   if PARTYCOUNT > 1 then
	SetClearType(4, 83, 1, 4800, 30, 3001, 7019, UID, "11510_Forkwain.lua");  -- complete condition setting 1:Boss Mob Eliminate, 12001: Mob ID
   end

end
   
--if EVENT == 7015 then
--   SetClearType(3, 83, 1, 4800, 30, 3001, 7019);  -- complete condition setting 1:Boss Mob Eliminate, 12001: Mob ID
--   SetClearType(UID, 2, 30, 30, 101, 4010);  -- complete condition setting 2:Time Endure, 30:Endure time (minutes)
--   SetClearType(UID, 3, 128128, 20, 101, 4010); -- completecondition setting 3:Region Arrival 128128:position cordinate
--end
if EVENT == 7026 then   -- A region passed  UID is contained zonenumber... broadcasting packets
   SelectMsg(UID, 6, 8304, 6084, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end

if EVENT == 7016 then   -- A region passed  UID is contained zonenumber... broadcasting packets
   SelectMsg(UID, 6, 8301, 6062, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end
--/*占시� UI f占�
if EVENT == 7017 then   -- B region passed
  SelectMsg(UID, 6, 8302, 6063, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end

if EVENT == 7018 then   -- C region passed
   SelectMsg(UID, 6, 8303, 6064, NPC, 10, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
end


local ITEM_COUNT=0;
local ITEM_COUNT1=0;
local RUN_EXCHANGE ;--占쏙옙체 占쏙옙占� 占쏙옙

local Check;
if EVENT == 7019 then   -- Quest Completed  WARNINIG!!! UID is contained zonenumber... broadcasting packets
     GiveItem(UID, 910136000, 1);		
        RunExchange(UID, 98)
      SaveEvent(UID, 6073);
end




--占시� UIf占�*/
------------------------------------------------------------------------
-- SANJUK Campaign Troops End
------------------------------------------------------------------------

---------占� 占쏙옙占�

local quest_ITEM_COUNT=0;
if EVENT == 7020 then
   quest_ITEM_COUNT = HowmuchItem(UID, 910136000);
if quest_ITEM_COUNT == 1 then
   NATION = CheckNation(UID);
   if NATION == 1 then --카營� 占� 
   SelectMsg(UID, 1, savenum1, 6082, NPC, 28, 7021, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   else -- 占싹�
   SelectMsg(UID, 1, savenum1, 6083, NPC, 28, 7021, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
  end
end

if EVENT == 7021 then
      ShowMap(UID, 6);
end

--1, 3
local ITEM_COUNT=0;
local ITEM_COUNT1=0;
local RUN_EXCHANGE ;--占쏙옙체 占쏙옙占� 占쏙옙

if EVENT == 7022 then
   ITEM_COUNT1 = HowmuchItem(UID, 910137000);
   ITEM_COUNT = HowmuchItem(UID, 910136000);
   if  ITEM_COUNT <= 0 then -- 占쏙옙;
      SelectMsg(UID, 2, savenum1, 6056, NPC, 18, 7023, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
   if  ITEM_COUNT1 <= 2 then -- 占쏙옙;
      SelectMsg(UID, 2, savenum1, 6056, NPC, 18, 7023, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
   if ITEM_COUNT  > 0 and  ITEM_COUNT1 > 2 then-- 占쏙옙占�;
      --SaveEvent(UID, 6004);
      SelectMsg(UID, 2, savenum1, 6057, NPC, 4006, 7025, 27, 3001, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
   end
end

if EVENT == 7023 then
--   SaveEvent(UID, 6002);
   ShowMap(UID, 39);
end


local Check;
if EVENT == 7025 then
        Check = CheckExchange(UID, 98)
        if  Check ==1 then
        RunExchange(UID, 98)
        else
        Ret = 1;	
        end	 
end


--------------------------------------
-----占쏙옙占쏙옙-----------------
--------------------------------------

return Ret;
