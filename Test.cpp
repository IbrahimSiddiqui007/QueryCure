#define _CRT_SECURE_NO_WARNINGS
#include "BckEnd.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <SQLAPI.h> 
#include <Windows.h>
#include <iomanip>

Process::Process() {}

std::string Process::trnsfrmL(std::string st)
{
    std::transform(st.begin(), st.end(), st.begin(), std::tolower);
    return st;
}

std::string Process::trnsfrmU(std::string st)
{
    std::transform(st.begin(), st.end(), st.begin(), std::toupper);
    return st;
}

void Process::detectdb()
{
    HKEY key;
}

void Process::display(SAString TbleNme, std::string funcName)
{

    std::string functionName = trnsfrmL(funcName);

    if (functionName == "select")
    {
        int fieldCount = cmd.FieldCount();
        for (int i = 1; i <= fieldCount; i++) {
            std::cout << std::setw(20) << std::left << (std::string)cmd.Field(i).Name() << " ";
        }
        std::cout << std::endl;
        std::cout << std::setfill('-')
            << std::setw(131)
            << "-"
            << std::setfill(' ')
            << std::endl;

        while (cmd.FetchNext())
        {
            for (int i = 1; i <= fieldCount; i++) {
                std::cout << std::setw(20) << std::left << (std::string)cmd.Field(i).asString() << " ";
            }
            std::cout << std::endl;
            std::cout << std::setfill('-')
                << std::setw(131)
                << "-"
                << std::setfill(' ')
                << std::endl;

        }
    }
    else if (functionName == "explain_plan")
    {
        while (cmd.FetchNext()) {
            std::cout << "|" << std::setw(10) << std::left << (std::string)cmd[1].asString() << "|"
                << std::setw(20) << std::left << (std::string)cmd[2].asString() << "|"
                << std::setw(10) << std::left << (std::string)cmd[3].asString() << "|"
                << std::setw(20) << std::left << (std::string)cmd[4].asString() << "|"
                << std::setw(15) << std::left << (std::string)cmd[5].asString() << "|"
                << std::setw(10) << std::left << (std::string)cmd[6].asString() << "|"
                << std::setw(10) << std::left << (std::string)cmd[7].asString() << "|"
                << std::setw(10) << std::left << (std::string)cmd[8].asString() << "|"
                << std::setw(10) << std::left << (std::string)cmd[9].asString() << "|"
                << std::setw(5) << std::left << (std::string)cmd[10].asString() << "|"
                << std::endl;
            std::cout << std::setfill('-')
                << std::setw(131)
                << "-"
                << std::setfill(' ')
                << std::endl;
        }
    }
    else if (functionName == "statistics")
    {
        int fieldCount = cmd.FieldCount();
        for (int i = 1; i <= fieldCount; i++) {
            std::cout << std::setw(20) << std::left << (std::string)cmd.Field(i).Name() << " ";
        }
        std::cout << std::endl;
        std::cout << std::setfill('-')
            << std::setw(200)
            << "-"
            << std::setfill(' ')
            << std::endl;

        while (cmd.FetchNext())
        {
            for (int i = 1; i <= fieldCount; i++) {
                std::cout << std::setw(20) << std::left << (std::string)cmd.Field(i).asString() << " ";
            }
            std::cout << std::endl;
            std::cout << std::setfill('-')
                << std::setw(200)
                << "-"
                << std::setfill(' ')
                << std::endl;

        }
    }

}

