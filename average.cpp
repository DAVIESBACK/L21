#include<iostream>
#include<iomanip>
#include<vector>
#include<cstdlib>
using namespace std;

int main(int argc, char* argv[]){
    if(argc<2){
        cout<<"Please input numbers to find average.";
        return 1;
    }
    vector<int> numbers;
    double sum=0;
    for(int i=1;i<argc;++i){
        double num=atof(argv[i]);
        numbers.push_back(num);
        sum+=num;
    }
    int average = sum / numbers.size();
    cout<<"---------------------------------"<<endl;
    cout<<"Average of "<<numbers.size()<<" numbers = "
        <<fixed<<setprecision(3)<<average<<endl;
    cout<<"---------------------------------"<<endl;
    return 0;
}
