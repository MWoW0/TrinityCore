/*
Made by MoltenX
!DO NOT RELEASE WITHOUT PERMISSIONS!
*/
#include "ScriptPCH.h"
#include "Chat.h"


uint32 auras[] = { 15366, 16609, 48162, 48074, 48170, 43223, 36880, 467, 69994, 33081, 24705, 26035, 48469 };

class buffcommand : public CommandScript
{
public:
    buffcommand() : CommandScript("buffcommand") { }

	ChatCommand* GetCommands() const
    {
        static ChatCommand IngameCommandTable[] =
        {
	{ "buff",           SEC_PLAYER,  	true,  &HandleBuffCommand,                "", NULL },
        { NULL,             0,                  false, NULL,                              "", NULL }
        };
		 return IngameCommandTable;
    }

	static bool HandleBuffCommand(ChatHandler * handler, const char * args)
    {
        Player * pl = handler->GetSession()->GetPlayer();
	
		pl->RemoveAurasByType(SPELL_AURA_MOUNTED);
		for(int i = 0; i < 11; i++)
		    pl->AddAura(auras[i], pl);
		handler->PSendSysMessage("|cffB400B4You have been buffed, enjoy!");
		return true;
    }
};

void AddSC_buffcommand()
{
    new buffcommand();
}