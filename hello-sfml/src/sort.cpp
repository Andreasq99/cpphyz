
#include <stdlib.h>
#include <vector>

using std::vector;


int partition(vector<int>& tab, int low, int high){
    int piv = tab[high];

    int i = low-1;
    for(int j = low; j < high; j++){
        if(tab[j]>piv){
            i++;
            std::swap(tab[i],tab[j]);
        }
    }

    std::swap(tab[i+1],tab[high]);
    return i+1;
}

void quicksort(vector<int>& tab, int low, int high){
    if(low<high){
        int pi = partition(tab,low,high);
        quicksort(tab,low,pi-1);
        quicksort(tab,pi+1,high);
    }
}

vector<int> sort(vector<int>& tab){
    int low = 0;
    int high = tab.size()-1;
    quicksort(tab,low,high);
    return tab;
}
