//
// Created by WeiXiwen on 2021/6/14.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "bot.h"
#include "constants.h"
#include "rand.h"


void ReadCourse(const std::string& course_list,CourseList * courseList){
    std::ifstream courseFile (course_list);
        std::string line;
        std::getline(courseFile, line);
        int n = std::stoi(line);
        courseList->CourseNumber=n;
        //allocate new memory for CourseInfo.
        courseList->Course = new CourseInfo[courseList->CourseNumber];
        int index = 0;
        while (std::getline(courseFile,line)) {
            std::istringstream iString_tmp;
            iString_tmp.str(line);
            std::getline(iString_tmp,courseList->Course[index].CourseCode,',');
            std::getline(iString_tmp,courseList->Course[index].CourseName,',');
            std::getline(iString_tmp,courseList->Course[index].Instructor);
            ++index;
        }
        courseFile.close();
}

void ReadGroup(const std::string& group_list,GroupList * groupList){
    std::ifstream groupFile (group_list);
        //get group files' address
        std::getline(groupFile,groupList->GroupAddress);
        //get group number
        std::string current;
        std::getline(groupFile,current);
        groupList->GroupNumber=std::stoi(current);
        //read each group's admin information
        groupList->Groups = new GroupInfo[groupList->GroupNumber];
        int index=0;
        while (std::getline(groupFile,groupList->Groups[index].GroupName)){
            ReadAdmin(groupList->GroupAddress+"/"+groupList->Groups[index].GroupName,&groupList->Groups[index]);
            ++index;
        }
}

void ReadAdmin(const std::string& group_address,GroupInfo * groupInfo){
    std::ifstream group (group_address);

        std::string current;
        //get admin number
        std::getline(group,current);
        groupInfo->AdminNumber=std::stoi(current);
        //read admin info
        groupInfo->AdminName = new std::string[groupInfo->AdminNumber];
        int index = 0;
        while (std::getline(group,groupInfo->AdminName[index])){
            ++index;
        }
}

void ParseMessage(Message * message,const std::string& line){
    std::istringstream iString;
    iString.str(line);
    std::getline(iString,message->time,',');
    std::getline(iString,message->group,',');
    std::getline(iString,message->user,',');
    std::getline(iString,message->content);
}

void PrintCoursesKeyword(const CourseList& courseList,const std::string& key){
    bool isFind = false;
    for (int i = 0; i < courseList.CourseNumber; ++i) {
        if (courseList.Course[i].CourseName.find(key)!= std::string::npos||courseList.Course[i].CourseCode.find(key)!= std::string::npos){
            isFind = true;
            std::cout<<"Course Code: "<<courseList.Course[i].CourseCode<<"\n";
            std::cout<<"Course Name: "<<courseList.Course[i].CourseName<<"\n";
            std::cout<<"Instructor: "<<courseList.Course[i].Instructor<<"\n";
        }
    }
    if (isFind) std::cout<<"\n";
    else std::cout<<COURSE_NOT_FOUND<<"\n"<<"\n";
}

void PrintInstructorKeyword(const CourseList & courseList,const std::string& key){
    //isFind: if an instructor contains keyword.
    bool isFind = false;
    std::string target_instructor[courseList.CourseNumber];
    int target_number=0;
    //go through the course list and find instructor containing keyword.
    for (int i = 0; i < courseList.CourseNumber; ++i) {
        //if the instructor contains keyword.
        if (courseList.Course[i].Instructor.find(key)!= std::string::npos){
            isFind = true;
            //judge if the instructor is already in target_instructor
            bool isInTargetInstructor = false;
            for (int j = 0; j < target_number; ++j) {
                if (courseList.Course[i].Instructor==target_instructor[j]){
                    isInTargetInstructor = true;
                }
            }
            //if not already in target_instructor, add it.
            if (!isInTargetInstructor) {
                target_instructor[target_number]=courseList.Course[i].Instructor;
                ++target_number;
            }
        }
    }
    //no instructor contains keyword.
    if (!isFind) {
        std::cout<<FACULTY_NOT_FOUND<<"\n"<<"\n";
        return;
    }
    //go through the course list to find all courses this instructor teaches.
    for (int j = 0; j < target_number; ++j) {
        std::cout<<"Instructor: "<<target_instructor[j]<<"\n"<<"Courses:";
        for (int i = 0; i < courseList.CourseNumber; ++i) {
            if (courseList.Course[i].Instructor==target_instructor[j])
                std::cout<<" "<<courseList.Course[i].CourseCode;
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void StopResponse(const Message& message,const GroupList& groupList){
    //find index of the group in the group list.
    int index = 0;
    while (message.group!=groupList.Groups[index].GroupName&&index<groupList.GroupNumber)
        ++index;
    //judge whether the admin is in the group
    int index_admin = 0;
    while (message.user!=groupList.Groups[index].AdminName[index_admin]&&index_admin<groupList.Groups[index].AdminNumber)
        ++index_admin;
    if (index_admin<groupList.Groups[index].AdminNumber){
        std::cout<<EXIT_PROMPT<<"\n"<<"\n";
        exit(0);
    }
    else {
        std::cout<<STOP_BOT_FAIL<<"\n"<<"\n";
    }
}

std::string KeyWordProcess(const std::string& content){
    std::string keyword;
    std::istringstream iString;
    iString.str(content);
    //load command
    std::string command;
    iString>>command;
    if (command==content)
        return "";
    else {
        iString>>keyword;
        if (keyword.empty()) return "";
        std::string tmp;
        while (std::getline(iString,tmp)){
            keyword+=tmp;
        }
        return keyword;
    }
}

void CommandLegalResponse(const Message& message,const CourseList &courseList,const GroupList &groupList){
    std::string content;
    std::istringstream iString;
    iString.str(message.content);
    std::getline(iString,content,' ');
    if (content=="#course"){
        if (KeyWordProcess(message.content).empty())
            std::cout<<MISSING_KEYWORD<<"\n"<<"\n";
        else PrintCoursesKeyword(courseList,KeyWordProcess(message.content));
    }
    else if (content=="#instructor"){
        if (KeyWordProcess(message.content).empty())
            std::cout<<MISSING_KEYWORD<<"\n"<<"\n";
        else PrintInstructorKeyword(courseList,KeyWordProcess(message.content));
    }
    else if (content=="#time"){
        std::cout<<message.time<<"\n"<<"\n";
    }
    else if (content=="#stop"){
        StopResponse(message,groupList);
    }
    else if (content=="#help") std::cout<<HELP_TEXT<<"\n"<<"\n";
}

void CommandIllegalResponse(const Message& message)
{
    RespChoice respond_choice;
    respond_choice = randomResponse();
    if (respond_choice == REPEAT)
    {
        std::cout << message.content << "\n"<< "\n";
    }
    else if (respond_choice == ADMIRE)
    {
        if (flipCoin())
        {
            std::cout << "Respect " << message.content << "\n"<< "\n";
        }
        else
        {
            std::cout << "I really admire " << message.content << "\n"<< "\n";
        }
    }
}

void CommandJudge(const Message& message,const CourseList &courseList,const GroupList& groupList){
    std::string s = message.content;
    std::stringstream iStream;
    iStream.str(s);
    std::string command;
    getline(iStream,command,' ');
    if(command == "#course" || command == "#instructor" || command == "#help" || command == "#time" || command == "#stop")
    {
        CommandLegalResponse(message,courseList,groupList);
    }
    else
    {
        CommandIllegalResponse(message);
    }
}

