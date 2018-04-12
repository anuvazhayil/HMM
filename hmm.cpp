#include<bits/stdc++.h>

using namespace std;

//Recursive function for foward algorithm
float forward(int pos, vector<int>in, int st, vector<vector<float> >trans, vector<vector<float> >emat){
    
    //Termination condition - when reaches the first observation
    if(!pos){
        if(st == 0)
            return emat[0][in[pos]] * trans[0][1];
        else
            return emat[1][in[pos]] * trans[0][2];
    }
    
    //State 2
    if(st){
        return emat[1][in[pos]] * (trans[1][2] * forward(pos-1, in, 0, trans, emat) + trans[2][2] * forward(pos-1, in, 1, trans, emat));
    }
    
    //State 1
    else{
        return emat[0][in[pos]] * (trans[1][1] * forward(pos-1, in, 0, trans, emat) + trans[2][1] * forward(pos-1, in, 1, trans, emat));
    }
    
}

//Recursive function for backward algorithm
float backward(int pos, vector<int>in, int st, vector<vector<float> >trans, vector<vector<float> >emat){

    //Termination condition - when reaches the final observation
    if(pos == (in.size()-1))
        return 1;
    
    //State 1
    if(!st){
        return trans[1][1] * emat[0][in[pos+1]] * backward(pos+1, in, 0, trans, emat) + trans[1][2] * emat[1][in[pos+1]] * backward(pos+1, in, 1, trans, emat);
    }
    
    //State 2
    else{
        return trans[2][1] * emat[0][in[pos+1]] * backward(pos+1, in, 0, trans, emat) + trans[2][2] * emat[1][in[pos+1]] * backward(pos+1, in, 1, trans, emat);
    }
}

int main(){
    vector<vector<float> >trans(3, vector<float>(3,0.0));  //Transition matrix
    vector<vector<float> >emat(2, vector<float>(2,0.0));   //Symbol emission probability matrix
    vector<int>in;  //Observations, H -> 0 and T -> 1
    
    int ob, n;
    float val, prob, bprob;
    
    cout<<"Enter the number of observations: ";
    cin>>ob;
    cout<<"Enter the sequence of observations: ";
    while(ob){
        cin>>n;
        in.push_back(n);
        --ob;
    }
    
    cout<<"Enter the transition matrix: ";
    for(int i = 0; i <= 2; i++){
        for(int j = 0; j <= 2; j++){
            cin>>val;
            trans[i][j] = val;
        }
    }
    
    cout<<"Enter the symbol emission probabilities: ";
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            cin>>val;
            emat[i][j] = val;
        }
    }
    
    n = in.size() - 1;
    prob = forward(n, in, 0, trans, emat) + forward(n, in, 1, trans, emat);
    cout<<"Probability of the sequence: "<<prob<<"\n";
    
    bprob = backward(0, in, 0, trans, emat) + backward(0, in, 1, trans, emat);
    cout<<"Using backward algorithm: "<<prob<<"\n";
    
    return 0;
}
