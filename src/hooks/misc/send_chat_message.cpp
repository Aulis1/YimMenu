#include "backend/command.hpp"
#include "backend/context/chat_command_context.hpp"
#include "gta/net_game_event.hpp"
#include "gta_util.hpp"
#include "hooking/hooking.hpp"
#include "packet.hpp"
#include "services/players/player_service.hpp"
#include "util/chat.hpp"

namespace big
{
	inline void gamer_handle_serialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		constexpr int PC_PLATFORM = 3;
		buf.Write<uint8_t>(PC_PLATFORM, 8);
		buf.WriteInt64(*(int64_t*)&hnd.m_rockstar_id, 64);
		buf.Write<uint8_t>(hnd.unk_0009, 8);
	}

	bool hooks::send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, char* message, bool is_team)
	{
		if (g.session.chat_commands && message[0] == g.session.chat_command_prefix)
			command::process(std::string(message + 1), std::make_shared<chat_command_context>(g_player_service->get_self()));

		chat::send_message(message, nullptr, false, is_team);

		if (g.session.log_chat_messages)
			chat::log_chat(message, g_player_service->get_self(), SpamReason::NOT_A_SPAMMER, is_team);

		return true;
	}
}