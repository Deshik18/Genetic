#include<bits/stdc++.h>
#include<time.h>

using namespace std;

int K;   //knapsack capacity
int N;   //no of items;
vector<int> weight;
vector<int> value;
int POPULATION_SIZE=10;

string producechromosone(){
    string str="";
    for(int i=0;i<N;i++){
        if(rand()%2==0){
            str+='0';
        }
        else{
            str+='1';
        }
    }
    return str;
}

char mutated_genes(){
    if(rand()%2==0){
        return '0';
    }
    else{
        return '1';
    }
}

string mate(string par1,string par2){
    // chromosome for offspring
    string child_chromosome = "";
    for(int i = 0;i<N;i++){
        // random probability 
        float p = (rand()%100)/100;
  
        // if prob is less than 0.45, insert gene
        // from parent 1 
        if(p < 0.45)
            child_chromosome += par1[i];
  
        // if prob is between 0.45 and 0.90, insert
        // gene from parent 2
        else if(p < 0.90)
            child_chromosome += par2[i];
  
        // otherwise insert random gene(mutate), 
        // for maintaining diversity
        else
            child_chromosome += mutated_genes();
    }
  
    // create new Individual(offspring) using 
    // generated chromosome for offspring
    return (child_chromosome);
} 
  
// Calculate fitness score
int cal_fitness(string chromosome){
    int cap=0;
    int val=0;
    for(int i=0;i<N;i++){
        if(chromosome[i]=='1'){
            cap+=weight[i];
            val-=value[i];
        }
    }
    if(cap>K){
        return 0;
    }
    else{
        return val;
    }  
}

int cal_weight(string chrom){
    int w=0;
    for(int i=0;i<N;i++){
        if(chrom[i]=='1'){
            w+=weight[i];
        }
    }
    return w;
}

vector<string> sorting(vector<string> population,ofstream & f){
    vector<string> sorted;
    map<string, int> popul;
    for(int i=0;i<population.size();i++){
        popul[population[i]]=cal_fitness(population[i]);
        f << "String: " << population[i] << "     " << "Fitness: " << (-1)*popul[population[i]] << endl;        
        int flag=0;
        for(int j=sorted.size()-1;j>=0;j--){
            if(popul[population[i]]>popul[sorted[j]]){
                sorted.insert(sorted.begin()+j+1,population[i]);
                flag=1;
            }
            if(popul[population[i]]==popul[sorted[j]]){
                if(cal_weight(population[i])>=cal_weight(sorted[j])){
                    sorted.insert(sorted.begin()+j+1,population[i]);
                    flag=1;
                }
            }
        }
        if(flag==0){
            sorted.insert(sorted.begin(),population[i]);
        }
    }
    return sorted;
}

int main(){
    srand((unsigned)(time(0)));
    cin >>  K;
    cin >> N;
    int x;
    for(int i=0;i<N;i++){
        cin >> x;
        weight.push_back(x);
    }
    for(int i=0;i<N;i++){
        cin >> x;
        value.push_back(x);
    }

    int generation=0;
    vector<string> population;

    for(int i = 0;i<POPULATION_SIZE;i++){
        string gnome = producechromosone();
        population.push_back((gnome));
    }

    ofstream f("out2.txt");
    while(generation<10){
        f << "Generation... " << generation << "\n";

        population = sorting(population,f);

        vector<string> new_generation;

        // Perform Elitism, that mean 10% of fittest population
        // goes to the next generation
        int s = (10*POPULATION_SIZE)/100;
        for(int i = 0;i<s;i++){
            new_generation.push_back(population[i]);
        }

        // From 50% of fittest population, Individuals
        // will mate to produce offspring
        s = (90*POPULATION_SIZE)/100;
        for(int i = 0;i<s;i++){
            int b = (50*POPULATION_SIZE)/100;
            int r = rand()%b;
            string parent1 = population[r];
            r = rand()%b;
            string parent2 = population[r];
            string offspring = mate(parent1,parent2);
            new_generation.push_back(offspring);
        }
        population = new_generation;
        f << "Best KnapSack is: [";
        for(int i=0;i<N;i++) {
            if(i!=N-1){
                f << population[0][i] << " , ";
            }
            else{
                f << population[0][i] << "] ";
            }
        }
        f << "Fitness is " << (-1)*cal_fitness(population[0]);
        f << "\n******************************************************************************************************************************************\n";
        generation++;
    }   
}