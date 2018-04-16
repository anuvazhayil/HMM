#include<bits/stdc++.h>

using namespace std;

int main(){
    vector<vector<float> >trans(3, vector<float>(3,0.0));  //Transition matrix
    vector<vector<float> >emat(2, vector<float>(2,0.0));   //Symbol emission probability matrix
    vector<int>st;
    vector<char>sy;
    double n, m;(double) rand() / RAND_MAX;
    int i = 20;
    float val;
    
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
    st.push_back(0);
    
    while(i){
        m = (double)rand()/RAND_MAX;
        if(m < trans[st.back()][1])
            st.push_back(1);
        else
            st.push_back(2);
        
        n = (double)rand()/RAND_MAX;
        if(n < emat[st.back()-1][0])
            sy.push_back('H');
        else
            sy.push_back('T');
        
        --i;
    }
    
    cout<<"State sequence generated: \n";
    for(int i = 0; i < st.size(); i++){
        cout<<st[i]<<" ";
    }
    
    cout<<"\nSymbol sequence generated: \n";
    for(int i = 0; i < sy.size(); i++){
        cout<<sy[i]<<" ";
    }
    cout<<"\n";
}