#pragma once
class Random
{
private:
    ConfigLoader* m_configLoader;
    MyDisplay* m_display;
    Level* m_level;
    LocalPlayer* m_localPlayer;
    std::vector<Player*>* m_players;
public:
    Random(ConfigLoader* configLoader,
          MyDisplay* display,
          Level* level,
          LocalPlayer* localPlayer,
          std::vector<Player*>* players
          )
    {
        m_configLoader = configLoader;
        m_display = display;
        m_level = level;
        m_localPlayer = localPlayer;
        m_players = players;
    }
    //==========---------[SUPERGLIDE]-------------==================
    void superGlide(){
        while (m_display->keyDown(XK_space))
        {
            static float startjumpTime = 0;
            static bool startSg = false;
            static float traversalProgressTmp = 0.0;
 
            float worldtime = mem::Read<float>(m_localPlayer->base + OFFSET_TIME_BASE); // Current time
            float traversalStartTime = mem::Read<float>(m_localPlayer->base + OFFSET_TRAVERSAL_START_TIME); // Time to start wall climbing
            float traversalProgress = mem::Read<float>(m_localPlayer->base + OFFSET_TRAVERSAL_PROGRESS); // Wall climbing, if > 0.87 it is almost over.
            auto HangOnWall = -(traversalStartTime - worldtime);
 
            if (HangOnWall > 0.1 && HangOnWall < 0.12)
            {
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
            }
            if (traversalProgress > 0.87f && !startSg && HangOnWall > 0.1f && HangOnWall < 1.5f)
            {
                //start SG
                startjumpTime = worldtime;
                startSg = true;
            }
            if (startSg)
            {
                //printf ("sg Press jump\n");
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
                while (mem::Read<float>(m_localPlayer->base + OFFSET_TIME_BASE) - startjumpTime < 0.011);
                {
                    mem::Write<int>(OFF_REGION + OFF_IN_DUCK + 0x8, 6);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
                    std::this_thread::sleep_for(std::chrono::milliseconds(600));
                }
                startSg = false;
                break;
            }
        }
 
        // Automatic wall jump
        int wallJumpNow = 0;
 
        static float onWallTmp = 0;
        float onWall = mem::Read<float>(m_localPlayer->base + OFFSET_WALL_RUN_START_TIME);
        if (onWall > onWallTmp + 0.1) // 0.1
        {
            if (mem::Read<int>(OFF_REGION + OFFSET_IN_FORWARD) == 0)
            {
                wallJumpNow = 1;
                //printf("wall jump Press jump\n");
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
            }
        }
        onWallTmp = onWall;
 
        static float onEdgeTmp = 0;
        float onEdge = mem::Read<float>(m_localPlayer->base + OFFSET_TRAVERSAL_PROGRESS);
        if (onEdge > onEdgeTmp + 0.1) // 0.1
        {
            if (mem::Read<int>(OFF_REGION + OFFSET_IN_FORWARD) == 0)
            {
                wallJumpNow = 2;
                //printf("wall jump onEdge Press jump\n");
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
            }
        }
        onEdgeTmp = onEdge;    
    }

