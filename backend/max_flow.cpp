#include <bits/stdc++.h>
#include <fstream>

using namespace std;

// Source -> Requesters -> Providers -> Sink
// Weights S->R are values from database of desired quantity (ex: 1 for doctors, 15 for potatoes)
// Weights R->P are values from database of max capacity of providers (ex: 1 for doctors, 10 for potatoes)
// Weights P->T are values from database of max capacity of providers (ex: 1 for doctors, 10 for potatoes)


//The graph is constructed with incremental thresholds for distances between requesters and providers
// The matching is computed for each threshold and updated in the Pending connections table

// You stop matching when all requesters are satisfied or all providers are at capacity

class MaxFlowMatching{
    private:
        int src, dest; // source = R + P, sink = R + P + 1
        int Requesters, Providers; // number of requesters (R) and providers (P)
        // 0 ... (R-1) are requesters, R ... (R+P-1) are providers
        int N; // total number of nodes = R + P + 2
        int resulting_flow = 0;
        vector<vector<pair<int,int>>> capacity_graph; // adjacency list with (neighbor, capacity)
        vector<int> levels;
        vector<pair<int, int>> matching; // (requester, provider)
        
        bool bfs(){
            queue<int> q;
            bool ok = 0;

            for(int i = 0; i < N; i++) 
                levels[i] = N;
            
            levels[src] = 0;
            q.push(src);

            while(!q.empty()){
                int node = q.front();
                q.pop();

                for(auto &[neighbor, capacity] : capacity_graph[node]){
                    if(capacity > 0 && levels[neighbor] > levels[node] + 1){
                        if(neighbor == dest) 
                            ok = 1;
                        else{
                            levels[neighbor] = levels[node] + 1;
                            q.push(neighbor);
                        }
                    }
                }
            }
            return ok;
        }

        int dfs(int node, int bottleneck){
            if(!bottleneck || node == dest) 
                return bottleneck;
            
            int maxflow = bottleneck;
            for(auto &[neighbor, capacity] : capacity_graph[node]){
                if(capacity && levels[neighbor] > levels[node]){
                    int new_flow = dfs(neighbor, min(bottleneck, capacity));
                    bottleneck -= new_flow;
                    capacity -= new_flow;
                    for(auto &[back_neighbor, back_capacity] : capacity_graph[neighbor]){
                        if(back_neighbor == node){
                            back_capacity += new_flow;
                            break;
                        }
                    }
                }
            }
            return maxflow - bottleneck;
        }

        bool dinic(){
            bool ok = 0;
            if(!bfs()) 
                return 0;
            int aux = dfs(src, numeric_limits<int>::max());
            resulting_flow += aux;
            while(aux){
                ok = 1;
                aux = dfs(src, numeric_limits<int>::max());
                resulting_flow += aux;
            }
            return ok;  
        }
        void print_graph(){
            for(int i = 0; i < N; i++){
                cout << i << ": ";
                for(auto &[neighbor, capacity] : capacity_graph[i]){
                    cout << "(" << neighbor << ", " << capacity << ") ";
                }
                cout << "\n";
            }
        }

        void find_matching(){
            for(int i = Requesters; i < Requesters + Providers; i++){
                for(auto &[neighbor, capacity] : capacity_graph[i]){
                    if(neighbor < Requesters && capacity != 0){
                        matching.push_back({neighbor, i - Requesters});
                    }
                }
            }
        }

    public: 
        MaxFlowMatching(int src, int dest, int Requesters, int Providers, vector<vector<pair<int, int>>> &capacity_graph){
            this->src = src;
            this->dest = dest;
            this->Requesters = Requesters;
            this->Providers = Providers;
            this->capacity_graph = capacity_graph;
            this->N = Requesters + Providers + 2;
            this->levels.resize(N);
        }
        int get_max_flow(){
            while(dinic());
            print_graph();
            find_matching();
            return resulting_flow;
        }
        vector<pair<int, int>> get_matching(){
            return matching;
        }
};

class Earth_Distance{
    private:
        static constexpr double R = 6371e3; // metres
        static double toRad(double degree){
            return degree * M_PI / 180;
        }
    public:
        static double compute(double lat1, double lon1, double lat2, double lon2){
            double phi1 = toRad(lat1);
            double phi2 = toRad(lat2);
            double delta_phi = toRad(lat2 - lat1);
            double delta_lambda = toRad(lon2 - lon1);

            double a = sin(delta_phi/2) * sin(delta_phi/2) +
                       cos(phi1) * cos(phi2) *
                       sin(delta_lambda/2) * sin(delta_lambda/2);
            double c = 2 * atan2(sqrt(a), sqrt(1-a));

            double d = R * c; // in metres
            return d;
        }
}

