D(OP_SendLoginInfo)
E(OP_ApproveWorld)
E(OP_EnterWorld)
E(OP_ExpansionInfo)
E(OP_SendCharInfo)
E(OP_ZoneEntry)
E(OP_PlayerProfile)
E(OP_ZoneServerInfo)
E(OP_NewZone)
E(OP_NewSpawn)
E(OP_ZoneSpawns)
//E(OP_GuildsList)
D(OP_EnterWorld)
D(OP_ChannelMessage)
E(OP_ChannelMessage)
E(OP_SpecialMesg)
E(OP_ClientUpdate)
D(OP_ClientUpdate)
E(OP_MobUpdate)
D(OP_TargetCommand)
D(OP_TargetMouse)
D(OP_CharacterCreate)
E(OP_Consider)
D(OP_Consider)
D(OP_ConsiderCorpse)
D(OP_SetServerFilter)
D(OP_ZoneChange)
E(OP_ZoneChange)
E(OP_CancelTrade)
E(OP_MemorizeSpell)
D(OP_MemorizeSpell)
E(OP_Buff)
D(OP_Buff)
E(OP_BeginCast)
E(OP_CastSpell)
D(OP_CastSpell)
E(OP_Damage)
D(OP_Damage)
E(OP_Action)
E(OP_Action2)
D(OP_EnvDamage)
D(OP_ClickDoor)
D(OP_GMEndTraining)
E(OP_ItemPacket)
E(OP_TradeItemPacket)
E(OP_ItemLinkResponse)
E(OP_CharInventory)
D(OP_MoveItem)
E(OP_MoveItem)
E(OP_DeleteCharge)
D(OP_DeleteCharge)
E(OP_Stamina)
E(OP_HPUpdate)
E(OP_MobHealth)
D(OP_Consume)
E(OP_ReadBook)
D(OP_ReadBook)
E(OP_Illusion)
D(OP_Illusion)
E(OP_ShopRequest)
D(OP_ShopRequest)
E(OP_ShopInventoryPacket)
D(OP_ShopPlayerBuy)
E(OP_ShopPlayerBuy)
E(OP_ShopDelItem)
D(OP_ShopPlayerSell)
E(OP_ShopPlayerSell)
E(OP_Animation)
D(OP_Animation)
E(OP_LootItem)
D(OP_LootItem)
E(OP_AAExpUpdate)
E(OP_AAAction)
E(OP_GroundSpawn)
D(OP_GroundSpawn)
E(OP_ClickObjectAction)
D(OP_ClickObjectAction)
D(OP_TradeSkillCombine)
D(OP_TradeRequest)
E(OP_TradeRequest)
E(OP_TradeRequestAck)
D(OP_TradeRequestAck)
D(OP_CancelTrade)
E(OP_ManaChange)
E(OP_DeleteSpawn)
E(OP_TimeOfDay)
D(OP_WhoAllRequest)
E(OP_GroupInvite)
D(OP_GroupInvite)
E(OP_GroupInvite2)
D(OP_GroupInvite2)
E(OP_TradeCoins)
D(OP_ItemLinkResponse)
E(OP_LogServer)
E(OP_RequestClientZoneChange)
D(OP_SetGuildMOTD)
E(OP_GuildMOTD)
D(OP_GuildInviteAccept)
E(OP_Trader)
D(OP_Trader)
D(OP_BazaarSearch)
E(OP_BecomeTrader)
E(OP_TraderBuy)
D(OP_TraderBuy)
E(OP_WearChange);
D(OP_WearChange);
E(OP_ExpUpdate);
E(OP_Death);
D(OP_Bug);
D(OP_Taunt);
D(OP_CombatAbility);
E(OP_Projectile);
E(OP_Charm);
E(OP_Sound);
E(OP_FaceChange);
D(OP_FaceChange);
D(OP_Assist);
E(OP_Assist);

//Below are invalid opcodes ONLY
E(OP_Unknown);
E(OP_DisciplineUpdate);
E(OP_Dye);
E(OP_RaidJoin);
E(OP_RemoveAllDoors);
E(OP_SendAAStats);
E(OP_SpellEffect);
E(OP_TraderDelItem);
E(OP_TraderItemUpdate);
E(OP_Untargetable);
E(OP_UpdateAA);
#undef E
#undef D
