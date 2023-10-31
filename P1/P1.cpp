//Elliptic Curve Point Adder and Multiplier
//VERSION 1.1.0
//by Alan Cervantes
//Created on 2023-09-11
//Last modified on 2023-09-18

//Bug Fixes: 
//*An issue was identified in the mod function; the formula was incorrect, leading to occasional failures in calculating negative remainders.
//*Some conditions were incorrectly declared, they have been fixed and now work correctly.

//New functions added:
//*It is now possible to multiply a generator point to obtain other points. 
//*Additionally, the structure of the 'sum' function was changed, improving the overall program performance.


#include <iostream>
using namespace std;
#include <math.h>

//Calculates the modulus of positive and negative numbers :)
int mod(int n, int m){
    return (n<0) ? (m - (abs(n)%m))%m : n % m;
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

    return gcd(n, m, x, y);
}

vector<pair<int,int>> sum(vector<pair<int,int>>P, int m, int a, bool showComments){
    vector<pair<int,int>> SUM;
    int x = 0, y = 0, l = 0, l1 = 0, l2 = 0;
    bool equal = false;
    if(P[0].first == 0 && P[0].second == 0 && P[1].first == 0 && P[1].second == 0){ // 0 + 0
        x = 0;
        y = 0;
        SUM.push_back(pair(x,y));

        //IGNORE THIS
        if (showComments){
            cout << "\t\t0 + 0 = (" << SUM[0].first << "," <<  SUM[0].second << ")" << "\n";   
        }
        
        return SUM;
    }else if (P[0].first == 0 && P[0].second == 0 || P[1].first == 0 && P[1].second == 0){  // 0 or 0
        //ESPECIAL CASE
        if(P[0].first == 0){
            x = P[1].first; 
            y = P[1].second; 
        }else{
            x = P[0].first; 
            y = P[0].second;
        }
        SUM.push_back(pair(x,y));

        //IGNORE THIS
        if (showComments){
            if (P[0].first == 0 && P[0].second == 0){
                cout << "\t\t0 + P = (" << SUM[0].first << "," <<  SUM[0].second << ")" << "\n";
            }else{
                cout << "\t\tP + 0 = (" << SUM[0].first << "," <<  SUM[0].second << ")" << "\n";

            }
        }

        return SUM;
    }else if (P[0].first == P[1].first && P[0].second == P[1].second){ // P = P
        equal = true;
        
    }else{ // P != Q 
        equal = false;
    }
    
    if(equal){
        l = mod(mod(3 * pow(P[0].first,2) +a, m) * mod(inverse(2 * P[0].second, m),m) , m); //lambda
        cout << "lambda = " << l << "\n";
    }else{
        l1 = mod((P[1].second - P[0].second),m); 
        //ESPECIAL CASE
        if (P[1].first - P[0].first == 0){ //This means that the result will be the point at infinity.
            x = 0; y = 0;
            SUM.push_back(pair(x,y));
                    //IGNORE THIS
            if (showComments){
                cout << "\t\tO = (" << SUM[0].first << "," <<  SUM[0].second << ")" << "\n";
            }
            return SUM;
        }
        
        l2 = (inverse(mod(P[1].first - P[0].first, m), m));
        l = mod(l1 * l2, m);    //lambda

        
        // cout << "\n\n\t LAMBDA -> " << l << "\n"; //DEBUG LINE

    }

        x = pow(l,2) - P[0].first - P[1].first;
        x = mod(x, m);

        y = l * (P[0].first - x) - P[0].second;
        y = mod(y,m);


    SUM.push_back(pair(x,y));
    if(showComments){
        if( (P[0].first == P[1].first)&&(P[0].second == P[0].second)){
            cout << "\t\t2P = (" << SUM[0].first << "," <<  SUM[0].second << ")" << "\n";
        }else{
            cout << "\t\tP + Q = (" << SUM[0].first << "," <<  SUM[0].second << ")" << "\n";
        }
    }

    return SUM;
}

