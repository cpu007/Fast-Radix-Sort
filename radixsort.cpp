/**
 * Created by Kenneth Chiguichon.
 * Full details can be found in the readme.txt file, but feel free to share, use, or modify any or all 
 * code found in this file.
 */
#include <iostream>
#include <random>
#include <time.h>
#include <string.h>

using namespace std;

bool arrayIsSorted(int*,int);
int* randomIntArray(int,int,int,mt19937&);
void printArray(int*,int);
void radixSort(int*, int);

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC (clock_t)1000
#endif //CLOCKS_PER_SEC

int main()
{
    int N, minNum, maxNum;
    cout << "Enter a size: ";
    cin >> N;
    cout << "\nEnter a minimum: ";
    cin >> minNum;
    cout << "\nEnter a maximum: ";
    cin >> maxNum;
	mt19937 seed(time(0));
    int *a = randomIntArray(N,minNum,maxNum,seed);
    clock_t startTime, endTime;
    startTime = clock();
    radixSort(a,N);
    endTime = clock();
    cout <<"Radix Sort took " << (((float) endTime)-((float)startTime)) / CLOCKS_PER_SEC << " second(s)" << endl;
	cout << "a[0] = " << a[0] << "\na[(N-1)/2] = " << a[(N-1)>>1] <<"\na[N-1] = " << a[N-1] << endl;
	cout << boolalpha;
    cout << "No elements out of place for array \"a\": " << arrayIsSorted(a,N) << endl;
    delete[] a;
    return 0;
}

bool arrayIsSorted(int* a,int N){
    for (int i = 0; i < N-1; i++) if (a[i] > a[i + 1]) return false;
    return true;
}


int * randomIntArray(int n, int minNum, int maxNum, mt19937 &seed){
    int* a = new int[n];
	uniform_int_distribution<int> genRand(minNum,maxNum);
    for (int i = 0; i<n; i++) a[i] = genRand(seed);
    return a;
}

void printArray(int* a, int N){
    cout << "[";
    int i=0;
    while(i < N-1){
        cout << a[i] << ", ";
        i++;
    }
    if(i < N) cout << a[i];
    cout << "]";
}

void radixSort(int* a, int N){
    const int INT_BIT_SIZE = sizeof(int)*8, RADIX = 0x100, MASK = RADIX-1, MASK_BIT_LENGTH = 8;
    int *result = new int[N](), *buckets = new int[RADIX](), *startIndex = new int[RADIX]();
    int flag = 0;
    bool hasNeg = false;
    while (flag < INT_BIT_SIZE){
        for (int i = 0; i < N; i++) {
            const int key = ((((a[i] & (MASK << flag)) >> flag)<0) && (hasNeg = true))? //assigns hasNeg to true if and only if first condition is false
                            ((a[i] & (MASK << flag)) >> flag)+MASK : (a[i] & (MASK << flag)) >> flag;
            ++buckets[key];
        }
        startIndex[0] = 0;
        for (int j = 1; j < RADIX; j++) startIndex[j] = startIndex[j - 1] + buckets[j - 1];
        for (int i = N-1; i >= 0; i--){
            const int key = (((a[i] & (MASK << flag)) >> flag)>=0)?
                            (a[i] & (MASK << flag)) >> flag : ((a[i] & (MASK << flag)) >> flag)+MASK;
            result[startIndex[key] + --buckets[key]] = a[i];
        }
        memcpy(a,result,N*sizeof(int));
        flag += MASK_BIT_LENGTH;
    }
    if(hasNeg){
        int indexOfNeg = 0;
        for (int i = 0; i < N; i++) {
            if(a[i] < 0) {
                indexOfNeg = i;
                break;
            }
        }
        memcpy(a,result+indexOfNeg,(N-indexOfNeg)*sizeof(int));
        memcpy(a+(N-indexOfNeg),result,indexOfNeg*sizeof(int));
    }
    delete[] result;
    delete[] buckets;
    delete[] startIndex;
}