class DoctorsAPI{
    private:
        vector<tuple<string, double, double, int>> requesters; // id, lat, lon, capacity
        vector<tuple<string, double, double, int>> providers; // id, lat, lon, capacity
        // database connection and methods to fetch data
        void fetch_requesters(){
            // fetch requester data from database
        }
        void fetch_providers(){
            // fetch provider data from database
        }
        void try_connect_requesters(int distance_threshold){
            // try to connect requester-provider pairs based on distance thresholds
            vector<vector<pair<int, int>>> capacity_graph; // adjacency list with (neighbor, capacity)
            map<int, string> requester_index, provider_index;

            int R = requesters.size();
            int P = providers.size();
            int src = R + P, dest = R + P + 1;
            capacity_graph.resize(R + P + 2);

            for(int i = 0; i < R; i++){
                auto &[r_id, r_lat, r_lon, r_cap] = requesters[i];
                requester_index[i] = r_id;
                capacity_graph[src].push_back({i, r_cap});
                capacity_graph[i].push_back({src, 0});
            }
            for(int i = 0; i < P; i++){
                auto &[p_id, p_lat, p_lon, p_cap] = providers[i];
                provider_index[i] = p_id;
                capacity_graph[R + i].push_back({dest, p_cap});
                capacity_graph[dest].push_back({R + i, 0});
            }
            // construct the capacity graph based on distance_threshold
            for(int i = 0; i < R; i++){
                auto &[r_id, r_lat, r_lon, r_cap] = requesters[i];
                for(int j = 0; j < P; j++){
                    auto &[p_id, p_lat, p_lon, p_cap] = providers[j];
                    double distance = Earth_Distance::compute(r_lat, r_lon, p_lat, p_lon);
                    if(distance <= distance_threshold){
                        capacity_graph[i].push_back({R + j, numeric_limits<int>::max()});
                        capacity_graph[R + j].push_back({i, 0});
                    }
                }
            }

            MaxFlowMatching mfm(src, dest, R, P, capacity_graph);
            vector<pair<int, int>> matching = mfm.get_matching();

            // If provider at max capacity, remove from providers list
            set<int> providers_to_remove;
            map<int, int> provider_current_capacity; // provider index -> current assigned capacity
            for(const auto& [r, p] : matching){
                provider_current_capacity[p]++;
            }
            for(int i = 0; i < P; i++){
                auto &[p_id, p_lat, p_lon, p_cap] = providers[i];
                if(provider_current_capacity[i] >= p_cap){
                    providers_to_remove.insert(i);
                }
            }
            vector<tuple<string, double, double, int>> new_providers;
            for(int i = 0; i < P; i++){
                if(providers_to_remove.find(i) == providers_to_remove.end()){
                    new_providers.push_back(providers[i]);
                }
            }
            providers = new_providers;
            // If requester fully satisfied, remove from requesters list
            set<int> requesters_to_remove;
            map<int, int> requester_current_capacity; // requester index -> current assigned capacity
            for(const auto& [r, p] : matching){
                requester_current_capacity[r]++;
            }
            for(int i = 0; i < R; i++){
                auto &[r_id, r_lat, r_lon, r_cap] = requesters[i];
                if(requester_current_capacity[i] >= r_cap){
                    requesters_to_remove.insert(i);
                }
            }
            vector<tuple<string, double, double, int>> new_requesters;
            for(int i = 0; i < R; i++){
                if(requesters_to_remove.find(i) == requesters_to_remove.end()){
                    new_requesters.push_back(requesters[i]);
                }
            }
            requesters = new_requesters;

            this->update_pending_connections(matching, requester_index, provider_index);
        }

        void update_pending_connections(const vector<pair<int, int>>& matching,
                                         const map<int, string>& requester_index,
                                         const map<int, string>& provider_index) {
            for (const auto& [r, p] : matching) {
                string r_id = requester_index.at(r);
                string p_id = provider_index.at(p);
                // Update the database to reflect the new connection
                // Create chat between r_id and p_id
                // Set status to "Pending" in PendingConnections table
            }
        }

    public:
        API(){
            // initialize database connection
            while(true){
                fetch_requesters();
                fetch_providers();
                int distance_threshold = 1000; // start with 1 km
                while(!requesters.empty() && !providers.empty()){
                    try_connect_requesters(distance_threshold);
                    distance_threshold += 1000; // increase threshold by 1 km
                }
                this_thread::sleep_for(chrono::minutes(5)); // wait for 5 minutes before next run
            }
        }
        ~API(){
            // close database connection
        }
}

/* Mock input format:
int main(){
    ifstream fin("mock_input.in");
    int R, P;
    fin >> R >> P;
    vector<int> requester_capacity(R);
    for(int i = 0; i < R; i++)
        fin >> requester_capacity[i];
    vector<int> provider_capacity(P);
    for(int i = 0; i < P; i++)
        fin >> provider_capacity[i];
    int src = R + P, dest = R + P + 1;

    vector<vector<pair<int, int> > > capacity_graph(R + P + 2);
    for(int i = 0; i < R; i++){
        capacity_graph[src].push_back({i, requester_capacity[i]});
        capacity_graph[i].push_back({src, 0});
    }
    for(int i = 0; i < P; i++){
        capacity_graph[R + i].push_back({dest, provider_capacity[i]});
        capacity_graph[dest].push_back({R + i, 0});
    }

    int E; // number of edges between requesters and providers
    fin >> E;
    for(int i = 0; i < E; i++){
        int r, p; // requester, provider
        fin >> r >> p;
        capacity_graph[r].push_back({R + p, numeric_limits<int>::max()});
        capacity_graph[R + p].push_back({r, 0});
    }

    MaxFlowMatching mfm(src, dest, R, P, capacity_graph);
    cout << mfm.get_max_flow() << endl;
    vector<pair<int, int>> matching = mfm.get_matching();
    for(auto &[r, p] : matching)
        cout << r << " " << p << endl;
    return 0;
}
*/