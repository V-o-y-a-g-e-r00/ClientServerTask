/*InputCalcFn.cpp*/
#include "InputCalcFn.h"
using namespace InputCalcFn;
void InputCalcFn::InputDigits(std::string &s1, unsigned int length,std::string InputMsg, std::string str) //s1 - строка, куда будет записан ввод, если он корректен. lenght - максимально допустимая длина строки( для строки "123" это соответсвтует
                                                                                                                                       //3) str - допустимые символы InputMsg - сообщение при вводе (если пустое, то просто ввод без пустой строки)
{
    while(1)
    {
        if(InputMsg!="")
        {
            std::cout<<InputMsg<<std::endl;
        }
        getline(std::cin, s1);
        if(s1.length()<=length) //<=64
        {
            if(s1.find_first_not_of(str)==std::string::npos && s1!="")
            {
                break;
            }
            else
            {
                std::cout<< "Extraneous symbols!" << std::endl;
            }
        }
        else //тут уже об ошибке можно выводить
        {
            std::cout<< "string length>" << length<<std::endl;
        }
    }
}
void InputCalcFn::ReplaceKB(std::string &s1)
{
    std::string::size_type pos=s1.find_first_of("02468");
    while(pos!=std::string::npos)
    {
        s1.replace(pos, 1, "KB");
        pos=s1.find_first_of("02468", pos);
    }
}

/*Для 2го потока*/
void InputCalcFn::CalcSumElements(char *KBstr, char *SumElements) //в KBstr и SumElements можно подставлять одну и ту же строку
{
    int Sum=0;
    for(unsigned int i=0; i<strlen(KBstr);i++)
    {
        if(KBstr[i]>='0' && KBstr[i]<='9')
        {
            Sum+=KBstr[i]-'0';
        }
    }
    sprintf(SumElements, "%d", Sum);
}


void InputCalcFn::MultiplicityCheck(char *ch)
{
    int chValue;
    sscanf(ch, "%d", &chValue);
    if(strlen(ch)>2 && chValue%32==0)
    {
        std::cout<<"Data has been received successfully!"<<std::endl;
        std::cout<<"Data:"<<ch<<std::endl;
    }
    else
    {
        std::cout<<"Error has occured: the number does not satisfy the condition (strlen(ch)>2 && chValue%32==0)"<<std::endl;
        std::cout<<"(Wrong data:"<<ch<<")"<<std::endl;
    }
}
