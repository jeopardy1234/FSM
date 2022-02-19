#include <bits/stdc++.h>
using namespace std;
 
#define ninja ios_base::sync_with_stdio(false);cin.tie(NULL);
#define rep(i, a, b) for (int i = int(a); i < int(b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ll long long
#define ld long double
#define pic pair<int,char>

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

int precedence(char c)
{
    if(c=='*')return 2;
    if(c=='.')return 1;
    if(c=='+')return 0;
    return -1;
}

typedef struct machine
{
    int final_state;
    vector<pair<int,pic>>transitions;
    vector<int>states;
    int start_state;
}NFA;

int cnt = 1;
vector<NFA>mch;

string infix_to_postfix(string s)
{
    /*
        if char -> push to output string
        if ( -> push to stack
        if ) -> pop until (
        else ensure that lower priority is never above higher.
        priority level:
            1) klene  *
            2) concat .
            3) union  +
    */
    string final;
    stack<char>st;
    for(auto &i : s)
    {
        if(isalpha(i))
            final.push_back(i);
        else
        {
            if(i == '(')
            {
                st.push('(');
            }
            else if(i == ')')
            {
                debug(st.top());
                while(st.top() != '(')
                {
                    final.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else
            {
               while(!st.empty() && precedence(st.top()) >= precedence(i))
                {
                    final.push_back(st.top());
                    st.pop();
                }
                st.push(i);
            }
        }
    }
    while(!st.empty())
    {
        final.push_back(st.top());
        st.pop();
    }
    return final;
}

void concat_handler()
{
    NFA x = mch[sz(mch) - 2];
    NFA y = mch[sz(mch) - 1];
    NFA z;
    mch.pop_back(); mch.pop_back();
    for(int i=0; i<sz(x.states) ; i++)
    {
        if(x.states[i] != x.final_state)
            z.states.push_back(x.states[i]);
    }
    for(int i=0; i<sz(y.states); i++)
        z.states.push_back(y.states[i]);
    for(int i=0; i<sz(x.transitions); i++)
    {
        if(x.transitions[i].second.first == x.final_state)
            x.transitions[i].second.first = y.start_state;
        z.transitions.push_back(x.transitions[i]);
    }
    for(int i=0; i<sz(y.transitions); i++)
        z.transitions.push_back(y.transitions[i]);
    z.start_state = x.start_state;
    z.final_state = y.final_state;
    mch.push_back(z);
}

void kleene_handler()
{
    NFA x = mch[sz(mch) - 1];
    NFA z;
    mch.pop_back();
    for(int i=0; i<sz(x.states) ; i++)
        z.states.push_back(x.states[i]);

    for(int i=0; i<sz(x.transitions); i++)
        z.transitions.push_back(x.transitions[i]);

    z.start_state = cnt++;
    z.final_state = cnt++;

    z.states.push_back(z.start_state);
    z.states.push_back(z.final_state);

    z.transitions.push_back({x.final_state, {z.final_state, 'E'}});
    z.transitions.push_back({z.start_state, {x.start_state, 'E'}});
    z.transitions.push_back({x.final_state, {x.start_state, 'E'}});

    mch.push_back(z);
}

void union_handler()
{
    NFA x = mch[sz(mch) - 2];
    NFA y = mch[sz(mch) - 1];
    NFA z;
    mch.pop_back(); mch.pop_back();
    z.start_state = x.start_state;
    for(int i=0; i<sz(x.states) ; i++)
        z.states.push_back(x.states[i]);
    for(int i=0; i<sz(y.states); i++)
        z.states.push_back(y.states[i]);
    for(int i=0; i<sz(x.transitions); i++)
        z.transitions.push_back(x.transitions[i]);
    for(int i=0; i<sz(y.transitions); i++)
        z.transitions.push_back(y.transitions[i]);

    z.start_state = cnt++;
    z.final_state = cnt++;

    z.states.push_back(z.start_state);
    z.states.push_back(z.final_state);

    z.transitions.push_back({z.start_state , {x.start_state, 'E'}});
    z.transitions.push_back({z.start_state , {y.start_state, 'E'}});
    z.transitions.push_back({x.final_state , {z.final_state, 'E'}});
    z.transitions.push_back({y.final_state , {z.final_state, 'E'}});
    mch.push_back(z);
}


void toNFA(string s)
{
    for(int i=0 ;i<s.length(); i++)
    {
        if(isalpha(s[i]))
        {
            NFA x;
            x.start_state = cnt;
            x.states.push_back(cnt++);
            x.states.push_back(cnt++);
            int s1 = x.start_state;
            int s2 = x.states[1];
            x.transitions.push_back({s1,{s2,s[i]}});
            x.final_state = s2;
            mch.push_back(x);
        }
        else if(s[i] == '.')
            concat_handler();
        else if(s[i] == '*')
            kleene_handler();
        else
            union_handler();
    }
}

int main()
{
    AilaJaadu();
    string s; cin >> s;
    string smod;
    for (int i = 0; i < s.length(); i++)
    {
        smod+=s[i];
        if (s[i] == ')' || s[i] == '*' || isalpha(s[i]))
        {
            if (s[i+1] == '(' || isalpha(s[i+1])){
                smod+='.';
            }
        }
    }
    s = smod;
    string psfix = infix_to_postfix(s);
    debug(psfix);
    debug(s);
    toNFA(psfix);
    debug(mch[0].states);
    debug(mch[0].final_state);
    debug(mch[0].start_state);

    for(int i=0; i<sz(mch[0].states); i++)
        if(mch[0].states[i] == mch[0].start_state)
            mch[0].states[i] = 0;
    for(int i=0; i<sz(mch[0].transitions); i++)
    {
        if(mch[0].transitions[i].first == mch[0].start_state)
            mch[0].transitions[i].first = 0;
        if(mch[0].transitions[i].second.first == mch[0].start_state)
            mch[0].transitions[i].second.first = 0;
    }
    if(mch[0].final_state == mch[0].start_state)mch[0].final_state = 0;
    mch[0].start_state = 0;

    cout << sz(mch[0].states) << " " << sz(mch[0].transitions) << " " << 1 << "\n";
    cout << mch[0].final_state << "\n";
    for(auto &i : mch[0].transitions)
    {
        cout << i.first << " " << i.second.second << " " << i.second.first << "\n";
    }
} 