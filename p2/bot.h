//
// Created by WeiXiwen on 2021/6/14.
//

#ifndef P2_BOT_H
#define P2_BOT_H
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

//IMPORT COURSE INFORMATION
struct CourseInfo{
    //OVERVIEW: store course information for each course (course code, course name, instructor)
    std::string CourseCode;
    std::string CourseName;
    std::string Instructor;
};

struct CourseList{
    //OVERVIEW: for a course list, store number of courses and course information is stored in array Course.
    int CourseNumber;
    CourseInfo * Course;
};

void ReadCourse(const std::string& course_list,CourseList * courseList);
//REQUIRES: the file course_list isn't empty and can be accessed
//EFFECTS: read the course code, course name and instructor into a CourseList.

//IMPORT GROUP LIST

struct GroupInfo{
    //OVERVIEW: store information for each group: group name, number of administers.
    // names of admins are stored in array AdminName.
    std::string GroupName;
    int AdminNumber;
    std::string * AdminName;
};

struct GroupList{
    int GroupNumber;
    GroupInfo * Groups;
    std::string GroupAddress;
};

void ReadGroup(const std::string& group_list,GroupList * groupList);
//REQUIRES: group list file is accessible.
// EFFECTS: read the group list file and return a list of group info.
void ReadAdmin(const std::string& group_address,GroupInfo * groupInfo);
//REQUIRES: single group file is accessible.
//EFFECTS: read the single group information and return the list of admin info.


//PARSE INPUT MESSAGE
struct Message{
    //OVERVIEW: parse message and store information (time, group, user and content) in struct Message.
    std::string time;
    std::string group;
    std::string user;
    std::string content;
};
void ParseMessage(Message * message,const std::string& line);
//EFFECTS: read message from cin and store information in struct Message.

//RESPONSE

//UNITS FUNCTION
std::string KeyWordProcess(const std::string& content);
//REQUIRES: string content is a legal command beginning with either "#course" or "#group".
//EFFECTS: check whether the content has a keyword. If it has, return the keyword;
// otherwise return empty string.

//COURSE command
//TODO: print courses containing keywords
void PrintCoursesKeyword(const CourseList & courseList,const std::string& key);
//REQUIRES: courseList not empty.
//EFFECTS: search the courses whose course code or course name contain the keyword
// and print the course information.

//INSTRUCTOR command
//TODO: print instructors containing keywords
void PrintInstructorKeyword(const CourseList & courseList,const std::string& key);
//REQUIRES: courseList not empty.
//EFFECTS: search the courses whose instructor the keyword
// and print the course that the instructors teach.

//STOP command
void StopResponse(const Message& message, const GroupList& groupList);
//REQUIRES: the group in message is in the group list.
//EFFECTS: check whether the "#stop" command is authorized. If so, print EXIT_MESSAGE and exit the program.
// Otherwise print EXIT_FAIL.

void CommandLegalResponse(const Message & message,const CourseList &courseList,const GroupList &groupList);
//REQUIRES: the command of content is legal.
//EFFECTS: identify the command and call corresponding response function.

void CommandIllegalResponse(const Message& message);
//REQUIRES: the command of content is illegal.
//EFFECTS: print messages, repeat or ignore randomly.

void CommandJudge(const Message& message,const CourseList &courseList,const GroupList& groupList);
//REQUIRES: group in message is in the group list.
//EFFECTS: check whether the command is legal. If legal, call CommandLegalResponse.
// Otherwise call CommandIllegalResponse.
#endif //P2_BOT_H
