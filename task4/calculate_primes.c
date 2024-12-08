int calculate_primes(int primes[], int e){
    for (int g = 0; g < e; g++){
        primes[g] = g;
    }
    primes[1] = 0;
    for (int i = 0; i < e; i++){
        if (primes[i] == 0){
            continue;
        }
        for (int j = 2; j < e; j++){
            if (i*j > e)
                break;
            primes[i*j] = 0;
        }
    }
    return 0;
}
