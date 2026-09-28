# 🎲 Domino Lineare in C99

Progetto accademico per il corso di **Introduzione alla Programmazione** (A.A. 2023/2024 - Università Ca' Foscari Venezia).

Il progetto consiste nell'implementazione in linguaggio C (standard **C99**) del gioco del **Domino Lineare**, giocabile sia in modalità interattiva singola sia in modalità sfida contro un risolutore automatico guidato da Intelligenza Artificiale (AI).

## 1. Descrizione del Progetto

Il Domino Lineare si gioca con tessere contenenti coppie di numeri compresi tra 1 e 6. Data una mano iniziale di $N$ tessere assegnate al giocatore (anche con ripetizioni), l'obiettivo è disporle su un piano di gioco orizzontale (inizialmente vuoto) per massimizzare il punteggio totale.

## 2. Regole del Gioco

1. **Adiacenza dei lati:** Due tessere adiacenti sul piano di gioco devono avere lo stesso numero sul lato in cui si toccano.
2. **Posizionamento:** Le tessere possono essere inserite sia all'estremità sinistra che all'estremità destra della sequenza esistente.
3. **Rotazione:** Ogni tessera può essere ruotata prima del posizionamento (ad esempio, la tessera $[1\vert{}6]$ può essere ruotata in $[6\vert{}1]$).
4. **Calcolo del Punteggio:** Il punteggio è dato dalla somma di tutte le cifre presenti sulle tessere posizionate sul piano di gioco.

### Esempio di Punteggio

Se la sequenza sul piano di gioco è:

$$
[2\vert{}6][6\vert{}6][6\vert{}6][6\vert{}1]
$$

Il punteggio accumulato è:

$$
2 + 6 + 6 + 6 + 6 + 6 + 6 + 1 = 39
$$

Il gioco termina quando non vi sono più mosse valide a disposizione.

## 3. Modalità di Gioco

### Modalità Interattiva (Single Player)

* Il programma mostra la mano del giocatore, la disposizione corrente sul piano di gioco e il punteggio aggiornato.
* L'utente inserisce la mossa da eseguire (scelta della tessera, posizione a destra/sinistra ed eventuale rotazione).
* Il sistema valida la mossa controllando la compatibilità delle cifre adiacenti prima di aggiornare lo stato di gioco.

### Modalità Sfida contro l'AI (Player vs AI)

In questa modalità il giocatore si confronta con l'Intelligenza Artificiale:

* **Partita dell'Utente:** Il giocatore affronta la propria partita inserendo manualmente le mosse fino al termine delle tessere o delle mosse disponibili.
* **Confronto e Proclamazione del Vincitore:** Alla fine della partita dell'utente, il programma mostra a schermo il punteggio ottenuto dall'utente e il punteggio calcolato dal computer (ottenuto dall'AI mediante ricerca della soluzione migliore), decretando il vincitore della partita.
* **Visualizzazione dei Passaggi dell'AI:** Successivamente, il giocatore ha la possibilità di esaminare in dettaglio tutti i singoli passaggi e le mosse eseguite dall'algoritmo del computer sul proprio campo di gioco.

## 4. Compilazione ed Esecuzione

Il progetto utilizza esclusivamente la libreria standard C e rispetta lo standard **C99**.

### Compilazione con GCC

```bash
gcc -std=c99 -Wall -Wextra -O2 src/*.c -I include -o domino
```

### Esecuzione

```bash
./domino
```
