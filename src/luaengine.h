/******************************************************************************
	Project: 	MicroMacro
	Author: 	SolarStrike Software
	URL:		www.solarstrike.net
	License:	Modified BSD (see license.txt)
******************************************************************************/

#ifndef LUAENGINE_H
#define LUAENGINE_H

	#include "error.h"
	#include "timer.h"
	#include <string>
	#include <vector>

	class Event;
	typedef struct lua_State lua_State;

	#define MACRO_TABLE_NAME		"macro"
	#define MACRO_INIT_NAME			"init"
	#define MACRO_MAIN_NAME			"main"
	#define MACRO_EVENT_NAME		"event"

	class LuaEngine
	{
		protected:
			lua_State *lstate;
			static int _macrotab_init(lua_State *);
			static int _macrotab_main(lua_State *);
			static int _macrotab_event(lua_State *);
			static int _macrotab_getVersion(lua_State *);
			static int err_msgh(lua_State *);

			void stdError();

			std::string basePath;
			std::string lastErrorMsg;
			TimeType lastTimestamp;			// Holds the timestamp so we can compute delta time
			float fDeltaTime;				// Holds the time elapsed between last cycle and current logic cycle

		public:
			LuaEngine() : lstate(NULL), lastErrorMsg("") { };
			~LuaEngine();

			int init();
			int reinit();
			int cleanup();
			int loadFile(const char *);
			int loadString(const char *);

			int runInit(std::vector<std::string> * = NULL);
			int runMain();
			int runEvent(Event &);

			float getDeltaTime();
			std::string getLastErrorMessage();
			lua_State *getLuaState();

			std::string getBasePath();
			void setBasePath(std::string);
	};


#endif
