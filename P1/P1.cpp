//In this practice I show you how to sum 2 points of a Eliptic Curve
//Basically we have 2 situations, P, Q, where P != Q, and when P==Q

//VERSION 1.0

#include <iostream>
using namespace std;
#include <math.h>

//Calculates the modulus of positive and negative numbers :)
int mod(int n, int m){
    return (n<0) ? m - ((-1)*n%m) : n % m;
}

// Function for extended Euclidean Algorithm modified to obtain de multiplicative inverse
int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    // return a1; // ORIGINAL ->  returns the gcd
    return (a1==1) ? x : -1; // MODIFIED -> returns x, who is the inverse so satisfies ax + by = gcd
    //if the gcd == 1, means that there's a inverse number such that n * x % k = 1
}

int inverse(int n, int m){
    int x, y;

    return gcd(n, m, x, y);;
}

vector<pair<int,int>> sum(vector<pair<int,int>>P, bool equal, int m, int a){
    int x = 0, y = 0, l = 0, l1 = 0, l2 = 0;
    if(equal){
        l = mod(mod(3 * pow(P[0].first,2) +a, m) * mod(inverse(2 * P[0].second, m),m) , m);

    }else{
        l = (P[1].second - P[0].second) * (inverse(mod(P[1].first - P[0].first, m), m)); //labmbda //Before calculate the inverse we calculate  2y1 mod m
        // cout << "\n\n\t LAMBDA -> " << l << "\n"; //DEBUG LINE

    }

        x = pow(l,2) - P[0].first - P[1].first;
        x = mod(x, m);

        y = l * (P[0].first - x) - P[0].second;
        y = mod(y,m);

    vector<pair<int,int>> SUM;
    SUM.push_back(pair(x,y));
    return SUM;
}

int main(){
    //Points vector
    vector<pair<int,int>>P;
    vector<pair<int,int>>ANS;

    //modulus and a (from the EC)
    int m = 0, a = 0;

    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

    cout << "Addition and multiplication operations over elliptic groups 💀" << "\n Introduce in one line: Modulus, a, x1, y1, x2 & y2. Thanks. \n";
    cin >> m >> a >> x1 >> y1 >> x2 >> y2;

    //We use mod function at this point for those negative numbers, so, we can obtain the positive form and work with that
    x1 = mod(x1,m); y1 = mod(y1,m); x2 = mod(x2, m); y2 = mod(y2,m);

    P.push_back(pair(x1,y1));
    P.push_back(pair(x2,y2));

    if ( (x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0)){
        cout << "\nSince it's P + 0 = P. \n";
        cout << "\tWhere: \n" << "\t\tP = (" << P[0].first << "," << P[0].second <<")\n";
        (P[0].first == 0) ?  cout << "\t\tP + 0 = (" <<  P[1].first  << "," << P[1].second << ")\n" :  cout << "\t\tP + 0 = (" <<  P[0].first  << "," << P[0].second << ")\n";
    }else if( (x1 == x2)&&(y1 == y2)){
        cout << "\nSince it's the same point, we will perform the 2P operation. \n";
        cout << "\tWhere: \n" << "\t\tP = (" << P[0].first << "," << P[0].second <<")\n";
        ANS = sum(P, true, m, a);
        cout << "\t\t2P = (" << ANS[0].first << "," <<  ANS[0].second << ")" << "\n";
    }else{
        cout << "\nSince isn't the same point, we will perform the P+Q operation. \n";
        cout << "\tWhere: \n" << "\t\tP = (" << P[0].first << "," << P[0].second <<")\n";
        cout << "\t\tQ = (" << P[1].first << "," << P[1].second <<")\n";
        ANS = sum(P, false, m, a);
        cout << "\t\tP + P = (" << ANS[0].first << "," <<  ANS[0].second << ")" << "\n";
    
    }

    return 0;
}