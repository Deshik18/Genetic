#include <bits/stdc++.h>
#include <time.h>

using namespace std;

int no_invest;
int max_invest;
double exp_ret[10];
double volat[10];
int pop_size=100;
double mut=0.01;
int gen=1;

int myrandom(int j)
{
    return rand() % j;
}

string genoff(string par1,string par2){
    string child="";
    int par_idx=rand()%no_invest;
    string s1=par1.substr(0,par_idx+1);
    string s2=par2.substr(par_idx+1,no_invest-par_idx-1);
    child = child + s1;
    child = child + s2;

    if(rand()%1000<10){
        int sel=rand()%no_invest;
        if(child[sel]=='0'){
            child[sel]='1';
        }
        else{
            child[sel]='0';
        }
    }

    return child;
}

int tourn(){
    int min=101;
    for(int i=0;i<5;i++){
        int mr=rand()%pop_size;
        if(mr<min){
            min=mr;
        }
    }
    return min;
}

void normalize(){
    double sum=0,vol=0;
    for(int i=0;i<no_invest;i++){
        sum+=exp_ret[i];
        vol+=volat[i];
    }
    for(int i=0;i<no_invest;i++){
        exp_ret[i]/=sum;
        volat[i]/=vol;
    }

}

int fitness(string ind){
    int x=0;
    double sc=0;
    for(int i=0;i<no_invest;i++){
        if(ind[i]=='1'){
            x++;
            sc+=(exp_ret[i]/volat[i]);   //weighted objective.....
        }
    }
    if(x!=max_invest){
        return 0;
    }
    else{
        return sc;
    }
}

vector<string> sorting(vector<string> new_pop,ofstream & of){
    vector<string> sorted;
    map<string, double> m;
    for(int i=0;i<new_pop.size();i++){
        m[new_pop[i]]=fitness(new_pop[i]);
        int flag=0;
        for(int j=sorted.size()-1;j>=0;j--){
            if(m[sorted[j]]>=m[new_pop[i]]){
                sorted.insert(sorted.begin()+j+1,new_pop[i]);
                flag=1;
                break;
            }
        }
        if(flag==0){
            sorted.insert(sorted.begin(),new_pop[i]);
        }
    }
    vector<string> best_pop;
    for(int i=0;i<pop_size;i++){
        best_pop.push_back(sorted[i]); 
        //of << sorted[i] << "  " << m[sorted[i]] << endl;
    }
    
    of << "Best Individual of Current Gen is :" << sorted[0] << endl;
    
    of << "\n\n***\n\n";
    return best_pop;
}

vector<string> init_pop(){
    vector<string> population;
    for(int i=0;i<pop_size;i++){
        string s="";
        vector<int> arr;
        for(int i=0;i<no_invest;i++){
            arr.push_back(i);
            s+='0';
        }
        for(int i=0;i<no_invest;i++){
            int j=myrandom(no_invest);
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }

        for(int i=0;i<max_invest;i++){
            s[arr[i]]='1';
        }
        population.push_back(s);
    }
    return population;
}


int main(){
    srand(time(0));
    int n;
    cout << "Number of investments:";
    cin >> no_invest;
    cout << "Enter the expected returns in percentages:\n";
    for(int i=0;i<no_invest;i++){
        cin >> exp_ret[i];
    }
    cout << "Enter the volatility in percentages:\n";
    for(int i=0;i<no_invest;i++){
        cin >> volat[i];
    }
    cout << "Enter the number of investments you want to do:";
    cin >> max_invest;

    ofstream f;
    f.open("ass1(p-r).txt");
    f<<"No of investments n:" << no_invest << endl;
    f << "Expected Returns : " ;
    for(int i=0;i<no_invest;i++){
        f << exp_ret[i] << " ";
    }
    f << endl;
    f << "Volatility : ";
    for(int i=0;i<no_invest;i++){
        f << volat[i] << " ";
    }
    f << endl;
    f << "Objective function used is P/R" << endl << endl;
    vector<string> population=init_pop();

    while(gen<=50){
        f << "Current Generation .." << gen << endl;
        vector<string> new_gen;
        for(int i=0;i<10000;i++){
            string m1=population[tourn()];
            string m2=population[tourn()];
            new_gen.push_back(genoff(m1,m2));
        }
        population = new_gen;
        population=sorting(population,f);
        gen++;
    }

    cout << "Final Sol is " << population[0];

    f << "Expected Return :";
    int b=0;
    for(int i=0;i<no_invest;i++){
        if(population[0][i]=='1'){
            b+=exp_ret[i];
        }
    }
    f << b << endl;
    b=0;
    f << "Volatility :";
    for(int i=0;i<no_invest;i++){
        if(population[0][i]=='1'){
            b+=volat[i];
        }
    }
    f << b << endl;

}