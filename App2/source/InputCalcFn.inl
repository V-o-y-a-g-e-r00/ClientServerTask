#ifndef INPUTCALCFN_INL_INCLUDED
#define INPUTCALCFN_INL_INCLUDED
/*InputCalcFn.inl Реализация шаблонных функций*/

using namespace InputCalcFn;

template<typename T>
void InputCalcFn::Heapify(T *Arr, int Length, int i, bool SortOrder) //Восстанавливает свойства кучи, начиная с корня i. Предполагается, что левое и правое деревья удовлетворяют куче. SortOrder - направление сортировки. по умолчанию - по возрастанию(т.е. в корне кучи стоит наибольший элемент).
{
    int LargestLowest=i;
    if(!SortOrder) //по умолчанию сортировка по возрастанию
    {
        if(2*i+1<Length && Arr[2*i+1]>Arr[LargestLowest]) LargestLowest=2*i+1;
        if(2*i+2<Length && Arr[2*i+2]>Arr[LargestLowest]) LargestLowest=2*i+2;
    }
    else
    {
        if(2*i+1<Length && Arr[2*i+1]<Arr[LargestLowest]) LargestLowest=2*i+1;
        if(2*i+2<Length && Arr[2*i+2]<Arr[LargestLowest]) LargestLowest=2*i+2;
    }
    if(LargestLowest!=i)
    {
        T temp=Arr[LargestLowest];
        Arr[LargestLowest]=Arr[i];
        Arr[i]=temp;
        Heapify<T>(Arr, Length, LargestLowest, SortOrder);
    }
}
template<typename T>
void InputCalcFn::BuildHeap(T *Arr, int Length, bool SortOrder) //строит кучу из неупорядоченного массива SortOrder - направление сортировки. по умолчанию - по возрастанию.(т.е. в корне кучи стоит наибольший элемент).
{
    for(int i=Length/2; i>=0; i--)
    {
        Heapify<T>(Arr, Length, i, SortOrder);
    }
}

template<typename T>
void InputCalcFn::HeapSort(T *Arr, int Length, bool SortOrder) //сортировка кучей. По умолчанию - по возрастанию.
{
    BuildHeap<T>(Arr, Length, SortOrder);
    for(int i=0; i<Length-1; i++)
    {
        T temp=Arr[0];
        Arr[0]=Arr[Length-1-i];
        Arr[Length-1-i]=temp;
        Heapify<T>(Arr, Length-1-i, 0, SortOrder);
    }
}
#endif // INPUTCALCFN_INL_INCLUDED
