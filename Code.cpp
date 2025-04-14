#include <iostream>
#include <string>
#include <climits>
#include <limits>

using namespace std;

class TreeNode {
public:
    string name;
    int donation;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string n, int value) {
        name = n;
        donation = value;
        left = NULL;
        right = NULL;
    }
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() {
        root = NULL;
    }

    void addNode(string name, int donation) {
        root = insert(root, name, donation);
    }

    void printDonors() {
        printDonors(root);
    }

    void printDonorn() {
        printDonorname(root);
    }

    void findMaxMinDonors() {
        int maxDonation = INT_MIN;
        int minDonation = INT_MAX;
        string maxDonor, minDonor;
        findMaxMinDonors(root, maxDonation, minDonation, maxDonor, minDonor);

        cout << "Maximum donation: " << maxDonation << " Rs. by " << maxDonor << endl;
        cout << "Minimum donation: " << minDonation << " Rs. by " << minDonor << endl;
    }

    void findMaxDonors() {
        int maxDonation = INT_MIN;
        int minDonation = INT_MAX;
        string maxDonor, minDonor;
        findMaxMinDonors(root, maxDonation, minDonation, maxDonor, minDonor);

        cout << "Maximum donation: " << maxDonation <<" Rs."<< endl;
    }

    void findMinDonors() {
        int maxDonation = INT_MIN;
        int minDonation = INT_MAX;
        string maxDonor, minDonor;
        findMaxMinDonors(root, maxDonation, minDonation, maxDonor, minDonor);

        cout << "Minimum donation: " << minDonation <<" Rs."<< endl;
    }

    bool searchDonor(TreeNode* node, string name) {
        if (node == NULL) {
            return false;
        }

        int comparison = name.compare(node->name);

        if (comparison == 0) {
            return true;
        } else if (comparison < 0) {
            return searchDonor(node->left, name);
        } else {
            return searchDonor(node->right, name);
        }
    }

    void deleteDonor(string name) {
        root = deleteDonor(root, name);
    }

private:
    TreeNode* insert(TreeNode* node, string name, int donation) {
        if (node == NULL) {
            return new TreeNode(name, donation);
        }

        int comparison = name.compare(node->name);

        if (comparison < 0) {
            node->left = insert(node->left, name, donation);
        } else {
            node->right = insert(node->right, name, donation);
        }

        return node;
    }

    TreeNode* deleteDonor(TreeNode* node, string name) {
        if (node == NULL) {
            return node;
        }

        int comparison = name.compare(node->name);

        if (comparison < 0) {
            node->left = deleteDonor(node->left, name);
        } else if (comparison > 0) {
            node->right = deleteDonor(node->right, name);
        } else {
            if (node->left == NULL) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = minValueNode(node->right);
            node->name = temp->name;
            node->donation = temp->donation;
            node->right = deleteDonor(node->right, temp->name);
        }
        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    void printDonors(TreeNode* node) {
        if (node == NULL) {
            return;
        }

        printDonors(node->left);
        cout << node->name << " has donated Rs. " << node->donation << endl;
        printDonors(node->right);
    }

    void printDonorname(TreeNode* node) {
        if (node == NULL) {
            return;
        }

        printDonorname(node->left);
        cout << "Mr/Mrs. " << node->name << endl;
        printDonorname(node->right);
    }

    void findMaxMinDonors(TreeNode* node, int& maxDonation, int& minDonation, string& maxDonor, string& minDonor) {
        if (node == NULL) {
            return;
        }

        findMaxMinDonors(node->left, maxDonation, minDonation, maxDonor, minDonor);

        if (node->donation > maxDonation) {
            maxDonation = node->donation;
            maxDonor = node->name;
        }

        if (node->donation < minDonation) {
            minDonation = node->donation;
            minDonor = node->name;
        }

        findMaxMinDonors(node->right, maxDonation, minDonation, maxDonor, minDonor);
    }
};

int main() {
    BinaryTree donations;
    string name, confr;
    int donation;

    int w = 1, ch;
    while (w == 1) {
        cout << "-------------------------------DONATION BOX------------------------------" << endl;
        cout << "1. DONATE " << endl;;
        cout << "2. VIEW DONORS " << endl;
        cout << "3. MAX DONATION " << endl;
        cout << "4. MIN DONATION " << endl;
        cout << "5. SEE ALL RECORDS " << endl;
        cout << "6. REMOVE DONOR " << endl;
        cout << "7. EXIT PROGRAM " <<endl;
        cout<<endl;
        cout <<"Enter your choice:";


        cin >> ch;
        switch (ch) {
            case 1:

                cout << "Enter your name: " << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                cout << "Enter amount you want to donate: " << endl;
                cin >> donation;

                cout << "Confirm your donation for Rs. " << donation << " (Y/N)" << endl;
                cin >> confr;

                if (confr == "y" || confr == "Y") {
                    donations.addNode(name, donation);
                    cout << "" << endl;
                    cout << "Thank you for donating." << endl;
                } else {
                    cout << "Donation process cancelled." << endl;
                }
                break;

            case 2:
                cout << "\nDonors:-" << endl;
                donations.printDonorn();
                break;

            case 3:
                donations.findMaxDonors();
                break;

            case 4:
                donations.findMinDonors();
                break;

            case 5:
                cout << "All donations:- \n";
                donations.findMaxMinDonors();
                cout<<"\n";
                donations.printDonors();
                break;

            case 6:
                cout << "Enter the name of the donor you want to delete:" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);

                if (donations.searchDonor(donations.root, name)) {
                    donations.deleteDonor(name);

                    cout << "Money succesfully refunded"<< endl;
                } else {
                    cout << "Mr/Mrs. " << name << " not found in the donor list." << endl;
                }
                break;
            case 7:
                cout<<"Program Exit. "<<endl;
                w=w+1;
                break;
            default:
                cout << "! INVALID CHOICE !" << endl;
                break;
        }
    }

    return 0;
}
