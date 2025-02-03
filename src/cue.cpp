
#include <assert.h>
#include <array>
#include <iostream>

template<typename T, size_t MaxSize> class Cue { 

// A class resembling a queue that wraps an array so that its contents are stored in contiguous memory. The pop functionality is different from a usual queue, and there is no push option since the underlying container is an array.

    public:

        Cue(){
            arr.fill(T());
            position = 0;
        }

        Cue(std::array<T, MaxSize> array){
            arr = array;
            position = 0;
        }

        T next() // Move one to the right in the queue
        {
            position = (position+1) % MaxSize;
            return arr[static_cast<int>(position)];
        }

        T front() // Return what's at the front of the queue
        {
            return arr[static_cast<int>(position)];
        }

        T pop() // Move the front element to the last index in the array
        {
            T current = arr[position];
            for(int i = position; i < MaxSize - 1; i++){
                arr[i] = arr[i + 1];
            }
            arr[MaxSize - 1] = current;
            return current;
        }

        T pop(int index){
            int pos = position;
            position = index;
            T current = pop();
            position = pos;
            return current;
        }


        size_t size()
        {
            return MaxSize;
        }

        T operator[](int n){
            assert(n < MaxSize && "Index put of bounds!");
            return arr[n];
        }

        int position;

    private:
        std::array<T,MaxSize> arr;
};

template<typename T,size_t size> void logCue(Cue<T,size> q){
    // q.position = 0;
    for(int i=0;i<size;i++){
        std::cout << "Entry in position " << i << ": " << q[i] << "\n";
    }
    std::cout << "\n";
}

// int main (){
//     std::array<int,10> arr{0,1,2,3,4,5,6,7,8,9};
//     Cue<int,10> q(arr);
//     // logCue(q);
//     q.next();
//     q.next();
//     q.pop();
//     logCue(q);
//     q.pop(6);
//     logCue(q);
//     return 0;
// }