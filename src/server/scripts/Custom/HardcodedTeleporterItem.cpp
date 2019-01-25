#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "ObjectGuid.h"
#include "Item.h"

enum GossipMenuOptions
{
	MAIN_MENU = 200000,
	STARTER_MALL = 200001,
	ZUL_FARAK = 200002
};

class HardcodedTeleporterItem : public ItemScript
{
	public:
		HardcodedTeleporterItem() : ItemScript("HardcodedTeleporterItem") {}

	/**
	 * Called when a player uses the item.
	 *
	 * @override ScriptMgr.h#L377
	 * @return bool
	 */
	bool OnUse(Player* player, Item* item, SpellCastTargets const & /*targets*/) override
	{
		if (player->IsInCombat())
		{
			return false;
		}

		AddGossipMenuItems(player);
		player->PlayerTalkClass->SendGossipMenu(MAIN_MENU, item->GetGUID());

		return true;
	}

	void AddGossipMenuItems(Player* player) 
	{
		player->PlayerTalkClass->ClearMenus();

		// @reference ScriptedGossip.h#L87
		// void TC_GAME_API AddGossipItemFor(Player* player, uint32 icon, std::string const& text, uint32 sender, uint32 action);
		
		AddGossipItemFor(player, 0, "|TInterface\\icons\\spell_arcane_teleportshattrath:20|tStarter Mall", GOSSIP_SENDER_MAIN, 200001);
		AddGossipItemFor(player, 0, "|TInterface\\icons\\achievement_zone_tanaris_01:20|tCustom Dungeon", GOSSIP_SENDER_MAIN, 2000000);
	}

	/**
	 * Called when player selects a menu item
	 *
	 * @implements Player.h#L1185 
	 */
    void OnGossipSelect(Player* player, uint32 gossipListId, uint32 menuId) 
	{
	    GossipMenu& gossipMenu = player->PlayerTalkClass->GetGossipMenu();

	    if (menuId != gossipMenu.GetMenuId()) {
	        return;
	    }

	    GossipMenuItem const* item = gossipMenu.GetItem(gossipListId);
	    if (!item) {
	    	return;
	    }

	    uint32 gossipOptionId = item->OptionType;

	    switch(gossipOptionId) {
	    	case 200001://STARTER_MALL
	    		player->TeleportTo(530, -2278.14f, 5568.74f, 66.9998f, 5.9990100f);
	    		break;

	    	case 2000000://Zul Farrak
	    		player->TeleportTo(1, -6806.85f, -2890.600f, 8.8868f, 6.257260f);
	    		break;
	    }
    }

	// void AddGossipItemFor(Player* player, uint32 icon, std::string const& text, uint32 sender, uint32 action) 
	// { 
	// 	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, icon, text, sender, action, "", 0);
	// }
};

void AddSC_HardcodedTeleporterItem()
{
	new HardcodedTeleporterItem();
}
