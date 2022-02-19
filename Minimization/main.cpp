#include <bits/stdc++.h>
using namespace std;
 
#define ninja ios_base::sync_with_stdio(false);cin.tie(NULL);
#define rep(i, a, b) for (int i = int(a); i < int(b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ll long long
#define ld long double

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
 
void AilaJaadu()
{
    ninja;
    freopen("error.txt", "w", stderr);
    #define debug(x...) cerr << "[" << #x << "] = ["; _print(x);
}

int n,k,a;
vector<vector<int>>v;
vector<int>f;
set<pair<int,pair<int,int>>>trns;
set<pair<int,pair<int,int>>>ftrans;
vector<vector<int>>dsu_curr;
vector<vector<int>>adj;

void dfs(int ver, bool vis[])
{
    vis[ver] = true;
    for(auto &i : adj[ver])
    {
        if(!vis[i])
            dfs(i,vis);
    }
}

int main()
{
    AilaJaadu();
    cin >> n >> k >> a;
    bool vis[n] = {};
    int no_final = -1;
    v.resize(n);
    adj.resize(n);
    dsu_curr.resize(n);
    bool fs[n] = {};
    for(int i=0; i<n; i++)
        v[i].resize(26);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<26; j++)
            v[i][j] = -1;
    }
    for(int i=0; i<a; i++)
    {
        int x; cin >> x;
        fs[x] = true;
    }
    for(int i=0; i<n; i++)
    {
        if(fs[i])f.push_back(i);
    }

    for(int i=0; i<k; i++)
    {
        int s,d; char c;
        cin >> s >> c >> d;
        adj[s].push_back(d);
        v[s][c-'a'] = d;
        trns.insert({s , {c-'a' , d}});
    }
    dfs(0,vis);
    for(int i=0 ;i<n; i++)
        cerr << vis[i] << " ";
    cerr << "\n";
    debug(adj);
    for(int i=0; i<n; i++)
    {
        if(fs[i] == false)
        {
            if(vis[i])
            {
                no_final = i;
                break;
            }
        }
    }

   vector<int>parent(n), temp_parent(n);
    for(int i=0; i<f.size(); i++)
    {
        dsu_curr[f[0]].push_back(f[i]);
        parent[f[i]] = f[0];
    }
    if(no_final != -1)
    {
        for(int i=0; i<n; i++)
        {
            if(!fs[i]){
                if(vis[i])
                {
                    dsu_curr[no_final].push_back(i);
                    parent[i] = no_final;
                }
                else
                    parent[i] = -1;
            }
        }
    }

    debug(dsu_curr);
    debug(parent);
    debug(v); 
    //Now, dsu_curr contians 0 equivalence (approved)
    //Now check for 1,2,3... equivalence
    //How to do it??????
    /*
        Plan:
        Say we have {1,2,3,4} in one set (parent = 1 say)
        parent[] = {1,1,1,1}
        temp_parent = {1,2,3,4} (intitially)
        O(n^2 loop){
            if(distinguishable(x,y))   [x < y]
            {
                do nothing
            }
            else
            {
                temp_parent[y] = temp_parent[x];
            }
        }
        set temp_parent = parent
        Please dont be complicated :((
    */
    while(1)
    {
        for(int i=0; i<n; i++)
        {
            if(parent[i] != -1)
                temp_parent[i] = i;
            else
                temp_parent[i] = -1;
        }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<dsu_curr[i].size(); j++)
            {
                for(int k=j+1; k<dsu_curr[i].size(); k++)
                {
                    bool dist = false;
                    int el1 = dsu_curr[i][j];
                    int el2 = dsu_curr[i][k];
                    
                    for(int l=0; l<26; l++)
                    {
                        int t1 = v[el1][l];
                        int t2 = v[el2][l];
                        if(t1 == t2)continue;
                        if((t1 == -1 && t2 != -1) || (t2 == -1 && t1 != -1))
                        {
                            dist = true;;
                            break;
                        }
                        if(parent[t1] != parent[t2])
                            dist = true;
                    }
                    if(!dist)
                    {
                        temp_parent[el2] = temp_parent[el1];
                    }
                }
            }
        } 
        if(parent == temp_parent)
            break;
        parent = temp_parent;
        for(int i=0; i<n; i++)
            dsu_curr[i].clear();
        for(int i=0; i<n; i++)
        {
            if(parent[i] == i)
                dsu_curr[i].push_back(i);
        }
        for(int i=0; i<n; i++)
        {
            if(parent[i] != i && parent[i] != -1)
                dsu_curr[parent[i]].push_back(i);
        }
        debug(dsu_curr);
    }

    int ftotal = 0;
    set<int>final_states;
    set<int>sfn;
    map<int,int>m;
    for(int i=0; i<n; i++)
    {
        if(parent[i] != -1)
            sfn.insert(parent[i]);
    }
    int cnt = 0;
    for(auto &i : sfn)
        m[i] = cnt++;
    for(int i=0; i<n; i++)
        if(!dsu_curr[i].empty())ftotal++;
    for(int i=0; i<f.size(); i++)
        final_states.insert(m[parent[f[i]]]);
    for(auto &i : trns)
    {
        if(!vis[i.first] || !vis[i.second.second])
            continue;
        ftrans.insert({m[parent[i.first]],{i.second.first, m[parent[i.second.second]]}});
    }

    cout << ftotal << " " << ftrans.size() << " " << final_states.size() << "\n";
    for(auto &i : final_states)
        cout << i << " ";
    cout << "\n";
    for(auto &i : ftrans)
    {
        cout << i.first << " " << char(i.second.first + 'a') << " " << i.second.second << "\n"; 
    }
} 