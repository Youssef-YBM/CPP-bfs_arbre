// bfs_arbre.cpp
// Compilation : g++ -O2 -std=c++17 bfs_arbre.cpp -o bfs
// Execution   : ./bfs

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>

using namespace std;

// ============================================================
// Noeud de l arbre binaire
// ============================================================
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// ============================================================
// Utilitaire : afficher la file (FIFO)
// ============================================================
string fileToString(queue<Node*> q) {
    if (q.empty()) return "[]";
    string s = "[";
    while (!q.empty()) {
        s += to_string(q.front()->val);
        q.pop();
        if (!q.empty()) s += ", ";
    }
    s += "]";
    return s;
}

// ============================================================
// Utilitaire : afficher le vecteur visited
// ============================================================
string visitedToString(const vector<int>& v) {
    if (v.empty()) return "[]";
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        s += to_string(v[i]);
        if (i + 1 < v.size()) s += ", ";
    }
    s += "]";
    return s;
}

// ============================================================
// BFS avec affichage des etapes
// ============================================================
void BFS(Node* racine) {
    if (racine == nullptr) {
        cout << "Arbre vide.\n";
        return;
    }

    cout << "\n=== DEBUT BFS ===\n";
    cout << "Racine : " << racine->val << "\n\n";

    queue<Node*> file;        // FIFO
    vector<int> visited;      // noeuds deja traites

    // Etape 0 : on met la racine dans la file
    file.push(racine);

    cout << left << setw(6)  << "Etape"
         << setw(28) << "File (FIFO)"
         << setw(28) << "Visited"
         << "Action\n";
    cout << string(95, '-') << "\n";

    int etape = 0;
    cout << left << setw(6)  << etape
         << setw(28) << fileToString(file)
         << setw(28) << visitedToString(visited)
         << "Push racine " << racine->val << "\n";

    // Boucle principale
    while (!file.empty()) {
        ++etape;

        // 1) Extraire le premier de la file
        Node* courant = file.front();
        file.pop();

        // 2) Marquer comme visite
        visited.push_back(courant->val);

        // 3) Ajouter les fils non nuls
        string action = "Pop " + to_string(courant->val) + " ; ";
        if (courant->left)  { file.push(courant->left);  action += "push gauche "  + to_string(courant->left->val)  + " ; "; }
        if (courant->right) { file.push(courant->right); action += "push droit "   + to_string(courant->right->val) + " ; "; }
        if (!courant->left && !courant->right) action += "feuille (aucun fils)";

        cout << left << setw(6)  << etape
             << setw(28) << fileToString(file)
             << setw(28) << visitedToString(visited)
             << action << "\n";
    }

    cout << string(95, '-') << "\n";
    cout << "\n=== FIN BFS ===\n";
    cout << "Ordre de visite (parcours en largeur) : " << visitedToString(visited) << "\n\n";
}

// ============================================================
// Petit utilitaire : afficher l arbre (rotated, simple)
// ============================================================
void afficherArbre(Node* n, int profondeur = 0) {
    if (n == nullptr) return;
    afficherArbre(n->right, profondeur + 1);
    cout << string(profondeur * 4, ' ') << n->val << "\n";
    afficherArbre(n->left, profondeur + 1);
}

// ============================================================
// MAIN
// ============================================================
int main() {
    // Construction d un arbre :
    //
    //              1
    //            /   \
    //           2     3
    //          / \   / \
    //         4   5 6   7
    //        /
    //       8
    //
    Node* racine   = new Node(1);
    racine->left   = new Node(2);
    racine->right  = new Node(3);
    racine->left->left   = new Node(4);
    racine->left->right  = new Node(5);
    racine->right->left  = new Node(6);
    racine->right->right = new Node(7);
    racine->left->left->left = new Node(8);

    cout << "Arbre construit :\n\n";
    afficherArbre(racine);
    cout << "\n";

    BFS(racine);

    return 0;
}