/**
    isadmin.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#ifndef _CCMD_ISADMIN_H
#define _CCMD_ISADMIN_H

#include "CustomCommands.h"

class Command_IsAdmin : public CustomCommand {
	public:
		/* Public Class Methods */
		//Constructor
		Command_IsAdmin() : CustomCommand() { }
		//Destructor
		virtual ~Command_IsAdmin() { }
		//Run the command
		virtual void Fire(std::string input) {
			std::string name, message;
			Lib::stripMessage(input, name, message);
	
			bool isAdmin = Admin::fetchInstance().CheckAdminStatus(name);
			std::string response = Lib::formatChatMessage(name + (isAdmin ? " is" : " is not") + " flagged as an administrator.");
			TwitchCommandLimit::fetchInstance().AddCommand(response);		
		}
};

#endif //_CCMD_ISADMIN_H