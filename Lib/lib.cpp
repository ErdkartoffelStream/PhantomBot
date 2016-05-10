/**
    lib.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#include "lib.h"

namespace Lib {

	Socket *createSocketAndConnect(const std::string addr, unsigned int port) {
		Socket *s = new Socket();
		if(!s->Create()) {
		    std::cout << "Lib::createSocketAndConnect(): Creation Failed" << std::endl;
		    return NULL;
		}
		if(!s->Connect(addr, port)) {
		    std::cout << "Lib::createSocketAndConnect(): Connection Failed" << std::endl;
		    return NULL;        
		}
		return s;
	}

	std::string currentTime() {
		time_t t = time(NULL);
		char *s = ctime(&t);
		s[strlen(s)-1] = 0;
		return std::string(s);
	}

	void writeToLog(std::string logLocation, std::string message) {
	    std::fstream f(logLocation.c_str(), std::fstream::app | std::fstream::out);
		std::string output;
		output = "[" + currentTime() + "]: " + message + "\n";
		f.write(output.c_str(), output.size());
		f.close();
	}
	
	std::string formatForPrint(std::string incoming) {
		std::string out = incoming;
		out.erase(std::remove(out.begin(), out.end(), '\r'), out.end());
		out.erase(std::remove(out.begin(), out.end(), '\n'), out.end());
		return out;
	}
	
	std::string formatChatMessage(const std::string message) {
		const std::string format = "PRIVMSG " + TwitchCommandLimit::fetchInstance().Channel() + " :" + message + "\r\n";
		return format;
	}	
	
	void stripMessage(std::string incoming, std::string &username, std::string &message) {
		std::string cName = TwitchCommandLimit::fetchInstance().Channel();
		size_t nameBegin = incoming.find("display-name=")+13;
		size_t nameEnd = incoming.find(";", nameBegin);
		size_t messageStart = incoming.find(cName + " :") + cName.size() + 2;
		//The correct format is :NAME!, test here
		username = incoming.substr(nameBegin, (nameEnd - nameBegin));
		//Fetch the message content
		if(messageStart != string::npos) {
			for(size_t i = messageStart; i < incoming.size(); i++) {
				message.push_back(incoming[i]);
			}
		}	
	}

};
