/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Made By: ??
 - Complete: 100%
 - ScriptName: 'Buff Command'
 - Comment: Tested & Working
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
#include "Chat.h"
#include "RBAC.h"
#include "WorldSession.h"

uint32 auras[] = { 48162, 48074, 48170, 43223, 36880, 467, 48469 };
 
class buffcommand : public CommandScript
{
public:
    buffcommand() : CommandScript("buffcommand") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> customCommandTable =
        {
            { "buff",  rbac::RBAC_PERM_COMMAND_BUFF,  true,   &HandleBuffCommand,  "" }
        };

        return customCommandTable;
    
    }
 
    static bool HandleBuffCommand(ChatHandler * handler, const char * args)
    {
        Player * pl = handler->GetSession()->GetPlayer();

        if(pl->InArena())
        {
            pl->GetSession()->SendNotification("You can't use that item in an arena match!");
            return false;
        }

        pl->RemoveAurasByType(SPELL_AURA_MOUNTED);
        for(int i = 0; i < 7; i++)

        {
            pl->AddAura(auras[i], pl);
        }
        
        handler->PSendSysMessage("|cffB400B4You have been buffed, enjoy!");

        return true;
    }
};
 
void AddSC_buffcommand()
{
    new buffcommand();
}