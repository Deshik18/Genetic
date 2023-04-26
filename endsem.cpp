#include <bits/stdc++.h>
#include <time.h>


using namespace std;

char genes[10]={'0','1','2','3','4','5','6','7','8','9'}

int popsize=50;
int chromlen=11;

int dist[10][10]={{0,2,1,3,2,4,3,5,4,6},{2,0,2,4,3,5,4,6,5,7},{1,2,0,2,1,3,2,4,3,5},{3,4,2,0,1,1,2,4,3,5},{2,3,1,1,0,2,1,3,2,4},{4,5,3,1,2,0,3,5,4,6},{3,4,2,2,1,3,0,2,1,3},{5,6,4,4,3,5,2,0,3,1},{4,5,3,3,2,4,1,3,0,2},{6,7,5,5,4,6,3,1,2,0}};

vector<string> initializepop(){
    vector<string> init;
    for(int i=0;i<popsize;i++){
        vector<int> arr;
        for(int i=0;i<10;i++){
            arr.push_back(i);
        }
        for(int i=0;i<10;i++){
            int k= rand()%10;
            int temp=arr[k];
            arr[k]=arr[i];
            arr[i]=temp;
        }
        string str="";
        for(int i=0;i<10;i++){
            str+=genes[arr[i]];
        }
        str+=arr[genes[0]];
        init.push_back(str);
    }
    return str;
}

int fitness(string a){
    int f=0;
    for(int i=0;i<10;i++){
        f-=dist[stoi(a[i])][stoi(a[i+1])];
    }
    return f;
}

pair<string,string> offspring(string par1,string par2){
    string offspring1="",offspring2="";
    offspring1+=par1[0];
    offspring2+=par2[0];
    for(int i=1;i<10;i++){
        if(par1[i]==par2[0]){
            offspring2+=par1[0];

        }
        else{
            offspring2+=par1[i];
        }
        if(par2[i]==par1[0]){
            offspring1+=par2[0];

        }
        else{
            offspring1+=par2[i];
        }
    }
    offspring1+=par1[0];
    offspring2+=par2[0];
    return {offspring1,offspring2};

}

string mutate(string child){
    int k1=rand()%9 + 1;
    int k2=rand()%9 + 1;
    string str="";
    for(int i=0;i<11;i++){
        if(i==k1){
            str+=child[k2];
        }
        else if(i==k2){
            str+=child[k1];
        }
        else{
            str+=child[i];
        }
    }
    return child;
}

vector<string> sorting(vector<string> new_pop){
    vector<string> sorted;
    map<string, int> m;
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
    cout << "Best pop of current gen is..."<< endl;
    for(int i=0;i<sorted[0].size();i++){
        if(i!=sorted.size()-1){
            cout << sorted[0][i] << " -> ";
        }
        else{
            cout << sorted[0][i];
        }
    }
    cout << endl << "Its fitness is " << fitness(sorted[0]);
    vector<string> best_pop;
    for(int i=0;i<pop_size;i++){
        best_pop.push_back(sorted[i]);
    }
    return best_pop;
}

int main(){
    srand(time(0));

    vector<string> population;
    int gen=0;
    population=initializepop();
    while(gen<100){
        vector<string> best_pop=sorted(population);
        vector<string> new_pop;
        for(int i=0;i<2*pop_size();i++){
            string m1=rand()%best_pop.size();
            string m2=rand()%best_pop.size();
            pair<string,string> child=offspring(m1,m2);
            string child1=child.first;
            string child2=child.second;
            double p=((double)(rand()%1000))/1000;
            if(p<=0.01){
                mutate(child1);
            }
            p=((double)(rand()%1000))/1000;
            if(p<=0.01){
                mutate(child2);
            }
            new_pop.push_back(child1);
            new_pop.push_back(child2);
        }
        population=new_pop;
    }
}