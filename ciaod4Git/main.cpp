#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
    char data;
    Node* left;
    Node* right;

    // Конструктор
    Node(char value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};


class BinarySearchTree{
private:
    Node* root;

    // Рекурсивная операция вставки значения в дерево
    Node* insertRecursively(Node* node, char value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertRecursively(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursively(node->right, value);
        }

        return node;
    }

    //Рекурсивынй метод для отображения дерева
    void printTreeRecursive(Node* node, std::string indent, bool isLast) {
        if (node != nullptr) {
            std::cout << indent;

            if (isLast) {
                std::cout << "└─";
                indent += "   ";
            } else {
                std::cout << "├─";
                indent += "│  ";
            }

            std::cout << node->data << std::endl;

            printTreeRecursive(node->left, indent, false);
            printTreeRecursive(node->right, indent, true);
        }
    }

    // Рекурсивная операция вычисления значения выражения в левом поддереве
    int calculateLeftSubtreeExpression(Node* node, int count = 0) {
        if (node == nullptr) {
            return 0;
        }

        int leftValue = calculateLeftSubtreeExpression(node->left);
        int rightValue = calculateLeftSubtreeExpression(node->right);

        return leftValue + rightValue + (node->data - '0');
    }

    char findMaxValueRecursively(Node* node) {
        if (node == nullptr) {
            return '\0'; // Возвращаем нулевой символ, чтобы обозначить, что дерево пустое
        }

        if (node->left == nullptr && node->right == nullptr) {
            return node->data; // Если текущий узел является листом, возвращаем его значение
        }

        char leftMax = findMaxValueRecursively(node->left); // Рекурсивный поиск максимального значения в левом поддереве
        char rightMax = findMaxValueRecursively(node->right); // Рекурсивный поиск максимального значения в правом поддереве

        char currentMax = node->data; // Максимальное значение на текущем уровне
        if (leftMax > currentMax) {
            currentMax = leftMax;
        }
        if (rightMax > currentMax) {
            currentMax = rightMax;
        }

        return currentMax; // Возвращаем максимальное значение на текущем уровне
    }

    int countDigitsInRightSubtreeRecursively(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int rightChildDigitsCount = countDigitsInRightSubtreeRecursively(node->right);
        int leftChildDigitsCount = countDigitsInRightSubtreeRecursively(node->left);// Рекурсивный подсчет цифр в правом поддереве
        int currentDigitsCount = 0;

        if (std::isdigit(node->data)) {
            currentDigitsCount = 1; // Увеличиваем счетчик, если информационная часть узла является цифрой
        }

        return rightChildDigitsCount + currentDigitsCount + leftChildDigitsCount;
    }

public:
    // Конструктор
    BinarySearchTree() {
        root = nullptr;
    }

    // Метод для вставки нового значения в БДП
    void insert(char value) {
        root = insertRecursively(root, value);
    }

    void printTree() {
        printTreeRecursive(root, "", true);
    }

    int calculateLeftSubtreeExpression() {
        cout << "Относительно какой вершины вы хотите считать левое поддерево?" << endl;
        char search;
        cin >> search;

        return calculateLeftSubtreeExpression(breadthFirstSearch(search)->left);
    }

    char findMaxLeafValue() {
        return findMaxValueRecursively(root);
    }

    int countDigitsInRightSubtree() {
        return countDigitsInRightSubtreeRecursively(root->right);
    }

    // Метод для поиска узла в ширину по информационной части
    Node* breadthFirstSearch(const char value) {
        if (root == nullptr) {
            return nullptr;
        }

        std::queue<Node*> queue;
        queue.push(root);

        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();

            if (current->data == value) {
                return current;
            }

            if (current->left != nullptr) {
                queue.push(current->left);
            }

            if (current->right != nullptr) {
                queue.push(current->right);
            }
        }

        return nullptr;
    }
};




int main() {
//    string Nodes;
//    cout << "PLS input your nodes from string" << endl;
//    cin >> Nodes;

    BinarySearchTree bst;

//    for(char element: Nodes){
//        bst.insert(element);
//    }


//     Вставка значений в БДП
    bst.insert('c');
    bst.insert('a');
    bst.insert('t');
    bst.insert('s');
    bst.insert('r');
    bst.insert('u');
    //Дополнительно
    bst.insert('q');
    bst.insert('b');

    bst.printTree();

    int result = bst.calculateLeftSubtreeExpression();
    cout << "Значение выражения в левом поддереве: " << result << endl;

    char resultMax = bst.findMaxLeafValue();
    cout << "Максимальное значение среди листьев дерева: " << resultMax << '-' << (int)resultMax - 48 << endl;

    BinarySearchTree bst2;
    bst2.insert('0');
    bst2.insert('2');
    bst2.insert('1');
    bst2.insert('3');
    bst2.insert('5');
    bst2.insert('4');

    bst2.printTree();
    int resultRight = bst2.countDigitsInRightSubtree();
    cout << resultRight << endl;


    return 0;
}