#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

namespace login {
	using namespace std;

	bool doesUserExsist(std::string checkUsername) {
		std::fstream myFile;
		myFile.open("login.txt");
		string line{}, usernames{};
		std::size_t pos = checkUsername.length();

		if (myFile.is_open()) {
			while (std::getline(myFile, line)) {
				usernames = line.substr(0, pos);

				if (checkUsername == usernames) {
					return true;
				}
			}

			return false;
		}
		myFile.close();
	}

	int createKeyValue() {
		std::fstream myFile;
		myFile.open("login.txt");
		string line;
		int lineCount{};
		if (myFile.is_open()) {
			string line{};
			while (std::getline(myFile, line)) {
				++lineCount;
			}
			myFile.close();
		}

		return lineCount;
	}

	int createUser() {
		string username{}, password{}, usernameCheck{};
		int keyValues = createKeyValue();

		std::ofstream myFile;
		myFile.open("login.txt", ios::app);
		if (myFile.is_open()) {
			std::cout << "Please enter a username: ";
			std::cin >> username;
			if (doesUserExsist(username)) {
				std::cout << "Username already in use." << std::endl;
				createUser();
				std::cin.clear();
			}
			else {
				std::cout << "Please enter a password: ";
				std::cin >> password;
				myFile << username << "u" << keyValues << "k" << password << "p" << keyValues << "v" << std::endl;
			}
		}
		myFile.close();
		return 0;
	}

	int loginUser() {
		std::fstream myFile;
		myFile.open("login.txt");
		string lineFile;
		string username{}, password{};
		string usernameCheck, passwordCheck, checkOne, checkTwo;
		std::cout << "Please Enter Username: ";
		std::cin >> username;
		std::cout << "Please Enter Password: ";
		std::cin >> password;

		std::size_t pos;
		std::size_t usernamePos = username.length();
		std::size_t passwordPos = password.length();
		if (myFile.is_open()) {
			while (std::getline(myFile, lineFile)) {
				usernameCheck = lineFile.substr(0, usernamePos);
				lineFile.erase(0, usernamePos + 1);
				pos = lineFile.find('k');
				checkOne = lineFile.substr(0, pos);
				lineFile.erase(0, pos + 1);
				passwordCheck = lineFile.substr(0, passwordPos);
				lineFile.erase(0, passwordPos + 1);
				pos = lineFile.find('v');
				checkTwo = lineFile.substr(0, pos);
				lineFile.erase(0, pos + 1);

				if (usernameCheck == username && passwordCheck == password && checkOne == checkTwo) {
					std::cout << "Sucessfully Logged in";
				}
				else if (usernameCheck == username && passwordCheck != password) {
					std::cout << "Incorrect Password";
				}
				else if (usernameCheck != username) {
					std::cout << "Username does not exsist";
					break;
				}
			}
		}
		myFile.close();
		return 0;
	}
};
