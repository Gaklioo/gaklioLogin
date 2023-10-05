#include <iostream>
#include <string>
#include <map>
#include <ostream>
#include <fstream>

namespace login {
	std::map<std::string, std::string> map;
	std::map<std::string, std::string>::iterator it;
	std::string username, password;

	void writeToFile() { // 
		std::ofstream myFile;
		myFile.open("mapLogin.txt");

		if (myFile.is_open()) {
			for (it = map.begin(); it != map.end(); it++) {
				myFile << it->first << " " << it->second << "\n";
			}
		}

		myFile.close();
	}

	void setMapFromFile() { // Call this before anything else in the login namespace.
		std::fstream myFile;
		myFile.open("mapLogin.txt");
		std::string username, password;
		std::size_t pos;

		if (myFile.is_open()) {
			std::string line;
			while (std::getline(myFile, line)) {
				pos = line.find(" ");
				username = line.substr(0, pos);
				line.erase(0, pos + 1);
				password = line;

				map[username] = password;
			}
		}

	}

	bool doesUserExsist(std::string& username) {
		for (it = map.begin(); it != map.end(); it++) {
			if (username == it->first) {
				return true;
			}
		}
		return false;
	}

	void createUser() {
		std::cout << "Please enter your username" << std::endl;
		std::getline(std::cin, username);
		if (!doesUserExsist(username)) {
			std::cout << "Please enter your password" << std::endl;
			std::getline(std::cin, password);
			map[username] = password;
			writeToFile();
		}
		else {
			std::cout << "Username Already Taken, Please Try Again." << std::endl;
			createUser();
		}
	}

	bool login() {
		std::cout << "Please enter your username" << std::endl;
		std::getline(std::cin, username);
		std::cout << "Please enter your password" << std::endl;
		std::getline(std::cin, password);

		for (it = map.begin(); it != map.end(); it++) {
			if (it->first == username && it->second == password) {
				return true;
			}
		}
		return false;
	}

}
