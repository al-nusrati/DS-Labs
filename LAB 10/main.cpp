#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

template<typename T>
class GraphSetup{
private:
    map<T, vector<pair<T, int>>> adj;
    bool directed;

public:
    GraphSetup(bool dir = false){ directed = dir; }
    
    void destroy(){ adj.clear(); }
    
    bool isEmpty(){ return adj.empty(); }
    
    int getVerticesCount(){ return adj.size(); }
    
    int getEdgesCount(){
        int count = 0;
        for(auto const& pair : adj)    count += pair.second.size();
        if(!directed)    return count / 2;
        return count;
    }

    bool edgeExists(T u, T v){
        if(adj.find(u) == adj.end())    return false;
        for(int i = 0; i < adj[u].size(); i++)    {if(adj[u][i].first == v)    return true;}
        return false;
    }

    void insertVertex(T v){
        if(adj.find(v) == adj.end())    adj[v] = vector<pair<T, int>>();
    }

    void insertEdge(T u, T v, int weight){
        insertVertex(u);
        insertVertex(v);
        adj[u].push_back({v, weight});
        if(!directed)    adj[v].push_back({u, weight});
    }

    void deleteVertex(T v){
        if(adj.find(v) == adj.end())    {cout << "Vertex not found." << endl; return;}
        adj.erase(v);
        for(auto& pair : adj){
            for(int i = 0; i < pair.second.size(); i++){
                if(pair.second[i].first == v)    {pair.second.erase(pair.second.begin() + i); i--;}
            }
        }
    }

    void deleteEdge(T u, T v){
        if(adj.find(u) != adj.end()){
            for(int i = 0; i < adj[u].size(); i++){
                if(adj[u][i].first == v)    {adj[u].erase(adj[u].begin() + i); break;}
            }
        }
        if(!directed && adj.find(v) != adj.end()){
            for(int i = 0; i < adj[v].size(); i++){
                if(adj[v][i].first == u)    {adj[v].erase(adj[v].begin() + i); break;}
            }
        }
    }

    bool searchVertex(T v){
        return adj.find(v) != adj.end();
    }

    void BFS(T start){
        if(adj.find(start) == adj.end())    {cout << "Vertex not found." << endl; return;}
        map<T, bool> visited;
        queue<T> q;
        q.push(start);
        visited[start] = true;
        cout << "BFS: ";
        while(!q.empty()){
            T curr = q.front();
            q.pop();
            cout << curr << " ";
            for(int i = 0; i < adj[curr].size(); i++){
                if(!visited[adj[curr][i].first])    {visited[adj[curr][i].first] = true; q.push(adj[curr][i].first);}
            }
        }
        cout << endl;
    }

    void DFS(T start){
        if(adj.find(start) == adj.end())    {cout << "Vertex not found." << endl; return;}
        map<T, bool> visited;
        stack<T> s;
        s.push(start);
        cout << "DFS: ";
        while(!s.empty()){
            T curr = s.top();
            s.pop();
            if(!visited[curr]){
                cout << curr << " ";
                visited[curr] = true;
            }
            for(int i = 0; i < adj[curr].size(); i++){
                if(!visited[adj[curr][i].first])    s.push(adj[curr][i].first);
            }
        }
        cout << endl;
    }

