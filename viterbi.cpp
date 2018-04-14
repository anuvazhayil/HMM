#include<bits/stdc++.h>

using namespace std;

//Viterbi algorithm
float viterbi(int pos, vector<int>in, int st, vector<vector<float> >trans, vector<vector<float> >emat, vector<int>&st1path, vector<int>&st2path, vector<vector<float> >&jtprob){
    
    //Termination condition - when reaches the first observation
    if(!pos){
        if(st == 0){
            jtprob[0][pos] = emat[0][in[pos]] * trans[0][1];
            return jtprob[0][pos];
        }
        else{
            jtprob[1][pos] = emat[1][in[pos]] * trans[0][2];
            return jtprob[1][pos];
        }
    
    }
    
    //State 1
    if(!st){
        if(jtprob[0][pos-1] > 1)
            jtprob[0][pos-1] = viterbi(pos-1, in, 0, trans, emat, st1path, st2path, jtprob);
        
        float st1 = trans[1][1] * jtprob[0][pos-1];
        
        if(jtprob[1][pos-1] > 1)
            jtprob[1][pos-1] = viterbi(pos-1, in, 1, trans, emat, st1path, st2path, jtprob);
        
        float st2 = trans[2][1] * jtprob[1][pos-1];
        
        if(st1 >= st2){
            st1path.push_back(1);
            jtprob[0][pos] = emat[0][in[pos]] * st1;
        }
        else{
            st1path.push_back(2);
            jtprob[0][pos] = emat[0][in[pos]] * st2;            
        }
        return jtprob[0][pos];
    }
    
    //State 2
    else{
        if(jtprob[0][pos-1] > 1)
            jtprob[0][pos-1] = viterbi(pos-1, in, 0, trans, emat, st1path, st2path, jtprob);
        
        float st1 = trans[1][2] * jtprob[0][pos-1];
        
        if(jtprob[1][pos-1] > 1)
            jtprob[1][pos-1] = viterbi(pos-1, in, 1, trans, emat, st1path, st2path, jtprob);
        
        float st2 = trans[2][2] * jtprob[1][pos-1];
        
        if(st1 >= st2){
            st2path.push_back(1);
            jtprob[1][pos] = emat[1][in[pos]] * st1;
        }
        else{
            st2path.push_back(2);
            jtprob[1][pos] = emat[1][in[pos]] * st2;
            
        }
        return jtprob[1][pos];
    }
}

int main(){
    vector<vector<float> >trans(3, vector<float>(3,0.0));  //Transition matrix
    vector<vector<float> >emat(2, vector<float>(2,0.0));   //Symbol emission probability matrix
    vector<int>in;  //Observations, H -> 0 and T -> 1
    vector<int>st1path, st2path;
    
    int ob,n;
    float val, st1, st2;
    stack<int>st;
    
    cout<<"Enter the number of observations: ";
    cin>>ob;
    cout<<"Enter the sequence of observations: ";
    while(ob){
        cin>>n;
        in.push_back(n);
        --ob;
    }
    
    n = in.size()-1;
    vector<vector<float> >jtprob(2, vector<float>(n+1,2));  //Joint probabilities
    
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
    
    st1path.push_back(0);
    st2path.push_back(0);
    st1 = viterbi(n, in, 0, trans, emat, st1path, st2path, jtprob);
    st2 = viterbi(n, in, 1, trans, emat, st1path, st2path, jtprob);
    jtprob[0][n] = st1;
    jtprob[1][n] = st2;
    
    if(st1 >= st2)
        st.push(1);
    else
        st.push(2);
    
    for(int i = n; i >=0; i--){
        if(st.top() == 1)
            st.push(st1path[i]);
        else 
            st.push(st2path[i]);
            
    }
    
    //Joint probabilities of all states
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= n; j++){
            cout<<jtprob[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    //Printing the path taken
    cout<<"Most probable path taken: ";
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<"\n";
    
    return 0;
}