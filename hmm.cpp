#include<bits/stdc++.h>

using namespace std;

float forward(int pos, vector<int>in, int st, vector<vector<float> >trans, vector<vector<float> >emat){
    
    if(!pos){
        if(st == 0)
            return emat[0][in[pos]] * trans[0][1];
        else
            return emat[1][in[pos]] * trans[0][2];
    }
    
    if(st){
        return emat[1][in[pos]] * (trans[1][2] * forward(pos-1, in, 0, trans, emat) + trans[2][2] * forward(pos-1, in, 1, trans, emat));
    }
    else{
        return emat[0][in[pos]] * (trans[1][1] * forward(pos-1, in, 0, trans, emat) + trans[2][1] * forward(pos-1, in, 1, trans, emat));
    }
    
}

int main(){
    vector<vector<float> >trans(3, vector<float>(3,0.0));
    vector<vector<float> >emat(2, vector<float>(2,0.0));
    vector<int>in;
    
    int ob, n;
    float val, prob;
    
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
    
    //Starts calculating the probabilites using forward algorithm through recursion
    n = in.size() - 1;
    prob = forward(n, in, 0, trans, emat) + forward(n, in, 1, trans, emat);
    cout<<"Probability of the sequence: "<<prob<<"\n";
    
    return 0;
}
