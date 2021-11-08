#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "bot.h"
#include "constants.h"
#include "rand.h"

int main(int argc, char * argv[]){
    //check whether any argument is missed.
    if (argc!=4) {
        std::cout<< MISSING_ARGUMENT_MESSAGE<<"\n"<<"\n";
        return 0;
    }
    else {
        //check whether the random seed is a number/within range of int (2147483647)
        std::istringstream iSeed;
        std::string seed = argv[3];
        iSeed.str(seed);
        long long int random_seed;
        iSeed >> random_seed;
        if (random_seed-2147483647>0)
            std::cout<<INVALID_ARGUMENT_MESSAGE<<"\n"<<"\n";
        else if (random_seed ==0){
            if (seed.find_first_of('0')!=0) std::cout<<INVALID_ARGUMENT_MESSAGE<<"\n"<<"\n";
        }
        else {
            //check is the file can be opened.
            std::ifstream courseFile (argv[1]);
            if (!courseFile.is_open()) {
                std::cout<<CANNOT_OPEN_FILE_PREFIX<<argv[1];
                return 0;
            }
            std::ifstream groupFile (argv[2]);
            if (!groupFile.is_open()){
                std::cout<<CANNOT_OPEN_FILE_PREFIX<<argv[2];
                return 0;
            }
            else {
                Message message;
                std::string line;
                //load course list from file.
                CourseList courseList{};
                ReadCourse(argv[1],&courseList);
                //load group list from file
                GroupList groupList{};
                ReadGroup(argv[2],&groupList);
                //initialize random seed
                int random_seed_int=int(random_seed);
                initializeWithSeed(random_seed_int);
                //read command line and process message.
                while (std::getline(std::cin,line)){
                    ParseMessage(&message,line);
                    //check whether the group in message is in group list.
                    int index = 0;
                    while (message.group!=groupList.Groups[index].GroupName&&index<groupList.GroupNumber) ++index;
                    if (index<groupList.GroupNumber)
                        CommandJudge(message,courseList,groupList);
                }
                //delete course and group memory.
                delete [] courseList.Course;
                delete [] groupList.Groups;
                return 0;
            }
        }
    }
}