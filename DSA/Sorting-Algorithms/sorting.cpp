#include<iostream>
#include<vector>
#include<random>



void bubbleSort(std::vector<int>& v){
    int n = v.size();

    for(int i = 0; i < n-1; i++){
        bool swapped = false;

        for(int j = 0; j < n-1-i; j++){
            if(v[j]>v[j+1]){
                std::swap(v[j], v[j+1]);
                swapped = true;
            }
	}
	if (!swapped) break;
    }
}

void insertionSort(std::vector<int>& v){
    int n = v.size();

    for(int i = 1; i < n; i++){
        int key = v[i];
        int j = i-1;

        while(j>=0 && v[j]>key){
            v[j+1] = v[j];
            j--;
        }

        v[j+1] = key;
    }
}

void selectionSort(std::vector<int>& v){
    int n = v.size();

    for(int i = 0; i < n-1; i++){
        int minIndx = i;

        for(int j=i+1; j<n;j++){
            if(v[j]<v[minIndx]){
                minIndx = j;
            }
        }
	    if(minIndx!=i){
	        std::swap(v[i],v[minIndx]);
	    }
    }
}

void mergeSort(std::vector<int>& v, int l, int r){
    if(l>=r) return;

    int m = l + (r-l)/2;
    mergeSort(v,l,m);
    mergeSort(v,m+1,r);
    merge(v,l,m,r);
}

void merge(std::vector<int>& v, int l, int m, int r){
    std::vector<int> a,b;
    for(int i = l; i <= m; i++){a.push_back(v[i]);}
    for(int i = m+1; i <= r; i++){b.push_back(v[i]);}

    int i=0,j=0;
    while(i<int(a.size()) && j<int(b.size())){
        if(a[i]<=b[j]){
            v[l++] = a[i++];
        }else{
            v[l++] = b[j++];
        } 
    }
    while(i<int(a.size())){v[l++]=a[i++];}
    while(j<int(b.size())){v[l++]=b[j++];}
}

int partition(std::vector<int>& v, int l, int r){
    int i = l-1;
    int pivot = v[r];
    for(int j = l; j<=r;j++){
        if(v[j]<=pivot){i++;std::swap(v[j],v[i]);}
        else if(v[j]>pivot){continue;}
    }
    return i;
}

int randomPartition(std::vector<int>& v, int l, int r, std::mt19937& rng){
    std::uniform_int_distribution<int> dist(l,r);
    int randIdx = dist(rng);
    std::swap(v[r],v[randIdx]);
    int i = l-1;
    int pivot = v[r];
    for(int k = l; k<=r; k++){
        if(v[k]<=pivot){i++;std::swap(v[i],v[k]);
        }else{continue;}
    }
    return i;
}

void quickSort(std::vector<int>& v, int l, int r, std::mt19937& rng)
{
    if(l>=r){return;}

    int indx = randomPartition(v,l,r,rng);
    quickSort(v,l,indx-1,rng);
    quickSort(v,indx+1,r,rng);
}

int main(){
    std::mt19937 rng(std::random_device{}());
    return 0;

}
