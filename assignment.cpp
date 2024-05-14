Wavelabs’ Lab setup consists of a network of n nodes, labeled from 1 to n.As a Network
Engineer, you are given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where
ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from
source to target.
We will send a signal from a given node k. Return the minimum time it takes for all the n nodes
to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.

#include <bits/stdc++.h>
using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
     
    unordered_map<int,vector<pair<int,int>>>adj;
    
    //edge is directed
    for(auto& edge : times) {
        adj[edge[0]].push_back({edge[1], edge[2]});
    }

    // Initializing distances with infinity
    //but not soucrce node
    
    vector<int> distances(n + 1, INT_MAX);
    distances[k] = 0;

    // Priority queue to store nodes with their tentative distances
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});

    while(!pq.empty()) 
    {
        auto it = pq.top();
        
        int distance=it.first;
        int node=it.second;
        
        pq.pop();
        
        if (distance > distances[node]) {
            continue;
        }
        for (const auto& [ngbr, wght] : adj[node]) 
        {
            int new_distance = distance + wght;
            
            if (new_distance < distances[ngbr]) 
            {
                distances[ngbr] = new_distance;
                
                pq.push({new_distance, ngbr});
                
            }
        }
    }

    //Checking that  whether  all nodes is reciving singnal
    int max_distance=INT_MIN;
    for (int i=1;i<=n;++i) 
    {
        if (distances[i]==INT_MAX) {
            return -1; // Not all nodes are reachable
        }
        max_distance = max(max_distance,distances[i]);
    }
    return max_distance;
}

int main() 
{
    vector<vector<int>>times={{2,1,1},{2,3,1},{3,4,1}};
    int n = 4;
    int k = 2;
    
    cout << networkDelayTime(times, n, k) << endl;
    
    return 0;
}
