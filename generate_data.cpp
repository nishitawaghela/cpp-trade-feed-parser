#include <iostream>
#include <fstream>

int main() {
    // file to write into
    std::ofstream file("data/trades.csv");
    
    // header row
    file << "timestamp,symbol,bid,ask,price,volume\n";
    
    // 100000 rows
    for (int i = 0; i < 100000; i++) {
        long long ts = 1717200000 + i;  // fake timestamp, just incrementing
        double bid = 22000.0 + (i % 1000) * 0.5;  // bid price cycles between 22000-22500
        double ask = bid + 0.50;  // ask is always 0.50 above bid
        double price = bid + 0.25;  // mid price
        int volume = 100 + (i % 400);  // volume cycles 100-500
        
        file << ts << ",NIFTY," << bid << "," << ask << "," << price << "," << volume << "\n";
    }
    
    file.close();
    std::cout << "100000 rows written.\n";
    return 0;
}