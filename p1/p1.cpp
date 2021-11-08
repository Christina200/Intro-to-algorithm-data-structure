#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

int MAX_INPUT = 10000000;

bool isInputQualified(int input1,int input2);
bool isArmstrongNumber(int x);
bool isCycloneJet(int input);
bool isBlackPremiumCarNumber(int x);
bool isAuspiciousNumber(int x);
int pow_int(int b,int n);
void Test();

void print_prompt() {
    std::cout << "Please enter the integer and the test number: ";
}

int main() {
    //TODO: write your code here
    Test();
    return 0;
}

//test code
void Test(){
    print_prompt();
    int input1,input2,output;
    std::cin>>input1>>input2;
    if (!isInputQualified(input1,input2))
        Test();
    else {
        switch (input2) {
            case 1:
                output = isArmstrongNumber(input1);
                break;
            case 2:
                output = isCycloneJet(input1);
                break;
            case 3:
                output = isBlackPremiumCarNumber(input1);
                break;
            default:
                output = isAuspiciousNumber(input1);
        }
        printf("%d",output);
    }

}

//test inputs qualified
bool isInputQualified(int input1,int input2){
    bool is1Qualified=(input1>0)&&(input1<=MAX_INPUT);
    bool is2Qualified=input2>=1&&input2<=4;
    return is1Qualified&&is2Qualified;
}

//power of integers
int pow_int(int b,int n){
    int res=1;
    for (int i = 0; i < n; ++i) {
        res*=b;
    }
    return res;
}

//1. test Armstrong number
bool isArmstrongNumber(int x){
    for (int i=1;i<x;++i){
        if (pow_int(i,x)%x!=i)
            return false;
    }
    return true;
}

//2. test Cyclone Jet
bool isCycloneJet(int input){
    int x=input;
    int inverse=0;
    while (x%10){
        inverse=inverse*10+x%10;
        x/=10;
    }
    return inverse==input;
}

//3. test Black Premium Car Number
bool isBlackPremiumCarNumber(int x){
    double square=sqrt(24*x+1.0);
    if (square!=floor(square))
        return false;
    double transition=(square+1)/6;
    return transition == floor(transition);
}

//4. test Auspicious number
bool isAuspiciousNumber(int x){
    int DivisorSum=0;//must initialize!!
    for (int i = 1; i < x; ++i) {
        if (!x%i)
            DivisorSum+=i;
    }
    return DivisorSum>x;
}