#include<iostream>
#include <math.h>
#include <vector>

using namespace std;
char s[1000];
double stlon, stlat, stt;

struct node{
    int txid;
    int t;
    double lon;
    double lat;
    int is_p;
    int speed;
}p[10000000];

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

inline void writeRoute(int i) {
    write(p[i].txid);
    putchar(',');
    write(stt);
    putchar(',');
    printf("%f", stlon);
    putchar(',');
    printf("%f", stlat);
    putchar(',');
    write(p[i].t);
    putchar(',');
    printf("%f", p[i].lon);
    putchar(',');
    printf("%f", p[i].lat);
//    putchar('\n');
}
inline void writeRouteDistance(int i, double distance) {
    writeRoute(i);
    putchar(',');
    printf("%f", distance);
//    putchar('\n');
}

vector<pair<double, double> > highDensity;
vector<double> coefficient;
inline void initDensity(){
    highDensity.push_back(make_pair<double, double>(113.8091930, 22.6260029));
    coefficient.push_back((double)3000/108480);
    highDensity.push_back(make_pair<double, double>(113.8948678, 22.5703062));
    coefficient.push_back((double)5000/108480);
    highDensity.push_back(make_pair<double, double>(113.9192072, 22.53257616));
    coefficient.push_back((double)11000/108480);
    highDensity.push_back(make_pair<double, double>(114.0584289, 22.53347450));
    coefficient.push_back((double)30000/108480);
    highDensity.push_back(make_pair<double, double>(114.1178171, 22.54066118));
    coefficient.push_back((double)25000/108480);
    highDensity.push_back(make_pair<double, double>(114.1148964, 22.59905292));
    coefficient.push_back((double)10000/108480);
    highDensity.push_back(make_pair<double, double>(114.0311687, 22.63588464));
    coefficient.push_back((double)10000/108480);
    highDensity.push_back(make_pair<double, double>(114.2434086, 22.71493808));
    coefficient.push_back((double)6000/108480);
//    highDensity.push_back(make_pair<double, double>(113.8091930203613, 22.62600296510122));
//    highDensity.push_back(make_pair<double, double>(113.89486785620619, 22.57030622114057));
//    highDensity.push_back(make_pair<double, double>(113.9192072982076, 22.53257616878011));
//    highDensity.push_back(make_pair<double, double>(114.05842890645562, 22.533474503360125));
//    highDensity.push_back(make_pair<double, double>(114.11781714493907, 22.540661180000214));
//    highDensity.push_back(make_pair<double, double>(114.11489641189888, 22.59905292770091));
//    highDensity.push_back(make_pair<double, double>(114.03116873141408, 22.63588464548134));
//    highDensity.push_back(make_pair<double, double>(114.24340866566627, 22.71493808852229));
}
inline double calCost(int i){
    double cost = 0;
    for(int m = 0; m < highDensity.size(); m++){
        pair<double, double> pr = highDensity[m];
        cost += coefficient[m]/pow(pow(p[i].lon-pr.first,2) + pow(p[i].lat-pr.second, 2), 0.5);
    }
    return cost;
}

inline void writeRouteDistanceCost(int i, double distance) {
    writeRouteDistance(i, distance);
    putchar(',');
    double cost = calCost(i);
    printf("%f", cost);
//    putchar('\n');
}

int li[10000];
int main() {
    freopen("valid_sorted_taxi.csv", "r", stdin);
    freopen("odDistanceCost_valid.csv", "w", stdout);
    scanf("%s", s);
    getchar();
    cout<<"taxi_id,start_time,start_lon,start_lat,end_time,end_lon,end_lat,distance,backup_level\n";

    int n = 9843421;
    initDensity();
    int cur = 0;
    bool state = 0;
    double distance = 0;
    double pre_lon = 0, pre_lat = 0, tmp = 0;
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
        if (txid != li[cur]) {
            li[++cur] = txid;
            if (state) {
                writeRouteDistanceCost(i-1, distance);
                putchar('\n');

            }
            state = is_p;
            if (state) {
                stt = t;
                stlon = lon;
                stlat = lat;
                distance = 0;
            }
        }
        if (is_p && !state) { // is_p: 1
            stlon = lon;
            stlat = lat;
            distance = 0;
            stt = t;
            state = 1;
        }
        else if (!is_p && state) { // is_p: 0
            writeRouteDistanceCost(i, distance + pow(pow(lon-pre_lon,2) + pow(lat-pre_lat, 2), 0.5));
            putchar('\n');
            state = 0;
        }
        if(is_p){
            tmp = pow(pow(lon-pre_lon,2) + pow(lat-pre_lat, 2), 0.5);
            distance += tmp;
        }
        pre_lon = lon;
        pre_lat = lat;
    }
    return 0;
}
