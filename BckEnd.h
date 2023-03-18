#pragma once
#include <stdio.h>
//#include <wx/wx.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <SQLAPI.h> 
#include <Windows.h>
#include <iomanip>

class Process
{
	public:
		int main();
		SACommand cmd;
		SAConnection con;
		void detectdb();
		std::string trnsfrmL(std::string st);
		std::string trnsfrmU(std::string st);
		void Select(SACommand& cmd, SAString TbleNme);
		void Statistics(SACommand& cmd, SAString TbleNme);
		void Explain_Plan(SACommand& cmd, SAString TbleNme);
		void display(SACommand& cmd, SAString TbleNme, std::string funcName);
		void connection(SAConnection& con, SACommand& cmd, std::string user, std::string pass, std::string host, std::string port, std::string service);
		SAConnection& getConnection();
		
private:
		int count;
		SAString TbleNme;
		SAString SChoice;
		SAString stats;
		SAString username;
		SAString password;
		SAString service_name;
		SAString host;
		SAString port;
		std::string funcName;
		std::string TableName;
		std::string StatChoice;
		std::string user;
		std::string pass;
		std::string sname;
		std::string hst;
		std::string prt;
		std::string choice;
		std::string tableChoice;
};