    void shortestPath(T start, T end){
        map<T, int> dist;
        map<T, T> parent;
        for(auto const& pair : adj)    dist[pair.first] = 1e9; 
        dist[start] = 0;
        
        priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
        pq.push({0, start});

        while(!pq.empty()){
            T u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if(d > dist[u]) continue;

            for(int i = 0; i < adj[u].size(); i++){
                T v = adj[u][i].first;
                int weight = adj[u][i].second;
                if(dist[u] + weight < dist[v]){
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if(dist[end] == 1e9)    {cout << "No path exists.\n"; return;}
        
        vector<T> path;
        T curr = end;
        while(curr != start){
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        
        cout << "Optimal Route: ";
        for(int i = 0; i < path.size(); i++)    cout << path[i] << (i == path.size()-1 ? "" : " -> ");
        cout << "\nTotal Cost: PKR " << dist[end] << endl;
    }

    void MST(T start){
        if(directed)    {cout << "MST is for undirected graphs." << endl; return;}
        if(adj.find(start) == adj.end())    {cout << "Vertex not found." << endl; return;}
        
        map<T, bool> inMST;
        priority_queue<pair<int, pair<T, T>>, vector<pair<int, pair<T, T>>>, greater<pair<int, pair<T, T>>>> pq;
        
        inMST[start] = true;
        for(int i = 0; i < adj[start].size(); i++)    pq.push({adj[start][i].second, {start, adj[start][i].first}});
        
        int totalCost = 0;
        cout << "MST Edges:\n";
        while(!pq.empty()){
            int weight = pq.top().first;
            T u = pq.top().second.first;
            T v = pq.top().second.second;
            pq.pop();

            if(inMST[v])    continue;
            
            inMST[v] = true;
            totalCost += weight;
            cout << u << " - " << v << " : " << weight << endl;
            
            for(int i = 0; i < adj[v].size(); i++){
                if(!inMST[adj[v][i].first])    pq.push({adj[v][i].second, {v, adj[v][i].first}});
            }
        }
        cout << "Total MST Cost: " << totalCost << endl;
    }

    void getOutgoing(T v){
        if(adj.find(v) == adj.end())    {cout << "Airport not found." << endl; return;}
        cout << "Outgoing from " << v << ":\n";
        for(int i = 0; i < adj[v].size(); i++)    cout << " -> " << adj[v][i].first << " (PKR " << adj[v][i].second << ")\n";
    }

    void getIncoming(T v){
        cout << "Incoming to " << v << ":\n";
        for(auto const& pair : adj){
            for(int i = 0; i < pair.second.size(); i++){
                if(pair.second[i].first == v)    cout << pair.first << " -> " << v << " (PKR " << pair.second[i].second << ")\n";
            }
        }
    }
};


class AirlineSetup{
private:
    GraphSetup<string> flightGraph;

public:
    AirlineSetup() : flightGraph(true) {} 

    void addAirport(string name){
        flightGraph.insertVertex(name);
    }

    void removeAirport(string name){
        flightGraph.deleteVertex(name);
    }

    void addFlight(string src, string dest, int cost){
        flightGraph.insertEdge(src, dest, cost);
    }

    void removeFlight(string src, string dest){
        flightGraph.deleteEdge(src, dest);
    }

    void checkFlight(string src, string dest){
        if(flightGraph.edgeExists(src, dest))    cout << "Flight exists: " << src << " -> " << dest << endl;
        else                                     cout << "No flight: " << src << " -> " << dest << endl;
    }

    void displayStats(){
        cout << "Total Airports: " << flightGraph.getVerticesCount() << endl;
        cout << "Total Flights: " << flightGraph.getEdgesCount() << endl;
    }

    void outgoingFlights(string airport){
        flightGraph.getOutgoing(airport);
    }

    void incomingFlights(string airport){
        flightGraph.getIncoming(airport);
    }

    void exploreReachable(string start){
        flightGraph.BFS(start);
    }

    void analyzeNetwork(string start){
        flightGraph.DFS(start);
    }

    void findOptimalRoute(string src, string dest){
        flightGraph.shortestPath(src, dest);
    }
};

int main(){
    AirlineSetup air;
    
    air.addAirport("KHI");
    air.addAirport("LHE");
    air.addAirport("ISB");
    air.addAirport("QTA");

    air.addFlight("KHI", "LHE", 15000);
    air.addFlight("KHI", "ISB", 20000);
    air.addFlight("LHE", "ISB", 8000);
    air.addFlight("ISB", "QTA", 12000);
    
    air.displayStats();
    cout << endl;

    air.checkFlight("KHI", "ISB");
    air.outgoingFlights("KHI");
    cout << endl;

    air.exploreReachable("KHI");
    air.analyzeNetwork("KHI");
    cout << endl;

    air.findOptimalRoute("KHI", "QTA");

    cin.ignore();
    cin.get();    
    return 0;
}