/**
    lib.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
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
	
	const unsigned long long fetchTime() {
		struct timeval tv;

		gettimeofday(&tv, NULL);

		unsigned long long millisecondsSinceEpoch =
    		(unsigned long long)(tv.tv_sec) * 1000 +
    		(unsigned long long)(tv.tv_usec) / 1000;
    		
    	return millisecondsSinceEpoch;
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
	
	bool validateExpr(const std::string incoming, const std::string validTokens) {
		return incoming.find_first_not_of(validTokens) == std::string::npos;
	}
	
	void tokenizeString(const std::string incoming, const std::vector<char> tokens, std::queue<std::string> &out) {
		const char *str = incoming.c_str();
		do {
			const char *begin = str;
			for(int i = 0; i < tokens.size(); i++) {
				while(*str != tokens[i] && *str) {
				    str++;
				}
			}
			out.push(string(begin, str));
		} while (0 != *str++);	

	}
	
	std::string strTrim(const std::string &s) {
		std::string::const_iterator it = s.begin();
		while (it != s.end() && isspace(*it)) {
		    it++;
		}
		std::string::const_reverse_iterator rit = s.rbegin();
		while (rit.base() != it && isspace(*rit)) {
		    rit++;
		}
		return std::string(it, rit.base());
	}	

};