vector<pair<int,int>> mul(vector<pair<int,int>>G, int m, int a, int n, bool showGs){
    vector<pair<int,int>> MUL;
    vector<pair<int,int>> Gs;
    int countOrder = 1;
    int auxCount = 0;
    int order = 0;

    //showGs is a boolean variable that indicates if we want to show the Gs or not
    //if showGs is true, we will show the Gs, if not, we will not show the Gs
    //for that reason we add Gs to the vector Gs, and then we show it
    Gs.push_back(pair(G[0].first, G[0].second));

    for(int i = 0; i < n; i++){
        MUL = sum(G, m, a, false);
        G[0] = MUL[0];
        Gs.push_back(pair(G[0].first, G[0].second));
        if(MUL[0].first == 0 && MUL[0].second == 0){
            order = countOrder; 
            countOrder = 0;
        }else{
            countOrder++;
        }
    }

    if(showGs){
        cout << "\n\n\t Gs -> \n";
        for(int i = 0; i < Gs.size(); i++){
            cout << "\t\t"<< i+1 << "G = (" << Gs[i].first << "," << Gs[i].second << ")\n";
        }
        // cout << "\t\t -> Order: " << countOrder << "\n";
        // cout << "\t\t -> Order: " << order+1 << "\n";
        cout << "\t\t -> Order: " << order+1 << "\n";
    }

    return MUL;
}

int sG(vector<pair<int,int>>G, vector<pair<int,int>>P, int m, int a, int n){
    vector<pair<int,int>> MUL;
    vector<pair<int,int>> Gs;
    int countOrder = 1;
    int auxCount = 0;
    int s = 0;

    Gs.push_back(pair(G[0].first, G[0].second));

    for(int i = 0; i < n; i++){
        if(G[0].first == P[0].first && G[0].second == P[0].second){
            return s+1;
        }
        MUL = sum(G, m, a, false);
        G[0] = MUL[0];
        Gs.push_back(pair(G[0].first, G[0].second));
        if(MUL[0].first == P[0].first && MUL[0].second == P[0].second){
            s = countOrder; 
            countOrder = 0;
        }else{
            countOrder++;
        }
    }

    return s+1;
}

int main(){
    //Points vector
    vector<pair<int,int>>G;
    vector<pair<int,int>>P;
    vector<pair<int,int>>ANS;

    //modulus and a (from the EC)
    int option = 0;
    int m = 0, a = 0, n = 1;
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int s = 0;


    cout << "Addition and multiplication operations over elliptic groups 💀" << "\n";
    cout << "Choose an option: \n";
    cout << "\t1. Sum and Double of Points  \n";
    cout << "\t2. Multiplication \n";
    cout << "\t3. sG = P \n";
    cout << "\t4. Exit \n";
    cin >> option;


    //Menu
    switch (option){
    case 1: //SUM
        cout << "Introduce in one line: Modulus, a, x1, y1, x2 & y2. \n";
        cin >> m >> a >> x1 >> y1 >> x2 >> y2;
        G.push_back(pair(x1,y1));
        G.push_back(pair(x2,y2));
        ANS = sum(P, m, a, true);  // (POINTS, MODULUS, A, SHOW COMMENTS)
        break;
    case 2: //MUL
        cout << "Introduce in one line: Modulus, a, x1, y1. \n";
        cin >> m >> a >> x1 >> y1;
        G.push_back(pair(x1,y1));
        G.push_back(pair(x1,y1));
        cout << "Introduce the number of times you want to multiply the point. \n";
        cin >> n;
        ANS = mul(G, m, a, n-1, true); // (POINTS, MODULUS, A, N, SHOW GS)
        break;
    case 3: //sG = P 
        cout << "Introduce in one line: Modulus, a, G -> (x1, y1), P -> (x2, y2), |E|. \n";
        cin >> m >> a >> x1 >> y1 >> x2 >> y2 >> n;
        G.push_back(pair(x1,y1));
        G.push_back(pair(x1,y1));

        P.push_back(pair(x2,y2));


        s = sG(G, P, m, a, n-1); // (Generator, Point, A, N, SHOW GS)
        cout << "\t\t s = " << s << "\n";
        break;
    case 4: //EXIT
        cout << "Bye bye! 👋🏻 \n";
        break;
    default:
        break;
    }

    return 0;
}