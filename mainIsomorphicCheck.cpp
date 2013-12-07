#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

bool isEq(vector<set<int> > & g1, vector<pair<int, set<int> > > &g2);

int main()
{  
    int n, m, u, v;
    cin >> n >> m;
    vector<set<int> > g1(n);
    vector<pair<int, set<int> > > g2(n);

    for (int i = 0; i < m; ++i){
        cin >> u >> v;
        g1[u - 1].insert(v - 1);
        g1[v - 1].insert(u - 1);
    }

    for (int i = 0; i < m; ++i){
        cin >> u >> v;
        g2[u - 1].second.insert(v - 1);
        g2[v - 1].second.insert(u - 1);
    }

    vector<int> nodes(n);
    for (int i = 0; i < n; ++i)
        nodes[i] = i;

    bool isEqual = false;
    do{
        for (int i = 0; i < n; ++i)
            g2[i].first = nodes[i];

        if (isEq(g1, g2)){
            isEqual = true;
            break;
        }
    } while (next_permutation(nodes.begin(), nodes.end()));

    if (isEqual)
        cout << "Yes";
    else
        cout << "No";
    cout << endl;
}

bool isEq(vector<set<int> > &g1, vector<pair<int, set<int> > > & g2)
{
    vector<set<int> > temp(g2.size());
    for (int i = 0; i < g2.size(); ++i){
        for (set<int>::iterator it = g2[i].second.begin(); it != g2[i].second.end(); ++it){
            temp[g2[i].first].insert(g2[*it].first);
        }
    }
    return temp == g1;
}
