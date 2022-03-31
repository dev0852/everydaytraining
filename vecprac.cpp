#include <bits/stdc++.h>
using namespace std;
//read the input and store it in a vector
vector<int> read_input(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    return v;
}
//sort the vector
void sort_vector(vector<int> &v){
    sort(v.begin(), v.end());
}
//print the vector
void print_vector(vector<int> &v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}
int main(){
    vector<int> v = read_input();
    sort_vector(v);
    print_vector(v);
    return 0;
}