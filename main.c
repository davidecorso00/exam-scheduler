#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



#define MAX_K 50 // Numero limite di crediti massimi accumulabili
#define MAX_N 1000000 // Numero limite degli esami possibili
int main() {
    int N, K;      // Inizializzazione del numero degli esami (N) e dei massimi crediti accumulabili(K)

    scanf("%d %d", &N, &K);     //lettura da file di N e K
    if(N > MAX_N || K > MAX_K){return 1;}   // Controllo se N e K superano il limite imposto dalla consegna
     
    // Allocazione dinamica della memoria per i due array che conterranno la somma dei tempi degli esami fino all'esame i-esimo 
    long long *dp_prev = (long long *)malloc((K + 1) * sizeof(long long));
    long long *dp_curr = (long long *)malloc((K + 1) * sizeof(long long));

    // Inizializzazione dell'array dp_prev, riempendolo con il numero più grande possibile
    for (int c = 0; c <= K; c++) {
        dp_prev[c] = LLONG_MAX; // LLONG_MAX è il valore più grande che un long long possa salvare
    }
    dp_prev[0] = 0;  // Azzerare l'indice zero, ovvero la situazione iniziale (studente con zero crediti e zero tempo impiegato)

    // Ciclo iterativo che scorre tutti gli esami
    for (int i = 0; i < N; i++) {
        int T_i, C_i;   // Inizializzazione tempo necessario per svolgere l'esame (t) e crediti ottenibili (c)
        scanf("%d %d", &T_i, &C_i);  // Salvataggio di t e di c

        // Inizializzazione di dp_curr, riempendolo con il numero più grnade possibile
        for (int c = 0; c <= K; c++) {
            dp_curr[c] = LLONG_MAX;
        }

        // Ciclo iterativo che scorre le celle degli array, di lunghezza K+1
        for (int c = 0; c <= K; c++) {
            // Se la cella attuale ha un numero finito, vengono eseguiti i controlli
            if (dp_prev[c] < LLONG_MAX) {  

                
                int new_c = c + C_i; // Salviamo i crediti ottenuti fino all'esame i-esimo (sommando quello attuale a quelli precedenti)
                // Se la somma precedente supera K, il valore viene impostato a K
                if (new_c > K)
                     new_c = K;  

                /* Se il valore già salvato, che proviene da uno sviluppo precedente a questo, 
                è maggiore di quello attuale, ovvero la dp_prev[c] + t, viene sostituito da quest'ultimo */
                if (dp_curr[new_c] > dp_prev[c] + T_i) {
                    dp_curr[new_c] = dp_prev[c] + T_i;
                }

                // Se c è il massimo dei crediti ottenibili, si aggiunge la possibilità di saltare l'esame
                if (c == K) {
                    // Se la situazione attuale a credito 0 è maggiore della situazione precedente in cui si può comprare l'esame, quest'ultima sostituisce il primo
                    if (dp_curr[0] > dp_prev[c]) {
                        dp_curr[0] = dp_prev[c];
                    }
                }
            }
        }

        // Scambio i due array, in modo da poter controllare l'esame successivo in dp_curr, e che l'esame attuale diventi quello precendente
        long long *temp = dp_prev; 
        dp_prev = dp_curr;
        dp_curr = temp;
    }
    long long result = LLONG_MAX; // Inizializzazione variabile dove verrà salvato il risultato
    // Ciclo iterativo che controlla tutte le celle di dp_prev, trovando il minore e salvandono in result
    for (int c = 0; c <= K; c++) {
        if (dp_prev[c] < result) {
            result = dp_prev[c];
        }
    }

    // Stampa il risultato ottimale
    printf("%lld\n", result);
    
    // Libera la memoria allocata dinamicamente
    free(dp_prev);  
    free(dp_curr);

    return 0;
}