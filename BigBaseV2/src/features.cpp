#include "features.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	void features::run_tick()
	{
		g_playerId = PLAYER::PLAYER_ID();

		update_player_structs();
		update_screen_sizes();

		god_mode();
		never_wanted();
		off_radar();
		no_ragdoll();
	}

	void features::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				run_tick();
			}
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}
