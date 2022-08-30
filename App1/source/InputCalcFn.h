#ifndef INPUTCALCFN_H_INCLUDED
#define INPUTCALCFN_H_INCLUDED

#include <iostream>
#include <cmath> //для pow в классе Digits64
#include <string>
#include <cstring> //для strlen в MultiplicityCheck

namespace InputCalcFn
{
void InputDigits(std::string &s1, unsigned int length,std::string InputMsg=std::string(""), std::string str=std::string("1234567890")); //s1 - строка, куда будет записан ввод, если он корректен. lenght - максимально допустимая длина строки( для строки "123" это соответсвтует
                                                                                                                                       //3) str - допустимые символы InputMsg - сообщение при вводе (если пустое, то просто ввод без пустой строки)
/*  Шаблонные функции для сортировки кучей (по возрастанию и убыванию)*/
template<typename T>
void Heapify(T *Arr, int Length, int i, bool SortOrder=false); //Восстанавливает свойства кучи, начиная с корня i. Предполагается, что левое и правое деревья удовлетворяют куче. SortOrder - направление сортировки. по умолчанию - по возрастанию(т.е. в корне кучи стоит наибольший элемент).

template<typename T>
void BuildHeap(T *Arr, int Length, bool SortOrder=false); //строит кучу из неупорядоченного массива SortOrder - направление сортировки. по умолчанию - по возрастанию.(т.е. в корне кучи стоит наибольший элемент).

template<typename T>
void HeapSort(T *Arr, int Length, bool SortOrder=false); //сортировка кучей. По умолчанию - по возрастанию.

/*  Для замены цифр на символы "KB"*/
void ReplaceKB(std::string &s1);

/*Для потока 2 приложения App1*/
void CalcSumElements(char *KBstr, char *SumElements); //вычисление суммы всех элементов

/*Для App2*/
void MultiplicityCheck(char *ch);

}

#include "InputCalcFn.inl" //Подключаем реализацию наших шаблонных функций
#endif // INPUTCALCFN_H_INCLUDED
