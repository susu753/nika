    //GameVersion=v3.0.51.45
    //LastUpdated=21/11/2023
    #pragma once
    //core
    constexpr long OFF_REGION = 0x140000000;                      //[Static]->Region
    constexpr long OFF_LEVEL = 0x16d6ac0;                         //[Miscellaneous]->LevelName o
    constexpr long OFF_LOCAL_PLAYER = 0x21615d8;                  //[Miscellaneous]->LocalPlayer o
    constexpr long OFF_ENTITY_LIST = 0x1db2ed8;                   //[Miscellaneous]->cl_entitylist o
    //buttons
    constexpr long OFF_IN_ATTACK = 0x073cd740;                     //[Buttons]->in_attack o
    constexpr long OFF_IN_JUMP = 0x073cd828;                       //[Buttons]->in_jump o
    constexpr long OFF_IN_DUCK = 0x073cd920;                       //[Buttons]->in_duck o
    constexpr long OFFSET_IN_FORWARD = 0x073cd670;                 //[Buttons]->in_forward o
    constexpr long OFFSET_TRAVERSAL_START_TIME = 0x2ac0;           //[Buttons]->m_traversalStartTime o
    constexpr long OFFSET_TRAVERSAL_PROGRESS = 0x2abc;             //[Buttons]->m_traversalProgress
    constexpr long OFFSET_WALL_RUN_START_TIME = 0x3524;           //[Buttons]->m_wallRunStartTime o
    constexpr long OFFSET_WALL_RUN_CLEAR_TIME = 0x3528;             //[Buttons]->m_wallRunClearTime o
    // player
    constexpr long OFF_VIEW_MATRIX = 0x11a350;                    //[RecvTable.DT_Player]->ViewMatrix o
    constexpr long OFF_VIEW_RENDER = 0x73cc460;                   //[RecvTable.DT_Player]->ViewRender o
    constexpr long OFF_ZOOMING = 0x1b91;                          //[RecvTable.DT_Player]->m_bZooming o
    constexpr long OFF_LOCAL_ORIGIN = 0x017c;                     //[DataMap.CBaseViewModel]->m_vecAbsOrigin o
    constexpr long OFF_ABSVELOCITY = 0x0170;                      //[DataMap.C_BaseEntity]->m_vecAbsVelocity o
    constexpr long OFF_TEAM_NUMBER = 0x030c;                      //[RecvTable.DT_BaseEntity]->m_iTeamNum o
    constexpr long OFF_CURRENT_HEALTH = 0x02fc;                   //[RecvTable.DT_BaseEntity]->m_iHealth
    constexpr long OFF_CURRENT_SHIELDS = 0x01a0;                  //[RecvTable.DT_BaseEntity]->m_shieldHealth o
    constexpr long OFF_NAME = 0x0449;                             //[RecvTable.DT_BaseEntity]->m_iName o
    constexpr long OFF_SIGNIFIER_NAME = 0x0440;                   //[RecvTable.DT_BaseEntity]->m_iSignifierName o
    constexpr long OFF_LIFE_STATE = 0x0658;                       //[RecvTable.DT_Player]->m_lifeState o
    constexpr long OFF_BLEEDOUT_STATE = 0x26a0;                   //[RecvTable.DT_Player]->m_bleedoutState o
    constexpr long OFF_LAST_VISIBLE_TIME = 0x194d + 0x3;          //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 o
    constexpr long OFF_LAST_AIMEDAT_TIME = 0x194d + 0x3 + 0x8;    //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 + 0x8 o
    constexpr long OFF_VIEW_ANGLES = 0x24f4 - 0x14;               //[DataMap.C_Player]-> m_ammoPoolCapacity - 0x14 o
    constexpr long OFF_PUNCH_ANGLES = 0x23f8;                     //[?]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle o
    constexpr long OFFSET_BREATH_ANGLES = (OFF_VIEW_ANGLES - 0x10);
    constexpr long OFF_STUDIOHDR = 0xfb0;                        //[Miscellaneous]->CBaseAnimating!m_pStudioHdr o
    constexpr long OFF_BONES = 0x0d60 + 0x48;                     //m_nForceBone   o
    constexpr long OFF_CAMERAORIGIN = 0x1e90;                     //[Miscellaneous]->CPlayer!camera_origin o
    constexpr long OFF_MODELNAME = 0x0030;                        //m_ModelName o
     
    constexpr long OFF_NAMELIST = 0xc451fb0;                      //[Miscellaneous]->NameList o
    constexpr long OFF_YAW = 0x21fc - 0x8;                        //m_currentFramePlayer.m_ammoPoolCount - 0x8 o
    constexpr long OFF_NAMEINDEX = 0x38;                          //nameIndex
    //weapon
    constexpr long OFF_WEAPON_HANDLE = 0x18F4;                    //[RecvTable.DT_Player]->m_latestPrimaryWeapons o
    constexpr long OFFSET_AMMO = 0x1540;                          // m_ammoInClip
    constexpr long OFF_GRENADE_HANDLE = 0x1904;                   //[RecvTable.DT_Player]->m_latestNonOffhandWeapons o
    constexpr long OFFSET_TIME_BASE = 0x2048;                     //m_currentFramePlayer.timeBase o
    constexpr long OFF_SKIN = 0x0d18;                             // m_nSkin 
     
    constexpr long OFF_WEAPON_INDEX = 0x1738;                     //[RecvTable.DT_WeaponX]->m_weaponNameIndex o
    constexpr long OFF_PROJECTILESCALE = 0x04ec;                  //projectile_gravity_scale + BASE o
    constexpr long OFF_PROJECTILESPEED = 0x04e4;                  //projectile_launch_speed + BASE o
    //glow
    constexpr long HIGHLIGHT_TYPE_SIZE = 0x34;                  
    constexpr long OFF_GLOW_ENABLE = 0x26c;                       //[DT_HighlightSettings].?
    constexpr long OFF_GLOW_THROUGH_WALL = 0x28c;                 //[DT_HighlightSettings].?
    constexpr long OFF_GLOW_FIX = 0x268;
    constexpr long OFF_GLOW_HIGHLIGHT_ID = 0x28C;                 //[DT_HighlightSettings].m_highlightServerActiveStates
    constexpr long OFF_GLOW_HIGHLIGHTS = 0xB7A6050;
