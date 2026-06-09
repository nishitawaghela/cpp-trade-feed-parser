# Trade Feed Parser & Latency Benchmarker

A high-throughput C++ trade feed parser built for low-latency market data processing.
Parses NSE tick data, computes financial metrics, and benchmarks throughput using high-resolution timers.

## What it does
- Parses 100,000+ tick records from a CSV trade feed
- Computes VWAP (Volume Weighted Average Price) and average bid-ask spread per symbol
- Benchmarks parse throughput and latency using `std::chrono::high_resolution_clock`

## Metrics (Apple M-series, -O2 optimization)
- Records parsed: 100,000
- Throughput: 2,269,426 records/sec
- Total parse latency: 44ms
- VWAP: 22,255.6
- Avg Bid-Ask Spread: 0.50

## Build & Run
```bash
# Generate synthetic tick data
g++ -O2 -o generate src/generate_data.cpp
./generate

# Run parser and benchmarker
g++ -O2 -o parser src/main.cpp
./parser
```

## Tech
- C++17
- STL: vector, fstream, sstream, chrono
- Synthetic NSE NIFTY tick data (100K rows)