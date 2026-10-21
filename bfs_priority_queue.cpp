// bfs_priority_queue.cpp
// Compilation : g++ -O2 -std=c++17 bfs_priority_queue.cpp -o bfsq
// Execution   : bfsq

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <iomanip>

using namespace std;

// ============================================================
// Noeud de l'arbre
// ============================================================
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// ============================================================
// Comparateur : min-heap par valeur du noeud
// (priority_queue est max-heap par defaut, donc on inverse)
// ============================================================
struct MinVal {
    bool operator()(const Node* a, const Node* b) const {
        return a->val > b->val;   // ">" => plus petite valeur en premier
    }
};

// ============================================================
// Affichage de la file a priorite (copie pour ne pas la detruire)
// On affiche dans l'ordre de sortie reel, pas dans l'ordre interne du heap
// ============================================================
string pqToString(priority_queue<Node*, vector<Node*>, MinVal> pq) {
    if (pq.empty()) return "[]";
    string s = "[";
    while (!pq.empty()) {
        s += to_string(pq.top()->val);
        pq.pop();
        if (!pq.empty()) s += ", ";
    }
    s += "]";
    return s;
}

// ============================================================
// Affichage du vecteur visited
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
// BFS avec priority_queue (min-heap par val)
// ============================================================
void BFS_priority(Node* racine) {
    if (racine == nullptr) {
        cout << "Arbre vide.\n";
        return;
    }

    cout << "\n=== DEBUT BFS (priority_queue, min-heap) ===\n";
    cout << "Racine : " << racine->val << "\n\n";

    // Declaration de la priority_queue avec ses 3 parametres templates :
    //   1) type stocke         : Node*
    //   2) conteneur sous-jacent : vector<Node*>  (defaut, mais explicite)
    //   3) comparateur          : MinVal (inverse l'ordre)
    priority_queue<Node*, vector<Node*>, MinVal> pq;
    vector<int> visited;

    // Etape 0 : on pousse la racine
    pq.push(racine);

    cout << left << setw(6)  << "Etape"
         << setw(28) << "File priorite (min)"
         << setw(28) << "Visited"
         << "Action\n";
    cout << string(95, '-') << "\n";

    int etape = 0;
    cout << left << setw(6)  << etape
         << setw(28) << pqToString(pq)
         << setw(28) << visitedToString(visited)
         << "Push racine " << racine->val << "\n";

    while (!pq.empty()) {
        ++etape;

        // 1) Extraire le noeud de plus petite valeur
        Node* courant = pq.top();
        pq.pop();

        // 2) Marquer comme visite
        visited.push_back(courant->val);

        // 3) Pousser les fils (non nuls)
        string action = "Pop " + to_string(courant->val) + " ; ";
        if (courant->left)  { pq.push(courant->left);  action += "push gauche " + to_string(courant->left->val)  + " ; "; }
        if (courant->right) { pq.push(courant->right); action += "push droit "  + to_string(courant->right->val) + " ; "; }
        if (!courant->left && !courant->right) action += "feuille (aucun fils)";

        cout << left << setw(6)  << etape
             << setw(28) << pqToString(pq)
             << setw(28) << visitedToString(visited)
             << action << "\n";
    }

    cout << string(95, '-') << "\n";
    cout << "\n=== FIN BFS ===\n";
    cout << "Ordre de visite : " << visitedToString(visited) << "\n\n";
}

// ============================================================
// Affichage de l'arbre (rotate 90 deg)
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
    // Arbre binaire :
    //
    //              1
    //            /   \
    //           2     3
    //          / \   / \
    //         4   5 6   7
    //        /
    //       8
    //
    Node* racine = new Node(1);
    racine->left  = new Node(2);
    racine->right = new Node(3);
    racine->left->left   = new Node(4);
    racine->left->right  = new Node(5);
    racine->right->left  = new Node(6);
    racine->right->right = new Node(7);
    racine->left->left->left = new Node(8);

    cout << "Arbre :\n\n";
    afficherArbre(racine);
    cout << "\n";

    BFS_priority(racine);

    return 0;
}