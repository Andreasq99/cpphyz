
#include <assert.h>
#include <array>
#include <iostream>
#include <vector>
#include <type_traits>

template <typename T> struct is_vector : std::is_same<T,std::vector<typename T::value_type>> {};

template<typename T, size_t MaxSize, typename Container = std::array<T,MaxSize>> class Cue { 
    // A class resembling a queue that wraps an array/vector so that its contents are stored in contiguous memory. Features a linear time bulkPop functionality, moving all items to the end, and there is no push option when the underlying container is an array.

    Container arr;

    public:

        Cue()
        {
            position = 0;
        }

        template <typename A = Container>
        Cue()
        {
            T a = T();
            if(std::is_array<A>::value){
                arr.fill(a);
            } else if (is_vector<A>::value){
                arr = std::vector<T> {};
                int j = 0;
                while(j < MaxSize){
                    arr.push_back(a);
                    j++;
                }
            } else {
                arr = Container();
            }
            position = 0;
        }

        Cue(std::array<T,MaxSize> array)
        {
            arr = array;
            position = 0;
        }


        T next() // Move one to the right in the queue
        {
            position = (position + 1) % size();
            return arr[position];
        }

        T front() // Return what's at the front of the queue
        {
            return arr[position];
        }

        T pop() // Move the front element to the last index in the array
        {
            assert(size() != 0 && "Cannot pop from empty container!");
            T current = arr[position];
            for(int i = position; i < size() - 1; i++){
                arr[i] = arr[i + 1];
            }
            arr[size() - 1] = current;
            return current;
        }


        template<size_t N, typename D>
        void bulkPop(Cue<idn,N,D> rml) // General purpose linear-time bulk popper function. Moves N elements in the container to the end.
        // ASSUMES rml IS IN THE SAME ORDER AS arr!! i.e. if we want to remove 3,4,5 from [6,4,2,8,1,3,5], then rml should be [4,3,5].
        {
            idn rsize = rml.size();
            idn msize = size();
            if(rsize == 0){return;}
            
            idn rid = rml.front();

            std::vector<idn> widths(rml.size() - 1,0);
            
            position = msize - 1;

            while(true){
                if(rid == next()){break;}
                if(position == msize - 1){return;}
            }

            int start = position;
            rid = rml.next();
            int wind = 0;
            widths[wind] = 1;
            
            while(rml.position != 0){
                if(rid == next()){
                    rid = rml.next();
                    wind++;
                } else {
                    widths[wind]++;
                }
            }

            position = start;
            int relind = 0;
            for(int i = 0; i < rsize-1; i++){
                for(int j = 0; j < widths[i]; j++){
                    arr[start + j] = arr[start + j + i + 1];
                }
            }

            rml.position = rsize - 1;
            for(int i = msize - 1 - rsize; i < msize; i++){
                arr[i] = rml.next();
            }

            position = 0;
        }

        template <typename A = Container> 
        void push(T entry)
        {
            assert(is_vector<A>::value && "Push is not implemented for this cue's container!");
            arr.push_back(entry);
        }

        template <typename A = Container>
        size_t size()
        {
            if(is_vector<A>::value){
                return static_cast<size_t>(arr.size());
            } else {
                return MaxSize;
            }
        }

        T operator[](int n){
            assert(n < size() && "Index put of bounds!");
            return arr[n];
        }

        int position;
};

template<typename T,size_t size,typename Container> void logCue(Cue<T,size,Container> q){
    for(int i=0;i<q.size();i++){
        std::cout << "Entry in position " << i << ": " << q[i] << "\n";
    }
    std::cout << "\n";
}

template<typename T> using VecCue = Cue<T,(size_t)0,std::vector<T>>;
