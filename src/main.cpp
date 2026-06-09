#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <map>

using namespace std;

struct Trade {
    long long timestamp;
    string symbol;
    double bid;
    double ask;
    double price;
    int volume;
};

vector<Trade> load_trades(const string& filename) {
    vector<Trade> trades;
    ifstream file(filename);
    string line;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Trade t;

        getline(ss, token, ','); t.timestamp = stoll(token);
        getline(ss, t.symbol, ',');
        getline(ss, token, ','); t.bid = stod(token);
        getline(ss, token, ','); t.ask = stod(token);
        getline(ss, token, ','); t.price = stod(token);
        getline(ss, token, ','); t.volume = stoi(token);

        trades.push_back(t);
    }
    return trades;
}

int main() {
    // overall parse benchmark
    auto start = chrono::high_resolution_clock::now();
    vector<Trade> trades = load_trades("data/trades.csv");
    auto end = chrono::high_resolution_clock::now();

    double total_vwap = 0;
    double total_volume = 0;
    double total_spread = 0;

    for (const Trade& t : trades) {
        total_vwap += t.price * t.volume;
        total_volume += t.volume;
        total_spread += (t.ask - t.bid);
    }

    double vwap = total_vwap / total_volume;
    double avg_spread = total_spread / trades.size();
    long long micros = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Records parsed   : " << trades.size() << "\n";
    cout << "VWAP             : " << vwap << "\n";
    cout << "Avg Spread       : " << avg_spread << "\n";
    cout << "Time taken       : " << micros << " microseconds\n";
    cout << "Throughput       : " << (trades.size() * 1000000LL / micros) << " records/sec\n";

    // per-symbol aggregation benchmark
    map<string, double> sym_vwap_num;
    map<string, double> sym_volume;
    map<string, double> sym_spread;
    map<string, int> sym_count;

    auto sym_start = chrono::high_resolution_clock::now();

    for (const Trade& t : trades) {
        sym_vwap_num[t.symbol] += t.price * t.volume;
        sym_volume[t.symbol] += t.volume;
        sym_spread[t.symbol] += (t.ask - t.bid);
        sym_count[t.symbol]++;
    }

    auto sym_end = chrono::high_resolution_clock::now();
    long long sym_micros = chrono::duration_cast<chrono::microseconds>(sym_end - sym_start).count();

    cout << "\nPer-Symbol Aggregation:\n";
    for (auto& kv : sym_vwap_num) {
        string sym = kv.first;
        double sym_vwap = kv.second / sym_volume[sym];
        double sym_avg_spread = sym_spread[sym] / sym_count[sym];
        cout << sym << " | VWAP: " << sym_vwap << " | Avg Spread: " << sym_avg_spread << " | Records: " << sym_count[sym] << "\n";
    }
    cout << "Aggregation latency: " << sym_micros << " microseconds\n";

    return 0;
}