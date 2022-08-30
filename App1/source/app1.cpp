#include "app1.h"

void app1::Thread1Function()
{
    std::cout << "Thread1 started!" << std::endl;
    std::string s1; //строка для ввода

    while(1) //основной цикл, в котором происходит ввод и обработка строк и где далее стока помещается в общий буфер
    {
        using namespace std::chrono_literals;
        std::unique_lock<std::mutex> ul1(mutInput);
         //   if(!BoolCounter) IsOutputted=false; //если вывели 2 раза между вводами,
            cvInput.wait_for(ul1, 1ms, [this]{return IsOutputted;});
            CurrentCounter=BoolCounter;
         //   cvInput.wait(ul1);
            IsOutputted=false;
        //    BoolCounter=false;
        ul1.unlock();

        InputCalcFn::InputDigits(s1, 64, "Thread1: Input s1:"); //Ввод с проверкой символов
        char chSort[65]={}; //Массив символов, который будет отсортирован
        strcpy(chSort, s1.c_str());
        InputCalcFn::HeapSort<char>(chSort, strlen(chSort), true); //Сортировка двоичной кучей

        s1=std::string(chSort);
        InputCalcFn::ReplaceKB(s1); //Меняем четный цифры на "KB"

        mutBuf.lock();
            if(CurrentCounter!=BoolCounter) IsOutputted=false;

            strcpy(Buf, s1.c_str());
            BufStatus=true;
            cvBuf.notify_one();
        mutBuf.unlock();

   //     std::this_thread::sleep_for(1ms);
    }
}

void app1::Thread2Function()
{
    std::cout << "Thread2 started!" << std::endl;
    char s2[129]={}; //будем принимать сюда данные из общего буфера (строку KB)
    char SendBuf[4]={}; //буфер для отправки на сервер
    tcpclient Client1(INADDR_LOOPBACK, 12345); //инициализация клиента

    while(1)
    {
        std::unique_lock<std::mutex> ul(mutBuf);
            cvBuf.wait(ul, [this]{return BufStatus;}); //если BufStatus true, то на ожидание не встаем. Эквивалентно while (!stop_waiting()) {wait(lock);}
            //cvBuf.wait(ul); //Вот так делать нельзя. т.к. если Thread1Function успеет занять mutex первой, то Thread2Function не сработает должным образом
            strcpy(s2, Buf);
            strcpy(Buf, ""); //затираем общий буфер
            BufStatus=false;

            mutInput.lock();
                //"Поток должен вывести полученные данные на экран"
                std::cout << "Thread2: s2=" << s2 <<std::endl; //выводим на экран
                IsOutputted=true;
                BoolCounter=!BoolCounter;
                cvInput.notify_one();
            mutInput.unlock();

        ul.unlock();
        //"рассчитать  общую  сумму всех  элементов , которые являются численными значениями."
        InputCalcFn::CalcSumElements(s2, SendBuf); //находим сумму элементов си-строке s2 и помещаем её в SendBuf
        //"Полученную сумму передать в Программу номер2. После этого поток ожидает следующие данные."
        Client1.SendBuf(SendBuf, 4);
    }
}
