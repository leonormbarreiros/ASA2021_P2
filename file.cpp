#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

#define WHITE 0
#define BLACK 1
#define GRAY 2
#define NIL -1

using namespace std;

int n, k;
int output;

vector <vector <int> > Gf; 
vector<int> pi;

void init() 
{
    Gf = vector< vector<int> >(n+2, vector<int>(n+2));
    pi = vector<int>(n+2);
}

void read() 
{
    for (int p = 0; p < n; p++) {
        int x,y;
        if(scanf("%d %d", &x, &y) == 1);

        Gf[0][p+1] = x;
        Gf[p+1][n+1] = y;
    }

    for (int u = 0; u < k; u++) {
        int i,j,c;
        if(scanf("%d %d %d", &i, &j, &c)== 1);

        Gf[i][j] = c;
        Gf[j][i] = c;
    }
}


bool augment()
{   
    std::vector<int> color(n+2, 0);
    std::fill(color.begin(), color.end(), WHITE);

    queue<int> q;
    q.push(0);
    color[0] = GRAY;
    pi[0] = NIL;
 
    while (!q.empty()) {

        int u = q.front();
        q.pop();
        
        for (int v = 0; v < n+2; v++) {
            if (color[v] == WHITE && Gf[u][v] > 0) { 
                if (v == n + 1) {
                    pi[v] = u;
                    return true;
                }
                q.push(v);
                color[v] = GRAY;
                pi[v] = u;
            }
        }
        color[u] = BLACK;
    }
    return false;
}

int computefp() {
    int cf = 1000000000; 
    for (int v = n + 1; v != 0; v = pi[v]) {
        int u = pi[v];
        if (cf > Gf[u][v]) {
            cf = Gf[u][v];
        } 
    }
    return cf;
}

void apply(int cf) {
    for (int v = n + 1; v != 0; v = pi[v]) {
        int u = pi[v];
        Gf[u][v] -= cf;
        Gf[v][u] += cf;
    }
}
 
int edmondsKarp() 
{
    int fluxo = 0;

    while (1) {
        if (augment() == false) {
            return fluxo;
        }
        int cf = computefp();
        apply(cf);
        fluxo += cf;
    }
}

int main() 
{
    if(scanf("%d %d", &n, &k) == 1);

    init();
    read();

    output = edmondsKarp();
    printf("%d\n", output);

    return 0;
}

