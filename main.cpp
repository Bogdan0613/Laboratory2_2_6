#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;



void determinator(int a, int b, int **det) {
    double d, tmp;
    for (int k = 0; k < a - 1; k++) {
        for (int i = k + 1; i < a; i++) {
            tmp = -det[i][k] / det[k][k];
            for (int j = 0; j < a; j++) {
                det[i][j] += det[k][j] * tmp;
            }
        }
    }
    cout << "\nTarget matrix (Gauss method):\n\n";
    cout.precision(2);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            cout.width(8);
            cout << fixed << det[i][j] << " ";
        }
        cout << "\n";
    }
    d = 1;
    for (int i = 0; i < a; i++) {
        d *= det[i][i];
    }
    cout << fixed << "\nMatrix determinant: " << d << "\n";
    for (int i = 0; i < b; i++) {
        delete [] det[i];
    }
    delete [] det;
}

int main() {

    ifstream file("graph.txt");;
    int a, b;
    if (!file) {
        cout << "Failed to load the file!";
    }
    file >> a >> b;


    int **arr = new int *[b];
    for (int i = 0; i < b; i++)
        arr[i] = new int[2];
    for (int i = 0; i < b; i++)
        file >> arr[i][1] >> arr[i][2];
    file.close();


    cout << "file reading - finished" << endl;
    int **inc = new int* [a+1];
    for (int i = 0; i < a+1; i++) {
        inc[i] = new int[b+1];
    }


    for (int i = 0; i < a+1; i++) {
        for (int j = 0; j < b+1; j++) {
            inc[i][j] = 0;
        }
    }
    for (int i = 0; i < a+1; i++) {
        inc[i][0] = i;
    }
    for (int i = 0; i < b+1; i++) {
        inc[0][i] = i;
    }

    for (int i = 0; i < b; i++) {
        int k = arr[i][1];
        int l = arr[i][2];
        if (k != l) {
            inc[k][i+1] = -1;
            inc[l][i+1] = 1;
        } else {
            inc[k][i+1] = 2;
        }

    }

    string res;
    cout << "Incidence matrix:" << endl;
    for (int i = 0; i < a+1; i++) {
        for (int j = 0; j < b+1; j++) {
            cout << setw(3) << inc[i][j] << "  ";
        }
        cout << endl;
    }

    int **adj = new int *[a+1];
    for (int i = 0; i < a+ 1; i++)
        adj[i] = new int[a+1];

    for (int i = 0; i < a+1; i++)
        for (int j = 0; j < a+ 1; j++) {
            adj[i][j] = 0;
        }
    for (int i = 0; i < a+1; i++)
        adj[i][0] = i;
    for (int i = 0; i < a+1; i++)
        adj[0][i] = i;
    for (int i = 0; i < b; i++) {
        int k = arr[i][1];
        int l = arr[i][2];
        adj[k][l] = 1;
    }

    cout << "Adjacency matrix:"<<endl;
    for (int i = 0; i < a+1; i++) {
        for (int j = 0; j < a+1; j++) {
            cout << setw(3) << adj[i][j] << "  ";
        }
        cout << endl;
    }

    int **det = new int *[a];
    for (int i = 0; i < a; i++)
        det[i] = new int[a];

    int k = 0, l =0;
    cout << endl;
    for (int i = 1; i < a+1; i++) {
        for (int j = 1; j < a+1; j++) {
            det[k][l] = adj[i][j];
            l++;
        }
        k++;
    }

    determinator(a, b, det);

}