    //==========---------[QUICKTURN]-------------==================
    void quickTurn()
    {
        Vector2D localYawtoClamp = m_localPlayer->viewAngles;
        localYawtoClamp.Clamp();
        float localYaw = localYawtoClamp.y;
        // quickTurn
        if(m_configLoader->FEATURE_QUICKTURN_ON){
            if(m_display->keyDown(m_configLoader->FEATURE_QUICKTURN_BUTTON)){
                m_localPlayer->setYaw((localYaw + 180));
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }

    //====================---------[PRINTLEVELS]-------------------------==================
    void printLevels()
    {
        if(m_configLoader->FEATURE_PRINT_LEVELS_ON){

            if(m_display->keyDown(m_configLoader->FEATURE_PRINT_LEVELS_BUTTON)){
                printf("[N]=[NAME]-[LEVEL]-[LEGEND]\n\n");
                for (auto i = 0; i < m_players->size(); i++)
                {
                    Player *p = m_players->at(i);
                    if(!p->dead && p->isPlayer()){
                        int playerLvl = p->GetPlayerLevel();
                        std::string namePlayer = p->getPlayerName();
                        std::string modelName = p->getPlayerModelName();
                        
                        if(p->friendly){
                            printf("\033[91m[%i]=[%s]-[%i]-[%s]\033[0m\n",
                            (i+1), namePlayer.c_str(), playerLvl, modelName.c_str());  
                        }else{
                            printf("[%i]=[%s]-[%i]-[%s]\n",
                            (i+1), namePlayer.c_str(), playerLvl, modelName.c_str());
                        }
                    }           
                }   
                printf("\n");
            }            
        }        
    }

    //==================---------------[SPECTATORVIEW]-------------------==================
    void spectatorView()
    {
        if(!m_level->playable) return;
        int spectatorcount = 0;   
        std::vector<std::string> spectatorlist;
        if(m_configLoader->FEATURE_SPECTATOR_ON){
            for (int i = 0; i < m_players->size(); i++)
            { 
                Player *p = m_players->at(i);          
                      
                float targetyaw = p->view_yaw; // get Yaw player
                float localyaw= m_localPlayer->local_yaw; // get Yaw LocalPlayer
                //printf("LocalViewYaw: %f == PlayerViewYaw: %f \n", localyaw, targetyaw);
                if (targetyaw == localyaw && p->currentHealth == 0){
                    spectatorcount++;
                    
                    std::string namePlayer = p->getPlayerName();    
                    spectatorlist.push_back(namePlayer);
                }            
            }
            const auto spectatorlist_size = static_cast<int>(spectatorlist.size());
           
            if (spectatorcount > 0){
                {   
                    printf("\n-[%d]-- SPECTATORS -- \n", spectatorcount);
                    for (int i = 0; i < spectatorlist_size; i++)   //show list of spectators by name
                    {   
                        printf("---[%s]---\n", spectatorlist.at(i).c_str());
                    }
                }
            }              
        }      
    }

    //==================---------[SKINCHANGER]-------------==========================================
    void SkinChange()
    {
        if(!m_level->playable) return;
        if(m_localPlayer->dead) return;
        long wephandle = mem::Read<long>(m_localPlayer->base + OFF_WEAPON_HANDLE);
        wephandle &= 0xffff;
        long wep_entity = m_localPlayer->weaponEntity;
        float curTime = mem::Read<float>(m_localPlayer->base + OFFSET_TIME_BASE);
        float endTime = curTime +5.5;
        std::map<int, std::vector<int>> weaponSkinMap;
        //Light ammo weapons
        weaponSkinMap[105] = {m_configLoader->SKIN_P2020};   //WEAPON_P2020 
        weaponSkinMap[81] = {m_configLoader->SKIN_RE45};   //WEAPON_RE45 
        weaponSkinMap[80] = {m_configLoader->SKIN_ALTERNATOR};   //WEAPON_ALTERNATOR 
        weaponSkinMap[104] = {m_configLoader->SKIN_R99};   //WEAPON_R99  
        weaponSkinMap[0] = {m_configLoader->SKIN_R301};     //WEAPON_R301   
        weaponSkinMap[106] = {m_configLoader->SKIN_SPITFIRE};    //WEAPON_SPITFIRE 
        weaponSkinMap[89] = {m_configLoader->SKIN_G7};    //WEAPON_G7 
        //Heavy ammo weapons
        weaponSkinMap[112] = {m_configLoader->SKIN_CARSMG};   // Car-SMG
        weaponSkinMap[21] = {m_configLoader->SKIN_RAMPAGE};    // Rampage 
        weaponSkinMap[111] = {m_configLoader->SKIN_3030};      //3030 
        weaponSkinMap[90] = {m_configLoader->SKIN_HEMLOCK};   //WEAPON_HEMLOCK  
        weaponSkinMap[88] = {m_configLoader->SKIN_FLATLINE};    //FlatLine  
        //Energy ammo weapons
        weaponSkinMap[113] = {m_configLoader->SKIN_NEMESIS};    //WEAPON_NEMESIS  
        weaponSkinMap[110] = {m_configLoader->SKIN_VOLT};    //WEAPON_VOLT 
        weaponSkinMap[107] = {m_configLoader->SKIN_TRIPLETAKE};    //WEAPON_TRIPLE_TAKE 
        weaponSkinMap[93] = {m_configLoader->SKIN_LSTAR};    //WEAPON_LSTAR 
        weaponSkinMap[84] = {m_configLoader->SKIN_DEVOTION};    //WEAPON_DEVOTION 
        weaponSkinMap[86] = {m_configLoader->SKIN_HAVOC};    //WEAPON_HAVOC 
        //Sniper ammo weapons
        weaponSkinMap[1] = {m_configLoader->SKIN_SENTINEL};    //WEAPON_SENTINEL 
        weaponSkinMap[83] = {m_configLoader->SKIN_CHARGERIFLE};    //WEAPON_CHARGE_RIFLE 
        weaponSkinMap[85] = {m_configLoader->SKIN_LONGBOW};    //WEAPON_LONGBOW 
        //Shotgun ammo weapons
        weaponSkinMap[96] = {m_configLoader->SKIN_MOZAMBIQUE};    //WEAPON_MOZAMBIQUE 
        weaponSkinMap[87] = {m_configLoader->SKIN_EVA8};    //WEAPON_EVA8 
        weaponSkinMap[103] = {m_configLoader->SKIN_PEACEKEEPER};    //WEAPON_PEACEKEEPER 
        weaponSkinMap[95] = {m_configLoader->SKIN_MASTIFF};    //WEAPON_MASTIFF 
        //Legendary ammo weapons
        weaponSkinMap[109] = {m_configLoader->SKIN_WINGMAN};    //WEAPON_WINGMAN 
        weaponSkinMap[102] = {m_configLoader->SKIN_PROWLER};    //WEAPON_PROWLER
        weaponSkinMap[2] = {m_configLoader->SKIN_BOCEK};    //WEAPON_BOCEK
        weaponSkinMap[92] = {m_configLoader->SKIN_KRABER};    //WEAPON_KRABER
        weaponSkinMap[163] = {m_configLoader->SKIN_THROWINGKNIFE};    //WEAPON_THROWING_KNIFE
        weaponSkinMap[213] = {m_configLoader->SKIN_THERMITEGRENADE};  //WEAPON_THERMITE_GRENADE 

        if (m_configLoader->FEATURE_SKINCHANGER_ON){
            int waponIndex = mem::Read<int>(wep_entity + OFF_WEAPON_INDEX);
            if (weaponSkinMap.count(waponIndex) == 0) return;
            int skinID = weaponSkinMap[waponIndex][0];
            //printf("Weapon: %s Activated Skin ID: %d \n", WeaponName(waponIndex).c_str(), skinID);  
            mem::Write<int>(m_localPlayer->base + OFF_SKIN, skinID+1);
            mem::Write<int>(wep_entity + OFF_SKIN, skinID);
            curTime = mem::Read<float>(m_localPlayer->base + OFFSET_TIME_BASE);
        }                    
    }
};
