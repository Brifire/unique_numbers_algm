// Lessons.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <deque>
#include <chrono>
#include <mutex>
//#define DEBUG

using namespace std;

int binarsearch(int a[],int size, int value)
{
    int mid=0;
    int l = 0;
    int r = size-1;
    while (l<=r)
    {
        mid = l + (r - l) / 2;
        int tmp = a[mid];
        cout <<"TMP: "<< tmp <<endl;
        if (a[mid] == value)
        {

            return mid;
        }
        if (value < a[mid]) r = mid-1;
        if (value > a[mid]) l = mid+1;

    }
    cout <<" NO NUMBER" << endl;
    return -1;
};

void buble_sort(int arr[],int size)
{
    int a = size;
#ifdef DEBUG
    cout << "Elemtnts " << a << endl;
#endif
    for (int i = 0; i < a; i++)
    {
        for (int x = 0; x < a-1; x++)
        {
            if (arr[x] > arr[x + 1])
            {
                swap(arr[x], arr[x + 1]);
            }
        }
    }
};
bool check_uniq(int arr_2[],int size)
{

    int a = size;
#ifdef DEBUG
    cout << "Elemtnts " << a << endl;
#endif
    for (int i = 0; i < a; i++)
    {
        for (int x = 0; x < a - 1; x++)
        {
            if (arr_2[x] == arr_2[x + 1])
            {
                return false;
            }
        }
    }
    return true;
}



void uniq_numbers(int arr_2[],int size )
{
    /*int x[10] = { 2,4,5,5,4,1,3,2,10,2 };
    * x[10]=9;
    * x[1]=5;
    *
    *
    int size = sizeof(x) / sizeof(x[0]);*/
    int l = 0;
    int r = 0;
    //int mid = size / 2;
    for (int i = 0; i < size; i++)
    {
        l = 0;
        r = (i+1);
#ifdef DEBUG

        cout << i << "-st Iteration" << endl;
#endif
        for (int y = i; y < size-1; y++)
        {
#ifdef DEBUG
            cout << "Arr_2[i]= " << arr_2[i] <<"\t"<< " Arr[y+1]= " << arr_2[y + 1]<<endl;
#endif
            if (arr_2[i] == arr_2[y + 1])
            {
                do
                {
                    arr_2[y + 1] = rand() % size;
                } while (arr_2[y + 1] == arr_2[i]);
#ifdef DEBUG
                cout << endl << "New number of arr_2[y+1]= " << arr_2[y + 1] << endl << endl;
#endif
                bool flag = true;
                while (flag)
                {
                    flag = false;

                    while (l != r)
                    {
                        if (arr_2[y + 1] == arr_2[l])
                        {
                            do
                            {
                                arr_2[y + 1] = rand() % size;
                            } while (arr_2[y + 1] == arr_2[l]);
                            arr_2[y + 1] = rand() % size;
                            flag = true;
                        }
                        ++l;
                    }
                    l = 0;
                    r = (i+1);
                    while (r != l)
                    {
                        if (arr_2[y + 1] == arr_2[r-1])
                        {
                            do
                            {
                                arr_2[y + 1] = rand() % size;
                            } while (arr_2[y + 1] == arr_2[l]);
                            flag = true;
                        }
                        --r;
                    }
                }
#ifdef DEBUG
                for (int i = 0; i < 10; i++)
                {
                    cout << "Index " << i << ": " << arr_2[i] << endl;
                }
#endif




            }


        }
    }


}



void make_fake_rand(int arr[],int size_3)
{
    for (int i = 0; i < size_3; i++)
    {
        arr[i] = (rand() % size_3);
    }
}
int main()
{

        int max_thr;
        int size_3;
        cout<< "One array created by default "<<endl;
        cout<< "Enter number of additional arrays(1-7) "<<endl;
        cin >> max_thr;
        if(max_thr>7||max_thr<1)
        {
            cout<< "Not valid number"<<endl;
            return 0;
        }
        cout<< "Enter the number of elements of arrays "<<endl;
        cin >> size_3;
        string s_1;
        vector<bool> bool_vector;
        vector<int*> ptr_int_vector;
        vector<thread> thread_vector;

        for (int i = 0; i < max_thr+1; i++)
        {
            bool res = false;
            bool_vector.push_back(res);
        }
        for (int i = 0; i < max_thr+1; i++)
        {
            int* arr_1 = new int[size_3];
            ptr_int_vector.push_back(arr_1);
        }
        for (int i = 0; i < max_thr; i++)
        {
            thread_vector.push_back(thread([i, &ptr_int_vector,&bool_vector,size_3]()
                {
                    make_fake_rand(ptr_int_vector[i], size_3);
                    uniq_numbers(ptr_int_vector[i], size_3);
                    buble_sort(ptr_int_vector[i], size_3);
                    bool_vector[i]= check_uniq(ptr_int_vector[i], size_3);
                }));
        }

        //this_thread::sleep_for(chrono::microseconds(10000));
        make_fake_rand(ptr_int_vector[max_thr], size_3);
        uniq_numbers(ptr_int_vector[max_thr], size_3);
        buble_sort(ptr_int_vector[max_thr], size_3);
        bool_vector[max_thr] = check_uniq(ptr_int_vector[max_thr], size_3);

        for (auto &thread : thread_vector)
        {
            thread.join();
        }
        thread_vector.clear();
#ifdef DEBUG
        for (int i = 0; i < max_thr+1; i++)
        {
            cout << "ARRAY " <<i << endl;
            auto arr=ptr_int_vector[i];
            for (int i = 0; i < size_3; i++)
            {
                cout << arr[i] << endl;
            }
            cout << endl << "====================ARRAY END============== " << i<< endl;
        }
#endif
        for (auto res : bool_vector)
        {
            cout <<boolalpha<< res << endl;
        }


    return 0;
}
