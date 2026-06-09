#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream file("data/trades.csv");
    file << "timestamp,symbol,bid,ask,price,volume\n";

    for (int i = 0; i < 100000; i++) {
        string sym = (i % 2 == 0) ? "NIFTY" : "BANKNIFTY";
        double base = (sym == "NIFTY") ? 22000.0 : 48000.0;
        double bid = base + (i % 1000) * 0.5;
        double ask = bid + 0.50;
        double price = bid + 0.25;
        int volume = 100 + (i % 400);
        long long ts = 1717200000 + i;

        file << ts << "," << sym << "," << bid << "," << ask << "," << price << "," << volume << "\n";
    }

    file.close();
    cout << "100000 rows written.\n";
    return 0;
}
