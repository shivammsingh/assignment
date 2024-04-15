// Wavelabs’ Lab setup consists of n workstations numbered from 0 to n - 1 connected by ethernet
// cable connections forming a network where connections[i] = [ai, bi] represents a connection
// between workstations ai and bi. Any workstation can reach any other workstation directly or
// indirectly through the network.
// As a Network Engineer, you are given initial computer network connections. You can extract
// certain cables between two directly connected workstations, and place them between any pair of
// disconnected workstations to make them directly connected.
// Return the minimum number of times you need to do this in order to make all the workstations
// connected. If it is not possible, return -1

#include <bits/stdc++.h>
using namespace std;

//In order to solve this question we will first find out the number of 
//extra-edges and then we will find out the number of components of the graph.
// We will be using the Disjoint Set data structure to do so.

class DisjointSet {
public:
    vector<int> rank, parent, size;

    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    
};
class Solution {
public:
    int Solve(int n, vector<vector<int>>& connections) {
        DisjointSet ds(n);
        int extraConnection = 0;
        for (auto it : connections) {
            int u = it[0];
            int v = it[1];

            // if the ultimate workstation parent is same
            if (ds.findUPar(u) == ds.findUPar(v)) {
                extraConnection++; // counting the extraedge
            }
            else { // if the workstation parent is differnet

                ds.unionByRank(u, v);  
            }
        }
        int disConnectedWorkStation = 0;

        //Total disconnected work sation
        for (int i = 0; i < n; i++) {
            if (ds.parent[i] == i) disConnectedWorkStation++;
        }
        int ans = disConnectedWorkStation - 1;

        //if the count of the extra connection is greater then we will return the answer
        if (extraConnection >= ans) return ans;

        return -1;
    }
};

int main() {

    int V = 9;
    vector<vector<int>> connections = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}};

    Solution obj;
    int ans = obj.Solve(V, connections);
    cout << "The number of operations needed: " << ans << endl;
    return 0;
}