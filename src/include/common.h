#ifndef SUBGRAPH_GENERATOR_COMMON_H
#define SUBGRAPH_GENERATOR_COMMON_H

#define PRINT_TIME_COST_S(INFO,T) std::cout<< INFO<< double(T)/CLOCKS_PER_SEC<<endl

#define PRINT_TIME_COST_MS(INFO,T) std::cout<< INFO<< double(T)/(CLOCKS_PER_SEC/1000)<<endl

#define LOOP(V,H,T) for(auto V = H ;V<T;++V)

#define NodeIDType size_t

namespace std {
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};
}
#endif