void Process::Explain_Plan(SAString TbleNme)
{
    std::string FuncName = __FUNCTION__;

    cmd.setCommandText("EXPLAIN PLAN FOR SELECT * FROM " + TbleNme);
    cmd.Execute();

    /*cmd.setCommandText("SELECT plan_table_output FROM TABLE(DBMS_XPLAN.DISPLAY())");
    cmd.Execute();

    while (cmd.FetchNext())
    {
        std::cout << (std::string)cmd[1].asString() << std::endl;;
    }*/


    cmd.setCommandText("SELECT PLAN_ID,OPERATION,OPTIONS,OBJECT_NAME,CARDINALITY,BYTES,COST,CPU_COST,IO_COST,TIME FROM PLAN_TABLE");
    cmd.Execute();

    std::cout << std::setfill('-')
        << std::setw(131)
        << "-"
        << std::setfill(' ')
        << std::endl;

    std::cout << "|" << std::setw(10) << std::left << "PLAN_ID" << "|"
        << std::setw(20) << std::left << "OPERATION" << "|"
        << std::setw(10) << std::left << "OPTIONS" << "|"
        << std::setw(20) << std::left << "OBJECT_NAME" << "|"
        << std::setw(15) << std::left << "ROWS" << "|"
        << std::setw(10) << std::left << "BYTES" << "|"
        << std::setw(10) << std::left << "COST" << "|"
        << std::setw(10) << std::left << "CPU_COST" << "|"
        << std::setw(10) << std::left << "IO_COST" << "|"
        << std::setw(5) << std::left << "TIME" << "|"
        << std::endl;

    std::cout << std::setfill('-')
        << std::setw(131)
        << "-"
        << std::setfill(' ')
        << std::endl;

    display(TbleNme, FuncName);

}

void Process::Statistics(SAString TbleNme)
{
    std::string FuncName = __FUNCTION__;
    std::string StatChoice;
    SAString SChoice, stats;


    std::cout << "Please enter the option number for the type of statistics that you want to view:" << "\n"
        << "1. Tables" << "\n"
        << "2. Indexes" << "\n"
        << "3. Materialized views" << "\n"
        << "4. Table Partitions" << "\n"
        << "5. Columns of tables" << "\n"
        << "6. Clusters" << std::endl;

    std::cin >> StatChoice;
    SChoice = StatChoice.c_str();
    // all stats get the same values
    if (StatChoice.find("1") || StatChoice.find("tables"))
    {
        stats = "ALL_TAB_STATISTICS";
    }
    else if (StatChoice.find("2") || StatChoice.find("indexes"))
    {
        stats = "ALL_IND_STATISTICS";
    }
    else if (StatChoice.find("3") || StatChoice.find("materialized views"))
    {
        stats = "ALL_MVIEW_STATISTICS";
    }
    else if (StatChoice.find("4") || StatChoice.find("table partitions"))
    {
        stats = "ALL_TAB_PARTITIONS";
    }
    else if (StatChoice.find("5") || StatChoice.find(" columns of tables"))
    {
        stats = "ALL_TAB_COL_STATISTICS";
    }
    else if (StatChoice.find("6") || StatChoice.find("Clusters"))
    {
        stats = "DBA_TAB_CLUSTER_STATISTICS";
    }

    cmd.setCommandText("SELECT * FROM " + stats + " WHERE TABLE_NAME = '" + TbleNme + "'");
    cmd.Execute();

    display(TbleNme, FuncName);

}

