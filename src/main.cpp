#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

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

    return 0;
}