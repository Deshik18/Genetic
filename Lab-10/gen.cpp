#include<bits/stdc++.h>
#include<time.h>

using namespace std;

double w,x,y,z;
int a,b,c,d;
int pop_size=50;

double fitness(string chromosome){
    int a1=stoi(chromosome.substr(0,8),nullptr,2);
    double a=(30*(double)a1)/255 - 15;
    double b=(30*(double)(stoi(chromosome.substr(8,8),nullptr,2)))/255-15;
    double c=(30*(double)(stoi(chromosome.substr(16,8),nullptr,2)))/255-15;
    double d=(30*(double)(stoi(chromosome.substr(24,8),nullptr,2)))/255-15;
    return a*w+b*x+c*y+d*z;
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
    }
    of << "Best Individual of Current Gen is a:" << (30*(double)(stoi(sorted[0].substr(0,8),nullptr,2)))/255-15<< " b:" << (30*(double)(stoi(sorted[0].substr(8,8),nullptr,2)))/255-15 << " c:" << (30*(double)(stoi(sorted[0].substr(16,8),nullptr,2)))/255-15 << " d:" << (30*(double)(stoi(sorted[0].substr(24,8),nullptr,2)))/255-15 << " Fitness:" << m[sorted[0]] << endl;
    of << "\n\n***\n\n";
    return best_pop;
}

string crossover(string par1,string par2){
    string child="";
    for(int i=0;i<32;i++){
        int pr=rand()%1000;
        if(pr<0.01){
            int k=rand()%2;
            if(k==0){
                child+='0';
            }
            else{
                child+='1';
            }
        }
        else if(pr<0.505){
            child+=par1[i];
        }
        else{
            child+=par2[i];
        }    
    }
    return child;
}

string producechromosone(){
    string chromosone="";
    for(int i=0;i<32;i++){
        int k=rand()%2;
        if(k==0){
            chromosone+='0';
        }
        else{
            chromosone+='1';
        }
    }
    return chromosone;
}

int main(){
    srand(time(0));
    cin >> w >> x >> y >> z;
    int gen=0;
    vector<string> population;
    ofstream f;
    f.open("ass10out1.txt");
    f << "W is " << w << "\nX is " << x << "\nY is " << y << "\nZ is " << z << endl;
    f << "Objective Function is aW+bX+cY+dZ" << endl;
    for(int i=0;i<pop_size;i++){
        string chromosome=producechromosone();
        population.push_back(chromosome);
    }
    while(gen<50){
        f << "Current Generation .." << gen+1 << endl;
        vector<string> best_pop=sorting(population,f);
        vector<string> new_pop;
        for(int i=0;i<pop_size/10;i++){
            new_pop.push_back(best_pop[i]);
        }
        for(int i=0;i<3*pop_size;i++){
            string m1=best_pop[rand()%pop_size];
            string m2=best_pop[rand()%pop_size];
            new_pop.push_back(crossover(m1,m2));
        }
        population=new_pop;
        gen++;
    }
    f.close();
}