void Process::Select(SAString TbleNme)
{
    std::string FuncName = __FUNCTION__;

    try {
        // Execute the SELECT statement
        cmd.setCommandText("SELECT * FROM " + TbleNme);
        cmd.Execute();
        // Call the display function to display the result set
        display(TbleNme, FuncName);
    }
    catch (SAException& ex) {
        // Handle any exceptions that occur during execution
        std::cerr << "Error executing SELECT statement: " << ex.ErrText().GetMultiByteChars() << std::endl;
    }
}
// Discover automatically
// If can't ask user
void Process::connection(std::string user, std::string pass, std::string sname, std::string hst, std::string prt)
{
    /*std::string user, pass, sname, hst, prt;*/

    /*std::cout << "Please enter the username" << std::endl;
    std::cin >> user;*/
    username = user.c_str();

    /*std::cout << "Please enter the password" << std::endl;
    std::cin >> pass;*/
    password = pass.c_str();

    /*std::cout << "Please enter the host address" << std::endl;
    std::cin >> hst;*/
    host = hst.c_str();

    /*std::cout << "Please enter the port address" << std::endl;
    std::cin >> prt;*/
    port = prt.c_str();

    /*std::cout << "Please enter the service name" << std::endl;
    std::cin >> sname;*/
    service_name = sname.c_str();

    try
    {
        //con.Connect("(DESCRIPTION=(ADDRESS=(PROTOCOL=tcp) (HOST="+host+") (PORT="+port+"))(CONNECT_DATA = (SERVICE_NAME = XEPDB1)))", username,password, SA_Oracle_Client);
        con.Connect("(DESCRIPTION=(ADDRESS=(PROTOCOL=tcp) (HOST=LocalHost) (PORT=1521))(CONNECT_DATA = (SERVICE_NAME = XEPDB1)))", "hr", "hr", SA_Oracle_Client);
        cmd.setConnection(&con);

    }
    catch (SAException& ex)
    {
        // Handle SQLAPI++ exceptions
        std::cerr << "Error: " << (const char*)ex.ErrText() << std::endl;
    }
    catch (std::exception& ex)
    {
        // Handle other standard exceptions
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    catch (...)
    {
        // Handle all other exceptions
        std::cerr << "Unknown error occurred" << std::endl;
    }
    std::cout << "Connected to Oracle Server!" << std::endl;
}

void Process::Suggestions(SAString TbleNme)
{
    std::string FuncName = __FUNCTION__;

    try {
    cmd.setCommandText(
        "DECLARE "
        "v_table_name VARCHAR2(30) := '"+ TbleNme +"'; "
        "v_threshold_rows NUMBER := 100; -- 100 rows "
        "v_table_size_rows NUMBER; "
        "v_index_exists NUMBER; "
        "BEGIN "
        "-- Check the number of rows in the table "
        "SELECT COUNT() "
        "INTO v_table_size_rows "
        "FROM customer; "
        "-- Check whether the table has an index "
        "SELECT COUNT() INTO v_index_exists "
        "FROM all_indexes "
        "WHERE table_name = v_table_name; "
        "-- If the table is larger than the threshold and does not have an index, suggest creating an index "
        "IF v_table_size_rows > v_threshold_rows AND v_index_exists = 0 THEN "
        "DBMS_OUTPUT.PUT_LINE('The ' || v_table_name || ' table has more than ' || v_threshold_rows || ' rows and does not have an index. Consider creating an index.'); "
        "ELSE "
        "DBMS_OUTPUT.PUT_LINE('The ' || v_table_name || ' table does not appear to need an index.'); "
        "END IF; "
        "END; ");

        cmd.Execute();
        std::cout << (std::string)cmd.Param("output").asString() << std::endl;
    }
    catch (SAException& ex) {
        // Handle any exceptions that occur during execution
        std::cerr << "Error executing suggestions statement: " << ex.ErrText().GetMultiByteChars() << std::endl;
    }

    //MV, DENORMALIZATION, DECOMPOSTION, DYNAMIC VIEWS, CLUSTERING, PARTIONING. 


    //index
    //denorm
    //cluster
}

SACommand& Process::GetCommand() {
    return cmd;
}

//int main()
//{
//    SACommand cmd;
//    SAConnection con;
//
//    bool quit = false;
//    std::string tableChoice;
//    int choice;
//    SAString TbleNme;
//
//    connection(con,cmd);
//
//    while (!quit)
//    {
//        std::cout << "Please enter the table you want to use" << std::endl;
//        std::cin >> tableChoice;
//        TbleNme = tableChoice.c_str();
//
//        std::cout << "Please choose your option:" << "\n"
//            << "1. Display data" << "\n"
//            << "2. Explain_plan" << "\n"
//            << "3. Statistics" << "\n"
//            << "4. Suggestions" << "\n"
//            << "0 to quit" << "\n"
//            << std::endl;
//
//        std::cin >> choice;
//
//        switch (choice)
//        {
//            case 1:
//            {
//                Select(cmd, TbleNme);
//                break;
//            }
//            case 2:
//            {
//                Explain_Plan(cmd, TbleNme);
//                break;
//            }
//            case 3:
//            {
//                Statistics(cmd, TbleNme);
//                break;
//            }
//            case 4:
//            {
//                Suggestions(cmd, TbleNme);
//                break;
//            }
//            case 5:
//            {
//               // Security(cmd, TbleNme);
//                break;
//            }
//            case 0:
//            {
//                exit(0);
//                break;
//            }
//            default:
//            {
//               break;
//            }
//        }
//    }
//
//    return 0;
//}

// connect gui and connection function, get host,port,
// get table and convert into string array
// make error for db dont exist 
// get table structure
// get different type of statistics

// what they have done on the db
// list of connections and privileges

// Scheduling (important)

