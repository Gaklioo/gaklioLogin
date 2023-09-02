#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <map>

/*
First in create user, Read the already created users line by line and assign the Username And Password to the line count as a key
For login user, Read the already created lines and if the Username and Password fall under the same key, login
*/

namespace login {
	using namespace std;
	map<string, string> userLogin{};
	map<string, string>::iterator it{};
	//ToDo: Check if username already exsists
	//Done: Create Users In File
	int createUser() {
		string username{}, password{};
		int lineCount{};
		std::fstream myFile;
		myFile.open("login.txt");

		if (myFile.is_open()) {
			string line{};
			while (std::getline(myFile, line)) {
				lineCount++;
			}
			myFile.close();
		}
		std::ofstream myFile2;
		myFile2.open("login.txt");
		if (myFile2.is_open()) {
			std::cout << "Please enter a username: ";
			std::cin >> username;
			std::cout << "Please enter a password: ";
			std::cin >> password;
			myFile2 << username + "u" << lineCount << "k" << password + "p" << lineCount << "v";
		}
		myFile2.close();
		return 0;
	}

	//ToDo: Check if username and password match
	//Format: uUsername0 pPassword0
	//Store username after u before 0, same for password and if the numbers match on both, login successful
	//Done:
	int loginUser() {
		std::fstream myFile;
		myFile.open("login.txt");
		string lineFile;
		string username{}, password{};
		string checkUsername{}, checkPassword{};
		string checkOne, checkTwo;
		std::cout << "Please Enter Username: ";
		std::cin >> username;
		std::cout << "Please Enter Password: ";
		std::cin >> password;
		if (myFile.is_open()) {
			while (std::getline(myFile, lineFile)) {
				checkUsername = lineFile.find(username);
				std::getline(myFile, checkPassword, 'p');
				std::getline(myFile, checkOne, 'k');
				std::getline(myFile, checkTwo, 'v');
				if (username == checkUsername && password == checkPassword && checkOne == checkTwo) {
					std::cout << "Login Successful";
				}
				std::cout << checkUsername;
			}

			//std::cout << checkUsername << " <- Username, Password ->" << checkPassword;
		}
		else {
			std::cout << " CAnnot open fiel;";
		}
		return 0;
	}
};

int main() {
	login::createUser();
	login::loginUser();
}