#include <iostream>

using namespace std;
char s[1000];
int visit_p[150][10000];
int visit_s[150][10000];

struct node{
    int txid;
    int t;
    double lon;
    double lat;
    int is_p;
    int speed;
}p[10000000];

struct timeN{    // every 10 minutes: 600s
    int id; // 1-144
    long speed_count;
    double avg_speed;
    int taxi_on;
    double true_speed;
    int passengers;

}ts[150];

inline int readInt(){
    int x=0;
    char c=getchar();
    while(c>='0'&&c<='9'){
        x *= 10;
        x += c-'0';
        c=getchar();
    }
    return x;
}

inline double readFloat(){
    double x=0;
    char c=getchar();
    while(c>='0'&&c<='9') {
        x *= 10;
        x += c-'0';
        c=getchar();
    }
    if (c == '.') {
        c = getchar();
        double p = 0.1;
        while(c>='0'&&c<='9') {
            x += (c - '0')*p;
            p *= 0.1;
            c = getchar();
        }
    }
    return x;
}

inline void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

inline void writeTime(int i) {
    printf("%d", ts[i].id); 
    putchar(',');
    printf("%f", ts[i].avg_speed);
    putchar(',');
    printf("%f", ts[i].true_speed);
    putchar(',');
    printf("%d", ts[i].passengers); 
    putchar('\n');
}

int main(){
    freopen("valid_sorted_taxi.csv", "r", stdin);
    freopen("timeCount_valid.csv", "w", stdout);
    scanf("%s", s);
    getchar();
    cout<<"time,speed_avg,true_speed,passengers\n";

    for(int i = 0; i < 150; i++){
        ts[i] = timeN{i, 0, 0, 0, 0, 0};
    }
    for(int i = 0; i < 150; i++){
        for(int j = 0; j < 10000; j++){
            visit_p[i][j] = 0;
            visit_s[i][j] = 0;
        }
    }

    int n = 9606279;
    int pointer;
    int txid, t, is_p, speed;
    double lon, lat;
    for ( int i = 1; i <= n; i++ ) {
        txid = readInt();
        t = readInt();
        lon = readFloat();
        lat = readFloat();
        is_p = readInt();
        speed = readInt();
        p[i] = node{txid, t, lon, lat, is_p, speed};
        pointer = int(t/600 + 1);;
        if(is_p){
            if(visit_p[pointer][txid] == 0){
                ts[pointer].passengers += 1;
                visit_p[pointer][txid] = 1;
            }
        }
        if(speed > 0){
            ts[pointer].taxi_on += 1;
//            if(visit_s[pointer][txid] == 0){
//                ts[pointer].taxi_on += 1;
//                visit_s[pointer][txid] = 1;
//            }
        }
        ts[pointer].speed_count += (long)speed;
    }
    for(int i = 1; i <= 144; i++){
        ts[i].avg_speed = (double)ts[i].speed_count/n;
        if(ts[i].taxi_on > 0)
            ts[i].true_speed = (double)ts[i].speed_count/ts[i].taxi_on;
        writeTime(i);
    }
    return 0;
}
