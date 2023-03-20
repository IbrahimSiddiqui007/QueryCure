cmake_minimum_required(VERSION 3.24)
project(QueryCure_Landing_Security_Manage)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(QueryCure_Landing_Security_Manage
        App.cpp
        App.h
        BckEnd.h
        DiagnosisAnalysis.cpp
        DiagnosisAnalysis.h
        MainFrame.cpp
        MainFrame.h
        ManageUsers.cpp
        ManageUsers.h
        SecurityFrame.cpp
        SecurityFrame.h
        SecurityPage.cpp
        SecurityPage.h
        Test.cpp)
