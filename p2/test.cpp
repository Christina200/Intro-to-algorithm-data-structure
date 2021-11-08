//
// Created by WeiXiwen on 2021/6/19.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "bot.h"
#include "constants.h"
int main() {
    /*
    CourseInfo s;
    CourseInfo *test_hh = &s;
    test_hh->CourseCode="VE280";
    std::cout<<test_hh->CourseCode;
    */
    /*
    std::ifstream courseFile ("../cases/JICourses.txt");
    if (courseFile.is_open()) {
        std::string line;
        //GET COURSE NUMBER n
        std::getline(courseFile, line);
        std::istringstream iString;
        iString.str(line);
        int n = std::stoi(line);
        //INITIALIZE STRING ARRAY OF LENGTH n
        CourseInfo Course[n];
        int index = 0;
        while (std::getline(courseFile, line) && index < n) {
            std::istringstream iString_tmp(line);
            std::string current;
            std::string divided[3];
            int index2=0;
            while (std::getline(iString_tmp,current,',')){
                divided[index2]=current;
                ++index2;
            }
            Course[index].CourseCode=divided[0];
            Course[index].CourseName=divided[1];
            Course[index].Instructor=divided[2];
            ++index;
        }
    }
    courseFile.close();*/
/*
    CourseList s{};
    ReadCourse("../cases/JICourses.txt",&s);
    std::cout<<s.CourseNumber<<"\n";
    delete [] s.Course;
*/
/*
    std::ifstream iFile ("../cases/JICourses.txt");
    if (iFile.is_open()) std::cout<<1;
    else std::cout<<0;
    */
/*
GroupList s;
ReadGroup("../cases/groupList",&s);
std::cout<<s.GroupNumber<<"\n"<<s.GroupAddress<<"\n"<<s.Groups[0].GroupName<<"\n"<<s.Groups[0].AdminNumber<<"\n";
std::cout<<s.Groups[0].AdminName[0]<<s.Groups[0].AdminName[1];
 */
/*
    std::string keyword;
    std::string content = "   hi   ve280";
    std::istringstream iString;
    iString.str(content);
    while (std::getline(iString,keyword,' ')){
        std::cout<<keyword<<"\n";
    };
    */
/*
    CourseList s{};
    ReadCourse("../cases/JICourse.txt",&s);
    GroupList g;
    ReadGroup("../cases/groupList",&g);
    Message message;
    //ParseMessage(&message);
    message.content="#instructor e";
    message.group="-6";
    message.user="Dio";
    message.time="13:31:33";
    //CommandJudge(message,s,g);
    //PrintInstructorKeyword(s,"e");
    //PrintCoursesKeyword(s,"VE477");
    std::cout<<s.CourseNumber;
   */
/*
    CourseList s{};
    ReadCourse("../cases/JICourse.txt",&s);
    GroupList g;
    ReadGroup("../cases/groupList",&g);
    Message message;
    std::string line;
    std::ifstream iFile ("../cases/query");
    while (std::getline(iFile,line)){
        std::istringstream iString;
        iString.str(line);
        std::string current;
        std::getline(iString,current,',');
        message.time=current;
        std::getline(iString,current,',');
        message.group=current;
        std::getline(iString,current,',');
        message.user=current;
        std::getline(iString,current);
        message.content=current;
        CommandJudge(message,s,g);
    }
*/
    //std::cout<<s.Course[0].CourseName<<"\n"<<g.Groups[0].AdminName[1];
    //std::cout<<message.group<<message.content;

    /*for (std::string line; std::getline(std::cin, line);){
        std::cout<<line;
    }
    std::cout<<"he";*/
/*
    std::string content = "#course  If if";
    std::cout<<KeyWordProcess(content);
    */
/*
std::string content ="#course VE477";
std::string res;
    std::string keyword;
    std::istringstream iString;
    iString.str(content);
    //load command
    std::string command;
    iString>>command;
    if (command==content)
        res = "";
    else {
        iString>>keyword;
        if (keyword.empty()) res= "";
        std::string tmp;
        while (std::getline(iString,tmp)){
            keyword+=tmp;
        }
        res= keyword;
    }
    std::cout<<res;
    */
}