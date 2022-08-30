#ifndef APP1_H_INCLUDED
#define APP1_H_INCLUDED
/*app1.h*/
#include <iostream>

#include <string> //для обычных строк

#include <thread> //для потоков
#include <mutex> //для мьютекса
#include <condition_variable> //для условной переменной

#include <chrono> //для mc

#include <cstring> //для работы с буфером

#include "tcpclient.h"
#include "InputCalcFn.h"

class app1 //класс, реализующий возможности 1ого приложения
{
private:
    bool BufStatus=false; //0 - пустой; 1 - содержит строку. Нужен для корректной работы cvBuf,т.к. позволяет избежать пропущенных уведомлений.
    std::mutex mutBuf; //mutex для Buf
    std::condition_variable cvBuf; //для Buf
    char Buf[129]={}; //общий буфер со строкой

    std::mutex mutInput; //мьютекс, для того, чтобы вводить новое значение по возможности не сразу, а после того, как 2й поток выведет свое (будем ожидать вывода 2го потока в течение небольшого промежутка времени)
    std::condition_variable cvInput;
    bool IsOutputted=true; //true - 2й уже вывел результат на экран. false- 2й поток ещё не вывел результат на экран.
    bool BoolCounter=false; //меняет значение на противоположное каждый раз, когда идет вывод 2м потоком. Поможет обранужить вывод в то время, когда шел ввод с клавиатуры.
    bool CurrentCounter=true; //Хранит текущее значение BoolCounter

public:
    app1()=default;
    void Thread1Function(); //функция, выполняемая в 1м потоке
    void Thread2Function(); //функция, выполняемая во 2м потоке
};

#endif // APP1_H_INCLUDED
