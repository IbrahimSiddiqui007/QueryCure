#pragma once
#include <stdio.h>
#include <wx/wx.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <SQLAPI.h> 
#include <Windows.h>
#include <iomanip>

class Process
{
	public:
		Process();
		void detectdb();
		std::string trnsfrmL(std::string st);
		std::string trnsfrmU(std::string st);
		void Select(SAString TbleNme);
		void Statistics(SAString TbleNme);
		void Explain_Plan(SAString TbleNme);
		void Suggestions(SAString TbleNme);
		void display(SAString TbleNme, std::string funcName);
		void connection(std::string user, std::string pass, std::string sname, std::string hst, std::string prt);
		SACommand& GetCommand();
		SAConnection& GetConnect();
		
private:
		SACommand cmd;
		SAConnection con;
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